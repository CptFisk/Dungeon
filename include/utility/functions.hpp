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
}