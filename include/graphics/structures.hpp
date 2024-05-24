#pragma once
#include <SDL.h>
#include <objects/objects.hpp>
#include <stdexcept>
#include <utility>
#include <vector>

namespace Graphics {

#define GENERATED_SHAPES(DO) \
    DO(CIRCLE)               \
    DO(SQUARE)
#define MAKE_GENERATED_SHAPES(VAR) VAR,
enum GeneratedShapes { GENERATED_SHAPES(MAKE_GENERATED_SHAPES) };
NLOHMANN_JSON_SERIALIZE_ENUM(GeneratedShapes, { { CIRCLE, "Circle" }, { SQUARE, "Square" } })

enum TextureTypes { SDL_TEXTURE, TEXT, SIMPLE_TEXTURE, ANIMATED_TEXTURE, GENERATED_TEXTURE };

/**
 * @brief Used for text and strings that have been generated
 */
struct typeTextTexture {
    SDL_Texture* Texture;
    SDL_FRect    Dimensions;
};

/***
 * @brief Used when Object is of type BASE_TEXTURE
 */
struct typeBaseTextureJSON {
    std::string File;   // File to be loaded
    std::string Name;   // Name of file
    int         Column; // Start column in sheet
    int         Row;    // Start row in sheet
    int         Length; // Number of sprites to be read
    int         Height; // Height of texture
    int         Width;  // Width of texture
};

struct typeAnimatedTextureJSON {
    std::string Name;   // Animation name
    int         Column; // Start column in sheet
    int         Row;    // Start row in sheet
    int         Length; // Number of sprites to be read
    int         Ticks;  // Number of seconds for each texture *100ms
    int         Width;  // Width of texture
    int         Height; // Height of texture
    bool        Paused; // Optional, not always existing
};

struct typeGeneratedTextureJSON {
    std::string     Name;
    GeneratedShapes Shape;
    int             Red1;
    int             Red2;
    int             Green1;
    int             Green2;
    int             Blue1;
    int             Blue2;
    int             Alpha;
    int             Height; // Height of texture
    int             Width;  // Width of texture
};

struct typeBaseTextureData {
    std::vector<typeBaseTextureJSON> Objects;
};

struct typeAnimatedTextureData {
    std::string                          File;
    std::vector<typeAnimatedTextureJSON> Objects;
};

struct typeGeneratedTextureData {
    std::vector<typeGeneratedTextureJSON> Objects;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeBaseTextureJSON, File, Name, Column, Row, Length, Height, Width)
// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeAnimatedTextureJSON, Name, Column, Row, Length, Ticks, Height, Width, Paused)
inline void
to_json(nlohmann::json& nlohmann_json_j, const typeAnimatedTextureJSON& nlohmann_json_t) {
    nlohmann_json_j["Name"]   = nlohmann_json_t.Name;
    nlohmann_json_j["Column"] = nlohmann_json_t.Column;
    nlohmann_json_j["Row"]    = nlohmann_json_t.Row;
    nlohmann_json_j["Length"] = nlohmann_json_t.Length;
    nlohmann_json_j["Ticks"]  = nlohmann_json_t.Ticks;
    nlohmann_json_j["Height"] = nlohmann_json_t.Height;
    nlohmann_json_j["Width"]  = nlohmann_json_t.Width;
    nlohmann_json_j["Paused"] = nlohmann_json_t.Paused;
}
inline void
from_json(const nlohmann::json& nlohmann_json_j, typeAnimatedTextureJSON& nlohmann_json_t) {
    nlohmann_json_j.at("Name").get_to(nlohmann_json_t.Name);
    nlohmann_json_j.at("Column").get_to(nlohmann_json_t.Column);
    nlohmann_json_j.at("Row").get_to(nlohmann_json_t.Row);
    nlohmann_json_j.at("Length").get_to(nlohmann_json_t.Length);
    nlohmann_json_j.at("Ticks").get_to(nlohmann_json_t.Ticks);
    nlohmann_json_j.at("Height").get_to(nlohmann_json_t.Height);
    nlohmann_json_j.at("Width").get_to(nlohmann_json_t.Width);
    if (nlohmann_json_j.contains("Paused")) {
        nlohmann_json_t.Paused = nlohmann_json_j.at("Paused").get<bool>();
    } else {
        nlohmann_json_t.Paused = false;
    }
}
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeGeneratedTextureJSON, Name, Shape, Red1, Red2, Green1, Green2, Blue1, Blue2, Alpha, Height, Width)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeBaseTextureData, Objects)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeAnimatedTextureData, File, Objects)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeGeneratedTextureData, Objects)

}