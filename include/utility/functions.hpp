#pragma once
#include <functional>

namespace Utility {

template<typename T, typename... U>
static bool
functions_equal(std::function<T(U...)> a, std::function<T(U...)> b) {
    typedef T (*fptr)(U...);
    fptr** pa = a.template target<fptr*>();
    fptr** pb = b.template target<fptr*>();

    return (*pa) == (*pb);
}

template <typename T, typename Getter>
void sortBy(std::vector<T>& vec, Getter getter) {
    std::sort(vec.begin(), vec.end(), [getter](const T& a, const T& b) {
        return getter(a) < getter(b);
    });
}

}