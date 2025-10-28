cmake_minimum_required(VERSION 3.16)
project(RaylibStarter CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json for editor support (e.g., VSCode)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Build Types ---
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "-g -Wall")
else()
  set(CMAKE_CXX_FLAGS "-O2")
endif()

# --- Dependencies ---
include(FetchContent)

# nlohmann/json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

# Raylib
# We will use FetchContent to get raylib to ensure it's always available.
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5 # Using a recent version of raylib
)
FetchContent_MakeAvailable(raylib)

# Fetch imgui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG master
)
FetchContent_MakeAvailable(imgui)

# Fetch rlImGui
FetchContent_Declare(
        rlimgui
        GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
        GIT_TAG main
)
FetchContent_MakeAvailable(rlimgui)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

# --- Executable ---
add_executable(RaylibStarter src/main.cpp
    ${rlimgui_SOURCE_DIR}/rlImGui.cpp
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
)

target_include_directories(RaylibStarter PUBLIC
        ${raylib_SOURCE_DIR}/src
        ${nlohmann_json_SOURCE_DIR}/include
        ${imgui_SOURCE_DIR}
        ${rlimgui_SOURCE_DIR}
        )

target_link_libraries(RaylibStarter
        raylib
        nlohmann_json::nlohmann_json
        )

# On Windows with MSVC, raylib needs these libraries
if(MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32 shell32)
endif()
