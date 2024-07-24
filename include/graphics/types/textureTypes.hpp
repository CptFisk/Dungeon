#pragma once
#include <nlohmann/json.hpp>

namespace Graphics {

enum class TextureTypes { Undefined, Text, BaseTexture, AnimatedTexture, GeneratedTexture, LightningTexture };

NLOHMANN_JSON_SERIALIZE_ENUM(TextureTypes,
                             { { Graphics::TextureTypes::Undefined, "Undefined" },
                               { Graphics::TextureTypes::BaseTexture, "BaseTexture" },
                               { Graphics::TextureTypes::AnimatedTexture, "AnimatedTexture" },
                               { Graphics::TextureTypes::GeneratedTexture, "GeneratedTexture" },
                               { Graphics::TextureTypes::LightningTexture, "LightningTexture" } })

}