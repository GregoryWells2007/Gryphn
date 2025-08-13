## Gryphn
Cross platform high performace abstracted rendering api

# Info
Gryphn works to abstract away platform API functions (Vulkan, Metal, D3D11/D3D12, OpenGL, Software) with its own API that aims to mimic the OpenGL API but with the use of exensions you can make it function simmilar to Vulkan so you can have the performance<br />
# Supported APIs

- [x] Vulkan
- [x] Metal
- [ ] Direct 3D 11
- [ ] Direct 3D 12
- [ ] OpenGL
- [ ] Software
* Currently working on the OpenGL backend

# Features
#### Application objects
- Instance:
  - This loads all of your functions into the runtime and allows them to be called, it takes in the underlying rendering API it wants to use<br />
- Debugger:
  - A debugger, which functions more as a validatior, loads different loaders for Gryphn and overrides function calls to make sure they have the correct arguments passed in.<br />
- Devices:
  - Provides a list of system devices, or in OpenGL it fakes a generic "OpenGL device" and then you create your output device with the specified features.
#### Rendering Objects
- Presentation Queues:
  - vulkan swapchain wrapper or in other APIs it just creates a fixed about of textures and swaps between them with a list of unused textures.<br />
- Render Passes and framebuffers.
  - A Render Pass descriptor is an object that is used to tell the GPU how your objects are going to be rendered and the framebuffer is where they are output to.<br />
- Graphics Pipelines:
  - these layout how an object is meant to be rendered on the screen<br />
- Command buffers:
  - allocated from a command pool, you record your render commnands to it and then submit it. <br />
- Uniform pools:
  - dynamic descriptor pools, on nvidia they use the "VK_NV_descriptor_pool_overallocation" to allow for this behavior, and on other cards they just hold a big list of internal descriptor pools. <br />
- Uniforms:
  - Uniform Buffers: can be used to hold smaller data like camera indicies at that type of stuff <br />
  - SSBOs: used for instanced rendering, big buffers that can be bound <br />
  - Image: textures that can be bound so they can be used <br />
- Synchronization:
  - Fences and Semaphores allow work to be submitted to the GPU and not block CPU side behavior. <br />
- Buffers:
  - buffers store GPU data so that it can be used in shaders <br />
- Textures:
  - Store image data so that it can be sampled in shaders <br />
# Extentions
- GN_EXT_SYNCHRONIZATION
  - allows sync primatives (fence, semaphore) and sync functions (gnPresentationQueueGetImageAsync, gnSubmitSync, gnPresentSync)<br />
  - Supported APIs<br />
    - Vulkan <br />
    - Metal* (metal support is buggy, fences are nonatomic so they cannot be used across multible threads) <br />
- GN_EXT_QUEUES
  - tells vulkan when used as a backend API to stop handling queue managment and instead hand control over to the programmer
  - Supported APIs <br />
    - Vulkan <br />
  - New Objects
    - gnQueueHandle <br />
    - gnQueueTypeBits+gnQueueTypeFlags <br />
    - gnQueueFamilyProperties <br />

# Validation
Gryphn its an interesting API to work with so ive attempted to put together a somewhat comprehensive set of validation tools that will tell you what you (or I) am doing wrong. Gryphn currently has support for 2 validation layers but I plan to support more in the future <br />
Gryphn validation layers are meant to be more specific so there are certain ones for just checking if handles are valid or if you passed in properly supported features
#### Supported layers: <br />
- GN_DEBUGGER_LAYER_PLATFORM, this only does anything on vulkan for the time being, metal currently doesnt allow you to disable its validation but that API has a lot more problems when working with it so im fine with that for the time being, it will do things like enable vulkan validation layers or it will also allow the APIs to load there specific validation layers
- GN_DEBUGGER_LAYER_FUNCTIONS, this is more for my own sake but when I am writing new backends or layers I may tend to forget to implement a specific function so this layer will just check to make sure that every function is loaded properly.
- GN_DEBUGGER_LAYER_ALLOCATORS, this layer will override all Gryphn allocation calls and provide a debug message telling the user an allocation has occured, gryphn will also keep track of all internal allocations and log when certain allocations are not being deallocated, NOTE: these are bugs in Gryphn, where a heap allocated array is never freed unless the programmer has not called the appropriate gnDestroyXXX function.
# Plans
#### 1.0 Spec <br />
Gryphn is getting to the point where I can't keep developing it in the same way I have in the past where I just implement functions and features based on when I need them so slowly over the coming weeks I want to have a true spec written down for every function, that its expected results are, what its functionality does, and just go back and look at every line of code. The spec is going to be based on what I have right now with a few modifacations and also I would like to add more features.
#### Improved Validation <br />
- More/Improved validation layers
  - GN_DEBUGGER_LAYER_HANDLES, will check to make sure that handles are valid and you dont do something like attempt to pass something like a gnBuffer handle into a gnDevice handle
- Improved return codes
  - Gryphn return codes are not super specific to the error that has ocurred more of the time returning a GN_FAIlED_TO_CREATE_XXXX value, instead they should look at the APIs error code and return something simmilar.
#### Performace
- Pass info structs in by reference instead of by copy
- Remove validation code from certain platform functions, add in validated functions for those cases
#### Extensions/Supports
- APIs like OpenGL dont support the full capabilities of vulkan so things like synchronization
I currently am planning to move synchronization primatives to be an extension.
Planned extensions: <br />
  - GN_EXT_COMPUTE, while compute pipelines might be a vulkan standard they are not an OpenGL standard so this does need to be an exension <br /><br />
- I will add more exensions as Gryphn grows in complexity, im currently attempting to simplify the API to make it more simmilar to OpenGL but then with extensions it can be made more like Vulkan
#### Standardization
I currently don't write out a gryphn standard for myself but I am planning on creating that before I attempt to implement new features. This is something I should have done from the start.
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
