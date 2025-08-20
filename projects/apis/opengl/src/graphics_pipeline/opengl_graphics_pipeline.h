#pragma once
#include "glad/glad.h"
#include "core/src/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#include "shaders/opengl_shader_compiler.h"


typedef struct gnPlatformGraphicsPipeline_t {
    glSet setMap[MAX_OPENGL_SETS];
    GLuint program;

    GLuint vertexArrayObject;
    GLsizei stride;
} gnPlatformGraphicsPipeline;

gnReturnCode openglCreateGraphicsPipeline(gnGraphicsPipeline graphicsPipeline, gnOutputDevice device, gnGraphicsPipelineInfo info);
void openglDestroyGraphicsPipeline(gnGraphicsPipeline graphicsPipeline);
