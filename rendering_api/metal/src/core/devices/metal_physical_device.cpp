// #include <core/output_device/gryphn_physical_output_device.h>
// #include <Metal/Metal.hpp>
// #include "metal_output_devices.h"

// GN_EXPORT gnPhysicalOutputDevice* gnGetPhysicalOutputDevicesFn(const gnInstance& instance, uint32_t* count) {
//     // gnList<gnPhysicalOutputDevice> physicalOutputDevices = gnCreateList<gnPhysicalOutputDevice>();
//     NS::Array *devices = MTL::CopyAllDevices();
//     gnPhysicalOutputDevice* devicesList = (gnPhysicalOutputDevice*)malloc(sizeof(gnPhysicalOutputDevice) * devices->count());
//     for (int i = 0; i < devices->count(); i++) {
//         devicesList[i].outputDeviceName = reinterpret_cast<MTL::Device*>(devices->object(0))->name()->cString(NS::StringEncoding::UTF8StringEncoding);
//         devicesList[i].physicalOutputDevice = new gnPlatformPhysicalOutputDevice();
//         devicesList[i].physicalOutputDevice->device = reinterpret_cast<MTL::Device*>(devices->object(0));
//     }
//     *count = devices->count();
//     return devicesList;
// }

// GN_EXPORT gnBool gnDeviceSupportsAPIFn(const gnPhysicalOutputDevice& device) {
//     // so as far as my understanding goes which is not very far I dont think that the
//     // method I am using to ge the devices would return a list of devices that are not supported on
//     // metal but idk or really care cuz fuck you for using metal
//     return true;
// }
