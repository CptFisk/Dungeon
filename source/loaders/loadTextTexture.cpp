#include <common/jsonTextTexture.hpp>
#include <error.hpp>
#include <graphics/graphics.hpp>
#include <nlohmann/json.hpp>

namespace Graphics {

void
loadTextTexture(const std::string& jsonString) {
    typeTextTextureData jsonData;
    try {
        jsonData = nlohmann::json::parse(jsonString)[nlohmann::json::json_pointer("/Data")].get<typeTextTextureData>();
    } catch (const std::exception& e) {
        ASSERT_WITH_MESSAGE(true, e.what());
    }
}
}