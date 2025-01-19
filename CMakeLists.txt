cmake_minimum_required(VERSION 3.5.0)

project(MeanShift)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/Thirdparty/glfw/include"
    "${CMAKE_SOURCE_DIR}/Thirdparty/glad/include"
    "${CMAKE_SOURCE_DIR}/Thirdparty/stb_image"
)

# Source files
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.h")

# Add third-party dependencies
add_subdirectory("${CMAKE_SOURCE_DIR}/Thirdparty/glfw")
add_subdirectory("${CMAKE_SOURCE_DIR}/Thirdparty/glad")
add_subdirectory("${CMAKE_SOURCE_DIR}/Thirdparty/stb_image")

# Add executable
add_executable(MeanShift "${SRC_FILES}")

# Link libraries
target_link_libraries(MeanShift glfw glad stb_image)

# Assets folder configuration
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/Assets)
set(ASSETS_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Assets)

# Copy assets folder to the build directory after build
add_custom_command(
    TARGET MeanShift POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR} ${ASSETS_OUTPUT_DIR}
    COMMENT "Copying assets folder to build directory"
)
