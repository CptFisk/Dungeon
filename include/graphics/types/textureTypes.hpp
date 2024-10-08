#pragma once
#include <nlohmann/json.hpp>

namespace Graphics {

enum class TextureTypes { Undefined, Font, FontTTF, BaseTexture, AnimatedTexture, GeneratedTexture, LightningTexture, UserInterface };

NLOHMANN_JSON_SERIALIZE_ENUM(TextureTypes,
                             { { TextureTypes::Undefined, "Undefined" },
                               { TextureTypes::Font, "Font" },
                               { TextureTypes::FontTTF, "FontTTF" },
                               { TextureTypes::BaseTexture, "BaseTexture" },
                               { TextureTypes::AnimatedTexture, "AnimatedTexture" },
                               { TextureTypes::GeneratedTexture, "GeneratedTexture" },
                               { TextureTypes::LightningTexture, "LightningTexture" },
                               { TextureTypes::UserInterface, "UserInterface" } })
}