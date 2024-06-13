#include <common/math.hpp>
#include <engine/engine.hpp>
#include <graphics/graphics.hpp>
#include <iostream>

namespace Engine {

void
Engine::createSegments(const Level::File::typeAssets& assets) {
    // Clear first if there is segments loaded
    clearSegments();
    // Calculating how many segments we need
    int        segmentX        = 1;
    int        remainderX      = 0;
    int        segmentY        = 1;
    // We always need at least one layer
    const auto animationLayers = std::max(static_cast<int>(assets.AnimationValue), 1);

    if (header.Level.SizeX >= segmentSizeX) {
        segmentX   = static_cast<int>(header.Level.SizeX / segmentSizeX);
        remainderX = header.Level.SizeX % segmentSizeX;
    }
    if (header.Level.SizeY >= segmentSizeY) {
        segmentY = static_cast<int>(header.Level.SizeY / segmentSizeY);
    }

    // Creating textures and positions
    for (int y = 0; y < segmentY; y++) {
        for (int x = 0; x < segmentX; x++) {
            auto                      xx  = static_cast<float>(x);            // Current x-position but as float
            auto                      yy  = static_cast<float>(y);            // Current y-position but as float
            auto                      ssx = static_cast<float>(segmentSizeX); // Segment size but as float
            auto                      ssy = static_cast<float>(segmentSizeY); // Segment size but as float
            std::vector<SDL_Texture*> layers;                                 // All the layers
            // Generating all layers
            for (int i = 0; i < animationLayers; i++) {
                // Create texture
                auto texture =
                  SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, segmentSizeX * 16, segmentSizeY * 16);
                SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
                SDL_SetTextureAlphaMod(texture, 255);
                // Creating all layers
                layers.emplace_back(texture);
            }
            mSegments.push_back({ layers, SDL_FRect{ xx * ssx * 16.0f, yy * ssy * 16.0f, ssx * 16.0f, ssy * 16.0f } });
        }
        // Is there any remainder
        if (remainderX != 0) {
            auto xx = static_cast<float>(remainderX); // Remainder but as float
            int  remainderY;                          // Don't assign value, we will assign it later
            // Calculate the height we can use
            if (segmentSizeY <= (header.Level.SizeY - (y * segmentSizeY))) {
                remainderY = segmentSizeY;
            } else {
                remainderY = (header.Level.SizeY - (y * segmentSizeY));
            }

            auto                      sx  = static_cast<float>(segmentX);     // Segments but as float
            auto                      ssx = static_cast<float>(segmentSizeX); // Segment size but as float
            auto                      ssy = static_cast<float>(segmentSizeY); // Segment size but as float
            std::vector<SDL_Texture*> layers;                                 // All the layers

            for (int i = 0; i < animationLayers; i++) {
                auto texture =
                  SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, remainderX * 16, remainderY * 16);
                SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
                SDL_SetTextureAlphaMod(texture, 255);
                layers.emplace_back(texture);
                layers.emplace_back(texture);
            }
            mSegments.push_back(
              { layers,
                SDL_FRect{ sx * ssx * 16.0f, static_cast<float>(y) * ssy * 16.0f, xx * 16.0f, static_cast<float>(remainderY) * 16.0f } });
        }
    }
}

void
Engine::addToSegment(const int& pos, const std::string& name) {
    auto coords = Common::getCoords(pos, header.Level.SizeX, header.Level.SizeY); // Fetching coords, hopefully

    if (coords.has_value()) {
        auto coord = coords.value();
        // Calculating what segment this area belongs to
        auto index = getSegment(coord);
        if (index <= mSegments.size()) {
            const auto x = static_cast<float>((coord.first * 16) % (segmentSizeX * 16));
            const auto y = static_cast<float>((coord.second * 16) % (segmentSizeY * 16));

            switch (mGraphics->getTextureType(name)) {
                case Graphics::TextureTypes::SIMPLE_TEXTURE: {
                    auto&           texture     = GET_SIMPLE(name);
                    const SDL_FRect destination = { x, y, static_cast<float>(texture.Width), static_cast<float>(texture.Height) };
                    const auto&     viewport    = texture.getRandomView();
                    // This is the most basic, apply this texture to all layers
                    for (auto& layer : mSegments[index].Layers) {
                        SDL_SetRenderTarget(pRenderer, layer); // Set render target
                        SDL_RenderCopyF(pRenderer, texture.getTexture(), &viewport, &destination);
                    }
                } break;
                case Graphics::TextureTypes::ANIMATED_TEXTURE: {
                    auto&           texture     = GET_ANIMATED(name);
                    const SDL_FRect destination = { x, y, static_cast<float>(texture->Width), static_cast<float>(texture->Height) };
                    /**
                     * We start the viewport at 0, then we increment it each time we draw a layer. When we have reached the end of our
                     * viewports we simply restart. Since we calculated the layers to match the lcm of the frames it should all be fine
                     */
                    const auto maxTicks     = texture->getTicks();
                    const auto maxViewports = texture->getViewports().size();
                    int        tick         = 0;
                    int        viewport     = 0;
                    for (auto layer : mSegments[index].Layers) {
                        if (SDL_SetRenderTarget(pRenderer, layer) != 0) {
                            std::cerr << SDL_GetError() << std::endl;
                        }
                        SDL_RenderCopyF(pRenderer, texture->getTexture(), &texture->getViewports()[viewport], &destination);
                        if (++tick >= maxTicks) {
                            tick = 0;
                            if (viewport++ >= maxViewports)
                                viewport = 0;
                        }
                    }
                }

                break;
                case Graphics::TextureTypes::GENERATED_TEXTURE:
                case Graphics::TextureTypes::SDL_TEXTURE:
                case Graphics::TextureTypes::TEXT:
                case Graphics::TextureTypes::UNDEFINED:
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

size_t
Engine::getSegment(const std::pair<int, int>& coord) const {
    const int indexX           = static_cast<int>(coord.first / segmentSizeX);
    const int indexY           = static_cast<int>(coord.second / segmentSizeY);
    const int numberOfSegments = static_cast<int>((header.Level.SizeX + segmentSizeX - 1) / segmentSizeX);

    return indexY * numberOfSegments + indexX;
}

void
Engine::clearSegments() {
    for (auto& segment : mSegments) {
        for (auto& layer : segment.Layers) {
            SDL_DestroyTexture(layer);
        }
    }
    mSegments.clear();
}

}