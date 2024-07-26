#pragma once
#include <nlohmann/json.hpp>

namespace Graphics {

enum class TextureTypes { Undefined, Text, BaseTexture, AnimatedTexture, GeneratedTexture, LightningTexture };

NLOHMANN_JSON_SERIALIZE_ENUM(TextureTypes,
                             { { TextureTypes::Undefined, "Undefined" },
                               { TextureTypes::BaseTexture, "BaseTexture" },
                               { TextureTypes::AnimatedTexture, "AnimatedTexture" },
                               { TextureTypes::GeneratedTexture, "GeneratedTexture" },
                               { TextureTypes::LightningTexture, "LightningTexture" } })

}