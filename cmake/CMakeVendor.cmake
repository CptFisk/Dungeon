message(STATUS "Vendor libs")
set(LIB_IMGUI DearImGui)
include(FetchContent)

#SDL
FetchContent_Declare(SDL URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.30.3.tar.gz)

#SDL_Image
FetchContent_Declare(SDL_image URL https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.8.2.tar.gz)
#JSON
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
#Imgui
FetchContent_Declare(imgui URL https://github.com/ocornut/imgui/archive/refs/tags/v1.90.6.tar.gz)

FetchContent_MakeAvailable(SDL SDL_image json imgui)

add_library(${LIB_IMGUI}
        STATIC
        ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
)

target_include_directories(
        ${LIB_IMGUI}
        PRIVATE
        ${imgui_SOURCE_DIR}
)

target_link_libraries(
        ${LIB_IMGUI}
        SDL2::SDL2
)

