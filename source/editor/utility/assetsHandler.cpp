#include <editor/editor.hpp>

namespace Editor {
void
Editor::removeSpecificTexture(const std::string& name, std::vector<Tile*>& tiles, const uint8_t& id) {
    auto texture = GET_SIMPLE(name);
    if (texture == nullptr)
        return;
    for (auto& tile : tiles) {
        if (tile->elementExist(texture->Texture))
            tile->removeElement(texture->Texture, id);
    }
}
}