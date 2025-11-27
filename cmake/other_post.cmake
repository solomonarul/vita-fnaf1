message(STATUS "Linking with system libraries.")
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        GL
)

if(EMSCRIPTEN)
    install(
        FILES
            ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.js
            ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.data
            ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.wasm
            ${CMAKE_SOURCE_DIR}/platform/web/favicon.ico
            ${CMAKE_SOURCE_DIR}/platform/web/index.html
        DESTINATION web
    )

    set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES LINK_FLAGS
            "-sUSE_SDL=3 -sALLOW_MEMORY_GROWTH=1 --preload-file ${CMAKE_SOURCE_DIR}/assets@/assets"
    )
else()
    install(
        DIRECTORY ${CMAKE_SOURCE_DIR}/assets
        DESTINATION bin
    )
endif()