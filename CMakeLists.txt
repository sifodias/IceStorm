cmake_minimum_required(VERSION 3.0.0)
project(IceStorm)
set(CMAKE_CXX_STANDARD 20)

find_package(nlohmann_json 3.2.0 REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../src/")
set(PROJECT_BINARY_DIR "src/")
include_directories("libs/imgui-1.82")
include_directories("src/Ressources Managers")
include_directories("src/")

file(GLOB_RECURSE CPPS "src/*.cpp")
file(GLOB_RECURSE CPPS2 "src/*/*.cpp")
file(GLOB_RECURSE LIBS "libs/imgui-1.82/*.cpp")
add_executable(IceStorm ${CPPS} ${CPPS2} ${LIBS})

target_link_libraries(IceStorm -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf nlohmann_json::nlohmann_json)



# You should install the SDL2 & nlohmann_json libs from your package manager
