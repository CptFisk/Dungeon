#pragma once
#include <SDL.h>
#include <editor/tile.hpp>
#include <global.hpp>
#include <graphicsForward.hpp>
#include <memory>
#include <vector>

namespace Common {

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

void
createMap();

/**
 * @brief Create segments that later can be used to generate the bigger picture
 * @param renderer Reference to the renderer
 * @param segment Reference to the segment (Bottom, Top, Lightning)
 * @param animationValue Highest animation value that exist on that layer, for Lightning its a constant
 * @param maxValue Number of layers for each segment. SAME AS ANIMATION VALUE?
 */
void
createSegments(SDL_Renderer*& renderer, typeSegmentData& segment, const uint8_t& animationValue, int& maxValue);

void
createMap(SDL_Renderer*&                       renderer,
          std::shared_ptr<Graphics::Graphics>& graphics,
          typeSegment&                         segments,
          const int&                           animationBase,
          const int&                           animationTop,
          File::typeTiles& tiles,
          File::typeAssets&                   assets);

/**
 * @brief Add a smaller texture to the bigger picture
 * @param renderer Reference to the renderer
 * @param graphics Reference to the graphics handler
 * @param segment Reference to the segment (Bottom, Top, Lightning)
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param name Name of the graphic that shall be added
 */
void
addToSegment(SDL_Renderer*&                       renderer,
             std::shared_ptr<Graphics::Graphics>& graphics,
             typeSegmentData&                     segment,
             const int&                           x,
             const int&                           y,
             const std::string&                   name);

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

/**
 * @Add a alpha channel to a segment and all its layers
 * @param segment Segment to add
 * @param blendMode SDL_BlendMode
 * @param value Alpha value 0-255
 */
void
setSegmentAlpha(typeSegmentData& segment, const SDL_BlendMode& blendMode, const int& value);

/**
 * @brief Add lightning to a texture
 * @param renderer Reference to the renderer, later used when calling addSegment
 * @param graphics Reference to graphic handler, later used when calling addSegment
 * @param segments Segment that shall receive the lightning effect
 * @param bitset Bitset for lightning
 * @param pos Current position
 */
void
addLightning(SDL_Renderer*&                       renderer,
             std::shared_ptr<Graphics::Graphics>& graphics,
             typeSegment&                         segments,
             const std::bitset<32>&               bitset,
             const int&                           pos);
}