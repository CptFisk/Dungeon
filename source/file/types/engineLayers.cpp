#include <error.hpp>
#include <file/export.hpp>
#include <file/import.hpp>
#include <file/types/engineLayers.hpp>

namespace File {

void
readEngineLayers(std::ifstream& file, SDL_Renderer*& renderer, typeEngineLayers& data) {
    readLayer(file, renderer, data.Bottom);
    readLayer(file, renderer, data.Top);
    readLayer(file, renderer, data.Lightning);
}

void
readLayer(std::ifstream& file, SDL_Renderer*& renderer, std::vector<SDL_Texture*>& data) {
    size_t layers{};
    file.read(reinterpret_cast<char*>(&layers), sizeof(layers));
    ASSERT_WITH_MESSAGE((layers <= 0), "Could not read layers")
    for (int i = 0; i < layers; i++) {
        size_t dataSize{};
        file.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
        ASSERT_WITH_MESSAGE((dataSize <= 0), "Could not get size of file")
        char* dataContent = new char[dataSize + 1];
        file.read(dataContent, dataSize);
        // Try to load the surface
        auto surface = readPngFromBuffer(dataContent, dataSize, renderer);
        data.push_back(surfaceToTexture(surface, renderer));
        SDL_FreeSurface(surface);
    }
}

void
writeEngineLayers(std::ofstream& file, SDL_Renderer*& renderer, const Common::typeSegment& data) {
    writeLayer(file, renderer, data.Bottom);    // Bottom
    writeLayer(file, renderer, data.Top);       // Top
    writeLayer(file, renderer, data.Lightning); // Lightning
}

void
writeLayer(std::ofstream& file, SDL_Renderer*& renderer, const Common::typeSegmentData& data) {
    const auto layers = data.Layers.size();
    file.write(reinterpret_cast<const char*>(&layers), sizeof(layers));
    for (auto layer : data.Layers) {
        auto surface = textureToSurface(layer, renderer); // Convert to SDL_Surface*
        // Buffer
        std::vector<char> buffer;
        ASSERT_WITH_MESSAGE(!savePngToBuffer(surface, buffer), "Buffer was not created") // Error handling
        const auto size = buffer.size();
        file.write(reinterpret_cast<const char*>(&buffer), sizeof(size));
        file.write(reinterpret_cast<const char*>(buffer.data()), size);
        SDL_FreeSurface(surface); // Cleaning
    }
}

}