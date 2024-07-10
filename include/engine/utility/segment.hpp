#pragma once
#include <SDL.h>
#include <vector>

namespace Engine {

struct typeSegmentData {
    std::vector<SDL_Texture*> Layers;       // Each layer contains one animation frame
    SDL_FRect                 Position;     // Position for the frames
};

struct typeSegment {
    std::vector<typeSegmentData> Bottom; // Bottom layer, contains grass, flowers, etc
    std::vector<typeSegmentData> Top;    // Contains all elements that will be above the player
};

void clearTypeSegmentData(std::vector<typeSegmentData>& data);
void clearTypeSegment(typeSegment& data);

}