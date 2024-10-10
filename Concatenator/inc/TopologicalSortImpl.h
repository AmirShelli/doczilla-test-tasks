#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// TODO create a struct for the arguments

struct sortArgs
{
    const std::map<std::string, std::vector<std::string>> &adj;
    std::vector<std::string> &sortedOrder;
    std::vector<std::string> &cyclePath;
};

class ISort
{
public:
    virtual bool sortDependencies(sortArgs &args) = 0;
};

class TopologicalSortImpl : public ISort
{
private:
    bool TopologicalSortUtil(const std::string &v,
                             std::map<std::string, bool> &visited,
                             std::map<std::string, bool> &recStack,
                             sortArgs &args);

public:
    TopologicalSortImpl();
    ~TopologicalSortImpl();

    bool sortDependencies(sortArgs &args);
};
