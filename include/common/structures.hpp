#pragma once
#include <nlohmann/json.hpp>
#include <objects/objects.hpp>
#include <string>

namespace Common {
struct Scale {
    float ScaleX;  // Scaling factor needed to archive 16x12 squares
    float ScaleY;  // Scaling factor needed to archive 16x12 squares
    int   WindowX; // Window size in X-direction
    int   WindowY; // Window size in Y-direction
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
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(HeaderJSON, Type)

}