#include <engine/engine.hpp>
/**
 * Contains all functions that is related to darkness and handling of the darkness
 */

namespace Engine {

void
Engine::setDarkness(const unsigned int& v) {
    if (v == 0) {
        pDarkness = nullptr; // Destroy link to texture if darkness should be removed
        return;
    }
    const std::string name    = "Shadow" + std::to_string(v);
    auto              texture = GET_GENERATED(name);
    pDarkness                 = texture->getTexture();
}

void
Engine::drawDarkness() {
    if (pDarkness == nullptr)
        return;
    SDL_RenderCopy(pRenderer, pDarkness, nullptr, nullptr);
}

}