set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 17)
project(GryphnOpenGLImpl)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "src/*.c" "src/*.cpp"
)
file(GLOB_RECURSE LOADER_FILES CONFIGURE_DEPENDS
    "loader/*.c"
)
add_library(GryphnOpenGLImpl STATIC ${SOURCE_FILES} ${LOADER_FILES} depends/glad/src/glad.c)
target_include_directories(GryphnOpenGLImpl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../extensions/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../utils/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../platform/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/
)
add_subdirectory(depends/SPIRV-Cross)
target_include_directories(GryphnOpenGLImpl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/depends/glad/include/
)
add_compile_definitions(GN_REVEAL_IMPL)
target_link_libraries(GryphnOpenGLImpl GL "X11" spirv-cross-core spirv-cross-glsl spirv-cross-cpp)
