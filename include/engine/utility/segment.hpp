#pragma once
#include <SDL.h>
#include <vector>

namespace Engine {

struct typeSegmentData {
    std::vector<SDL_Texture*> Layers;   // Each layer contains one animation frame
    SDL_FRect                 Position; // Position for the frames
};

struct typeSegment {
    std::vector<typeSegmentData> Bottom;    // Bottom layer, contains grass, flowers, etc
    std::vector<typeSegmentData> Top;       // Contains all elements that will be above the player
    std::vector<typeSegmentData> Lightning; // Contains static lightning effects

    int CurrentLayerBottom;    // Current layer bottom
    int MaxLayerBottom;        // Max layers for bottom graphic
    int CurrentLayerTop;       // Current layer top
    int MaxLayerTop;           // Max layers for top graphic
    int CurrentLayerLightning; // Current layer for lightning effects
    int MaxLayerLightning;     // May layer for lightning effects
};

/**
 * @brief Clear all data inside a typeSegmentData
 */
void
clearTypeSegmentData(typeSegmentData& data);
/**
 * @brief Clear all data inside typeSegment
 * @param data
 */
void
clearTypeSegment(typeSegment& data);

}