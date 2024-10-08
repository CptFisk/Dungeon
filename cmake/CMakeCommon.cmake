message(STATUS "Common library")
set(LIB_COMMON Common)

add_library(
        ${LIB_COMMON}
        STATIC
        ${CMAKE_SOURCE_DIR}/source/common/initializer/initializer.cpp
        ${CMAKE_SOURCE_DIR}/source/common/initializer/sdl.cpp
        ${CMAKE_SOURCE_DIR}/source/common/initializer/sdlTTF.cpp
        ${CMAKE_SOURCE_DIR}/source/common/initializer/imgui.cpp

        ${CMAKE_SOURCE_DIR}/source/common/handlers.cpp
        ${CMAKE_SOURCE_DIR}/source/common/actionmgr.cpp
        ${CMAKE_SOURCE_DIR}/source/common/scale.cpp
        ${CMAKE_SOURCE_DIR}/source/common/math.cpp
        ${CMAKE_SOURCE_DIR}/source/common/sdl.cpp
        ${CMAKE_SOURCE_DIR}/source/common/perspective.cpp
        ${CMAKE_SOURCE_DIR}/source/common/interrupt.cpp
        ${CMAKE_SOURCE_DIR}/source/common/segment.cpp

        ${CMAKE_SOURCE_DIR}/source/graphics/graphics.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/floatingText.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/types/texture.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/types/baseTexture.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/types/animatedTexture.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/types/lightningTexture.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/types/generatedTexture.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/types/userInterfaceTexture.cpp
        ${CMAKE_SOURCE_DIR}/source/graphics/types/fontTTF.cpp

        ${CMAKE_SOURCE_DIR}/source/loaders/loadGraphics.cpp
        ${CMAKE_SOURCE_DIR}/source/loaders/loadBaseTexture.cpp
        ${CMAKE_SOURCE_DIR}/source/loaders/loadAnimatedTexture.cpp
        ${CMAKE_SOURCE_DIR}/source/loaders/loadGeneratedTexture.cpp
        ${CMAKE_SOURCE_DIR}/source/loaders/loadLightningTexture.cpp
        ${CMAKE_SOURCE_DIR}/source/loaders/loadUserInterfaceTexture.cpp
        ${CMAKE_SOURCE_DIR}/source/loaders/loadFontTexture.cpp
)

target_include_directories(
        ${LIB_COMMON}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${imgui_SOURCE_DIR}         #ImGui folders
        ${CMAKE_CURRENT_BINARY_DIR} #Needed for generated cmake.hpp
)

target_link_libraries(
        ${LIB_COMMON}
        PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        nlohmann_json::nlohmann_json
        ${LIB_IMGUI}
)
