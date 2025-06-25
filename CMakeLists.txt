set(CMAKE_EXPORT_COMPILE_COMMANDS on)
project(Gryphn)

add_compile_definitions(GN_REVEAL_IMPL)

add_subdirectory(projects/loader) # build gryphn loader
add_subdirectory(projects/core) # build gryphn core
add_subdirectory(projects/platform) # build gryphn platform
add_library(Gryphn INTERFACE)
if (UNIX AND NOT APPLE)
    add_compile_definitions(GN_PLATFORM_LINUX GN_WINDOW_X11)
    add_subdirectory(projects/apis/vulkan/)
    target_link_libraries(Gryphn INTERFACE GryphnVulkanImpl)
endif()
if (APPLE)
    add_compile_definitions(GN_PLATFORM_MACOS)
    add_subdirectory(projects/apis/vulkan/)
    target_link_libraries(Gryphn INTERFACE GryphnVulkanImpl)
endif()
target_link_libraries(Gryphn INTERFACE GryphnCore GryphnLoader GryphnPlatform)
