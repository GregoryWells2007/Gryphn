#include "gryphn_push_constant.h"

void gnPushConstantSetShaderStage(gnPushConstant& pushConstant, gnShaderModuleStage stage) {
    pushConstant.stage = stage;
}
void gnPushConstantSetOffset(gnPushConstant& pushConstant, gnSize offset){
    pushConstant.offset = offset;
}
void gnPushConstantSetSize(gnPushConstant& pushConstant, gnSize size) {
    pushConstant.size = size;
}
