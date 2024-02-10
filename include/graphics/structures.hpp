#pragma once
#include <SDL3/SDL.h>
#include <objects/objects.hpp>
#include <stdexcept>
#include <utility>
#include <vector>

namespace Graphics {

#define GENERATED_SHAPES(DO) \
    DO(CIRCLE)                  \
    DO(SQUARE)
#define MAKE_GENERATED_SHAPES(VAR) VAR,
enum GeneratedShapes {GENERATED_SHAPES(MAKE_GENERATED_SHAPES)};
NLOHMANN_JSON_SERIALIZE_ENUM(GeneratedShapes, {{CIRCLE, "Circle"}, {SQUARE, "Square"}})


struct BaseTexture {
    SDL_Texture*           Texture;
    std::vector<SDL_FRect> Views;

    std::pair<SDL_Texture*, SDL_FRect> operator[](size_t n) const {
        if (n < Views.size()) {
            return { Texture, Views[n] };
        } else {
            throw std::runtime_error("Index out of bounds");
        }
    }
};

struct BaseTextureJSON {
    std::string File;
    int         Rows;
    int         Columns;
};

struct AnimationObjectJSON {
    std::string Name;   // Animation name
    int         Column; // Start column in sheet
    int         Row;    // Start row in sheet
    int         Length; // Number of sprites to be read
    int         Ticks;  //Number of seconds for each texture *100ms
};

struct GeneratedObjectJSON{
    std::string Name;
    GeneratedShapes Shape;
    int Red1;
    int Red2;
    int Green1;
    int Green2;
    int Blue1;
    int Blue2;
    int Alpha;
};

struct AnimationDataJSON {
    std::string                      File;
    std::vector<AnimationObjectJSON> Animations;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BaseTextureJSON, File, Rows, Columns)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimationObjectJSON, Name, Column, Row, Length, Ticks)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimationDataJSON, File, Animations)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GeneratedObjectJSON, Name, Shape, Red1, Red2, Green1, Green2, Blue1, Blue2, Alpha)

}