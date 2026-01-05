cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(NEX_APP_EXECUTABLE app)
set(VITA_APP_NAME "Five Nights at Freddy's")
set(VITA_TITLEID "FNAF1SLMN")
set(VITA_VERSION "01.00")
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")
# set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d ATTRIBUTE2=12")  # Uncomment to download more RAM.

# NOTE: Important that Nex is compiled before anything else because of the cmake toolchain for Vita and / or Windows.
add_subdirectory(lib)

project(${NEX_APP_EXECUTABLE})
add_executable(
    ${PROJECT_NAME}
        "src/entry.cpp"
        "src/main.cpp"
        "src/menu.cpp"
        "src/newspaper.cpp"
        "src/nightloader.cpp"
        "src/office.cpp"
        "src/objects/cursor.cpp"
        "src/objects/menu/background.cpp"
        "src/objects/menu/manager.cpp"
        "src/objects/office/call.cpp"
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

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
		nex
)
include("lib/nexgl/cmake/app_post.cmake")
