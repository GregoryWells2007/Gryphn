#include "core/uniform_descriptor/sampler/gryphn_sampler.h"

GN_EXPORT void gnUpdateSamplerUniformFn(gnSamplerUniform& samplerUniform, const gnOutputDevice& outputDevice) {
    if (samplerUniform.uniform->uniformLayout->bindings[samplerUniform.binding].type != GN_SAMPLER_DESCRIPTOR) {
        std::cout << "uniform layout [" << samplerUniform.binding << "] is of type GN_UNIFORM_BUFFER_DESCRIPTOR but calling gnUpdateSamplerUniform\n";
    }
}
