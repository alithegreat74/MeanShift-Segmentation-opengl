cmake_minimum_required(VERSION 3.5.0)

project(MeanShift)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/Thirdparty/glfw/include"
	"${CMAKE_SOURCE_DIR}/Thirdparty/glad/include"
)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.h")

add_subdirectory("${CMAKE_SOURCE_DIR}/Thirdparty/glfw")
add_subdirectory("${CMAKE_SOURCE_DIR}/Thirdparty/glad")

add_executable(MeanShift "${SRC_FILES}")

target_link_libraries(MeanShift glfw glad)