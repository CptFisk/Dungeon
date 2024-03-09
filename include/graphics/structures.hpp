#pragma once
#include <SDL3/SDL.h>
#include <objects/objects.hpp>
#include <stdexcept>
#include <utility>
#include <vector>

namespace Graphics {

const int TEXT_MAX_LENGTH = 31;

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

struct typeSimpleTexture {
    SDL_Texture*           Texture;
    std::vector<SDL_FRect> Views;

    std::pair<SDL_Texture*, SDL_FRect> operator[](size_t n) const {
        if (n == -1)
            return { Texture, Views[rand() % Views.size()] };
        if (n < Views.size()) {
            return { Texture, Views[n] };
        } else {
            throw std::runtime_error("Index out of bounds");
        }
    }
};
/***
 * @brief Used when Object is of type BASE_TEXTURE
 */
struct typeBaseTextureJSON {
    std::string File;     // File to be loaded
    std::string Name;     // Name of file
    int         Column;   // Start column in sheet
    int         Row;      // Start row in sheet
    int         Length;   // Number of sprites to be read
    int         Height;   // Height of texture
    int         Width;    // Width of texture
};

struct typeAnimatedTextureJSON {
    std::string Name;     // Animation name
    int         Column;   // Start column in sheet
    int         Row;      // Start row in sheet
    int         Length;   // Number of sprites to be read
    int         Ticks;    // Number of seconds for each texture *100ms
    int         Width;    // Width of texture
    int         Height;   // Height of texture
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
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeAnimatedTextureJSON, Name, Column, Row, Length, Ticks, Height, Width)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeGeneratedTextureJSON, Name, Shape, Red1, Red2, Green1, Green2, Blue1, Blue2, Alpha, Height, Width)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeBaseTextureData, Objects)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeAnimatedTextureData, File, Objects)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeGeneratedTextureData, Objects)

}