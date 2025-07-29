#include "src/gryphn_rendering_api.h"
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

gnBool gnSupportsRenderingAPI(gnRenderingAPI api) {
    for (int i = 0; i < 3; i++) if (api == renderingAPIs[i]) return GN_TRUE;
    return GN_FALSE;
}

CAMetalLayer* gnCreateCAMetalLayer(NSWindow* window) {
    NSView* view = window.contentView;
    CAMetalLayer* layer = [CAMetalLayer layer];
    [layer setContentsScale:[window backingScaleFactor]];
    [layer setFramebufferOnly:YES];
    [view setLayer:layer];
    [view setWantsLayer:YES];
    // [layer setDisplaySyncEnabled:NO];
    CGSize viewSize = view.bounds.size;
    CGFloat scale = window.screen.backingScaleFactor;
    layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    layer.drawableSize = CGSizeMake(viewSize.width * scale,
                                         viewSize.height * scale);
    return layer;
}

void gnResizeCAMetalLayer(NSWindow* window) {
    CAMetalLayer* layer = (CAMetalLayer*)window.contentView.layer;

    CGSize viewSize = window.contentView.bounds.size;
    CGFloat scale = window.screen.backingScaleFactor;
    layer.drawableSize = CGSizeMake(viewSize.width * scale,
                                         viewSize.height * scale);
}

// CAMetalLayer* gnGetCAMetalLayer(NSWindow* window) {
//     return (CAMetalLayer*)window.contentView.layer;
// }

// void gnAttachMetalLayer(NSWindow* window, CAMetalLayer* layer) {
//     // CGSize newSize = window.contentView.bounds.size;
//     // CGFloat scale = window.contentView.window.backingScaleFactor;
//     // layer.drawableSize = CGSizeMake(newSize.width * scale, newSize.height * scale);
//     // CAMetalLayer* layer = [CAMetalLayer layer];
//     // layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
//     // layer.frame = window.contentView.layer.bounds;
//     // window.contentView.wantsLayer = YES;
//     // window.contentView.layer = layer;
//     layer.drawableSize = CGSizeMake(window.frame.size.width, window.frame.size.height);
// }


// /*
// CAMetalLayer* gnCreateMetalLayer(NSWindow* window) {
//     // CAMetalLayer* layer = [CAMetalLayer layer];
//     // [window.contentView setWantsLayer:YES];
//     // [layer setContentsScale:[window backingScaleFactor]];
//     // [layer setFrame:window.contentView.bounds];
//     // [window.contentView setLayer:layer];
//     // return layer;

//     CAMetalLayer* layer = [CAMetalLayer layer];

//     // if (window.scaleFramebuffer)
//         // [window->ns.layer setContentsScale:[window->ns.object backingScaleFactor]];

//     [window.contentView layer];
//     [window.contentView setWantsLayer:YES];
//     return layer;
// }

// void gnAttachMetalLayer(NSWindow* window, CAMetalLayer* layer) {
//     // [window.contentView setWantsLayer:YES];
//     // // [window.contentView setLayer:layer];
//     // [layer setFrame:window.contentView.bounds];
//     // [layer setContentsScale:[window backingScaleFactor]];
// }

// void gnMetalLayerSetBounds(CAMetalLayer* layer, NSWindow* window) {
//     // CGSize size = window.contentView.bounds.size;
//     // CGFloat scale = window.backingScaleFactor;

//     // [layer setFrame:window.contentView.bounds];
//     // [layer setDrawableSize:CGSizeMake(size.width * scale, size.height * scale)];
//     // [layer setContentsScale:[window backingScaleFactor]];
// }
// */
