#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace fs = std::filesystem;

std::vector<std::string> getTextFiles(const std::string &rootPath)
{
    std::vector<std::string> textFiles;

    for (const auto &entry : fs::recursive_directory_iterator(rootPath))
    {
        if (entry.is_regular_file())
        {
            auto relativePath = fs::relative(entry.path(), rootPath).string();
            textFiles.push_back(relativePath);
        }
    }

    return textFiles;
}

std::map<std::string, std::vector<std::string>> buildDependencyGraph(const std::vector<std::string> &textFiles, const std::string &rootPath)
{
    std::map<std::string, std::vector<std::string>> graph;

    for (const auto &filePath : textFiles)
    {
        std::vector<std::string> dependencies;
        std::ifstream file(fs::path(rootPath) / filePath);
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

void topologicalSortUtil(const std::string &v,
                         const std::map<std::string, std::vector<std::string>> &adj,
                         std::map<std::string, bool> &visited,
                         std::vector<std::string> &rec_stack)
{
    visited[v] = true;

    if (adj.find(v) != adj.end())
    {
        std::vector<std::string> neighbors = adj.at(v);
        // std::sort(neighbors.begin(), neighbors.end()); if needs to be sorted by name

        for (const auto &neighbor : neighbors)
        {
            if (!visited[neighbor])
            {
                topologicalSortUtil(neighbor, adj, visited, rec_stack);
            }
        }
    }

    rec_stack.push_back(v);
}

std::vector<std::string> sortDependencies(const std::map<std::string, std::vector<std::string>> &adj)
{
    std::vector<std::string> deps;
    std::map<std::string, bool> visited;

    for (const auto &pair : adj)
    {
        visited[pair.first] = false;
        for (const auto &neighbor : pair.second)
        {
            if (visited.find(neighbor) == visited.end())
            {
                visited[neighbor] = false;
            }
        }
    }

    for (const auto &pair : adj)
    {
        if (!visited[pair.first])
        {
            topologicalSortUtil(pair.first, adj, visited, deps);
        }
    }

    for (const auto &pair : visited)
    {
        if (!pair.second)
        {
            topologicalSortUtil(pair.first, adj, visited, deps);
        }
    }

    return deps;
}

void manualTest()
{
    std::map<std::string, std::vector<std::string>> graph;

    graph["A"] = {"B", "C"}; // A -> B & C
    graph["B"] = {"D"};      // B -> D
    graph["C"] = {"D"};      // C -> D
    graph["D"] = {};         // D has no deps

    std::vector<std::string> sortedDependencies = sortDependencies(graph);

    std::cout << "Topological Sort Order:\n";
    for (const auto &file : sortedDependencies)
    {
        std::cout << file << " ";
    }
    std::cout << std::endl;
}

void fileTest(char *argv[])
{
    std::string rootPath = argv[1];

    std::vector<std::string> textFiles = getTextFiles(rootPath);

    if (!textFiles.empty())
    {
        auto fileDependencies = buildDependencyGraph(textFiles, rootPath);

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

        auto sortedDependencies = sortDependencies(fileDependencies);

        std::cout << "Sorted dependencies:" << std::endl;
        for (const auto &dependency : sortedDependencies)
        {
            std::cout << " -> " << dependency << std::endl;
        }
    }
    else
    {
        std::cout << "No text files found in the directory." << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        fileTest(argv);
    }
    else
    {
        manualTest();
    }
}
