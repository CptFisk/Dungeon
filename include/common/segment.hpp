#pragma once
#include <SDL.h>
#include <common/segmentType.hpp>
#include <editor/tile.hpp>
#include <global.hpp>
#include <graphicsForward.hpp>
#include <memory>
#include <vector>

namespace Common {

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
          File::typeEditorTiles&               tiles,
          File::typeAssets&                    assets);

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
 * @param bitset Tile data
 * @param segment Reference to the segment, in this case Lightning
 * @param x X-position
 * @param y Y-position
 */
void
addLightning(SDL_Renderer*&                       renderer,
             std::shared_ptr<Graphics::Graphics>& graphics,
             const std::bitset<32>&               bitset,
             Common::typeSegmentData&             segment,
             const int&                           x,
             const int&                           y);
}