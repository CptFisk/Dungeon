#pragma once
#include <SDL3/SDL.h>
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

struct BaseObjectJSON {
    std::string File;   // File to be loaded
    std::string Name;   // Name of file
    int         Column; // Start column in sheet
    int         Row;    // Start row in sheet
    int         Length; // Number of sprites to be read
    int         Height; // Height of texture
    int         Width;  // Width of texture
};

struct AnimationObjectJSON {
    std::string Name;   // Animation name
    int         Column; // Start column in sheet
    int         Row;    // Start row in sheet
    int         Length; // Number of sprites to be read
    int         Ticks;  // Number of seconds for each texture *100ms
    int         Width;  // Width of texture
    int         Height; // Height of texture
};

struct GeneratedObjectJSON {
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

struct BaseTextureDataJSON {
    std::vector<BaseObjectJSON> Objects;
};

struct AnimationDataJSON {
    std::string                      File;
    std::vector<AnimationObjectJSON> Objects;
};

struct GeneratedDataJSON{
    std::vector<GeneratedObjectJSON> Objects;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BaseObjectJSON, File, Name, Column, Row, Length, Height, Width)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimationObjectJSON, Name, Column, Row, Length, Ticks, Height, Width)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GeneratedObjectJSON,
                                   Name,
                                   Shape,
                                   Red1,
                                   Red2,
                                   Green1,
                                   Green2,
                                   Blue1,
                                   Blue2,
                                   Alpha,
                                   Height,
                                   Width)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BaseTextureDataJSON, Objects)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimationDataJSON, File, Objects)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GeneratedDataJSON, Objects)



}