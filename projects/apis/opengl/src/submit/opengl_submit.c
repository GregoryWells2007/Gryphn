#include "core/src/submit/gryphn_submit.h"
#include "commands/buffers/opengl_command_buffer.h"

gnReturnCode openglSubmit(gnOutputDevice device, gnSubmitInfo info) {
    if (device == GN_NULL_HANDLE) return GN_INVALID_HANDLE;

    for (uint32_t i = 0; i < info.commandBufferCount; i++)
        openglRunCommandRunner(info.commandBuffers[i]->commandBuffer->commmandRunner);

    return GN_SUCCESS;
}
