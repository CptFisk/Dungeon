#include <common/initializer/sdlTTF.hpp>
#include <error.hpp>
namespace Common {

SDLTTFInitializer::SDLTTFInitializer() {
}

SDLTTFInitializer::~SDLTTFInitializer() {
}

void
SDLTTFInitializer::startup() {
    ASSERT_WITH_MESSAGE(TTF_Init() < 0, SDL_GetError());
}

void
SDLTTFInitializer::shutdown() {
    TTF_Quit();
}

}