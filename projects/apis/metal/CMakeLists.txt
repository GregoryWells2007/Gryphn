set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 17)
project(GryphnMetalImpl)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "src/*.c" "src/*.h" "src/*.m"
)
add_library(GryphnMetalImpl STATIC ${SOURCE_FILES})
target_include_directories(GryphnMetalImpl PUBLIC
    ${CMAKE_SOURCE_DIR}/gryphn/include/
    ${CMAKE_SOURCE_DIR}/gryphn/src/
    ${CMAKE_SOURCE_DIR}/gryphn/src/utils/
    src/
    depends/SPIRV-Cross/
)
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
