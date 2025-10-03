#ifndef FILEMAP_H
#define FILEMAP_H

#include <string>
#include <map>

namespace RSDK
{

// This map will store lowercase file paths as keys and their original-case counterparts as values.
extern std::map<std::string, std::string> fileMap;

/**
 * @brief Initializes the file map by scanning the "Data" directory recursively.
 */
void InitFileMap();

/**
 * @brief Retrieves the correct-case file path from the map.
 *
 * @param originalPath The path to look up, typically case-insensitive.
 * @return The original-cased path if found, otherwise the original path.
 */
const char *GetMappedFilePath(const char *originalPath);

} // namespace RSDK

#endif // FILEMAP_H