cmake_minimum_required(VERSION 3.28)
project(WFCBiomeProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(_local_sfml_dir "${CMAKE_BINARY_DIR}/_deps/sfml-build")
if(EXISTS "${_local_sfml_dir}/SFMLConfig.cmake")
    set(SFML_DIR "${_local_sfml_dir}")
endif()

find_package(SFML 3 COMPONENTS Graphics CONFIG QUIET)

if(NOT SFML_FOUND)
    include(FetchContent)
    set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)
endif()

add_executable(WFCBiomeGenerator
    src/main.cpp
    BiomeClasses/cell.cpp
    BiomeClasses/map.cpp 
    BiomeClasses/Biome.cpp
    Graphics/mapRenderer.cpp
    Graphics/button.cpp
)
target_include_directories(WFCBiomeGenerator PRIVATE
    BiomeClasses
    Graphics
)
target_compile_features(WFCBiomeGenerator PRIVATE cxx_std_17)
target_link_libraries(WFCBiomeGenerator PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT WFCBiomeGenerator)
