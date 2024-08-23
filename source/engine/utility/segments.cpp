#include <common/math.hpp>
#include <engine/engine.hpp>
#include <engine/utility/segment.hpp>
#include <global.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <level/types/tile.hpp>
#include <utility/bits.hpp>
#include <utility/scale.hpp>

namespace Engine {

void
clearTypeSegmentData(typeSegmentData& data) {
    for (auto& texture : data.Layers) {
        if (texture)
            SDL_DestroyTexture(texture);
    }
}
void
clearTypeSegment(typeSegment& data) {

    for (auto& bottom : data.Bottom)
        clearTypeSegmentData(bottom);
    for (auto& top : data.Top)
        clearTypeSegmentData(top);
    for (auto& lightning : data.Lightning)
        clearTypeSegmentData(lightning);
    data.Bottom.clear();
    data.Top.clear();
    data.Lightning.clear();
    data.MaxLayerBottom     = {};
    data.CurrentLayerBottom = {};
    data.MaxLayerTop        = {};
    data.CurrentLayerTop    = {};
}

void
Engine::createSegments(std::vector<typeSegmentData>& segment, const uint8_t& animationValue, int& maxValue) {
    // Calculating how many segments we need
    int segmentX = 1;
    int segmentY = 1;
    // We always need at least one layer
    const auto animationLayers = std::max(static_cast<int>(animationValue), 1);
    if (MAP_WIDTH >= segmentSizeX) {
        segmentX = static_cast<int>(MAP_WIDTH / segmentSizeX);
    }
    if (MAP_WIDTH >= segmentSizeY) {
        segmentY = static_cast<int>(MAP_WIDTH / segmentSizeY);
    }

    // Creating textures and positions
    for (int y = 0; y < segmentY; y++) {
        for (int x = 0; x < segmentX; x++) {
            const auto     xx  = static_cast<float>(x);            // Current x-position but as float
            const auto     yy  = static_cast<float>(y);            // Current y-position but as float
            constexpr auto ssx = static_cast<float>(segmentSizeX); // Segment size but as float
            constexpr auto ssy = static_cast<float>(segmentSizeY); // Segment size but as float

            std::vector<SDL_Texture*> layers; // All the layers
            // Generating all layers
            for (int i = 0; i < animationLayers; i++) {
                // Create texture
                auto texture =
                  SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, segmentSizeX * 16, segmentSizeY * 16);
                /**
                 * It appears that SDL_CreateTexture dont always provide a 100% clean texture, resulting in that we sometime
                 * inherit older parts, we first need to make sure that its cleared.
                 */
                ASSERT_WITH_MESSAGE(texture == nullptr, SDL_GetError())
                ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, texture) != 0, SDL_GetError())
                ASSERT_WITH_MESSAGE(SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0) != 0, SDL_GetError())
                ASSERT_WITH_MESSAGE(SDL_RenderClear(pRenderer) != 0, SDL_GetError())

                ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) != 0, SDL_GetError())
                ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(texture, 255) != 0, SDL_GetError())
                ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, nullptr) != 0, SDL_GetError())
                // Creating all layers
                layers.emplace_back(texture);
            }
            segment.push_back({ layers, SDL_FRect{ xx * ssx * 16.0f, yy * ssy * 16.0f, ssx * 16.0f, ssy * 16.0f } });
        }
    }
    maxValue = INT(segment[0].Layers.size());
}

