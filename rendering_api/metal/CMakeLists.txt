set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 17)
project(GryphnMetalImpl)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "src/*.cpp" "src/*.hpp"
    "src/*.c" "src/*.h"
    "src/*.mm" "src/*.m"
)
add_library(GryphnMetalImpl SHARED ${SOURCE_FILES})
target_include_directories(GryphnMetalImpl PUBLIC
    ${CMAKE_SOURCE_DIR}/gryphn/include/
    ${CMAKE_SOURCE_DIR}/gryphn/src/
    ${CMAKE_SOURCE_DIR}/gryphn/src/
    src/
    depends/SPIRV-Cross/
)
# target_link_options(GryphnMetalImpl PRIVATE -rdynamic)
add_compile_definitions(GN_REVEAL_IMPL)
add_subdirectory(depends/SPIRV-Cross)

target_link_libraries(GryphnMetalImpl spirv-cross-core spirv-cross-msl spirv-cross-c)

target_link_libraries(GryphnMetalImpl
    "-framework IOKit"
    "-framework CoreFoundation"
    "-framework CoreGraphics"
    "-framework Foundation"
    "-framework Metal"
    "-framework QuartzCore"
)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/gryphn/rendering_apis)
add_custom_command(TARGET GryphnMetalImpl POST_BUILD
    COMMAND mv libGryphnMetalImpl.dylib ../../rendering_apis/GryphnMetalImpl.dylib
)
