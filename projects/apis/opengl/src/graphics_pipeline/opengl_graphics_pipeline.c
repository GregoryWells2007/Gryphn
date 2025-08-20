#include "opengl_graphics_pipeline.h"
#include "core/src/instance/gryphn_instance.h"
#include "shaders/opengl_shader_module.h"
#include "stdio.h"

gnReturnCode openglCreateGraphicsPipeline(gnGraphicsPipeline graphicsPipeline, gnOutputDevice device, gnGraphicsPipelineInfo info) {
    graphicsPipeline->graphicsPipeline = malloc(sizeof(gnPlatformGraphicsPipeline));

    GLuint* ids = malloc(sizeof(GLuint) * info.shaderModuleCount);
    for (int i = 0; i < info.shaderModuleCount; i++) {
        glShader shader = glCompilerCompilerShader(info.shaderModules[i]->shaderModule->compiler, &info.uniformLayout);
        if (i == 0)
            for (int set = 0; set < MAX_OPENGL_SETS; set++)
                for (int binding = 0; binding < MAX_OPENGL_BINDINGS; binding++)
                    graphicsPipeline->graphicsPipeline->setMap[set].bindings[binding] = shader.sets[set].bindings[binding];

        ids[i] = glCreateShader(gnShaderTypeToGLEnum(info.shaderModules[i]->info.stage));
        const char* source = shader.source;
        printf("Shader Source %s\n", source);
        glShaderSource(ids[i], 1, &source, NULL);
        glCompileShader(ids[i]);

        GLint returnCode;
        glGetShaderiv(ids[i], GL_COMPILE_STATUS, &returnCode);
        if(!returnCode) {
            char infoLog[512];
            glGetShaderInfoLog(ids[i], 512, NULL, infoLog);
            gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
                .message = gnCreateString(infoLog)
            });
        }
    }

    graphicsPipeline->graphicsPipeline->program = glCreateProgram();
    for (int i = 0; i < info.shaderModuleCount; i++)
        glAttachShader(graphicsPipeline->graphicsPipeline->program, ids[i]);
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

    for (int i = 0; i < info.shaderModuleCount; i++)
        glDeleteShader(ids[i]);

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
