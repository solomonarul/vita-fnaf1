cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

if(CMAKE_BUILD_PLATFORM MATCHES "VITA")
    include("cmake/vita_pre.cmake")
endif()

project(app)

add_executable(
    ${PROJECT_NAME}
        "src/main.cpp"
        "src/core/state.cpp"
        "src/core/file.cpp"
        "src/gl/window.cpp"
        "src/gl/shader.cpp"
        "src/gl/texture.cpp"
        "src/game/menu.cpp"
)

find_package(SDL3 REQUIRED)
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        SDL3
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
