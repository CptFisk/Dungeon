#include <common/math.hpp>
#include <graphics/graphics.hpp>
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
    for (int y = 0; y <= segmentY; y++) {
        for (int x = 0; x < segmentX; x++) {
            auto xx  = static_cast<float>(x);            // Current x-position but as float
            auto yy  = static_cast<float>(y);            // Current y-position but as float
            auto ssx = static_cast<float>(segmentSizeX); // Segment size but as float
            auto ssy = static_cast<float>(segmentSizeY); // Segment size but as float
            // Create texture
            auto texture =
              SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, segmentSizeX * 16, segmentSizeY * 16);
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(texture, 255);
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
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(texture, 255);
            // Creating all segments
            mSegments.emplace_back(SDL_FRect{ sx * ssx * 16.0f, static_cast<float>(y) * ssy * 16.0f, xx * 16.0f, yy * 16.0f }, texture);
        }
    }
}

void
Level::addToSegment(const int& pos, const std::string& name) {

    auto texture = GET_SIMPLE(name);                                               // First we extract the texture
    auto coords  = Common::getCoords(pos, header.Level.SizeX, header.Level.SizeY); // Fetching coords, hopefully

    if (coords.has_value()) {
        auto coord = coords.value();
        // Calculating what segment this area belongs to
        auto index = getSegment(coord);
        if(index == 1){
            int a = 20;
        }
        if (index <= mSegments.size()) {
            //Fix this, the issue is that the position is not the same in picture as in game. Due to segmentations
            SDL_FRect destination = { static_cast<float>(coord.first) * 16.0f,
                                      static_cast<float>(coord.second) * 16.0f,
                                      static_cast<float>(texture.Width),
                                      static_cast<float>(texture.Height) };
            // Change render target
            if (SDL_SetRenderTarget(pRenderer, mSegments[index].second) != 0) {
                std::cerr << SDL_GetError() << std::endl;
            };
            if(SDL_RenderTexture(pRenderer, texture.getTexture(), &texture.getRandomView(), &destination) != 0){
                std::cerr << SDL_GetError() << std::endl;
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
Level::getSegment(const std::pair<int, int> coord) const{
    const int indexX           = static_cast<int>(coord.first / segmentSizeX);
    const int indexY           = static_cast<int>(coord.second / segmentSizeY);
    const int numberOfSegments = static_cast<int>((header.Level.SizeX + segmentSizeX - 1) / segmentSizeX);

    return indexY * numberOfSegments + indexX;
}

}