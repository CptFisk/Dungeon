message(STATUS "File library")
project(File)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LIB_FILE File)

add_library(
        ${LIB_FILE}
        SHARED
        ${CMAKE_SOURCE_DIR}/source/file/editorFile.cpp
        ${CMAKE_SOURCE_DIR}/source/file/engineFile.cpp
        ${CMAKE_SOURCE_DIR}/source/file/types/editorAssets.cpp
        ${CMAKE_SOURCE_DIR}/source/file/types/editorDoor.cpp
        ${CMAKE_SOURCE_DIR}/source/file/types/editorHeader.cpp
        ${CMAKE_SOURCE_DIR}/source/file/types/editorTile.cpp
        ${CMAKE_SOURCE_DIR}/source/file/types/editorWarp.cpp
        ${CMAKE_SOURCE_DIR}/source/file/types/engineHeader.cpp
)

target_include_directories(
        ${LIB_FILE}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
        ${LIB_FILE}
        PRIVATE
        SDL2::SDL2
)

