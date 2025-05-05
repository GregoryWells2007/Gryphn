#include "core/uniform_descriptor/uniform_buffer/gryphn_uniform_buffer.h"

GN_EXPORT void gnUpdateBufferUniformFn(gnBufferUniform& uniformBuffer, const gnOutputDevice& outputDevice) {
    if (uniformBuffer.uniform->uniformLayout->bindings[uniformBuffer.binding].type != GN_UNIFORM_BUFFER_DESCRIPTOR) {
        std::cout << "uniform layout [" << uniformBuffer.binding << "] is of type GN_SAMPLER_DESCRIPTOR but calling gnUpdateBufferUniform\n";
    }
}
