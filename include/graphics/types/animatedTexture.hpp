#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Graphics {

struct typeAnimatedTextureJSON {
    std::string Name;   // Animation name
    int         Column; // Start column in sheet
    int         Row;    // Start row in sheet
    int         Length; // Number of sprites to be read
    int         Ticks;  // Number of seconds for each texture *100ms
    int         Width;  // Width of texture
    int         Height; // Height of texture
    bool        Paused; // Optional, not always existing

    typeAnimatedTextureJSON()
      : Name{}
      , Column{}
      , Row{}
      , Length{}
      , Ticks{}
      , Width{}
      , Height{}
      , Paused(false) {}
};

struct typeAnimatedTextureData {
    std::string                          File;
    std::vector<typeAnimatedTextureJSON> Objects;
};


inline void
to_json(nlohmann::json& nlohmann_json_j, const typeAnimatedTextureJSON& nlohmann_json_t) {
    nlohmann_json_j["Name"]   = nlohmann_json_t.Name;
    nlohmann_json_j["Column"] = nlohmann_json_t.Column;
    nlohmann_json_j["Row"]    = nlohmann_json_t.Row;
    nlohmann_json_j["Length"] = nlohmann_json_t.Length;
    nlohmann_json_j["Ticks"]  = nlohmann_json_t.Ticks;
    nlohmann_json_j["Height"] = nlohmann_json_t.Height;
    nlohmann_json_j["Width"]  = nlohmann_json_t.Width;
    nlohmann_json_j["Paused"] = nlohmann_json_t.Paused;
}
inline void
from_json(const nlohmann::json& nlohmann_json_j, typeAnimatedTextureJSON& nlohmann_json_t) {
    nlohmann_json_j.at("Name").get_to(nlohmann_json_t.Name);
    nlohmann_json_j.at("Column").get_to(nlohmann_json_t.Column);
    nlohmann_json_j.at("Row").get_to(nlohmann_json_t.Row);
    nlohmann_json_j.at("Length").get_to(nlohmann_json_t.Length);
    nlohmann_json_j.at("Ticks").get_to(nlohmann_json_t.Ticks);
    nlohmann_json_j.at("Height").get_to(nlohmann_json_t.Height);
    nlohmann_json_j.at("Width").get_to(nlohmann_json_t.Width);
    if (nlohmann_json_j.contains("Paused")) {
        nlohmann_json_t.Paused = nlohmann_json_j.at("Paused").get<bool>();
    } else {
        nlohmann_json_t.Paused = false;
    }
}


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeAnimatedTextureData, File, Objects)

}