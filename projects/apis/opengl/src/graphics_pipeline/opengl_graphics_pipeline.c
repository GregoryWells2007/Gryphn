#include "opengl_graphics_pipeline.h"
#include "shaders/opengl_shader_module.h"
#include "core/src/instance/gryphn_instance.h"

#include "stdio.h"

gnReturnCode openglCreateGraphicsPipeline(gnGraphicsPipeline graphicsPipeline, gnOutputDevice device, gnGraphicsPipelineInfo info) {
    graphicsPipeline->graphicsPipeline = malloc(sizeof(gnPlatformGraphicsPipeline));
    graphicsPipeline->graphicsPipeline->program = glCreateProgram();
    for (int i = 0; i < info.shaderModuleCount; i++)
        glAttachShader(graphicsPipeline->graphicsPipeline->program, info.shaderModules[i]->shaderModule->id);
    glLinkProgram(graphicsPipeline->graphicsPipeline->program);
    GLint linked;
    glGetProgramiv(graphicsPipeline->graphicsPipeline->program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLchar infoLog[512];
        glGetProgramInfoLog(graphicsPipeline->graphicsPipeline->program, 512, NULL, infoLog);
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCreateString(infoLog)
        });
    } else {
        gnDebuggerSetVerboseMessage(&device->instance->debugger, (gnMessageData){
            .message = gnCreateString("Successfully linked program")
        });
    }

    glCreateVertexArrays(1, &graphicsPipeline->graphicsPipeline->vertexArrayObject);

    glVertexArrayAttribFormat(graphicsPipeline->graphicsPipeline->vertexArrayObject, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(graphicsPipeline->graphicsPipeline->vertexArrayObject, 0, 0);

    // Attribute 1: texcoord (2 floats)
    glVertexArrayAttribFormat(graphicsPipeline->graphicsPipeline->vertexArrayObject, 1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*3);
    glVertexArrayAttribBinding(graphicsPipeline->graphicsPipeline->vertexArrayObject, 1, 0);

    // Attribute 2: color (3 floats)
    glVertexArrayAttribFormat(graphicsPipeline->graphicsPipeline->vertexArrayObject, 2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5);
    glVertexArrayAttribBinding(graphicsPipeline->graphicsPipeline->vertexArrayObject, 2, 0);

    graphicsPipeline->graphicsPipeline->stride = (sizeof(float) * 8);

    // Enable them
    glEnableVertexArrayAttrib(graphicsPipeline->graphicsPipeline->vertexArrayObject, 0);
    glEnableVertexArrayAttrib(graphicsPipeline->graphicsPipeline->vertexArrayObject, 1);
    glEnableVertexArrayAttrib(graphicsPipeline->graphicsPipeline->vertexArrayObject, 2);

    return GN_SUCCESS;
}
void openglDestroyGraphicsPipeline(gnGraphicsPipeline graphicsPipeline) {
    glDeleteProgram(graphicsPipeline->graphicsPipeline->program);
    free(graphicsPipeline->graphicsPipeline);
}
