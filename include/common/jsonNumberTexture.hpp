#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Graphics {
/***
 * @brief Used when Object is of type BASE_TEXTURE
 */
struct typeNumberTextureJSON {
    std::string File;   // File to be loaded
    std::string Name;   // Name of file
    int         Row;    // Start row in sheet
    int         Column; // Start column in sheet
    int         Length; // Number of sprites to be read
    int         Height; // Height of texture
    int         Width;  // Width of texture

    typeNumberTextureJSON()
      : File{}
      , Name{}
      , Column{}
      , Row{}
      , Length{}
      , Height{}
      , Width{} {}
};

struct typeNumberTextureData {
    std::vector<typeNumberTextureJSON> Objects;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeNumberTextureJSON, File, Name, Row, Column, Length, Height, Width)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeNumberTextureData, Objects)
}