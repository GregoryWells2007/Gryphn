#pragma once
#include <gryphn/gryphn_utils.h>
#include "gryphn_shader_module.h"

struct gnPlatformShader;

struct gnShader {
ACCESS_LEVEL:
    gnPlatformShader* shader;
    gnList<gnShaderModule> shaderModules = gnCreateList<gnShaderModule>();
public:
    gnShader() {}
};

void gnShaderAddModule(gnShader& shader, gnShaderModule& module);

inline gnReturnCode (*gnBuildShader)(gnShader* shader);
inline void (*gnShaderDestroyModules)(gnShader& shader);
