#pragma once
#include <string>
#include <vector>

namespace NPC {

enum class Type {
    COW = 1 // Our own special cow
};

const std::vector<std::pair<std::string, std::string>> npc = { { "", "" }, // Default blank
                                                               { "Cow1", "Cow1South" }

};
}