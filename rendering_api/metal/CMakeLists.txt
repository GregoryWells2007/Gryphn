set(CMAKE_EXPORT_COMPILE_COMMANDS on)
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
    ${CMAKE_SOURCE_DIR}/depends/glfw/glfw-3.4/include/
    depends/metal-cpp/
    src/
    depends/SPIRV-Cross/
)
# target_link_options(GryphnMetalImpl PRIVATE -rdynamic)
add_compile_definitions(GN_REVEAL_IMPL)
add_subdirectory(depends/metal-cpp)

add_library(glfw SHARED IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/build/depends/glfw/glfw-3.4/src/libglfw.dylib)

target_link_libraries(GryphnMetalImpl METAL_CPP glfw spirv-cross-core spirv-cross-msl spirv-cross-cpp)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/gryphn/rendering_apis)
add_custom_command(TARGET GryphnMetalImpl POST_BUILD
    COMMAND mv libGryphnMetalImpl.dylib ../../rendering_apis/GryphnMetalImpl.dylib
)
