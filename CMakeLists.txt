set(CMAKE_EXPORT_COMPILE_COMMANDS on)
project(Gryphn)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "src/*.cpp" "src/*.hpp"
    "src/*.c" "src/*.h"
)
if(APPLE)

file(GLOB_RECURSE METAL_FILES CONFIGURE_DEPENDS
    "src/*.m")

endif()
add_library(Gryphn ${SOURCE_FILES} ${METAL_FILES})
target_include_directories(Gryphn PUBLIC ${CMAKE_SOURCE_DIR}/gryphn/src/)
target_include_directories(Gryphn PUBLIC ${CMAKE_SOURCE_DIR}/gryphn/include/)
target_include_directories(Gryphn PUBLIC ${CMAKE_SOURCE_DIR}/gryphn/src/utils)
target_include_directories(Gryphn PUBLIC ${CMAKE_SOURCE_DIR}/gryphn/src/utils/utils)
add_compile_definitions(GN_REVEAL_IMPL)

if(WIN32)
    add_compile_definitions(GN_PLATFORM_WIN32)
    # add_subdirectory(rendering_api/dirctx/)
    add_subdirectory(rendering_api/vulkan/)
endif()
if(APPLE)
    add_compile_definitions(GN_PLATFORM_MACOS)
    add_subdirectory(rendering_api/metal/)
    add_subdirectory(rendering_api/vulkan/)

    target_link_libraries(Gryphn
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework CoreGraphics"
        "-framework AppKit"
        "-framework Metal"
        "-framework QuartzCore"
        "-framework MetalKit"
    )
endif()
if(UNIX AND NOT APPLE)
    add_compile_definitions(GN_PLATFORM_LINUX)
    add_subdirectory(rendering_api/vulkan/)
    target_include_directories(Gryphn PUBLIC ${CMAKE_SOURCE_DIR/Gryphn/rendering_api/metal/depends/metal-cpp/)
endif()

target_link_libraries(Gryphn)
