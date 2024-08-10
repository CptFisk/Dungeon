#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Graphics {

enum typeShape { Undefined, Circle, Square };

struct typeGeneratedTextureJSON {
    std::string Name;
    typeShape   Shape;
    int         Red1;
    int         Red2;
    int         Green1;
    int         Green2;
    int         Blue1;
    int         Blue2;
    int         Alpha;
    int         Height; // Height of texture
    int         Width;  // Width of texture

    typeGeneratedTextureJSON()
      : Name{}
      , Shape(typeShape::Undefined)
      , Red1{}
      , Red2{}
      , Green1{}
      , Green2{}
      , Blue1{}
      , Blue2{}
      , Alpha{}
      , Height{}
      , Width{} {}
};

struct typeGeneratedTextureData {
    std::vector<typeGeneratedTextureJSON> Objects;
};

NLOHMANN_JSON_SERIALIZE_ENUM(typeShape, { { typeShape::Circle, "Circle" }, { typeShape::Square, "Square" } })
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeGeneratedTextureJSON, Name, Shape, Red1, Red2, Green1, Green2, Blue1, Blue2, Alpha, Height, Width)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(typeGeneratedTextureData, Objects)

}