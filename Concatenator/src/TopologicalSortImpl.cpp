#include "../inc/TopologicalSortImpl.h"

TopologicalSortImpl::TopologicalSortImpl()
{
}

TopologicalSortImpl::~TopologicalSortImpl()
{
}


bool TopologicalSortImpl::TopologicalSortUtil(const std::string &v,
                         std::map<std::string, bool> &visited,
                         std::map<std::string, bool> &recStack, sortArgs &args)
{
    visited[v] = true;
    recStack[v] = true;

    const std::map<std::string, std::vector<std::string>> &adj = args.adj;
    std::vector<std::string> &sortedOrder = args.sortedOrder;
    std::vector<std::string> &cyclePath = args.cyclePath;

    if (adj.find(v) != adj.end())
    {
        for (const auto &neighbor : adj.at(v))
        {
            if (!visited[neighbor])
            {
                if (TopologicalSortUtil(neighbor, visited, recStack, args))
                {
                    cyclePath.push_back(v);
                    return true;
                }
            }
            else if (recStack[neighbor])
            {
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

    bool TopologicalSortImpl::sortDependencies(sortArgs &args)
{
    std::map<std::string, bool> visited;
    std::map<std::string, bool> recStack;

    const std::map<std::string, std::vector<std::string>> &adj = args.adj;

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
            if (TopologicalSortUtil(pair.first, visited, recStack, args))
            {
                return false;
            }
        }
    }

    return true;
}