#pragma once
#include <vector>
#include <algorithm>

namespace Utility{
template <typename T, typename Condition>
bool removeElementInVector(std::vector<T> vector, Condition con){
    const auto size = vector.size();
    vector.erase(std::remove_if(vector.begin(), vector.end(), con), vector.end());
    return size != vector.size();
}

}