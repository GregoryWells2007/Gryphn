set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 17)
project(GryphnVulkanImpl)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "src/*.cpp" "src/*.hpp"
    "src/*.c" "src/*.h"
)

if (APPLE)
    file(GLOB_RECURSE METAL_FILES CONFIGURE_DEPENDS
    "src/*.mm"
)
endif()

add_library(GryphnVulkanImpl SHARED ${SOURCE_FILES} ${METAL_FILES})
target_include_directories(GryphnVulkanImpl PUBLIC
    ${CMAKE_SOURCE_DIR}/gryphn/include/
    ${CMAKE_SOURCE_DIR}/gryphn/src/
    ${CMAKE_SOURCE_DIR}/gryphn/src/
    src/
    /Applications/vulkansdk/macOS/include/
)
add_compile_definitions(GN_REVEAL_IMPL)

add_library(libvulkan SHARED IMPORTED)
set_target_properties(libvulkan PROPERTIES IMPORTED_LOCATION /Applications/vulkansdk/macOS/lib/libvulkan.dylib)

target_link_libraries(GryphnVulkanImpl libvulkan)

if(WIN32)
    add_compile_definitions(GN_PLATFORM_WIN32)
endif()
if(APPLE)

    target_link_libraries(GryphnVulkanImpl
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework CoreGraphics"
        "-framework AppKit"
        "-framework Metal"
        "-framework QuartzCore"
    )

    add_compile_definitions(GN_PLATFORM_MACOS)
endif()
if(UNIX AND NOT APPLE)
    add_compile_definitions(GN_PLATFORM_LINUX)
endif()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/gryphn/rendering_apis)
add_custom_command(TARGET GryphnVulkanImpl POST_BUILD
    COMMAND mv libGryphnVulkanImpl.dylib ../../rendering_apis/GryphnVulkanImpl.dylib
)
