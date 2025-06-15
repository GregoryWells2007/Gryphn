## Gryphn
Cross platform high performace rendering api

# Info
Gryphn works to abstract away platform API functions (Vulkan, Metal, D3D11/D3D12, OpenGL, Software) with its own API that aims to mimic vulkans API while simplifying it and adding more utils <br />|
Supported APIs

- [x] Vulkan
- [x] Metal
- [ ] Direct 3D 11
- [ ] Direct 3D 12
- [ ] OpenGL
- [ ] Software

# Features
Ability to create applications that can leverage Buffers and Textures to render full 3d scenes <br />

# Plans
Improved Validation <br />
  Currently validation is always run and it discards the messages if you dont have a debugger attached, I plan to support layers like vulkan that can validation certain parts of the API
