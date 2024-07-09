#pragma once
#include <vector>

namespace Utility{
template <typename T>
bool removeElementInVector(std::vector<T> vector, T element){
    bool removed = false;
    for(auto it = vector.begin(); it != vector.end();){
        if((it) == element){
            it = vector.erase(it);
        }else{
            ++it;
        }
    }
}

}