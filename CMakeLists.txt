set(CMAKE_EXPORT_COMPILE_COMMANDS on)
project(Gryphn)

add_compile_definitions(GN_REVEAL_IMPL)

add_library(Gryphn INTERFACE)
if (UNIX AND NOT APPLE)
    add_compile_definitions(
        GN_PLATFORM_LINUX
        GN_WINDOW_X11

        GN_API_VULKAN GN_API_OPENGL
    )
    add_subdirectory(projects/apis/vulkan/)
    add_subdirectory(projects/apis/opengl/)
    set(VULKAN_BUILT ON)
    set(OPENGL_BUILT ON)
endif()
if (APPLE)
    add_compile_definitions(
        GN_PLATFORM_MACOS

        GN_API_VULKAN GN_API_METAL
    )
    add_subdirectory(projects/apis/vulkan/)
    add_subdirectory(projects/apis/metal/)

    set(VULKAN_BUILT ON)
    set(METAL_BUILT ON)
endif()
add_subdirectory(projects/utils)
add_subdirectory(projects/loader) # build gryphn loader
add_subdirectory(projects/core) # build gryphn core
add_subdirectory(projects/extensions)
add_subdirectory(projects/platform) # build gryphn platform
add_subdirectory(projects/validation_layers/function_loader/)
target_link_libraries(Gryphn INTERFACE GryphnUtils GryphnCore GryphnLoader GryphnPlatform GryphnFunctionValidator GryphnExtensions)

if (VULKAN_BUILT)
    target_link_libraries(Gryphn INTERFACE GryphnVulkanImpl)
endif()
if (METAL_BUILT)
    target_link_libraries(Gryphn INTERFACE GryphnMetalImpl)
endif()
if (OPENGL_BUILT)
    target_link_libraries(Gryphn INTERFACE GryphnOpenGLImpl)
endif()
