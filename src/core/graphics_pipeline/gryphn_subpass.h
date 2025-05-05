#pragma once
#include <gryphn/gryphn_utils.h>

struct gnPlatformSubpass;

// I only think that this is a thing in vulkan
//      - greg, march 11th 7:15
struct gnSubpass {
ACCESS_LEVEL:
    gnPlatformSubpass* subpass = nullptr;
public:
    gnSubpass() {}
};