void
Engine::addToSegment(std::vector<typeSegmentData>& segment, const int& pos, const std::string& name) {
    const auto coords = Common::getCoords(pos, MAP_WIDTH, MAP_WIDTH); // Fetching coords, hopefully
    if (coords.has_value()) {
        const auto coord = coords.value();
        // Calculating what segment this area belongs to
        const auto index = getSegment(coord);
        if (index <= segment.size()) {
            auto x = FLOAT((coord.first * 16) % (segmentSizeX * 16));
            auto y = FLOAT((coord.second * 16) % (segmentSizeY * 16));

            switch (mGraphics->getTextureType(name)) {
                case Graphics::TextureTypes::BaseTexture: {
                    auto            texture     = GET_BASE(name);
                    const SDL_FRect destination = SDL_FRect{ x, y, FLOAT(texture->getWidth()), FLOAT(texture->getHeight()) };
                    const auto&     viewport    = texture->getRandomViewport();
                    // This is the most basic, apply this texture to all layers
                    for (auto& layer : segment[index].Layers) {
                        SDL_SetRenderTarget(pRenderer, layer); // Set render target
                        SDL_RenderCopyF(pRenderer, texture->getTexture(), &viewport, &destination);
                        ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, nullptr) != 0, SDL_GetError())
                    }

                } break;
                case Graphics::TextureTypes::AnimatedTexture: {
                    auto texture = GET_ANIMATED(name);

                    const SDL_FRect destination = { x, y, FLOAT(texture->getWidth()), FLOAT(texture->getHeight()) };
                    /**
                     * We start the viewport at 0, then we increment it each time we draw a layer. When we have reached the end of our
                     * viewports we simply restart. Since we calculated the layers to match the lcm of the frames it should all be fine
                     */
                    const auto maxTicks     = texture->getTicks();
                    const auto maxViewports = texture->getViewports().size() - 1;
                    int        tick         = 0;
                    int        viewport     = 0;
                    for (auto layer : segment[index].Layers) {
                        ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, layer) != 0, SDL_GetError())
                        SDL_RenderCopyF(pRenderer, texture->getTexture(), &texture->getViewport(viewport), &destination);
                        ASSERT_WITH_MESSAGE(SDL_SetRenderTarget(pRenderer, nullptr) != 0, SDL_GetError())
                        if (++tick >= maxTicks) {
                            tick = 0;
                            if (viewport++ >= maxViewports)
                                viewport = 0;
                        }
                    }

                }

                break;
                case Graphics::TextureTypes::GeneratedTexture:
                    std::cerr << "GENERATED" << std::endl;
                    break;
                case Graphics::TextureTypes::Text:
                    std::cerr << "TEXT" << std::endl;
                    break;
                case Graphics::TextureTypes::Undefined:
                    std::cerr << name << std::endl;
                    std::cerr << "UNDEFINED" << std::endl;
                    break;
                case Graphics::TextureTypes::LightningTexture: {
                    auto texture = GET_LIGHTNING(name);
                    x -= (FLOAT((texture->getWidth() / 2)) - 8.0);
                    y -= (FLOAT((texture->getHeight() / 2)) - 8.0);
                    int viewport = 0;
                    for (auto layer : segment[index].Layers) {
                        SDL_FRect destination = { x, y, FLOAT(texture->getWidth()), FLOAT(texture->getHeight()) };
                        SDL_SetRenderTarget(pRenderer, layer);
                        SDL_RenderCopyF(pRenderer, texture->getTexture(), &texture->getViewport(viewport++), &destination);
                        SDL_SetRenderTarget(pRenderer, nullptr);
                    }

                } break;
                default:
                    std::cerr << "Not supported" << std::endl;
            }
            SDL_SetRenderTarget(pRenderer, nullptr); // Reset renderer
        } else {
            std::cerr << "Error in calculations";
        }
    } else {
        std::cerr << "Cant translate coordinates" << std::endl;
    }
}

void
Engine::setSegmentAlpha(std::vector<typeSegmentData>& segments, const SDL_BlendMode& blendMode, const int& value) {
    for (auto& segment : segments) {
        for (auto& layer : segment.Layers) {
            ASSERT_WITH_MESSAGE(SDL_SetTextureBlendMode(layer, blendMode) != 0, SDL_GetError())
            ASSERT_WITH_MESSAGE(SDL_SetTextureAlphaMod(layer, Utility::Scale(value, 0, 100, 0, 255)) != 0, SDL_GetError())
        }
    }
}

void
Engine::addLightning(const std::bitset<32> bitset, const int& pos) {
    std::string textureName = "Light";
    switch (Utility::getSetBit(bitset, std::bitset<32>(LIGHT_SHAPE))) {
        case Level::LIGHT_CIRCLE:
            textureName += "Circle";
            break;
        case Level::LIGHT_SQUARE:
            textureName += "Square";
            break;
        default:
            return;
    }
    switch (Utility::getSetBit(bitset, std::bitset<32>(LIGHT_COLOUR))) {
        case Level::LIGHT_RED:
            textureName += "Red";
            break;
        case Level::LIGHT_YELLOW:
            textureName += "Yellow";
            break;
        case Level::LIGHT_WHITE:
            textureName += "White";
            break;
        default:
            return;
    }
    switch (Utility::getSetBit(bitset, std::bitset<32>(LIGHT_SIZE))) {
        case Level::LIGHT_BIG:
            addToSegment(mSegments.Lightning, pos, textureName + "Big");
        case Level::LIGHT_MEDIUM:
            addToSegment(mSegments.Lightning, pos, textureName + "Medium");
        case Level::LIGHT_SMALL:
            addToSegment(mSegments.Lightning, pos, textureName + "Small");
            break;
        default:
            return;
    }
}

size_t
Engine::getSegment(const std::pair<int, int>& coord) {
    const int     indexX           = INT(coord.first / segmentSizeX);
    const int     indexY           = INT(coord.second / segmentSizeY);
    constexpr int numberOfSegments = INT((MAP_WIDTH + segmentSizeX - 1) / segmentSizeX);

    return indexY * numberOfSegments + indexX;
}
}