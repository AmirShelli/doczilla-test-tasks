#include "../inc/FileHandler.h"

FileHandler::FileHandler(const std::string &rootPath)
    : rootPath(rootPath)
{
    this->textFiles = this->findFiles();
}

FileHandler::~FileHandler()
{
}

void FileHandler::concatFiles(std::vector<std::string> sortedFiles)
{
    std::ofstream resultFile("result.txt");

    for (const auto &filePath : sortedFiles)
    {
        std::ifstream file(fs::path(this->rootPath) / filePath);
        std::string line;

        while (std::getline(file, line))
        {
            resultFile << line << std::endl;
        }
    }

    resultFile.close();
}

std::vector<std::string> FileHandler::getTextFiles()
{
    return this->textFiles;
}

std::vector<std::string> FileHandler::findFiles()
{
    std::vector<std::string> textFiles;

    for (const auto &entry : fs::recursive_directory_iterator(this->rootPath))
    {
        if (entry.is_regular_file())
        {
            auto relativePath = fs::relative(entry.path(), this->rootPath).string();
            textFiles.push_back(relativePath);
        }
    }

    return textFiles;
}

std::map<std::string, std::vector<std::string>> FileHandler::buildDependencyGraph()
{
    std::map<std::string, std::vector<std::string>> graph;

    for (const auto &filePath : this->textFiles)
    {
        std::vector<std::string> dependencies;
        std::ifstream file(fs::path(this->rootPath) / filePath);
        std::string line;

        while (std::getline(file, line))
        {
            std::size_t requirePos = line.find("require");
            if (requirePos != std::string::npos)
            {
                std::size_t startQuote = line.find('\'', requirePos);
                std::size_t endQuote = line.find('\'', startQuote + 1);

                if (startQuote != std::string::npos && endQuote != std::string::npos)
                {
                    std::string dependencyPath = line.substr(startQuote + 1, endQuote - startQuote - 1);
                    dependencies.push_back(dependencyPath);
                }
            }
        }

        graph[filePath] = dependencies;
    }

    return graph;
}
