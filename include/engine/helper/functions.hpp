#pragma once
#include <array>
#include <engine/helper/include.hpp>
#include <string_view>
#include <unordered_map>
#include <utility>

using functionPointer = void (*)();

using functionPair = std::pair<std::string_view, functionPointer>;

constexpr std::array<functionPair, 50> externalFunctions{ { { "removeDarkness", &removeDarkness },
                                                            { "setDarkness5", &setDarkness5 },
                                                            { "setDarkness10", &setDarkness10 },
                                                            { "setDarkness20", &setDarkness20 },
                                                            { "setDarkness30", &setDarkness30 },
                                                            { "setDarkness40", &setDarkness40 },
                                                            { "setDarkness50", &setDarkness50 },
                                                            { "setDarkness60", &setDarkness60 },
                                                            { "setDarkness70", &setDarkness70 },
                                                            { "setDarkness80", &setDarkness80 },
                                                            { "setDarkness90", &setDarkness90 } } };

constexpr functionPointer
getExternalFunction(std::string_view name) {
    for (const auto& [key, function] : externalFunctions) {
        if(key == name)
            return function;
    }
    return nullptr;
}