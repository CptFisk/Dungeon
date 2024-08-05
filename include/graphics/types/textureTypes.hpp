#pragma once
#include <nlohmann/json.hpp>

namespace Graphics {

enum class TextureTypes { Undefined, Text, Number, BaseTexture, AnimatedTexture, GeneratedTexture, LightningTexture, T };

NLOHMANN_JSON_SERIALIZE_ENUM(TextureTypes,
                             { { TextureTypes::Undefined, "Undefined" },
                               { TextureTypes::Text, "Text" },
                               { TextureTypes::Number, "Number" },
                               { TextureTypes::BaseTexture, "BaseTexture" },
                               { TextureTypes::AnimatedTexture, "AnimatedTexture" },
                               { TextureTypes::GeneratedTexture, "GeneratedTexture" },
                               { TextureTypes::LightningTexture, "LightningTexture" } })
}