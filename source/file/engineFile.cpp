#include <error.hpp>
#include <file/engineFile.hpp>
namespace File {

typeEngineFile
readEngineData(const std::string& filename, SDL_Renderer*& renderer) {
    std::ifstream file(filename, std::ios::binary);
    ASSERT_WITH_MESSAGE(!file, "Cant open file: " << filename)
    typeEngineFile data;
    readHeaderData(file, data.Header);
    readEngineLayers(file, renderer, data.Layers);
    readEngineTileData(file, data.Tiles);
    return data;
}

void
writeEngineData(const std::string&         filename,
                SDL_Renderer*&             renderer,
                const typeHeaderData&      header,
                const Common::typeSegment& data,
                const typeEditorTiles&     tiles) {
    std::ofstream file(filename, std::ios::binary); // File stream
    ASSERT_WITH_MESSAGE(!file.is_open(), "Cant create file buffer")
    writeHeaderData(file, header);
    writeEngineLayers(file, renderer, data);
    writeEngineTileData(file, tiles);
    file.close();
}

}