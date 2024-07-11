message(STATUS "Utility library")
set(LIB_UTILITY Utility)

add_library(
        ${LIB_UTILITY}
        STATIC
        ${CMAKE_SOURCE_DIR}/source/utility/file.cpp
        ${CMAKE_SOURCE_DIR}/source/utility/trigonometry.cpp
        ${CMAKE_SOURCE_DIR}/source/utility/texture.cpp
        ${CMAKE_SOURCE_DIR}/source/utility/math.cpp
)

target_include_directories(
        ${LIB_UTILITY}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
        ${LIB_UTILITY}
        PRIVATE
        SDL2::SDL2
)
