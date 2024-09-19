#pragma once
#include <vector>
#include <SDL.h>

namespace Common{
struct typeSegmentData {
    std::vector<SDL_Texture*> Layers;   // Each layer contains one animation frame
    SDL_FRect                 Position; // Position for the frames
};

struct typeSegment {
    typeSegmentData Bottom;    // Bottom layer, contains grass, flowers, etc
    typeSegmentData Top;       // Contains all elements that will be above the player
    typeSegmentData Lightning; // Contains static lightning effects

    int CurrentLayerBottom{};    // Current layer bottom
    int MaxLayerBottom{};        // Max layers for bottom graphic
    int CurrentLayerTop{};       // Current layer top
    int MaxLayerTop{};           // Max layers for top graphic
    int CurrentLayerLightning{}; // Current layer for lightning effects
    int MaxLayerLightning{};     // May layer for lightning effects

    typeSegment()
      : Bottom{}
      , Top{}
      , Lightning{}
      , CurrentLayerBottom{}
      , MaxLayerBottom{}
      , CurrentLayerTop{}
      , MaxLayerTop{}
      , CurrentLayerLightning{}
      , MaxLayerLightning{} {}
};
}