set(CMAKE_EXPORT_COMPILE_COMMANDS on)
project(GryphnLoader)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.c")
add_library(GryphnLoader STATIC ${SOURCE_FILES})
