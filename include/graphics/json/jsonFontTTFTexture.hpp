#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Common {
/***
 * @brief Used when Object is of type BASE_TEXTURE
 */
struct typeFontTTFTextureJSON {
    std::string File; // File to be loaded
    std::string Name; // Name of file

    typeFontTTFTextureJSON()
      : File{}
      , Name{} {};
};

struct typeFontTTFTextureData {
    std::vector<typeFontTTFTextureJSON> Objects;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeFontTTFTextureJSON , File, Name)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeFontTTFTextureData, Objects)
}