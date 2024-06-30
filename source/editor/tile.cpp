#include <editor/tile.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/graphics.hpp>
#include <global.hpp>
namespace Editor {

Tile::Tile(const int& x, const int& y, const Common::typeScale& scale)
  : xPos(static_cast<float>(x) * 16.0f * scale.factorX)
  , yPos(static_cast<float>(y) * 16.0f * scale.factorY)
  , scale(scale) {}

Tile&
Tile::operator=(const Editor::Tile& other) {
    if (this == &other)
        return *this;
    data = other.data;
    return *this;
}

void
Tile::clear() {
    data.clear();
}

void
Tile::addData(const std::string& asset, const std::shared_ptr<Graphics::Graphics>& graphics) {
    const auto type = graphics->getTextureType(asset);
    switch (type) {
        case Graphics::TextureTypes::SIMPLE_TEXTURE:
            if (graphics->getTexture<Graphics::typeSimpleTexture>(asset) == nullptr)
                return;
            // The asset exist and we can use it
            data.emplace_back(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->getTexture(),
                              &graphics->getTexture<Graphics::typeSimpleTexture>(asset)->getRandomView(),
                              SDL_FRect{
                                xPos,
                                yPos,
                                FLOAT(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->Width) * scale.factorX,
                                FLOAT(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->Height) * scale.factorY,
                              });
            break;
        case Graphics::TextureTypes::ANIMATED_TEXTURE:
            if (graphics->getTexture<Graphics::AnimatedTexture*>(asset) == nullptr)
                return;
            // The asset exist and we can use it
            data.emplace_back((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->getTexture(),
                              (*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->getViewport(),
                              SDL_FRect{
                                xPos,
                                yPos,
                                FLOAT((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->Width) * scale.factorX,
                                FLOAT((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->Height) * scale.factorY,
                              });
            break;
        default:;
    }
}

std::vector<Common::typeDrawData>
Tile::getDrawData() {
    std::vector<Common::typeDrawData> ret;
    for (auto& tile : data)
        ret.emplace_back(tile.Texture, tile.Viewport, &tile.Position);
    return ret;
}

std::vector<tileData>&
Tile::getTileData() {
    return data;
}

}