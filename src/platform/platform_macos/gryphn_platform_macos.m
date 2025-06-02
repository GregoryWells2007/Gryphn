#ifdef GN_PLATFORM_MACOS
#undef GN_UTILS_CPP
#include "core/gryphn_rendering_api.h"
#include "core/instance/init/gryphn_dynamic_library.h"
#include "dlfcn.h"
#include "gryphn_platform_macos.h"
#import <QuartzCore/QuartzCore.h>
#import <Cocoa/Cocoa.h>
#import <MetalKit/MetalKit.h>

gnRenderingAPI renderingAPIs[3] = {
    GN_RENDERINGAPI_METAL,
    GN_RENDERINGAPI_VULKAN,
    GN_RENDERINGAPI_SOFTWARE
};

gnRenderingAPI* gnGetSupportedRenderingAPIs(int* count) {
    *count = 3;
    return renderingAPIs;
}

struct gnDynamicLibrary_t* gnLoadDynamicLibrary(const gnString path) {
    struct gnDynamicLibrary_t* dll = malloc(sizeof(struct gnDynamicLibrary_t));
    dll->dllPtr = dlopen(gnToCString(gnCombineStrings(path, ".dylib")), RTLD_LAZY),
    dll->isValid = true;
    if (dll->dllPtr == NULL) dll->isValid = false;
    return dll;
}
void* gnLoadFunctionPtr(struct gnDynamicLibrary_t* dll, const char* name) {
    if (dll->isValid == false) return NULL;
    return dlsym(dll->dllPtr, name);
}
void gnUnloadDynamicLibrary(struct gnDynamicLibrary_t* dll) {
    if (dll->isValid) dlclose(dll->dllPtr);
}

MTKView* gnCreateMTKView(NSWindow* window) {
    MTKView* view = [[MTKView alloc] initWithFrame:window.frame];
    [view setColorPixelFormat:MTLPixelFormatBGRA8Unorm_sRGB];
    [view setPreferredFramesPerSecond:120];
    CGSize rect = { window.frame.size.width * window.backingScaleFactor, window.frame.size.height * window.backingScaleFactor };
    [view setClearColor:MTLClearColorMake(1.0f, 0.0f, 0.0f, 1.0f)];
    [view setDrawableSize:rect];
    return view;
}

void gnWindowSetMTKView(NSWindow* window, MTKView* view) {
    [window setContentView:view];
}

CAMetalLayer* gnGetCAMetalLayer(NSWindow* window) {
    MTKView* view = window.contentView;
    return (CAMetalLayer*)view.layer;
}

/*
CAMetalLayer* gnCreateMetalLayer(NSWindow* window) {
    // CAMetalLayer* layer = [CAMetalLayer layer];
    // [window.contentView setWantsLayer:YES];
    // [layer setContentsScale:[window backingScaleFactor]];
    // [layer setFrame:window.contentView.bounds];
    // [window.contentView setLayer:layer];
    // return layer;

    CAMetalLayer* layer = [CAMetalLayer layer];

    // if (window.scaleFramebuffer)
        // [window->ns.layer setContentsScale:[window->ns.object backingScaleFactor]];

    [window.contentView layer];
    [window.contentView setWantsLayer:YES];
    return layer;
}

void gnAttachMetalLayer(NSWindow* window, CAMetalLayer* layer) {
    // [window.contentView setWantsLayer:YES];
    // // [window.contentView setLayer:layer];
    // [layer setFrame:window.contentView.bounds];
    // [layer setContentsScale:[window backingScaleFactor]];
}

void gnMetalLayerSetBounds(CAMetalLayer* layer, NSWindow* window) {
    // CGSize size = window.contentView.bounds.size;
    // CGFloat scale = window.backingScaleFactor;

    // [layer setFrame:window.contentView.bounds];
    // [layer setDrawableSize:CGSizeMake(size.width * scale, size.height * scale)];
    // [layer setContentsScale:[window backingScaleFactor]];
}
*/
#endif
