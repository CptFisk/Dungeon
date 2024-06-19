#pragma once
#include <SDL.h>
#include <nlohmann/json.hpp>
#include <object/objects.hpp>
#include <string>

namespace Common {

/**
 * @brief Structure used when transferring data that is passed to render
 */
struct typeDrawData {
    SDL_Texture* Texture;  // Texture
    SDL_Rect*    Viewport; // Viewport
    SDL_FRect*   Position; // Position

    // Constructors
    typeDrawData()
      : Texture(nullptr)
      , Viewport(nullptr)
      , Position(nullptr){};
    explicit typeDrawData(SDL_Texture* texture)
      : Texture(texture)
      , Viewport(nullptr)
      , Position(nullptr){};
    typeDrawData(SDL_Texture* texture, SDL_Rect* view)
      : Texture(texture)
      , Viewport(view)
      , Position(nullptr){};
    typeDrawData(SDL_Texture* texture, SDL_Rect* view, SDL_FRect* position)
      : Texture(texture)
      , Viewport(view)
      , Position(position){};
};

struct typeDrawDataAngled {
    SDL_Texture* Texture;
    SDL_Rect*    Viewport;
    SDL_FRect*   Position;
    const float  Angle;
};

/**
 * @brief Structure that contains all information about SDL_Window.
 * @brief The factor X and Y is a calculated value that shall be multiplied to accomplish
 * @brief a grid size of 16x12 squares.
 */
struct typeScale {
    float factorX;
    float factorY;
    int   windowWidth;  // Window width
    int   windowHeight; // Window Height
    typeScale()
      : factorX(0.0f)
      , factorY(0.0f)
      , windowWidth(0)
      , windowHeight(0) {}
};

#define HEADER_TYPES(DO) \
    DO(BASE_TEXTURE)     \
    DO(ANIMATED_TEXTURE) \
    DO(GENERATED_TEXTURE)
#define MAKE_HEADER_TYPES(VAR) VAR,
enum typeObjectType { HEADER_TYPES(MAKE_HEADER_TYPES) };
NLOHMANN_JSON_SERIALIZE_ENUM(typeObjectType,
                             { { BASE_TEXTURE, "BaseTexture" },
                               { ANIMATED_TEXTURE, "AnimatedTexture" },
                               { GENERATED_TEXTURE, "GeneratedTexture" } })

struct typeHeaderJSON {
    typeObjectType Type;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeHeaderJSON, Type)

}