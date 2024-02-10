#pragma once
#include <nlohmann/json.hpp>
#include <objects/objects.hpp>
#include <string>

namespace Engine {
struct Scale {
    float ScaleX;
    float ScaleY;
};


#define HEADER_TYPES(DO) \
    DO(BASE_TEXTURE)     \
    DO(ANIMATED_TEXTURE) \
    DO(GENERATED_TEXTURE)
#define MAKE_HEADER_TYPES(VAR) VAR,
enum HeaderTypes { HEADER_TYPES(MAKE_HEADER_TYPES) };
NLOHMANN_JSON_SERIALIZE_ENUM(HeaderTypes,
                             { { BASE_TEXTURE, "BaseTexture" },
                               { ANIMATED_TEXTURE, "AnimatedTexture" },
                               { GENERATED_TEXTURE, "GeneratedTexture" } })

struct HeaderJSON {
    HeaderTypes Type;
    std::string Name;
    int         Width;
    int         Height;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(HeaderJSON, Type, Name, Width, Height)

}