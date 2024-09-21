#include <algorithm>
#include <editor/tile.hpp>
#include <global.hpp>
#include <graphics/graphics.hpp>
#include <graphics/types/animatedTexture.hpp>
#include <graphics/types/baseTexture.hpp>
#include <iostream>
#include <monster/definition.hpp>
#include <utility/bits.hpp>
#include <utility/vector.hpp>

namespace Editor {

Tile::Tile(const int& x, const int& y, const Common::typeScale& scale, Graphics::Font* font, SDL_Renderer* renderer)
  : pRenderer(renderer)
  , mPosX(static_cast<float>(x) * 16.0f * scale.selectedScale)
  , mPosY(static_cast<float>(y) * 16.0f * scale.selectedScale)
  , mScale(scale)
  , pFont(font)
  , mTileData{}
  , mLastLayer(false)
  , mStandardPosition(mPosX, mPosY, 16.0f * scale.selectedScale, 16.0f * scale.selectedScale)
  , mOverlay{} {
    generateOverlay();
}

Tile::~Tile() {
    clear();
    SDL_DestroyTexture(mOverlay.Texture); // Cleanup
}

void
Tile::generateOverlay() {
    // Clear first if set
    if (mOverlay.Texture)
        SDL_DestroyTexture(mOverlay.Texture);
    // Setup overlay
    mOverlay.Texture = SDL_CreateTexture(
      pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, INT(16.0f * mScale.selectedScale), INT(16.0f * mScale.selectedScale));
    if (mOverlay.Texture == nullptr)
        std::cout << "Error in creating texture" << std::endl;
    mOverlay.Position = &mStandardPosition;
    mOverlay.Viewport = nullptr;
    SDL_SetTextureBlendMode(mOverlay.Texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(mOverlay.Texture, 127);
}

void
Tile::clear() {
    for (auto& element : mBaseLayer) {
        delete element.Position;
    }
    for (auto& element : mTopLayer) {
        delete element.Position;
    }
    mBaseLayer.clear();
    mTopLayer.clear();
    mOverlays.clear();
    mTileData = {};
}

int
Tile::addData(const std::string&                         asset,
              File::typeAssets&                         assetList,
              const std::shared_ptr<Graphics::Graphics>& graphics,
              const bool&                                mode) {
    return addData(asset, assetList, graphics, mode ? Mouse::TOP_LAYER : Mouse::TEXTURE);
}

int
Tile::addData(const std::string&                         asset,
              File::typeAssets&                         assetList,
              const std::shared_ptr<Graphics::Graphics>& graphics,
              const Mouse&                               mouse) {
    auto&      data           = mouse == Mouse::TEXTURE ? mBaseLayer : mTopLayer;
    auto       tileType       = mouse == Mouse::TEXTURE ? File::TileEditorType::BASE_TEXTURE : File::TileEditorType::TOP_TEXTURE;
    const auto type           = graphics->getTextureType(asset);
    int        animationValue = 0;
    switch (type) {
        case Graphics::TextureTypes::BaseTexture: {
            auto texture = dynamic_cast<Graphics::BaseTexture*>(graphics->getTexture(asset));
            data.emplace_back(
              texture->getTexture(),
              &texture->getRandomViewport(),
              new SDL_FRect{ mPosX, mPosY, texture->getWidthF() * mScale.selectedScale, texture->getHeightF() * mScale.selectedScale });
        } break;
        case Graphics::TextureTypes::AnimatedTexture: {
            auto texture = dynamic_cast<Graphics::AnimatedTexture*>(graphics->getTexture(asset));
            data.emplace_back(
              texture->getTexture(),
              texture->getAnimatedViewport(),
              new SDL_FRect{ mPosX, mPosY, texture->getWidthF() * mScale.selectedScale, texture->getHeightF() * mScale.selectedScale });
            animationValue = texture->getViewports().size() * texture->getTicks();
        } break;
        default:;
    }
    // Handles the list of assets
    if (File::findAsset(asset, assetList).has_value()) {
        // The item exist in asset list. Append it to the end of our graphics
        switch (mouse) {
            case Mouse::TEXTURE:
                mTileData.Base.emplace_back(File::findAsset(asset, assetList).value());
                break;
            case Mouse::TOP_LAYER:
                mTileData.Top.emplace_back(File::findAsset(asset, assetList).value());
                break;
            default:;
        }
    } else {
        switch (mouse) {
            case Mouse::TEXTURE:
                mTileData.Base.emplace_back(File::addAsset(asset, assetList));
                break;
            case Mouse::TOP_LAYER:
                mTileData.Top.emplace_back(File::addAsset(asset, assetList));
                break;
            default:;
        }
    }
    mTileData.Type.set(tileType);
    return animationValue;
}

void
Tile::clearLastData() {
    if (!mLastLayer && !mBaseLayer.empty()) {
        mBaseLayer.pop_back();
        mTileData.Base.pop_back();
    } else if (!mTopLayer.empty()) {
        mTopLayer.pop_back();
        mTileData.Top.pop_back();
    }
}

void
Tile::addMonster(const int& id, SDL_Texture* texture, const SDL_Rect& viewport) {
    // Add graphics
    SDL_SetRenderTarget(pRenderer, mOverlay.Texture);
    const auto destination = SDL_FRect{ 0.0f, 0.0f, 16.0f * mScale.selectedScale, 16.0f * mScale.selectedScale };
    SDL_RenderCopyF(pRenderer, texture, &viewport, &destination);
    SDL_SetRenderTarget(pRenderer, nullptr);

    Utility::setBitValue(mTileData.Type, 10, 17, id);
}

void
Tile::addOverlay(Graphics::GeneratedTexture* overlay) {
    SDL_FRect destination;
    if (mOverlays.empty()) {
        SDL_SetRenderTarget(pRenderer, mOverlay.Texture);
        SDL_RenderCopyF(pRenderer, overlay->getTexture(), nullptr, nullptr);
    } else {
        switch (mOverlays.size()) {
            case 1:
                SDL_SetRenderTarget(pRenderer, mOverlay.Texture);
                destination = SDL_FRect{ 0.0f, 8.0f * mScale.selectedScale * 16.0f * mScale.selectedScale, 8.0f * mScale.selectedScale };
                SDL_RenderCopyF(pRenderer, overlay->getTexture(), nullptr, &destination);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
    }
    SDL_SetRenderTarget(pRenderer, nullptr);
    mOverlays.insert(overlay->getTexture());
}

void
Tile::addType(const File::TileEditorType& value, Graphics::GeneratedTexture* overlay) {
    mTileData.Type.set(value);
    if (mOverlays.find(overlay->getTexture()) == mOverlays.end())
        addOverlay(overlay);
}

void
Tile::clearType() {
    Utility::resetBits(mTileData.Type, std::bitset<32>(0xFFFFFFFC)); // Clear all types
    generateOverlay();
}

void
Tile::addLightning(const Editor::LightningShape& shape, const Editor::LightningColour& colour, const Editor::LightningSize& size) {
    /*
    Since the enums for shape, colour and size have the same values as the one in File::Types they can be cast directly
        between each other.
    */
    mTileData.Type.set(shape);
    mTileData.Type.set(colour);
    mTileData.Type.set(size);
}

std::vector<Graphics::typeDrawData>
Tile::getBaseDrawData() {
    return mBaseLayer;
}

std::vector<Graphics::typeDrawData>
Tile::getTopDrawData() {
    return mTopLayer;
}

Graphics::typeDrawData
Tile::getNumbers() {
    return Graphics::typeDrawData();
    // return { mNumbers.getTexture(), &numbers.getView(baseLayer.size()), &standardPosition };
}

Graphics::typeDrawData
Tile::getOverlay() {
    return mOverlay;
}

bool
Tile::elementExist(SDL_Texture* texture, const uint8_t& id) const {
    auto t1 =
      std::find_if(mBaseLayer.begin(), mBaseLayer.end(), [&texture](const Graphics::typeDrawData& d) { return d.Texture == texture; });
    auto t2 =
      std::find_if(mTopLayer.begin(), mTopLayer.end(), [&texture](const Graphics::typeDrawData& d) { return d.Texture == texture; });
    auto i1 = std::find_if(mTileData.Base.begin(), mTileData.Base.end(), [&id](const uint8_t& d) { return d == id; });
    auto i2 = std::find_if(mTileData.Top.begin(), mTileData.Top.end(), [&id](const uint8_t& d) { return d == id; });
    return t1 != mBaseLayer.end() || t2 != mTopLayer.end() || i1 != mTileData.Base.end() || i2 != mTileData.Top.end() ? true : false;
}

void
Tile::removeElement(SDL_Texture* texture, const uint8_t& id) {
    // Remove from all the vectors
    Utility::removeElementInVector(mBaseLayer, [texture](const Graphics::typeDrawData a) { return a.Texture == texture; });
    Utility::removeElementInVector(mTopLayer, [texture](const Graphics::typeDrawData a) { return a.Texture == texture; });
    Utility::removeElementInVector(mTileData.Base, [id](const uint8_t& a) { return a == id; });
    Utility::removeElementInVector(mTileData.Top, [id](const uint8_t& a) { return a == id; });
    // Now lower all the values that was above the  id for base and top
    for (auto& element : mTileData.Base) {
        if (element > id)
            --element;
    }
    for (auto& element : mTileData.Top) {
        if (element > id)
            --element;
    }
}

File::typeTileData
Tile::getTileData() const {
    return mTileData;
}

}