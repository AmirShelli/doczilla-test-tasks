#pragma once
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>

namespace fs = std::filesystem;

class FileHandler
{
private:
    const std::string rootPath;
    std::vector<std::string> textFiles;
    std::vector<std::string> findFiles();

public:
    FileHandler(const std::string &rootPath);
    ~FileHandler();

    std::vector<std::string> getTextFiles();
    std::map<std::string, std::vector<std::string>> buildDependencyGraph();
};
