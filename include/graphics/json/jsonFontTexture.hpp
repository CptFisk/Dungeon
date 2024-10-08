#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Common {
/***
 * @brief Used when Object is of type BASE_TEXTURE
 */
struct typeFontTextureJSON {
    std::string File; // File to be loaded
    std::string Name; // Name of file

    typeFontTextureJSON()
      : File{}
      , Name{} {};
};

struct typeFontTextureData {
    std::vector<typeFontTextureJSON> Objects;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeFontTextureJSON , File, Name)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeFontTextureData, Objects)
}