#pragma once

namespace Editor {
enum Mouse { DEFAULT, REMOVE, TEXTURE, WALL, OBSTACLE };

/**
 * @brief Structure used to store all visuals for a tile. This vector should match the Level::typeTiles
 */
struct typeVisualTile {
    struct _tile {
        SDL_Texture* Texture;
        SDL_FRect    Position;
        SDL_FRect    Viewport;
    }; // Internal struct
    std::vector<_tile> Visuals;

    typeVisualTile(const int& x, const int& y, const int& maxX, Common::typeScale& scale) {
        Visuals.reserve(x * y);
        for (int _y = 0; _y < y; _y++) {
            for (int _x = 0; _x < x; _x++) {
                auto index = Common::getIndex(x, y, maxX);
                if (index.has_value())
                    Visuals.push_back({ nullptr, Common::newSDL_FRectScaled(x, y, scale), SDL_FRect{ 0.0, 0.0, 0.0, 0.0 } });
            }
        }
    }
};

}