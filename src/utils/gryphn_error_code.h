#include "utils/strings/gryphn_string.h"

typedef enum gnReturnCode {
    GN_SUCCESS, GN_FAILED, GN_FATAL,
    GN_ERROR = GN_FAILED
} gnReturnCode;

typedef gnReturnCode gnErrorCode;

typedef enum gnReturnMessage {
    GN_UNKNOWN_ERROR,
    GN_UNKNOWN_FRAMEBUFFER_ATTACHMENT,
    GN_UNKNOWN_SHADER_MODULE,
    GN_SHADER_FAILED_TO_COMPILE,
    GN_UNSUPPORTED_COLOR_FORMAT,
    GN_UNKNOWN_COLOR_FORMAT,
    GN_UNSUPPORTED_RENDERING_API,
    GN_FUNCTION_NOT_FOUND,
    GN_UNABLE_TO_LOAD_DLL,
    GN_FAILED_CREATE_DEVICE,
    GN_FAILED_CREATE_GRAPHICS_PIPELINE,
    GN_FAILED_CREATE_PRESENTATION_QUEUE,
    GN_FAILED_TO_CREATE_FRAMEBUFFER,
    GN_FAILED_CREATE_RENDERPASS,
    GN_FAILED_CREATE_INSTANCE,
    GN_FAILED_TO_ATTACH_WINDOW,
    GN_FAILED_TO_CREATE_IMAGE
} gnReturnMessage;

inline gnString lastReturnAPIMessage = "";
inline gnReturnMessage lastReturnMessage = GN_UNKNOWN_ERROR;

static const gnString gnGetErrorString() { return lastReturnAPIMessage; }
static const gnReturnMessage gnGetErrorMessage() { return lastReturnMessage; }

static gnReturnCode gnReturnError(gnReturnMessage message, gnString errorMessage) {
    lastReturnAPIMessage = errorMessage;
    lastReturnMessage = message;
    return GN_ERROR;
}
