project (glad LANGUAGES C)

set(CURRENT_DIR "${CMAKE_SOURCE_DIR}/Thirdparty/glad")
file(GLOB_RECURSE SRC_FILES "${CURRENT_DIR}/*.h" "${CURRENT_DIR}/*.c")

add_library(glad ${SRC_FILES})

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)
