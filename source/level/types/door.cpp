#include <global.hpp>
#include <iostream>
#include <level/types/door.hpp>

namespace Level{

void
readDoorData(std::ifstream& file, std::vector<typeDoorsData>& data){
    uint16_t readSize;

    file.read(reinterpret_cast<char*>(&readSize), sizeof(readSize));
    for (int i = 0; i < readSize; i++) {
        try {
            uint8_t x;
            uint8_t y;

            uint8_t openLength;
            uint8_t closeLength;
            uint8_t conditionLength;

            file.read(reinterpret_cast<char*>(&x), sizeof(x));
            file.read(reinterpret_cast<char*>(&y), sizeof(y));

            // Read open animation
            file.read(reinterpret_cast<char*>(&openLength), sizeof(openLength));
            char* openGraphic = new char[openLength + 1]{};
            file.read(openGraphic, openLength);

            // Read close animation
            file.read(reinterpret_cast<char*>(&closeLength), sizeof(closeLength));
            char* closeGraphic = new char[closeLength + 1]{};
            file.read(closeGraphic, closeLength);

            // Read condition
            file.read(reinterpret_cast<char*>(&conditionLength), sizeof(conditionLength));
            char* condition = new char[conditionLength + 1]{};
            file.read(condition, conditionLength);

            data.emplace_back(x, y, condition, openGraphic, closeGraphic);
            // Cleanup
            delete[] openGraphic;
            delete[] closeGraphic;
            delete[] condition;
        }catch(...){
            std::cerr << "Error reading doors" << std::endl;
        }
    }
}

void
writeDoorData(std::ofstream& file, const std::vector<typeDoorsData>& data){
    const auto numDoors = UINT16(data.size());
    file.write(reinterpret_cast<const char*>(&numDoors), sizeof(numDoors));

    for (const auto& door : data) {
        try {
            file.write(reinterpret_cast<const char*>(&door.X), sizeof(door.X));
            file.write(reinterpret_cast<const char*>(&door.Y), sizeof(door.Y));
            const auto open      = static_cast<uint8_t>(door.GraphicOpen.size());
            const auto close     = static_cast<uint8_t>(door.GraphicClosing.size());
            const auto condition = static_cast<uint8_t>(door.Condition.size());
            file.write(reinterpret_cast<const char*>(&open), sizeof(open));
            file.write(door.GraphicOpen.c_str(), open);
            file.write(reinterpret_cast<const char*>(&close), sizeof(close));
            file.write(door.GraphicClosing.c_str(), close);
            file.write(reinterpret_cast<const char*>(&condition), sizeof(condition));
            file.write(door.Condition.c_str(), condition);
        }catch(...){
            std::cerr << "Error writing door data" << std::endl;
        }
    }
}

}