#include <editor/editor.hpp>

namespace Editor {
void
Editor::removeSpecificTexture(const std::string& name, std::vector<Tile*>& tiles, const uint8_t& id) {
    SDL_Texture* texture = nullptr;
    switch (mGraphics->getTextureType(name)) {
        case Graphics::TextureTypes::BaseTexture:
            texture = GET_BASE(name)->getTexture();
            break;
        case Graphics::TextureTypes::AnimatedTexture:
            texture = GET_ANIMATED(name)->getTexture();
            break;
        default:
            break;
    }
    if (texture == nullptr)
        return;
    for (auto& tile : tiles) {
        if (tile->elementExist(texture, id))
            tile->removeElement(texture, id);
    }
}
}