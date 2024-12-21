#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Graphics {
/**
 * @brief Used when Object is of type BASE_TEXTURE
 */
struct typeBaseTextureJSON {
    std::string File;    // File to be loaded
    std::string Name;    // Name of file
    int         Column;  // Start column in sheet
    int         Row;     // Start row in sheet
    int         Length;  // Number of sprites to be read
    int         Height;  // Height of texture
    int         Width;   // Width of texture
    int         Opacity; // Optional, is not set use the value 0

    typeBaseTextureJSON()
      : File{}
      , Name{}
      , Column{}
      , Row{}
      , Length{}
      , Height{}
      , Width{}
      , Opacity{} {}
};

struct typeBaseTextureData {
    std::vector<typeBaseTextureJSON> Objects;
};

inline void
to_json(nlohmann::json& nlohmann_json_j, const typeBaseTextureJSON& nlohmann_json_t) {
    nlohmann_json_j["File"]    = nlohmann_json_t.File;
    nlohmann_json_j["Name"]    = nlohmann_json_t.Name;
    nlohmann_json_j["Column"]  = nlohmann_json_t.Column;
    nlohmann_json_j["Row"]     = nlohmann_json_t.Row;
    nlohmann_json_j["Length"]  = nlohmann_json_t.Length;
    nlohmann_json_j["Height"]  = nlohmann_json_t.Height;
    nlohmann_json_j["Width"]   = nlohmann_json_t.Width;
    nlohmann_json_j["Opacity"] = nlohmann_json_t.Opacity;
}
inline void
from_json(const nlohmann::json& nlohmann_json_j, typeBaseTextureJSON& nlohmann_json_t) {
    nlohmann_json_j.at("File").get_to(nlohmann_json_t.File);
    nlohmann_json_j.at("Name").get_to(nlohmann_json_t.Name);
    nlohmann_json_j.at("Column").get_to(nlohmann_json_t.Column);
    nlohmann_json_j.at("Row").get_to(nlohmann_json_t.Row);
    nlohmann_json_j.at("Length").get_to(nlohmann_json_t.Length);
    nlohmann_json_j.at("Height").get_to(nlohmann_json_t.Height);
    nlohmann_json_j.at("Width").get_to(nlohmann_json_t.Width);

    if (nlohmann_json_j.contains("Opacity")) {
        nlohmann_json_t.Opacity = nlohmann_json_j.at("Opacity").get<int>();
    } else {
        nlohmann_json_t.Opacity = 0;
    }
}

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeBaseTextureData, Objects)
}