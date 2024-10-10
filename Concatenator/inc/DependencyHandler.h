#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>



// TODO create a struct for the arguments
// TODO create an interface for Sorting and Topology Sort implementation 

class DependencyHandler
{
private:
    bool topologicalSortUtil(const std::string &v,
                             const std::map<std::string, std::vector<std::string>> &adj,
                             std::map<std::string, bool> &visited,
                             std::map<std::string, bool> &recStack,
                             std::vector<std::string> &sortedOrder,
                             std::vector<std::string> &cyclePath);
public:
    DependencyHandler();
    ~DependencyHandler();

    bool sortDependencies(const std::map<std::string, std::vector<std::string>> &adj,
                          std::vector<std::string> &sortedOrder,
                          std::vector<std::string> &cyclePath);

};
