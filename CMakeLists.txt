cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

message(STATUS "CMAKE_BUILD_PLATFORM = ${CMAKE_BUILD_PLATFORM}")

if(CMAKE_BUILD_PLATFORM MATCHES "VITA")
    include("cmake/vita_pre.cmake")
endif()

project(app)
add_executable(
    ${PROJECT_NAME}
        "src/main.cpp"
        "src/core/audio.cpp"
        "src/core/file.cpp"
        "src/core/state.cpp"
        "src/core/delta.cpp"
        "src/core/timer.cpp"
        "src/core/assetmanager.cpp"
        "src/core/inputmanager.cpp"
        "src/gl/window.cpp"
        "src/gl/mtsdf/font.cpp"
        "src/gl/mtsdf/text.cpp"
        "src/gl/assets/shader.cpp"
        "src/gl/assets/texture.cpp"
        "src/gl/assets/texturearray.cpp"
        "src/gl/rendertexture.cpp"
        "src/game/main.cpp"
        "src/game/menu.cpp"
        "src/game/menu/background.cpp"
        "src/game/menu/manager.cpp"
        "src/game/newspaper.cpp"
        "src/game/nightloader.cpp"
        "src/game/night.cpp"
)

add_subdirectory(lib)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        stb_image
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
        NASSET_LOAD_LOG
        NSCENE_LOAD_LOG
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

if(NOT EMSCRIPTEN)
    install(
        TARGETS
            ${PROJECT_NAME}
    )
endif()
