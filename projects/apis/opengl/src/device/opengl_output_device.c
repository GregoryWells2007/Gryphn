#include "glad/glad.h"
#include "opengl_output_device.h"
#include "glsl_shader.glsl"
#include "stdlib.h"

gnReturnCode createOpenGLOutputDevice(gnInstanceHandle instance, gnOutputDeviceHandle device, gnOutputDeviceInfo deviceInfo) {
    device->outputDevice = malloc(sizeof(gnPlatformOutputDevice));
    float vertices[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 0.0f,
    };
    glCreateBuffers(1, &device->outputDevice->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, device->outputDevice->buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragmentShader);

    device->outputDevice->shaderProgram = glCreateProgram();
    glAttachShader(device->outputDevice->shaderProgram, vertexShader);
    glAttachShader(device->outputDevice->shaderProgram, fragmentShader);
    glLinkProgram(device->outputDevice->shaderProgram);

    return GN_SUCCESS;
}
void waitForOpenGLDevice(const gnOutputDeviceHandle device) {}
void destroyOpenGLOutputDevice(gnOutputDeviceHandle device) {}
