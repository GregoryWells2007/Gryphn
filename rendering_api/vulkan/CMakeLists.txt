set(CMAKE_EXPORT_COMPILE_COMMANDS on)
project(GryphnVulkanImpl)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "src/*.cpp" "src/*.hpp"
    "src/*.c" "src/*.h"
)
add_library(GryphnVulkanImpl SHARED ${SOURCE_FILES})
target_include_directories(GryphnVulkanImpl PUBLIC
    ${CMAKE_SOURCE_DIR}/gryphn/include/
    ${CMAKE_SOURCE_DIR}/gryphn/src/
    ${CMAKE_SOURCE_DIR}/gryphn/src/
    ${CMAKE_SOURCE_DIR}/depends/glfw/glfw-3.4/include/
    src/
    /Applications/vulkansdk/macOS/include/
)
add_compile_definitions(GN_REVEAL_IMPL)

add_library(glfw SHARED IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/build/depends/glfw/glfw-3.4/src/libglfw.3.4.dylib)

add_library(libvulkan SHARED IMPORTED)
set_target_properties(libvulkan PROPERTIES IMPORTED_LOCATION /Applications/vulkansdk/macOS/lib/libvulkan.dylib)

target_link_libraries(GryphnVulkanImpl glfw libvulkan)

target_link_libraries(GryphnVulkanImpl
    "-framework IOKit"
    "-framework CoreFoundation"
    "-framework CoreGraphics"
    "-framework AppKit"
)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/gryphn/rendering_apis)
add_custom_command(TARGET GryphnVulkanImpl POST_BUILD
    COMMAND mv libGryphnVulkanImpl.dylib ../../rendering_apis/GryphnVulkanImpl.dylib
)
