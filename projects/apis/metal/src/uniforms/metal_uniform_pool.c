#include <uniforms/gryphn_uniform_pool.h>
#include <uniforms/gryphn_uniform.h>
#include "metal_uniform.h"

gnReturnCode gnCreateUniformPoolFn(gnUniformPool pool, gnDeviceHandle device) {
    return GN_SUCCESS;
}

gnUniform* gnUniformPoolAllocateUniformsFn(gnUniformPool pool, const gnUniformAllocationInfo allocInfo) {
    gnUniform* uniforms = malloc(sizeof(gnUniform) * allocInfo.setCount);
    for (int i = 0; i < allocInfo.setCount; i++) {
        uniforms[i] = malloc(sizeof(struct gnUniform_t));
        uniforms[i]->uniform = malloc(sizeof(gnPlatformUniform));
        uniforms[i]->uniform->bindings = malloc(sizeof(metalUniformBinding) * allocInfo.sets[i].uniformBindingCount);
        for (int c = 0; c < allocInfo.sets[i].uniformBindingCount; c++) {
            uniforms[i]->uniform->bindings[c].type = allocInfo.sets[i].uniformBindings[c].type;
            uniforms[i]->uniform->bindings[c].binding = allocInfo.sets[i].uniformBindings[c].binding;
        }
    }
    return uniforms;
}

void gnDestroyUniformPoolFn(gnUniformPool pool) { }
