set(CMAKE_EXPORT_COMPILE_COMMANDS on)
project(GryphnVulkanImpl)
add_compile_definitions(GN_REVEAL_IMPL)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.c" "src/*.h")
file(GLOB_RECURSE LOADER_FILES CONFIGURE_DEPENDS "loader/*.c" "loader/*.h")
if (APPLE)
    file(GLOB_RECURSE METAL_FILES CONFIGURE_DEPENDS "src/*.m")
endif()

find_package(Vulkan REQUIRED)
add_library(GryphnVulkanImpl STATIC ${SOURCE_FILES} ${METAL_FILES} ${LOADER_FILES})
target_link_libraries(GryphnVulkanImpl ${Vulkan_LIBRARY})

target_include_directories(GryphnVulkanImpl PUBLIC
    ${Vulkan_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../utils/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../platform/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/
)

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
