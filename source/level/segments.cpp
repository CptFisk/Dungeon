#include <level/level.hpp>

namespace Level {
void
Level::createSegments() {
    // Clear first if there is segments loaded
    for (auto [position, texture] : mSegments) {
        SDL_DestroyTexture(texture);
    }
    mSegments.clear();

    // Calculating how many segments we need
    int segmentX   = 1;
    int remainderX = 0;
    int segmentY   = 1;
    int remainderY = 0;

    if (header.Level.SizeX >= segmentSizeX) {
        segmentX   = static_cast<int>(header.Level.SizeX / segmentSizeX);
        remainderX = header.Level.SizeX % segmentSizeX;
    }

    if (header.Level.SizeY >= segmentSizeY) {
        segmentY   = static_cast<int>(header.Level.SizeY / segmentSizeY);
        remainderY = header.Level.SizeY % segmentSizeY;
    }

    // Creating textures and positions
    for (int y = 0; y < segmentY; y++) {
        for (int x = 0; x < segmentX; x++) {

            // Create texture
            auto texture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, segmentSizeX, segmentSizeY);
            SDL_SetTextureBlendMode(mLevel, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(mLevel, 255);
            // Creating all segments
            mSegments.emplace_back(SDL_FRect{ x * segmentSizeX * 16.0f, y * segmentY * 16.0f, segmentX * 16.0f, segmentY * 16.0f },
                                   texture);
        }
        //Is there any remainder
        if(remainderX != 0){
            auto texture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, remainderX * 16, remainderY * 16);
            SDL_SetTextureBlendMode(mLevel, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(mLevel, 255);
            // Creating all segments
            mSegments.emplace_back(SDL_FRect{ segmentX * segmentSizeX * 16.0f, y * segmentY * 16.0f, remainderX * 16.0f, remainderX * 16.0f },
                                   texture);
        }
    }
}
}