#include "present/gryphn_present.h"
#include "instance/metal_instance.h"
#include "surface/metal_surface.h"
#include "devices/metal_output_devices.h"
#include "sync/semaphore/metal_semaphore.h"
#include "presentation_queue/metal_presentation_queue.h"
#include "debugger/gryphn_debugger.h"
#include "texture/metal_texture.h"
#import <QuartzCore/CAMetalLayer.h>

gnReturnCode metalPresent(gnOutputDeviceHandle device, gnPresentInfo info);
