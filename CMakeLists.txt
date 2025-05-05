set(CMAKE_EXPORT_COMPILE_COMMANDS on)
project(Gryphn)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "src/*.cpp" "src/*.hpp"
    "src/*.c" "src/*.h"
)
add_library(Gryphn ${SOURCE_FILES})
target_include_directories(Gryphn PUBLIC ${CMAKE_SOURCE_DIR}/gryphn/src/)
target_include_directories(Gryphn PUBLIC ${CMAKE_SOURCE_DIR}/gryphn/include/)
add_compile_definitions(GN_REVEAL_IMPL)

if(WIN32)
    add_compile_definitions(GN_PLATFORM_WIN32)
    add_subdirectory(rendering_api/dirctx/)
    add_subdirectory(rendering_api/vulkan/)
endif()
if(APPLE)
    add_compile_definitions(GN_PLATFORM_MACOS)
    add_subdirectory(rendering_api/metal/)
    add_subdirectory(rendering_api/vulkan/)
endif()
if(UNIX AND NOT APPLE)
    add_compile_definitions(GN_PLATFORM_LINUX)
    add_subdirectory(rendering_api/vulkan/)
endif()

add_subdirectory(depends/SPIRV-Cross/)

target_link_libraries(Gryphn)
