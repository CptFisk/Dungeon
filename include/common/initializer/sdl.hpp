#pragma once
#include <common/initializer/initializer.hpp>

#include <SDL3/SDL.h>

namespace Common{
    class SDLInitializer : public Initializer{
      public:
        SDLInitializer(SDL_Window** window, SDL_Renderer** render, const std::string& title);
        void startup();
        void shutdown();
      private:
      protected:
        SDL_Window** pWindow;
        SDL_Renderer** pRenderer;
        const std::string mTitle;
    };
}