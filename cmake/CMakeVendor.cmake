message(STATUS "Vendor libs")
set(LIB_IMGUI DearImGui)

add_subdirectory(vendor/SDL ${CMAKE_BINARY_DIR}/SDL)
add_subdirectory(vendor/SDL_image ${CMAKE_BINARY_DIR}/SDL_image)
add_subdirectory(vendor/SDL_ttf ${CMAKE_BINARY_DIR}/SDL_ttf)
add_subdirectory(vendor/nanosvg ${CMAKE_BINARY_DIR}/nanosvg)
add_subdirectory(vendor/json)


set(SDL3_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/vendor/SDL/include)
set(SDL3_LIBRARIES ${CMAKE_BINARY_DIR}/SDL/SDL3.dll)


set(IMGUI_INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/vendor/imgui
)

add_library(${LIB_IMGUI}
        STATIC
        ${CMAKE_SOURCE_DIR}/vendor/imgui/misc/cpp/imgui_stdlib.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdl3.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdlrenderer3.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/misc/cpp/imgui_stdlib.cpp
)

target_include_directories(
        ${LIB_IMGUI}
        PRIVATE
        ${IMGUI_INCLUDE_DIRS}
        ${SDL3_INCLUDE_DIRS}
)

target_link_libraries(
        ${LIB_IMGUI}
        SDL3::SDL3
)

