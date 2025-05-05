#include "gryphn_sampler.h"

void gnSamplerUniformSetTexture(gnSamplerUniform& samplerUniform, const gnTexture& texture) {
    samplerUniform.texture = const_cast<gnTexture*>(&texture);
}
void gnSamplerUniformSetTexture(gnSamplerUniform& samplerUniform, const gnTexture* texture) {
    samplerUniform.texture = texture;
}
void gnSamplerUniformSetBinding(gnSamplerUniform& samplerUniform, gnUInt binding) {
    samplerUniform.binding = binding;
}
void gnSamplerUniformSetUniformIndex(gnSamplerUniform& samplerUniform, gnUInt index) {
    samplerUniform.index = index;
}
void gnSamplerUniformSetUniform(gnSamplerUniform& samplerUniform, const gnUniform& uniformDescriptor) {
    samplerUniform.uniform = const_cast<gnUniform*>(&uniformDescriptor);
}
