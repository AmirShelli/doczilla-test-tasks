#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

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

std::unordered_map<std::string, std::vector<std::string>> buildDependencyGraph(const std::vector<std::string> &textFiles)
{
    std::unordered_map<std::string, std::vector<std::string>> graph;

    for (const auto &filePath : textFiles)
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
                         const std::unordered_map<std::string, std::vector<std::string>> &adj,
                         std::unordered_map<std::string, bool> &visited,
                         std::stack<std::string> &Stack)
{

    if (adj.find(v) == adj.end())
    {
        return;
    }

    visited[v] = true;

    for (const auto &neighbor : adj.at(v))
    {
        if (!visited[neighbor])
        {
            topologicalSortUtil(neighbor, adj, visited, Stack);
        }
    }

    Stack.push(v);
}

std::vector<std::string> sortDependencies(const std::unordered_map<std::string, std::vector<std::string>> &adj)
{
    std::stack<std::string> Stack;
    std::unordered_map<std::string, bool> visited;

    // Mark all the vertices as not visited
    for (const auto &pair : adj)
    {
        visited[pair.first] = false;
    }

    for (const auto &pair : adj)
    {
        if (!visited[pair.first])
        {
            topologicalSortUtil(pair.first, adj, visited, Stack);
        }
    }

    std::vector<std::string> sortedOrder;
    while (!Stack.empty())
    {
        sortedOrder.push_back(Stack.top());
        Stack.pop();
    }

    return sortedOrder;
}

void manualTest()
{
    std::unordered_map<std::string, std::vector<std::string>> graph;

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
        auto fileDependencies = buildDependencyGraph(textFiles);

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
