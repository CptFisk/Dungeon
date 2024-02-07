#pragma once
#include <engine/initializer.hpp>
#include <SDL3/SDL.h>

namespace Engine{
    class SDLInitializer : public Initializer{
      public:
        SDLInitializer(SDL_Window** window, SDL_Renderer** render);
        void startup();
        void shutdown();
      private:
      protected:
        SDL_Window** pWindow;
        SDL_Renderer** pRenderer;
    };
}