cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.h")

add_executable(MeanShift "${SRC_FILES}")