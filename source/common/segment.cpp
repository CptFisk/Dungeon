#include <common/math.hpp>
#include <common/segment.hpp>
#include <editor/tile.hpp>
#include <file/types/editorTile.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <utility/bits.hpp>
#include <utility/scale.hpp>

namespace Common {

void
clearTypeSegment(typeSegment& data) {
    for (auto& texture : data.Bottom.Layers)
        SDL_DestroyTexture(texture);
    for (auto& texture : data.Top.Layers)
        SDL_DestroyTexture(texture);
    for (auto& texture : data.Lightning.Layers)
        SDL_DestroyTexture(texture);
    data.Bottom.Layers.clear();
    data.Top.Layers.clear();
    data.Lightning.Layers.clear();
    data.MaxLayerBottom     = {};
    data.CurrentLayerBottom = {};
    data.MaxLayerTop        = {};
    data.CurrentLayerTop    = {};
}

void
createMap(SDL_Renderer*&                       renderer,
          std::shared_ptr<Graphics::Graphics>& graphics,
          typeSegment&                         segments,
          const int&                           animationBase,
          const int&                           animationTop,
          File::typeEditorTiles&               tiles,
          File::typeAssets&                    assets) {
    // Create segments
    Common::createSegments(renderer, segments.Bottom, animationBase, segments.MaxLayerBottom);
    Common::createSegments(renderer, segments.Top, animationTop, segments.MaxLayerTop);
    Common::createSegments(renderer, segments.Lightning, LIGHT_ANIMATION_FRAMES, segments.MaxLayerLightning);
    Common::setSegmentAlpha(segments.Lightning, SDL_BLENDMODE_MUL, 0);

    // Start values
    int  pos        = 0;
    bool layersLeft = false;
    auto it         = tiles.Tiles.begin();

    do {
        if (it == tiles.Tiles.end()) {
            it         = tiles.Tiles.begin();
            pos        = 0;
            layersLeft = false;
        }
        const auto& [x, y] = Common::getCoords(pos, MAP_WIDTH, MAP_WIDTH);
        auto& tile         = (*it);
        // Base graphics
        if ((tile.Type.test(Common::TileType::BASE_TEXTURE) || tile.Type.test(Common::TileType::TOP_TEXTURE)) && !tile.Base.empty()) {
            const auto id    = tile.Base.front();
            const auto asset = assets.Assets[id];
            addToSegment(renderer, graphics, segments.Bottom, x, y, asset);
            tile.Base.erase(tile.Base.begin()); // Remove the element since it have been displayed
            if (!tile.Base.empty())
                layersLeft = true;
        }
        // Overlay
        if (tile.Type.test(Common::TileType::TOP_TEXTURE) && !tile.Top.empty()) {
            const auto id    = INT(tile.Top.front());
            const auto asset = assets.Assets[id];
            addToSegment(renderer, graphics, segments.Top, x, y, asset);
            tile.Top.erase(tile.Top.begin()); // Remove element
            if (!tile.Top.empty())
                layersLeft = true;
        }
        if (Utility::isAnyBitSet((it->Type), std::bitset<32>(LIGHT_BITS))) {
            auto b = it->Type;
            addLightning(renderer, graphics, (it->Type), segments.Lightning, x, y);
            Utility::resetBits(it->Type, std::bitset<32>(LIGHT_BITS));
        }
        pos++;
    } while (!(++it == tiles.Tiles.end() && !layersLeft));
    SDL_SetRenderTarget(renderer, nullptr);
}

void
createSegments(SDL_Renderer*& renderer, typeSegmentData& segment, const uint8_t& animationValue, int& maxValue) {
    // We always need at least one layer
    const auto animationLayers = std::max(static_cast<int>(animationValue), 1);

    std::vector<SDL_Texture*> layers; // All the layers
    // Generating all layers
    for (int i = 0; i < animationLayers; i++) {
        // Create texture
        auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 2048, 2048);
        /**
         * It appears that SDL_CreateTexture dont always provide a 100% clean texture, resulting in that we sometime
         * inherit older parts, we first need to make sure that its cleared.
         */
        ASSERT_WITH_MESSAGE(texture == nullptr, SDL_GetError())
        ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(renderer, texture) != 0, SDL_GetError())
        ASSERT_WITH_MESSAGE(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0) != 0, SDL_GetError())
        ASSERT_WITH_MESSAGE(SDL_RenderClear(renderer) != 0, SDL_GetError())

        ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) != 0, SDL_GetError())
        ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(texture, 255) != 0, SDL_GetError())
        ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(renderer, nullptr) != 0, SDL_GetError())
        // Creating all layers
        layers.emplace_back(texture);
    }
    segment  = { layers, SDL_FRect{ 0, 0, 2048, 2048 } };
    maxValue = INT(segment.Layers.size());
}

