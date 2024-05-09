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
            auto xx  = static_cast<float>(x);            // Current x-position but as float
            auto yy  = static_cast<float>(y);            // Current y-position but as float
            auto ssx = static_cast<float>(segmentSizeX); // Segment size but as float
            auto ssy = static_cast<float>(segmentSizeY); // Segment size but as float
            // Create texture
            auto texture =
              SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, segmentSizeX * 16, segmentSizeY * 16);
            SDL_SetTextureBlendMode(mLevel, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(mLevel, 255);
            // Creating all segments
            mSegments.emplace_back(SDL_FRect{ xx * ssx * 16.0f, yy * ssy * 16.0f, ssx * 16.0f, ssy * 16.0f }, texture);
        }
        // Is there any remainder
        if (remainderX != 0) {
            auto xx  = static_cast<float>(remainderX);   // Remainder but as float
            auto yy  = static_cast<float>(remainderY);   // Remainder but as float
            auto sx  = static_cast<float>(segmentX);     // Segments but as float
            auto ssx = static_cast<float>(segmentSizeX); // Segment size but as float
            auto ssy = static_cast<float>(segmentSizeY); // Segment size but as float

            auto texture =
              SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, remainderX * 16, remainderY * 16);
            SDL_SetTextureBlendMode(mLevel, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(mLevel, 255);
            // Creating all segments
            mSegments.emplace_back(SDL_FRect{ sx * ssx * 16.0f, static_cast<float>(y) * ssy * 16.0f, xx * 16.0f, yy * 16.0f }, texture);
        }
    }
}
}