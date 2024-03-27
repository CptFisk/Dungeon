#pragma once
#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>
#include <objects/objects.hpp>
#include <string>

namespace Common {

/**
 * @brief Structure used when transferring data that is passed to render
 */
struct typeDrawData {
    SDL_Texture* Texture;  // Texture
    SDL_FRect*   Viewport; // Viewport
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
    typeDrawData(SDL_Texture* texture, SDL_FRect* view)
      : Texture(texture)
      , Viewport(view)
      , Position(nullptr){};
    typeDrawData(SDL_Texture* texture, SDL_FRect* view, SDL_FRect* position)
      : Texture(texture)
      , Viewport(view)
      , Position(position){};
};

struct typeDrawDataAngled {
    SDL_Texture* Texture;
    SDL_FRect*   Viewport;
    SDL_FRect*   Position;
    const float  Angle;
};

struct typeScale {
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