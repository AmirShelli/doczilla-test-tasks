#include <iostream>
#include "../inc/TopologicalSortImpl.h"
#include "../inc/FileHandler.h"

void mock(ISort &sortingAlgorithm)
{
    std::map<std::string, std::vector<std::string>> graph;
    std::vector<std::string> sortedGraph;
    std::vector<std::string> cyclePath;

    sortArgs args = {graph, sortedGraph, cyclePath};

    graph["A"] = {"B", "C"}; // A -> B & C
    graph["B"] = {"D"};      // B -> D
    graph["C"] = {"D"};      // C -> D
    graph["D"] = {};         // D has no deps

    if (sortingAlgorithm.sortDependencies(args))
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

void run(FileHandler &fileHandler, ISort &sortingAlgorithm)
{

std::vector<std::string> textFiles = fileHandler.getTextFiles();

    if (!fileHandler.getTextFiles().empty())
    {
        auto fileDependencies = fileHandler.buildDependencyGraph();

        std::vector<std::string> sortedFiles;
        std::vector<std::string> cyclePath;

        sortArgs args = {fileDependencies, sortedFiles, cyclePath};

        if (sortingAlgorithm.sortDependencies(args))
        {
            std::cout << "Sorted files:" << std::endl;
            for (const auto &filePath : sortedFiles)
            {
                std::cout << " -> " << filePath << std::endl;
            }
            fileHandler.concatFiles(sortedFiles);
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
    
    TopologicalSortImpl topologicalSort;

    if (argc == 2)
    {
        FileHandler fileHandler(argv[1]);
        run(fileHandler, topologicalSort);
    }
    else
    {
        mock(topologicalSort);
    }
}
