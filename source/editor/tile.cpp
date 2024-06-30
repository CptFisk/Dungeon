#include <algorithm>
#include <editor/tile.hpp>
#include <global.hpp>
#include <graphics/animatedTexture.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
namespace Editor {

Tile::Tile(const int& x, const int& y, const Common::typeScale& scale, Graphics::typeSimpleTexture& number, SDL_Renderer* renderer)
  : pRenderer(renderer)
  , xPos(static_cast<float>(x) * 16.0f * scale.factorX)
  , yPos(static_cast<float>(y) * 16.0f * scale.factorY)
  , scale(scale)
  , numbers(number)
  , standardPosition(xPos, yPos, 16.0f * scale.factorX, 16.0f * scale.factorY)
  , mOverlay{} {

    // Setup overlay
    mOverlay.Texture = SDL_CreateTexture(
      renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, INT(16.0f * scale.factorX), INT(16.0f * scale.factorY));
    if(mOverlay.Texture == nullptr)
        std::cout << "Error in creating texture" << std::endl;
    mOverlay.Position = &standardPosition;
    mOverlay.Viewport = nullptr;
    SDL_SetTextureBlendMode(mOverlay.Texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(mOverlay.Texture, 127);
}

Tile::~Tile() {
    clear();
    SDL_DestroyTexture(mOverlay.Texture); // Cleanup
}

Tile&
Tile::operator=(const Editor::Tile& other) {
    if (this == &other)
        return *this;
    data = other.data;

    return *this;
}

void
Tile::clear() {
    for (auto& element : data) {
        delete element.Position;
    }
    data.clear();
}

bool
Tile::addData(const std::string& asset, const std::shared_ptr<Graphics::Graphics>& graphics) {
    const auto size = data.size();
    const auto type = graphics->getTextureType(asset);
    switch (type) {
        case Graphics::TextureTypes::SIMPLE_TEXTURE:
            if (graphics->getTexture<Graphics::typeSimpleTexture>(asset) == nullptr)
                return false;
            // The asset exist and we can use it
            data.emplace_back(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->getTexture(),
                              &graphics->getTexture<Graphics::typeSimpleTexture>(asset)->getRandomView(),
                              new SDL_FRect{
                                xPos,
                                yPos,
                                FLOAT(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->Width) * scale.factorX,
                                FLOAT(graphics->getTexture<Graphics::typeSimpleTexture>(asset)->Height) * scale.factorY,
                              });
            break;
        case Graphics::TextureTypes::ANIMATED_TEXTURE:
            if (graphics->getTexture<Graphics::AnimatedTexture*>(asset) == nullptr)
                return false;
            // The asset exist and we can use it
            data.emplace_back((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->getTexture(),
                              (*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->getViewport(),
                              new SDL_FRect{
                                xPos,
                                yPos,
                                FLOAT((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->Width) * scale.factorX,
                                FLOAT((*graphics->getTexture<Graphics::AnimatedTexture*>(asset))->Height) * scale.factorY,
                              });
            break;
        default:;
    }
    return data.size() > size ? true : false;
}

void
Tile::addOverlay(SDL_Texture* overlay) {
    if (overlays.empty()) {
        SDL_SetRenderTarget(pRenderer, mOverlay.Texture);
        SDL_RenderCopyF(pRenderer, overlay, nullptr, nullptr);
        SDL_SetRenderTarget(pRenderer, nullptr);
    }
    overlays.insert(overlay);
}

std::vector<Common::typeDrawData>
Tile::getDrawData() {
    return data;
}

Common::typeDrawData
Tile::getNumbers() {
    return { numbers.getTexture(), &numbers.getView(data.size()), &standardPosition };
}

Common::typeDrawData
Tile::getOverlay() {
    return mOverlay;
}

bool
Tile::elementExist(SDL_Texture* texture) const {
    auto it = std::find_if(data.begin(), data.end(), [&texture](const Common::typeDrawData& d) { return d.Texture == texture; });
    return it != data.end() ? true : false;
}

size_t
Tile::removeElement(SDL_Texture* texture) {
    const auto size = data.size();
    for(auto it = data.begin(); it != data.end(); ){
        if((*it).Texture == texture){
            it= data.erase(it);
        }else{
            ++it;
        }
    }
    return size - data.size();
}

}