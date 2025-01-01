#pragma once
#include <SDL.h>
#include <cmake.hpp>
#include <common/scale.hpp>
#include <global.hpp>

namespace Common {
class Perspective {
  public:
#ifdef GAME_MODE
    Perspective(SDL_Renderer*& renderer, float& offsetX, float& offsetY, SDL_FPoint& playerCenter, Common::typeScale& scale);
#endif
#ifdef EDITOR_MODE
    Perspective(SDL_Renderer*& renderer, float& offsetX, float& offsetY, Common::typeScale& scale);
#endif

    void render(SDL_Texture* texture, const SDL_Rect* viewport, SDL_FRect* position);
    void renderRotated(SDL_Texture* texture, const SDL_Rect* viewport, SDL_FRect* position, const double& angle);

#ifdef GAME_MODE
    void move(const SDL_FPoint& vector);
    //void move(Orientation direction, const float& velocity); // Move the camera
#endif
#ifdef EDITOR_MODE
    void move(Directions direction, const float& velocity); // Move the camera
#endif
    void center(const SDL_FPoint& point, const float& offset);
    void center(const float& x, const float& y);

    struct {
        float& x;
        float& y;
    } mOffset;

  private:
    void updateScale();
  protected:
    SDL_Renderer*&     pRenderer;
    Common::typeScale& mScale;
#ifdef GAME_MODE
    SDL_FPoint& mPlayerCenter;
#endif
    float halfMaxY;
    float halfMinY;
    float halfX;    //Half the screen in x-axis
};
}