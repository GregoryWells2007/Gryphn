#include "gryphn_graphics_pipeline.h"
#include "instance/gryphn_instance.h"

gnReturnCode gnCreateGraphicsPipeline(gnGraphicsPipelineHandle* graphicsPipeline, gnDevice device, gnGraphicsPipelineInfo info) {
    *graphicsPipeline = malloc(sizeof(struct gnGraphicsPipeline_t));
    (*graphicsPipeline)->device = device;
    (*graphicsPipeline)->info = info;
    return device->instance->callingLayer->deviceFunctions._gnCreateGraphicsPipeline(*graphicsPipeline, device, info);
}

void gnDestroyGraphicsPipeline(gnGraphicsPipelineHandle graphicsPipeline) {
    graphicsPipeline->device->instance->callingLayer->deviceFunctions._gnDestroyGraphicsPipeline(graphicsPipeline);
}
