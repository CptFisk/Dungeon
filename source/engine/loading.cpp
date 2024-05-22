#include <engine/loading.hpp>
#include <common/sdl.hpp>
namespace Engine {

LoadingScreen::LoadingScreen(SDL_Renderer*& renderer, std::mutex& mutex)
  : pRender(renderer),
    mMutex(mutex){
    pLogo = Common::loadImage(pRender, "rsrc/icons/logo.png");
}

void
LoadingScreen::run(){
    mMutex.lock();
    Uint32 time = SDL_GetTicks() + 3000;
    while(SDL_GetTicks() < time){
        SDL_FRect pos = {0.0f,0.0f, 183.0f, 93.0f};
        SDL_RenderTexture(pRender, pLogo, nullptr,&pos );
        SDL_RenderPresent(pRender);
    }
    mMutex.unlock();
}

}