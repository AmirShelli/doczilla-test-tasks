#include "../inc/DependencyHandler.h"

DependencyHandler::DependencyHandler()
{
}

DependencyHandler::~DependencyHandler()
{
}


bool DependencyHandler::topologicalSortUtil(const std::string &v,
                         const std::map<std::string, std::vector<std::string>> &adj,
                         std::map<std::string, bool> &visited,
                         std::map<std::string, bool> &recStack,
                         std::vector<std::string> &sortedOrder,
                         std::vector<std::string> &cyclePath)
{
    visited[v] = true;
    recStack[v] = true;

    if (adj.find(v) != adj.end())
    {
        for (const auto &neighbor : adj.at(v))
        {
            if (!visited[neighbor])
            {
                if (topologicalSortUtil(neighbor, adj, visited, recStack, sortedOrder, cyclePath))
                {
                    cyclePath.push_back(v);
                    return true;
                }
            }
            else if (recStack[neighbor])
            {
                // Cycle detected
                cyclePath.push_back(neighbor);
                cyclePath.push_back(v);
                return true;
            }
        }
    }

    recStack[v] = false;
    sortedOrder.push_back(v);
    return false;
}

    bool DependencyHandler::sortDependencies(const std::map<std::string, std::vector<std::string>> &adj,
                      std::vector<std::string> &sortedOrder,
                      std::vector<std::string> &cyclePath)
{
    std::map<std::string, bool> visited;
    std::map<std::string, bool> recStack;

    for (const auto &pair : adj)
    {
        visited[pair.first] = false;
        recStack[pair.first] = false;
        for (const auto &neighbor : pair.second)
        {
            if (visited.find(neighbor) == visited.end())
            {
                visited[neighbor] = false;
                recStack[neighbor] = false;
            }
        }
    }

    for (const auto &pair : adj)
    {
        if (!visited[pair.first])
        {
            if (topologicalSortUtil(pair.first, adj, visited, recStack, sortedOrder, cyclePath))
            {
                return false;
            }
        }
    }

    return true;
}