void
addToSegment(SDL_Renderer*&                       renderer,
             std::shared_ptr<Graphics::Graphics>& graphics,
             typeSegmentData&                     segment,
             const int&                           x,
             const int&                           y,
             const std::string&                   name) {
    auto xPos = FLOAT(x * 16.0f);
    auto yPos = FLOAT(y * 16.0f);

    switch (graphics->getTextureType(name)) {
        case Graphics::TextureTypes::BaseTexture: {
            auto            texture     = dynamic_cast<Graphics::BaseTexture*>(graphics->getTexture(name));
            const SDL_FRect destination = SDL_FRect{ xPos, yPos, FLOAT(texture->getWidth()), FLOAT(texture->getHeight()) };
            const auto&     viewport    = texture->getRandomViewport();
            // This is the most basic, apply this texture to all layers
            for (auto& layer : segment.Layers) {
                SDL_SetRenderTarget(renderer, layer); // Set render target
                SDL_RenderCopyF(renderer, texture->getTexture(), &viewport, &destination);
                ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(renderer, nullptr) != 0, SDL_GetError())
            }

        } break;
        case Graphics::TextureTypes::AnimatedTexture: {
            auto            texture     = dynamic_cast<Graphics::AnimatedTexture*>(graphics->getTexture(name));
            const SDL_FRect destination = { xPos, yPos, FLOAT(texture->getWidth()), FLOAT(texture->getHeight()) };
            /**
             * We start the viewport at 0, then we increment it each time we draw a layer. When we have reached the end of our
             * viewports we simply restart. Since we calculated the layers to match the lcm of the frames it should all be fine
             */
            const auto maxTicks     = texture->getTicks();
            const auto maxViewports = texture->getViewports().size() - 1;
            int        tick         = 0;
            int        viewport     = 0;
            for (auto layer : segment.Layers) {
                ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(renderer, layer) != 0, SDL_GetError())
                SDL_RenderCopyF(renderer, texture->getTexture(), &texture->getViewport(viewport), &destination);
                ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(renderer, nullptr) != 0, SDL_GetError())
                if (++tick >= maxTicks) {
                    tick = 0;
                    if (viewport++ >= maxViewports)
                        viewport = 0;
                }
            }

        }

        break;
        case Graphics::TextureTypes::LightningTexture: {
            auto texture = dynamic_cast<Graphics::LightningTexture*>(graphics->getTexture(name));
            xPos -= texture->getWidthF() / 2.0f - 8.0f;
            yPos -= texture->getHeightF() / 2.0f - 8.0f;
            int viewport = 0;
            for (auto layer : segment.Layers) {
                SDL_FRect destination = { xPos, yPos, FLOAT(texture->getWidth()), FLOAT(texture->getHeight()) };
                SDL_SetRenderTarget(renderer, layer);
                SDL_RenderCopyF(renderer, texture->getTexture(), &texture->getViewport(viewport++), &destination);
                SDL_SetRenderTarget(renderer, nullptr);
            }

        } break;
        default:
            std::cerr << "Not supported" << std::endl;
    }
    SDL_SetRenderTarget(renderer, nullptr); // Reset renderer
}

void
setSegmentAlpha(typeSegmentData& segment, const SDL_BlendMode& blendMode, const int& value) {
    for (auto& layer : segment.Layers) {
        ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(layer, blendMode) != 0, SDL_GetError())
        ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(layer, Utility::Scale(value, 0, 100, 0, 255)) != 0, SDL_GetError())
    }
}

void
addLightning(SDL_Renderer*&                       renderer,
             std::shared_ptr<Graphics::Graphics>& graphics,
             const std::bitset<32>&               bitset,
             Common::typeSegmentData&             segment,
             const int&                           x,
             const int&                           y) {
    std::string textureName = "Light";
    switch (Utility::getSetBit(bitset, std::bitset<32>(LIGHT_SHAPE))) {
        case Common::LIGHT_CIRCLE:
            textureName += "Circle";
            break;
        case Common::LIGHT_SQUARE:
            textureName += "Square";
            break;
        default:
            return;
    }
    switch (Utility::getSetBit(bitset, std::bitset<32>(LIGHT_COLOUR))) {
        case Common::LIGHT_RED:
            textureName += "Red";
            break;
        case Common::LIGHT_YELLOW:
            textureName += "Yellow";
            break;
        case Common::LIGHT_WHITE:
            textureName += "White";
            break;
        default:
            return;
    }
    switch (Utility::getSetBit(bitset, std::bitset<32>(LIGHT_SIZE))) {
        case Common::LIGHT_BIG:
            addToSegment(renderer, graphics, segment, x, y, textureName + "Big");
        case Common::LIGHT_MEDIUM:
            addToSegment(renderer, graphics, segment, x, y, textureName + "Medium");
        case Common::LIGHT_SMALL:
            addToSegment(renderer, graphics, segment, x, y, textureName + "Small");
            break;
        default:
            return;
    }
}
}