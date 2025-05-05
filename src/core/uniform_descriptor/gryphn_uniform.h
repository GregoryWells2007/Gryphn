#pragma once
#include <gryphn/gryphn_utils.h>
#include "gryphn_uniform_layout.h"

struct gnPlatformUniform;

struct gnUniform {
ACCESS_LEVEL:
    gnPlatformUniform* uniform = nullptr;
    gnUniformLayout* uniformLayout;
    int descriptorCount;
public:
    gnUniform() {}
};

void gnUniformSetCount(gnUniform& uniform, gnUInt count);
void gnUniformSetLayout(gnUniform& uniform, gnUniformLayout* uniformLayout);
inline gnReturnCode (*gnCreateUniform)(gnUniform* uniform, gnOutputDevice& outputDevice);
inline void (*gnDestroyUniform)(gnUniform& uniform);
