#pragma once
#include <graphics/types/textureTypes.hpp>
#include <nlohmann/json.hpp>

struct typeHeaderJSON {
    Graphics::TextureTypes Type;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeHeaderJSON, Type)
