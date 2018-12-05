cmake_minimum_required(VERSION 3.12)
project(BulletManager)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSFML_STATIC")

set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
set(SOURCE_FILES main.cpp BulletManager.cpp float2.hpp Wall.hpp)
add_executable(BulletManager main.cpp BulletManager.cpp float2.hpp Wall.hpp)

target_link_libraries(BulletManager -lsfml-window-s -lgdi32 -lsfml-graphics-s -lopengl32 -lfreetype -lsfml-audio-s -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lsfml-network-s -lsfml-system-s -lwinmm -lz)