#include "RSDK/Core/RetroEngine.hpp"
#include "FileMap.hpp"

#include <algorithm>
#include <string>
#include <vector>

#if RETRO_PLATFORM == RETRO_WIN
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

namespace RSDK
{

std::map<std::string, std::string> fileMap;

// Helper function to convert a string to lowercase.
static std::string ToLower(const std::string &str)
{
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lower_str;
}

// Helper function to normalize path separators from '\' to '/'.
static std::string NormalizePath(const std::string &path)
{
    std::string normalized = path;
    for (char &c : normalized) {
        if (c == '\\') {
            c = '/';
        }
    }
    return normalized;
}

// Scans a directory recursively and populates the file map.
static void ScanDirectory(const std::string &scanPath, const std::string &relativePathPrefix)
{
#if RETRO_PLATFORM == RETRO_WIN
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA((scanPath + "/*").c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        const std::string name = findData.cFileName;
        if (name == "." || name == "..") {
            continue;
        }

        std::string newScanPath = scanPath + "/" + name;
        std::string newRelativePath = relativePathPrefix.empty() ? name : relativePathPrefix + "/" + name;

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            ScanDirectory(newScanPath, newRelativePath);
        } else {
            std::string lowerKey = ToLower(NormalizePath(newRelativePath));
            fileMap[lowerKey] = NormalizePath(newScanPath);
        }
    } while (FindNextFileA(hFind, &findData) != 0);

    FindClose(hFind);

#else // POSIX implementation
    DIR *dir = opendir(scanPath.c_str());
    if (!dir) {
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        const std::string name = entry->d_name;
        if (name == "." || name == "..") {
            continue;
        }

        std::string newScanPath = scanPath + "/" + name;
        std::string newRelativePath = relativePathPrefix.empty() ? name : relativePathPrefix + "/" + name;

        struct stat st;
        if (stat(newScanPath.c_str(), &st) == -1) {
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            ScanDirectory(newScanPath, newRelativePath);
        } else {
            std::string lowerKey = ToLower(NormalizePath(newRelativePath));
            fileMap[lowerKey] = NormalizePath(newScanPath);
        }
    }
    closedir(dir);
#endif
}

void InitFileMap()
{
    fileMap.clear();
    // Start scanning from the "Data" directory. The file paths passed to LoadFile
    // are relative to the CWD, so we start there.
    std::string dataPath = std::string(SKU::userFileDir) + "Data";
    ScanDirectory(dataPath, "Data");
}

const char *GetMappedFilePath(const char *originalPath)
{
    std::string lowerPath = ToLower(NormalizePath(originalPath));

    auto it = fileMap.find(lowerPath);
    if (it != fileMap.end()) {
        // The value is the full path needed by fOpen, with the correct case.
        return it->second.c_str();
    }

    // If not in the map, return the original path to let the existing logic handle it.
    // This could be a mod file or a file outside the "Data" folder.
    return originalPath;
}

} // namespace RSDK