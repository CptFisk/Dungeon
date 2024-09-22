#pragma once
#include <bitset>
#include <vector>
#include <fstream>
#include <file/types/editorTile.hpp>
namespace File {

/**
 * @brief Read tiles from a filestream
 */
void
readEngineTileData(std::ifstream& file, std::vector<std::bitset<32>>& data);

/**
 * @brief Write tiles to a filestream
 */
void
writeEngineTileData(std::ofstream& file, const typeEditorTiles& data);

}