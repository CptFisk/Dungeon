#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

// Helping macro
#define GENERATE_JSON_CODE(key)                                    \
    if (nlohmann_json_j.contains(#key)) {                          \
        nlohmann_json_t.key = nlohmann_json_j.at(#key).get<int>(); \
    } else {                                                       \
        nlohmann_json_t.key = 0;                                   \
    }

namespace Graphics {
/***
 * @brief JSON type for User Interface
 */
struct typeUITextureJSON {
    std::string File;   // File to be loaded
    std::string Name;   // Name of file
    int         Column; // Start column in sheet
    int         Row;    // Start row in sheet
    int         Length; // Number of sprites to be read
    int         Height; // Height of texture
    int         Width;  // Width of texture
    int         MarginTop;
    int         MarginBottom;
    int         MarginLeft;
    int         MarginRight;

    typeUITextureJSON()
      : File{}
      , Name{}
      , Column{}
      , Row{}
      , Length{}
      , Height{}
      , Width{}
      , MarginTop{}
      , MarginBottom{}
      , MarginLeft{}
      , MarginRight{} {}
};

inline void
to_json(nlohmann::json& nlohmann_json_j, const typeUITextureJSON& nlohmann_json_t) {
    nlohmann_json_j["Name"]         = nlohmann_json_t.Name;
    nlohmann_json_j["Column"]       = nlohmann_json_t.Column;
    nlohmann_json_j["Row"]          = nlohmann_json_t.Row;
    nlohmann_json_j["Length"]       = nlohmann_json_t.Length;
    nlohmann_json_j["Height"]       = nlohmann_json_t.Height;
    nlohmann_json_j["Width"]        = nlohmann_json_t.Width;
    nlohmann_json_j["MarginTop"]    = nlohmann_json_t.MarginTop;
    nlohmann_json_j["MarginBottom"] = nlohmann_json_t.MarginBottom;
    nlohmann_json_j["MarginLeft"]   = nlohmann_json_t.MarginLeft;
    nlohmann_json_j["MarginRight"]  = nlohmann_json_t.MarginRight;
}
inline void
from_json(const nlohmann::json& nlohmann_json_j, typeUITextureJSON& nlohmann_json_t) {
    nlohmann_json_j.at("Name").get_to(nlohmann_json_t.Name);
    nlohmann_json_j.at("Column").get_to(nlohmann_json_t.Column);
    nlohmann_json_j.at("Row").get_to(nlohmann_json_t.Row);
    nlohmann_json_j.at("Length").get_to(nlohmann_json_t.Length);
    nlohmann_json_j.at("Height").get_to(nlohmann_json_t.Height);
    nlohmann_json_j.at("Width").get_to(nlohmann_json_t.Width);
    GENERATE_JSON_CODE(MarginTop)
    GENERATE_JSON_CODE(MarginBottom)
    GENERATE_JSON_CODE(MarginLeft)
    GENERATE_JSON_CODE(MarginRight)
}

}