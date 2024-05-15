message(STATUS "Vendor libs")
set(LIB_IMGUI DearImGui)
include(FetchContent)

#SDL
FetchContent_Declare(SDL URL https://github.com/libsdl-org/SDL/releases/download/prerelease-3.1.2/SDL3-3.1.2.tar.xz)

#SDL_Image
FetchContent_Declare(
        SDL_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG        main # release-3.0
)
#JSON
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
#Imgui
FetchContent_Declare(imgui URL https://github.com/ocornut/imgui/archive/refs/tags/v1.90.6.tar.gz)

FetchContent_MakeAvailable(SDL SDL_image json imgui)

add_library(${LIB_IMGUI}
        STATIC
        ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
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
        SDL3::SDL3
)

