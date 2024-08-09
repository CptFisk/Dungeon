#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Graphics {
/***
 * @brief Used when Object is of type BASE_TEXTURE
 */
struct typeTextTextureJSON {
    std::string File;   // File to be loaded
    std::string Name;   // Name of file
    int         Row;    // Start row in sheet
    int         Column; // Start column in sheet
    int         Length; // Number of sprites to be read
    int         Height; // Height of texture
    int         Width;  // Width of texture
    int         Ticks;  // Ticks for animation
    typeTextTextureJSON()
      : File{}
      , Name{}
      , Column{}
      , Row{}
      , Length{}
      , Height{}
      , Width{}
      , Ticks{} {}
};

struct typeTextTextureData {
    std::vector<typeTextTextureJSON> Objects;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeTextTextureJSON, File, Name, Row, Column, Length, Height, Width, Ticks)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeTextTextureData, Objects)
}