#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.bin>" << std::endl;
        return 1;
    }

    std::ifstream inFile(argv[1]);
    if (!inFile) {
        std::cerr << "Error opening input file: " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream outFile(argv[2], std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening output file: " << argv[2] << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        // Ignore comments
        size_t commentPos = line.find("//");
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }

        std::stringstream ss(line);
        int byte;
        while (ss >> std::hex >> byte) {
            outFile.put(static_cast<char>(byte));
        }
    }

    return 0;
}
