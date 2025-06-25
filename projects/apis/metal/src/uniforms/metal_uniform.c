#include <uniforms/gryphn_uniform.h>
#include "metal_uniform.h"

void gnUpdateBufferUniformFn(gnUniform uniform, gnBufferUniformInfo* info) {
    for (int i = 0; i < uniform->uniform->bindingCount; i++) {
        if (uniform->uniform->bindings[i].binding == info->binding) {
            uniform->uniform->bindings[i].data = malloc(sizeof(gnBufferUniformInfo));
            memcpy(uniform->uniform->bindings[i].data, info, sizeof(gnBufferUniformInfo));
            break;
        }
    }
}
