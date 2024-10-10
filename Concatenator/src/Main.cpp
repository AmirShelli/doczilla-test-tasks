#include <iostream>
#include "../inc/DependencyHandler.h"
#include "../inc/FileHandler.h"

void manualTest(DependencyHandler &dependencyHandler)
{
    std::map<std::string, std::vector<std::string>> graph;
    std::vector<std::string> sortedGraph;
    std::vector<std::string> cyclePath;

    graph["A"] = {"B", "C"}; // A -> B & C
    graph["B"] = {"D"};      // B -> D
    graph["C"] = {"D"};      // C -> D
    graph["D"] = {};         // D has no deps

    if (dependencyHandler.sortDependencies(graph, sortedGraph, cyclePath))
    {
        std::cout << "Topological Sort Order:\n";
        for (const auto &file : sortedGraph)
        {
            std::cout << file << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Cannot perform concatenation due to cyclic dependencies." << std::endl;
        std::cout << "Cycle detected: ";
        for (auto it = cyclePath.rbegin(); it != cyclePath.rend(); ++it)
        {
            std::cout << *it << " -> ";
        }
        std::cout << cyclePath.back() << std::endl;
    }
}

void fileTest(FileHandler &fileHandler, DependencyHandler &dependencyHandler)
{

std::vector<std::string> textFiles = fileHandler.getTextFiles();

    if (!fileHandler.getTextFiles().empty())
    {
        auto fileDependencies = fileHandler.buildDependencyGraph();

        std::vector<std::string> sortedDependencies;
        std::vector<std::string> cyclePath;

        if (dependencyHandler.sortDependencies(fileDependencies, sortedDependencies, cyclePath))
        {
            std::cout << "Sorted dependencies:" << std::endl;
            for (const auto &dependency : sortedDependencies)
            {
                std::cout << " -> " << dependency << std::endl;
            }

            // TODO concat
        }
        else
        {
            std::cout << "Cannot perform concatenation due to cyclic dependencies." << std::endl;
            std::cout << "Cycle detected: ";
            for (auto it = cyclePath.rbegin(); it != cyclePath.rend(); ++it)
            {
                std::cout << *it << " -> ";
            }
            std::cout << cyclePath.back() << std::endl;
        }
    }
    else
    {
        std::cout << "No text files found in the directory." << std::endl;
    }
}

int main(int argc, char *argv[])
{

    DependencyHandler dependencyHandler;

    if (argc == 2)
    {
        FileHandler fileHandler(argv[1]);
        fileTest(fileHandler, dependencyHandler);
    }
    else
    {
        manualTest(dependencyHandler);
    }
}
