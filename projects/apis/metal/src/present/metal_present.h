#include "present/gryphn_present.h"
#include "instance/metal_instance.h"
#include "surface/metal_surface.h"
#include "devices/metal_output_devices.h"
#include "sync/semaphore/metal_semaphore.h"
#include "presentation_queue/metal_presentation_queue.h"
#include "texture/metal_texture.h"
#import <QuartzCore/CAMetalLayer.h>

gnReturnCode metalPresentSync(gnOutputDeviceHandle device, gnPresentSyncInfo info);
gnReturnCode metalPresent(gnOutputDeviceHandle device, gnPresentInfo info);
