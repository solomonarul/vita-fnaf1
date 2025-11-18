message(STATUS "Linking with system libraries.")
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        GL
)