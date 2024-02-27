#pragma once
#include <vector>
#include <algorithm>

namespace Utility{
    std::vector<int> splitNumbers(int n){
        std::vector<int> numbers;
        while(n > 0){
            numbers.push_back(n % 10);
            n /= 10;
        }
        std::reverse(numbers.begin(), numbers.end());
        return numbers;
    }
}