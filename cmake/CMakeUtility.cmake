message(STATUS "Utility library")
project(UtilityLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LIB_UTILITY Utility)

enable_testing()

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

add_executable(
        MathTest
        ${CMAKE_SOURCE_DIR}/test/utility/math.cpp
)

add_executable(
        StringTest
        ${CMAKE_SOURCE_DIR}/test/utility/string.cpp
)

target_include_directories(
        MathTest
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include

)

target_include_directories(
        StringTest
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include

)

# Link the utility library and testing libraries to the test executable
target_link_libraries(
        MathTest
        ${LIB_UTILITY}
)

target_link_libraries(
        StringTest
        ${LIB_UTILITY}
)

add_test(NAME MathTest COMMAND MathTest)
add_test(NAME StringTest COMMAND StringTest)

