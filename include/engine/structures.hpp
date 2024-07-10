#pragma once
#include <SDL.h>
#include <vector>

namespace Engine {

struct typeSegmentData {
    std::vector<SDL_Texture*> Layers;       // Each layer contains one animation frame
    SDL_FRect                 Position;     // Position for the frames
    int                       MaxLayers;    // Maximum numbers of layers, should be the same as Layers.Size()
    int                       CurrentLayer; // Current layer that is being drawn
};

struct typeSegment {
    std::vector<typeSegmentData> Bottom; // Bottom layer, contains grass, flowers, etc
    std::vector<typeSegmentData> Top;    // Contains all elements that will be above the player
};

}