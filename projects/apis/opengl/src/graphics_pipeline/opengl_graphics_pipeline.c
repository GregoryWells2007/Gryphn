#include "opengl_graphics_pipeline.h"
#include "shaders/opengl_shader_module.h"

gnReturnCode openglCreateGraphicsPipeline(gnGraphicsPipeline graphicsPipeline, gnOutputDevice device, gnGraphicsPipelineInfo info) {
    graphicsPipeline->graphicsPipeline = malloc(sizeof(gnPlatformGraphicsPipeline));
    graphicsPipeline->graphicsPipeline->program = glCreateProgram();
    for (int i = 0; i < info.shaderModuleCount; i++) {
        glAttachShader(graphicsPipeline->graphicsPipeline->program, info.shaderModules[i]->shaderModule->id);
    }
    glLinkProgram(graphicsPipeline->graphicsPipeline->program);
    return GN_SUCCESS;
}
void openglDestroyGraphicsPipeline(gnGraphicsPipeline graphicsPipeline) {
    glDeleteProgram(graphicsPipeline->graphicsPipeline->program);
    free(graphicsPipeline->graphicsPipeline);
}
