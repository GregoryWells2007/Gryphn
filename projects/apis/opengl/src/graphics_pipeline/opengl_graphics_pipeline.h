#pragma once
#include "glad/glad.h"
#include "core/src/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"

typedef struct gnPlatformGraphicsPipeline_t {
    GLuint program;

    GLuint vertexArrayObject;
    GLsizei stride;
} gnPlatformGraphicsPipeline;

gnReturnCode openglCreateGraphicsPipeline(gnGraphicsPipeline graphicsPipeline, gnOutputDevice device, gnGraphicsPipelineInfo info);
void openglDestroyGraphicsPipeline(gnGraphicsPipeline graphicsPipeline);
