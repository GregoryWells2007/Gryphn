#include "gryphn_graphics_pipeline.h"
#include "gryphn_platform_functions.h"

gnReturnCode gnCreateGraphicsPipeline(gnGraphicsPipelineHandle* graphicsPipeline, gnDevice device, gnGraphicsPipelineInfo info) {
    *graphicsPipeline = malloc(sizeof(struct gnGraphicsPipeline_t));
    (*graphicsPipeline)->device = device;
    (*graphicsPipeline)->info = info;
    return device->deviceFunctions->_gnCreateGraphicsPipeline(*graphicsPipeline, device, info);
}

void gnDestroyGraphicsPipeline(gnGraphicsPipelineHandle graphicsPipeline) {
    graphicsPipeline->device->deviceFunctions->_gnDestroyGraphicsPipeline(graphicsPipeline);
}
