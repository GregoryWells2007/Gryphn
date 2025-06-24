## Gryphn
Cross platform high performace abstracted rendering api

# Info
Gryphn works to abstract away platform API functions (Vulkan, Metal, D3D11/D3D12, OpenGL, Software) with its own API that aims to mimic the Vulkan API while simplifying away some of its quirks<br />
# Supported APIs

- [x] Vulkan
- [x] Metal*
- [ ] Direct 3D 11
- [ ] Direct 3D 12
- [ ] OpenGL
- [ ] Software

*Metal support is a little iffy, it works for the most part

# Features
- Instance:
  - This loads all of your functions into the runtime and allows them to be called, it takes in the underlying rendering API it wants to use<br />
- Debugger:
  - A debugger, which functions more as a validatior, loads different loaders for Gryphn and overrides function calls to make sure they have the correct arguments passed in.<br />
- Devices:
  - Provides a list of system devices, or in OpenGL it fakes a generic "OpenGL device" and then you create your output device with the specified features.
- Presentation Queues:
  - vulkan swapchain wrapper or in other APIs it just creates a fixed about of textures and swaps between them.<br />
- Render Passes and framebuffers.
  - A Render Pass descriptor is an object that is used to tell the GPU how your objects are going to be rendered and the framebuffer is where they are output to.<br />
- Graphics Pipelines:
  - these layout how an object is meant to be rendered on the screen<br />
- Command buffers:
  - allocated from a command pool, you record your render commnands to it and then submit it. <br />
- Uniform pools:
  - dynamic descriptor pools, on nvidia they use the "VK_NV_descriptor_pool_overallocation" to allow for this behavior, and on other cards they just hold a big list of internal descriptor pools. <br />
- Synchronization:
  - Fences and Semaphores allow work to be submitted to the GPU and not block CPU side behavior. <br />
- Buffers:
  - buffers store GPU data so that it can be used in shaders <br />
- Textures:
  - Store image data so that it can be sampled in shaders <br />

# Plans
#### Improved Loading Scheme <br />
- Instead of loading everything from DLLS I am just going to compile everything into one single big static library and do something that I found when browsing the GLFW source code to load all of the functions so I can get rid of the DLLs classes<br />
#### Improved Validation <br />
- More layers, I want to have 3 layers for now
  - The Gryphn Validation layer which will check to make sure object passed in have proper gryphn handles and such
  - The Gryphn function validator, this will run a sanity check to make sure all of the functions have been loaded from the loader properly and will also run for every extra layer that has been run to make sure all of the functions are implemented all of the way down.
  - The Gryphn Platform validator, this will only be enabled on APIs like vulkan and it will enable vulkan validation layers.
- Improved performance
  - Validation layers are slow right now and theres not much I can do on the vulkan side to speed them up but I want to work on the gryphn side to make sure they are as performant as possible<br />
- Improved return codes
  - Gryphn return codes are not super specific to the error that has ocurred more of the time returning a GN_FAIlED_TO_CREATE_XXXX value, instead they should look at the APIs error code and return something simmilar.
#### Device Features <br />
- Physical Devices dont report features that they support at all so the developer can't chose them based on features<br />
#### Performace
- Pass info structs in by reference instead of by copy
- Remove validation code from certain platform functions, add in validated functions for those cases
# Utils library
Gryphn comes with its own utlity library, aptly named Gryphn Utils, its written in C with some helper code in C++ that can be enabled by defining GN_UTILS_CPP, more information can be found on the gryphn utils github page, gryphn make extensive use of features in the utils library like Array Lists and 2d/3d types.
# Usage
Gryphn functions like vulkan where to create an object you need a create info struct, unlike vulkan you dont pass in this create info struct by reference you pass it in by copying it, why see plans, and then you call a create function which all return a gnReturnCode/gnErrorCode enum, note these are not super specific see plans for more info

```C
gnXXXXInfo info = {
  ....
};

gnReturnCode code = gnCreateXXXX(&xxxx, ..., info);
if (code != GN_SUCCESS) printf("Failed to create XXXX %s\n", gnErrorCodeToCString(code));


```
