set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 17)
project(GryphnVulkanImpl)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "src/*.cpp" "src/*.hpp"
    "src/*.c" "src/*.h"
)

if (APPLE)
    file(GLOB_RECURSE METAL_FILES CONFIGURE_DEPENDS
    "src/*.m"
)
endif()

find_package(Vulkan REQUIRED)
add_library(GryphnVulkanImpl SHARED ${SOURCE_FILES} ${METAL_FILES})
target_include_directories(GryphnVulkanImpl PUBLIC
    ${Vulkan_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/utils/
    src/
)
add_compile_definitions(GN_REVEAL_IMPL)
target_link_libraries(GryphnVulkanImpl ${Vulkan_LIBRARY})

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

if (APPLE)
    add_custom_command(TARGET GryphnVulkanImpl POST_BUILD
        COMMAND mv libGryphnVulkanImpl.dylib
        ${CMAKE_BINARY_DIR}/gryphn/rendering_apis/GryphnVulkanImpl.dylib
    )
endif()
if (UNIX AND NOT APPLE)
    add_custom_command(TARGET GryphnVulkanImpl POST_BUILD
        COMMAND mv libGryphnVulkanImpl.so
        ${CMAKE_BINARY_DIR}/gryphn/rendering_apis/GryphnVulkanImpl.so
    )
endif()
