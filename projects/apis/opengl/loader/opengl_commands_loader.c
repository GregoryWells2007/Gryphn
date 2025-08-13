#include "opengl_loader.h"
#include "commands/buffers/opengl_command_buffer.h"

gnCommandFunctions loadOpenGLCommandFunctions() {
    return (gnCommandFunctions) {
        ._gnCommandPoolAllocateCommandBuffers = openglCommandPoolAllocateCommandBuffers
    };
}
