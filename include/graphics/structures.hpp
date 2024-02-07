#pragma once
#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>
#include <objects/objects.hpp>
#include <stdexcept>
#include <utility>
#include <vector>

namespace Graphics {
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
    std::string           Name;   // Animation name
    int                   Column; // Start column in sheet
    int                   Row;    // Start row in sheet
    int                   Length; // Number of sprites to be read
};

struct AnimationDataJSON {
    std::string                    File;
    std::vector<AnimationObjectJSON> Animations;
};



NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BaseTextureJSON, File, Rows, Columns)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimationObjectJSON,
                                   Name,
                                   Column,
                                   Row,
                                   Length)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimationDataJSON, File, Animations)

}