#include <file/engineFile.hpp>
#include <error.hpp>
namespace File{

void
writeEngineData(const std::string& filename, SDL_Renderer*& renderer, const Common::typeSegment& data){
    std::ofstream file(filename, std::ios::binary); //File stream
    ASSERT_WITH_MESSAGE(!file.is_open(), "Cant create file buffer")
    writeEngineLayers(file, renderer, data);
    file.close();
}

}