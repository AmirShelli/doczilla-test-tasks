#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <regex>

namespace fs = std::filesystem;

std::vector<std::string> getTextFiles(const std::string &rootPath)
{
    std::vector<std::string> textFiles;

    for (const auto &entry : fs::recursive_directory_iterator(rootPath))
    {
        if (entry.is_regular_file())
        {
            textFiles.push_back(entry.path().string());
        }
    }

    return textFiles;
}

std::vector<std::string> extractDependencies(const std::string filePath)
{
    std::vector<std::string> dependencies;
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line))
    {
        std::size_t requirePos = line.find("require");
        if (requirePos != std::string::npos)
        {
            std::size_t startQuote = line.find('\'', requirePos);
            std::size_t endQuote = line.find('\'', startQuote + 1);

            std::string dependencyPath = line.substr(startQuote + 1, endQuote - startQuote - 1);
            dependencies.push_back(dependencyPath);
        }
    }

    return dependencies;
}

std::vector<std::pair<std::string, std::vector<std::string>>> parseTextFiles(const std::vector<std::string> &textFiles)
{
    std::vector<std::pair<std::string, std::vector<std::string>>> fileDependencies;

    for (const auto &filePath : textFiles)
    {
        std::vector<std::string> dependencies = extractDependencies(filePath);
        fileDependencies.push_back({filePath, dependencies});
    }

    return fileDependencies;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Please provide the root path as an argument." << std::endl;
        return 1;
    }

    std::string rootPath = argv[1];

    std::vector<std::string> textFiles = getTextFiles(rootPath);

    if (!textFiles.empty())
    {
        std::cout << "Found text files:" << std::endl;
        for (const auto &file : textFiles)
        {
            std::cout << file << std::endl;
        }

        auto fileDependencies = parseTextFiles(textFiles);

        std::cout << "\nFile dependencies:" << std::endl;
        for (const auto &[file, dependencies] : fileDependencies)
        {
            std::cout << "File: " << file << " depends on: ";
            if (dependencies.empty())
            {
                std::cout << "No dependencies";
            }
            else
            {
                for (const auto &dep : dependencies)
                {
                    std::cout << dep << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "No text files found in the directory." << std::endl;
    }

    return 0;
}
