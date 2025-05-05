#include "gryphn_uniform_layout.h"

void gnUniformLayoutBindingSetBinding(gnUniformLayoutBinding& uniformLayoutBinding, gnUInt binding) {
    uniformLayoutBinding.binding = binding;
}
void gnUniformLayoutBindingSetShaderStage(gnUniformLayoutBinding& uniformLayoutBinding, gnShaderModuleStage stage) {
    uniformLayoutBinding.stage = stage;
}
void gnUniformLayoutBindingSetType(gnUniformLayoutBinding& uniformLayoutBinding, gnUniformLayoutBindingType type) {
    uniformLayoutBinding.type = type;
}

void gnUniformLayoutAddBinding(gnUniformLayout& uniformLayout, gnUniformLayoutBinding binding) {
    uniformLayout.bindings.push_back(binding);
}


std::vector<gnUniformLayoutBinding> gnUniformLayoutGetBindings(gnUniformLayout& uniformLayout) {
    return uniformLayout.bindings;
}
