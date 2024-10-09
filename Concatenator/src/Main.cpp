#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<std::string> getTextFiles(const std::string& rootPath) {
    std::vector<std::string> textFiles;

    for (const auto& entry : fs::recursive_directory_iterator(rootPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            textFiles.push_back(entry.path().string());
        }
    }

    return textFiles;
}

int main(int argc, char* argv[]) {

    std::string rootPath = argv[1];

    std::vector<std::string> textFiles = getTextFiles(rootPath);

    if (!textFiles.empty()) {
        std::cout << "Found text files:" << std::endl;
        for (const auto& file : textFiles) {
            std::cout << file << std::endl;
        }
    } else {
        std::cout << "No text files found in the directory." << std::endl;
    }

    return 0;
}
