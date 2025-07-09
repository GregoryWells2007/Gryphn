set(CMAKE_EXPORT_COMPILE_COMMANDS on)
project(GryphnLoader)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.c")
add_library(GryphnLoader STATIC ${SOURCE_FILES})
target_include_directories(GryphnLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../utils)
target_include_directories(GryphnLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_include_directories(GryphnLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../core/src/)
target_include_directories(GryphnLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../core/)
