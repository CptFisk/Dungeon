project(Editor)

add_executable(
        ${PROJECT_NAME}
        ${COMMON_FILES}
        ${UTILITY_FILES}

        ${CMAKE_SOURCE_DIR}/editor.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/editor.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/loadLevel.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/ui.cpp

        ${CMAKE_SOURCE_DIR}/source/editor/ui/door.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/ui/header.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/ui/uiMouse.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/ui/mouseLightning.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/ui/assets.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/ui/textures.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/ui/functions.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/ui/uiUnit.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/ui/menu.cpp


        ${CMAKE_SOURCE_DIR}/source/editor/grid.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/tiles.cpp

        ${CMAKE_SOURCE_DIR}/source/editor/tile.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/warps.cpp

        ${CMAKE_SOURCE_DIR}/source/editor/utility/assetsHandler.cpp
        ${CMAKE_SOURCE_DIR}/source/editor/utility/mouse.cpp
)


target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${imgui_SOURCE_DIR}         #ImGui folders
        ${CMAKE_CURRENT_BINARY_DIR} #Needed for generated cmake.hpp
)


target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        nlohmann_json::nlohmann_json
        ${LIB_IMGUI}
        ${LIB_COMMON}
        ${LIB_UTILITY}
        ${LIB_FILE}
)