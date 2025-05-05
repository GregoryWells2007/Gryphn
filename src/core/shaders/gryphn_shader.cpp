#include "gryphn_shader.h"

void gnShaderAddModule(gnShader& shader, gnShaderModule& module) { gnListAdd(shader.shaderModules, module); }
