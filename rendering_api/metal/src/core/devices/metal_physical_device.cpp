#include <core/output_device/gryphn_physical_output_device.h>
#include <Metal/Metal.hpp>
#include "metal_output_devices.h"

GN_EXPORT gnList<gnPhysicalOutputDevice> gnGetPhysicalOutputDevicesFn(const gnInstance& instance) {
    gnList<gnPhysicalOutputDevice> physicalOutputDevices = gnCreateList<gnPhysicalOutputDevice>();
    NS::Array *devices = MTL::CopyAllDevices();
    for (int i = 0; i < devices->count(); i++) {
        gnPhysicalOutputDevice physicalOutputDevice;
        physicalOutputDevice.outputDeviceName = reinterpret_cast<MTL::Device*>(devices->object(0))->name()->cString(NS::StringEncoding::UTF8StringEncoding);
        physicalOutputDevice.physicalOutputDevice = new gnPlatformPhysicalOutputDevice();
        physicalOutputDevice.physicalOutputDevice->device = reinterpret_cast<MTL::Device*>(devices->object(0));
        gnListAdd(physicalOutputDevices, physicalOutputDevice);
    }
    return physicalOutputDevices;
}

GN_EXPORT gnBool gnDeviceSupportsAPIFn(const gnPhysicalOutputDevice& device) {
    // so as far as my understanding goes which is not very far I dont think that the
    // method I am using to ge the devices would return a list of devices that are not supported on
    // metal but idk or really care cuz fuck you for using metal
    return true;
}
