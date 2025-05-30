#include "gryphn_graphics_pipeline.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreateGraphicsPipeline(struct gnGraphicsPipeline_t* graphicsPipeline, struct gnOutputDevice_t* device, struct gnGraphicsPipelineInfo_t info) {
    graphicsPipeline->device = device;
    graphicsPipeline->info = info;
    return graphicsPipeline->device->deviceFunctions->_gnCreateGraphicsPipeline(graphicsPipeline, device, info);
}

void gnDestroyGraphicsPipeline(struct gnGraphicsPipeline_t* graphicsPipeline) {
    graphicsPipeline->device->deviceFunctions->_gnDestroyGraphicsPipeline(graphicsPipeline);
}
