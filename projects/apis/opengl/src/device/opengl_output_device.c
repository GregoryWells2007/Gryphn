#include "glad/glad.h"
#include "opengl_output_device.h"
#include "glsl_shader.glsl"
#include "stdlib.h"
#include "core/src/instance/gryphn_instance.h"

gnReturnCode createOpenGLOutputDevice(gnInstanceHandle instance, gnOutputDeviceHandle device, gnOutputDeviceInfo deviceInfo) {
    int  success;
    char infoLog[512];

    device->outputDevice = malloc(sizeof(gnPlatformOutputDevice));
    float vertices[] = {
        -1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f,  1.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
    };
    glCreateBuffers(1, &device->outputDevice->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, device->outputDevice->buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCreateString(infoLog)
        });
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCreateString(infoLog)
        });
    }

    device->outputDevice->shaderProgram = glCreateProgram();
    glAttachShader(device->outputDevice->shaderProgram, vertexShader);
    glAttachShader(device->outputDevice->shaderProgram, fragmentShader);
    glLinkProgram(device->outputDevice->shaderProgram);
    glGetProgramiv(device->outputDevice->shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(device->outputDevice->shaderProgram, 512, NULL, infoLog);
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCreateString(infoLog)
        });
    }

    return GN_SUCCESS;
}
void waitForOpenGLDevice(const gnOutputDeviceHandle device) {}
void destroyOpenGLOutputDevice(gnOutputDeviceHandle device) {}
