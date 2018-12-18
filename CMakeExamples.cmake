macro(add_example_target EXAMPLE_TARGET EXAMPLE_FILE)
    add_executable(${EXAMPLE_TARGET} ${EXAMPLE_FILE})
    target_include_directories(${EXAMPLE_TARGET} PUBLIC src)
    target_link_libraries(${EXAMPLE_TARGET} ${OPENGL_LIBRARIES} ${SFML_LIBRARIES} ${OpenCV_LIBS})
    target_compile_definitions(${EXAMPLE_TARGET} PRIVATE __EXAMPLE_TARGET__="${EXAMPLE_TARGET}")
endmacro(add_example_target)

file(WRITE run_all_examples.sh "#!/usr/bin/env bash\n\n")

macro(add_example_directory EXAMPLE_DIRECTORY)
    file(GLOB_RECURSE EXAMPLE_FILES "${EXAMPLE_DIRECTORY}/*.cpp" "${EXAMPLE_DIRECTORY}/*.c++" "${EXAMPLE_DIRECTORY}/*.cc" "${EXAMPLE_DIRECTORY}/*.c")
    foreach (EXAMPLE_FILE IN LISTS EXAMPLE_FILES)
        get_filename_component(EXAMPLE_TARGET ${EXAMPLE_FILE} NAME_WE)
        message(STATUS "Example target: ${EXAMPLE_TARGET}")
        add_example_target(${EXAMPLE_TARGET} ${EXAMPLE_FILE})

        file(APPEND run_all_examples.sh "echo\n")
        file(APPEND run_all_examples.sh "echo \"-------------------------------------------------\"\n")
        file(APPEND run_all_examples.sh "echo \"    Starting ${EXAMPLE_TARGET}\"\n")
        file(APPEND run_all_examples.sh "echo \"-------------------------------------------------\"\n")
        file(APPEND run_all_examples.sh "${CMAKE_BINARY_DIR}/${EXAMPLE_TARGET}\n")
        file(APPEND run_all_examples.sh "\n")
    endforeach (EXAMPLE_FILE)
endmacro(add_example_directory)