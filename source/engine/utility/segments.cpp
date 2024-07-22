#include <common/math.hpp>
#include <engine/engine.hpp>
#include <engine/utility/segment.hpp>
#include <global.hpp>
#include <graphics/graphics.hpp>
#include <iostream>
#include <level/types/tile.hpp>

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
                SDL_SetRenderTarget(pRenderer, texture);
                SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
                SDL_RenderClear(pRenderer);

                SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
                SDL_SetTextureAlphaMod(texture, 255);
                SDL_SetRenderTarget(pRenderer, nullptr);
                // Creating all layers
                layers.emplace_back(texture);
            }
            segment.push_back({ layers, SDL_FRect{ xx * ssx * 16.0f, yy * ssy * 16.0f, ssx * 16.0f, ssy * 16.0f } });
        }
    }
    maxValue = INT(segment[0].Layers.size());
}

void
Engine::addToSegment(std::vector<typeSegmentData>& segment, const int& pos, const std::string& name, std::optional<SDL_FRect> position) {
    const auto coords = Common::getCoords(pos, MAP_WIDTH, MAP_WIDTH); // Fetching coords, hopefully
    if (coords.has_value()) {
        const auto coord = coords.value();
        // Calculating what segment this area belongs to
        const auto index = getSegment(coord);
        if (index <= segment.size()) {
            const auto x = FLOAT((coord.first * 16) % (segmentSizeX * 16));
            const auto y = FLOAT((coord.second * 16) % (segmentSizeY * 16));

            switch (mGraphics->getTextureType(name)) {
                case Graphics::TextureTypes::SIMPLE_TEXTURE: {
                    auto texture = GET_SIMPLE(name);
                    if (texture != nullptr) {
                        const SDL_FRect destination =
                          position.has_value() ? position.value() : SDL_FRect{ x, y, FLOAT(texture->Width), FLOAT(texture->Height) };
                        const auto& viewport = texture->getRandomView();
                        // This is the most basic, apply this texture to all layers
                        for (auto& layer : segment[index].Layers) {
                            SDL_SetRenderTarget(pRenderer, layer); // Set render target
                            SDL_RenderCopyF(pRenderer, texture->getTexture(), &viewport, &destination);
                        }
                    }
                } break;
                case Graphics::TextureTypes::ANIMATED_TEXTURE: {
                    auto texture = GET_ANIMATED(name);
                    if (texture != nullptr) {
                        const SDL_FRect destination = { x, y, FLOAT((*texture)->Width), FLOAT((*texture)->Height) };
                        /**
                         * We start the viewport at 0, then we increment it each time we draw a layer. When we have reached the end of our
                         * viewports we simply restart. Since we calculated the layers to match the lcm of the frames it should all be fine
                         */
                        const auto maxTicks     = (*texture)->getTicks();
                        const auto maxViewports = (*texture)->getViewports().size() - 1;
                        int        tick         = 0;
                        int        viewport     = 0;
                        for (auto layer : segment[index].Layers) {
                            if (SDL_SetRenderTarget(pRenderer, layer) != 0) {
                                std::cerr << SDL_GetError() << std::endl;
                            }
                            SDL_RenderCopyF(pRenderer, (*texture)->getTexture(), &(*texture)->getViewports()[viewport], &destination);
                            if (++tick >= maxTicks) {
                                tick = 0;
                                if (viewport++ >= maxViewports)
                                    viewport = 0;
                            }
                        }
                    }
                }

                break;
                case Graphics::TextureTypes::GENERATED_TEXTURE:
                    std::cerr << "GENERATED" << std::endl;
                    break;
                case Graphics::TextureTypes::SDL_TEXTURE:
                    std::cerr << "SDL" << std::endl;
                    break;
                case Graphics::TextureTypes::TEXT:
                    std::cerr << "TEXT" << std::endl;
                    break;
                case Graphics::TextureTypes::UNDEFINED:
                    std::cerr << "UNDEFINED" << std::endl;
                    break;
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
Engine::addLightning(const std::bitset<32> bitset) {
    std::string textureName = "Light";
    SDL_FRect   position;
    if (bitset.test(Level::File::TileType::LIGHT_CIRCLE))
        textureName += "Circle";
    else if (bitset.test(Level::File::TileType::LIGHT_SQUARE))
        textureName += "SQUARE";
    else {
        std::cerr << "Wrong shape on lightning" << std::endl;
        return;
    }
    if (bitset.test(Level::File::TileType::LIGHT_RED))
        textureName += "Red";
    else if (bitset.test(Level::File::TileType::LIGHT_YELLOW))
        textureName += "Yellow";
    else if (bitset.test(Level::File::TileType::LIGHT_WHITE))
        textureName += "White";
    else {
        std::cerr << "Wrong colour on lightning" << std::endl;
        return;
    }
    if (bitset.test(Level::File::TileType::LIGHT_SMALL)) {
        textureName += "Small";
    } else if (bitset.test(Level::File::TileType::LIGHT_MEDIUM)) {
        textureName += "Medium";
    } else if (bitset.test(Level::File::TileType::LIGHT_BIG)) {
        textureName += "Big";
    } else {
        std::cerr << "Wrong size on lightning";
    }
    std::cout << textureName << std::endl;
}

size_t
Engine::getSegment(const std::pair<int, int>& coord) {
    const int     indexX           = INT(coord.first / segmentSizeX);
    const int     indexY           = INT(coord.second / segmentSizeY);
    constexpr int numberOfSegments = INT((MAP_WIDTH + segmentSizeX - 1) / segmentSizeX);

    return indexY * numberOfSegments + indexX;
}
}