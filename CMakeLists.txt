cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

if(CMAKE_BUILD_PLATFORM MATCHES "VITA")
    include("cmake/vita_pre.cmake")
endif()

project(app)

add_executable(
    ${PROJECT_NAME}
        "src/main.cpp"
        "src/core/file.cpp"
        "src/core/state.cpp"
        "src/core/delta.cpp"
        "src/core/assetmanager.cpp"
        "src/core/assets/audio.cpp"
        "src/gl/window.cpp"
        "src/gl/mtsdf/font.cpp"
        "src/gl/mtsdf/text.cpp"
        "src/gl/assets/shader.cpp"
        "src/gl/assets/texture.cpp"
        "src/gl/assets/textureatlas.cpp"
        "src/game/main.cpp"
        "src/game/menu.cpp"
        "src/game/menu/background.cpp"
        "src/game/menu/manager.cpp"
        "src/game/newspaper.cpp"
        "src/game/nightloader.cpp"
)

find_package(SDL3 REQUIRED)
find_package(SDL3_mixer REQUIRED)
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        SDL3
        SDL3_mixer
)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        "inc"   
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
        APP_IS_DEMO
)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Werror -fno-exceptions>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Werror -fno-exceptions>
)

if(CMAKE_BUILD_PLATFORM MATCHES "VITA")
    include("cmake/vita_post.cmake")
else()
    include("cmake/other_post.cmake")
endif()

install(
    TARGETS
        ${PROJECT_NAME}
)
