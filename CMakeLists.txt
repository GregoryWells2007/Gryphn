set(CMAKE_EXPORT_COMPILE_COMMANDS on)
project(Gryphn)

add_compile_definitions(GN_PLATFORM_LINUX GN_WINDOW_X11 GN_REVEAL_IMPL)

add_subdirectory(projects/loader) # build gryphn loader
add_subdirectory(projects/core/) # build gryphn core
add_subdirectory(projects/apis/vulkan/)

add_library(Gryphn INTERFACE)
target_link_libraries(Gryphn INTERFACE GryphnCore GryphnLoader GryphnVulkanImpl)

# set(CMAKE_EXPORT_COMPILE_COMMANDS on)
# project(Gryphn)
# add_library(Gryphn STATIC "")

# # build gryphn core
# add_subdirectory(src/core/)
# target_link_libraries(Gryphn GryphnCore)

# # build the selected apis
# if(WIN32)
#     add_compile_definitions(GN_PLATFORM_WIN32)
#     add_subdirectory(src/apis/vulkan/)

#     target_link_libraries(Gryphn GryphnVulkanImpl)
# endif()
# if(APPLE)
#     add_compile_definitions(GN_PLATFORM_MACOS)
#     add_subdirectory(src/apis/metal/)
#     add_subdirectory(src/apis/vulkan/)

#     target_link_libraries(Gryphn
#         "-framework IOKit"
#         "-framework CoreFoundation"
#         "-framework CoreGraphics"
#         "-framework AppKit"
#         "-framework Metal"
#         "-framework QuartzCore"
#         "-framework MetalKit"
#     )

#     target_link_libraries(Gryphn GryphnVulkanImpl GryphnMetalImpl)
# endif()
# if(UNIX AND NOT APPLE)
#     add_compile_definitions(GN_PLATFORM_LINUX)
#     add_compile_definitions(GN_WINDOW_X11)
#     add_subdirectory(src/apis/vulkan/)

#     target_link_libraries(Gryphn GryphnVulkanImpl)
# endif()
