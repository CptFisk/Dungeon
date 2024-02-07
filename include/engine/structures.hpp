#pragma once
#include <string>

#include <nlohmann/json.hpp>

#include <objects/objects.hpp>


namespace Engine{

struct HeaderJSON{
    std::string Type;
    std::string Name;
    int Width;
    int Height;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(HeaderJSON, Type, Name, Width, Height)

}