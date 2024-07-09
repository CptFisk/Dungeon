#include <editor/editor.hpp>

namespace Editor {
void
Editor::removeSpecificTexture(const std::string& name, std::vector<Tile*>& tiles, const uint8_t& id) {
    SDL_Texture* texture = nullptr;
    switch (mGraphics->getTextureType(name)) {
        case Graphics::TextureTypes::SIMPLE_TEXTURE:
            if (GET_SIMPLE(name) != nullptr)
                texture = GET_SIMPLE(name)->Texture;
            break;
        case Graphics::TextureTypes::ANIMATED_TEXTURE:
            if (GET_ANIMATED(name) != nullptr)
                texture = (*GET_ANIMATED(name))->getTexture();
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