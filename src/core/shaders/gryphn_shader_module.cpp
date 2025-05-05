#include "gryphn_shader_module.h"

void gnSetShaderModuleType(gnShaderModule& module, gnShaderModuleStage shaderModuleType) {
    module.shaderType = shaderModuleType;
}
void gnSetShaderModuleUse(gnShaderModule& module, gnShaderUse shaderUse) {
    module.shaderUse = shaderUse;
}
void gnSetShaderModuleCode(gnShaderModule& module, gnList<gnByte>& shaderModuleCode) {
    module.codeSize = gnListLength(shaderModuleCode);
    module.shaderData = gnListData(shaderModuleCode);
}
void gnSetShaderModuleCode(gnShaderModule& module, gnList<gnByte> shaderModuleCode) {
    module.codeSize = gnListLength(shaderModuleCode);
    module.shaderData = gnListData(shaderModuleCode);
}

void gnSetShaderModuleCode(gnShaderModule& module, const std::vector<char>& shaderModuleCode) {
    module.codeSize = shaderModuleCode.size();
    module.shaderData = const_cast<gnChar*>(shaderModuleCode.data());
}

gnBool gnContainsShaderStage(gnShaderModuleStage stage, gnShaderModuleStage stageToContain);
