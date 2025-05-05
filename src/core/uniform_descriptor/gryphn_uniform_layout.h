#pragma once
#include <gryphn/gryphn_utils.h>
#include "gryphn_uniform_layout_binding.h"

struct gnPlatformUniformLayout;

struct gnUniformLayout {
ACCESS_LEVEL:
    gnPlatformUniformLayout* uniformLayout = nullptr;
    std::vector<gnUniformLayoutBinding> bindings;
public:
    gnUniformLayout() {}
};

void gnUniformLayoutAddBinding(gnUniformLayout& uniformLayout, gnUniformLayoutBinding binding);
std::vector<gnUniformLayoutBinding> gnUniformLayoutGetBindings(gnUniformLayout& uniformLayout);
inline gnReturnCode (*gnCreateUniformLayout)(gnUniformLayout* uniformLayout, gnOutputDevice& device);
inline void (*gnDestroyUniformLayout)(gnUniformLayout& uniformLayout);
