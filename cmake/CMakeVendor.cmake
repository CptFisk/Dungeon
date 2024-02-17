message(STATUS "Vendor libs")

add_subdirectory(vendor/SDL ${CMAKE_BINARY_DIR}/SDL)
add_subdirectory(vendor/SDL_image ${CMAKE_BINARY_DIR}/SDL_image)
add_subdirectory(vendor/SDL_ttf ${CMAKE_BINARY_DIR}/SDL_ttf)
add_subdirectory(vendor/nanosvg ${CMAKE_BINARY_DIR}/nanosvg)
add_subdirectory(vendor/json)


set(SDL3_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/vendor/SDL/include)
set(SDL3_LIBRARIES ${CMAKE_BINARY_DIR}/SDL/SDL3.dll)