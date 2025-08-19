#include "opengl_texture.h"
#include "surface/opengl_surface.h"

GLenum GryphnTargetToOpenGL(gnTextureType type) {
    switch(type) {
    case GN_TEXTURE_2D: return GL_TEXTURE_2D;
    }
}

gnReturnCode openglCreateTexture(gnTexture texture, gnDevice device, const gnTextureInfo info) {
    texture->texture = malloc(sizeof(gnPlatformTexture));
    glCreateTextures(GryphnTargetToOpenGL(info.type), 1, &texture->texture->id);
    glTextureStorage2D(
        texture->texture->id,
        1,
        glGryphnFormatToOpenGLInternalFormat(info.format),
        info.extent.x, info.extent.y
    );
    return GN_SUCCESS;
}
void openglTextureData(gnTextureHandle texture, void* pixelData) {
    glTextureSubImage2D(
        texture->texture->id,
    	0,
    	0, 0,
    	texture->info.extent.x, texture->info.extent.y,
    	GL_RGBA,
    	GL_UNSIGNED_BYTE,
    	pixelData
    );
}
void openglDestroyTexture(gnTexture texture) {

}
