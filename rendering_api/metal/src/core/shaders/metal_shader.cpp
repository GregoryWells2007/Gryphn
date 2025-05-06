#include "metal_shader_module.h"
#include "spirv_msl.hpp"
#include "core/devices/metal_output_devices.h"
#include "core/shaders/gryphn_shader.h"

static uint32_t* chars_to_uint32s(const char* chars, size_t num_chars) {
  if (chars == NULL || num_chars == 0) {
    return NULL;
  }

  // Determine the number of uint32_t elements needed.
  // Round up in case the number of chars isn't a multiple of 4.
  size_t num_uint32s = (num_chars + 3) / 4;

  // Allocate memory for the uint32_t array.
  uint32_t* uint32s = (uint32_t*)malloc(num_uint32s * sizeof(uint32_t));
  if (uint32s == NULL) {
    return NULL; // Allocation failed
  }

  // Initialize the uint32_t array to 0.
  for (size_t i = 0; i < num_uint32s; ++i) {
    uint32s[i] = 0;
  }

  // Iterate through the char array and build uint32_t values.
  for (size_t i = 0; i < num_chars; ++i) {
    size_t uint32_index = i / 4;
    int shift = 8 * (i % 4);
    uint32s[uint32_index] |= (uint32_t)(unsigned char)chars[i] << shift;
  }
  return uint32s;
}

GN_EXPORT gnReturnCode gnBuildShaderModuleFn(gnShaderModule* shaderModule, const gnOutputDevice& outputDeviec) {
    if (shaderModule->shaderModule == nullptr) shaderModule->shaderModule = new gnPlatformShaderModule();

    spirv_cross::CompilerMSL::Options options;
    options.enable_decoration_binding = true;
    options.pad_argument_buffer_resources = true;

    std::string shaderSource;
    uint32_t* data = chars_to_uint32s(shaderModule->shaderData, shaderModule->codeSize);
    if (shaderModule->shaderType == GN_VERTEX_SHADER_MODULE) {
        spirv_cross::CompilerMSL vertexMSL(data, (shaderModule->codeSize + 3) / 4);
        vertexMSL.set_msl_options(options);

        spirv_cross::ShaderResources resources = vertexMSL.get_shader_resources();
        int largestBinding = 0;
    	for (auto &resource : resources.uniform_buffers) {
    		unsigned binding = vertexMSL.get_decoration(resource.id, spv::DecorationBinding) + 1;
    		vertexMSL.unset_decoration(resource.id, spv::DecorationDescriptorSet);
    		vertexMSL.set_decoration(resource.id, spv::DecorationBinding, binding);
            if (binding > largestBinding) largestBinding = binding;
    	} // bullshit stuff to remap bindings so that metal can not being a whining little baby bitch boy

        for (auto &resource : resources.push_constant_buffers) {
    		unsigned binding = vertexMSL.get_decoration(resource.id, spv::DecorationBinding) + 1;
    		vertexMSL.unset_decoration(resource.id, spv::DecorationDescriptorSet);
    		vertexMSL.set_decoration(resource.id, spv::DecorationBinding, largestBinding + binding);
    	} // bullshit stuff to remap push constants for metal because its being a little baby bitch boy
    	shaderSource = vertexMSL.compile();
        shaderModule->shaderModule->uniformBufferOffset = 1;
        shaderModule->shaderModule->pushConstantOffset = largestBinding + 1;
    } else if (shaderModule->shaderType == GN_FRAGMENT_SHADER_MODULE) {
        spirv_cross::CompilerMSL fragmentMSL(data, (shaderModule->codeSize + 3) / 4);
        fragmentMSL.set_msl_options(options);

        spirv_cross::ShaderResources resources = fragmentMSL.get_shader_resources();
        int largestBinding = 0;
    	for (auto &resource : resources.uniform_buffers) {
    		unsigned binding = fragmentMSL.get_decoration(resource.id, spv::DecorationBinding);
            if (binding > largestBinding) largestBinding = binding;
    	}

        for (auto &resource : resources.push_constant_buffers) {
    		unsigned binding = fragmentMSL.get_decoration(resource.id, spv::DecorationBinding);
    		fragmentMSL.unset_decoration(resource.id, spv::DecorationDescriptorSet);
    		fragmentMSL.set_decoration(resource.id, spv::DecorationBinding, (largestBinding + 1) + binding);
    	} // bullshit stuff to remap push constants for metal because its being a little baby bitch boy

        int bindingIndex = 0;
        for (auto &resource : resources.sampled_images) {
      		unsigned binding = fragmentMSL.get_decoration(resource.id, spv::DecorationBinding);
            unsigned set = fragmentMSL.get_decoration(resource.id, spv::DecorationDescriptorSet);
      		fragmentMSL.unset_decoration(resource.id, spv::DecorationDescriptorSet);
      		fragmentMSL.set_decoration(resource.id, spv::DecorationBinding, bindingIndex);
            shaderModule->shaderModule->texturesSetBindings[{set, binding}] = bindingIndex;
            bindingIndex++;
        }

        shaderSource = fragmentMSL.compile();
        shaderModule->shaderModule->uniformBufferOffset = 0;
        shaderModule->shaderModule->pushConstantOffset = largestBinding + 1;
    } else {
        return gnReturnError(GN_UNKNOWN_SHADER_MODULE, "unknown shader module type (vertex and fragment are the only supported ones for now)");
    }

    // std::cout << shaderSource << "\n";

    NS::Error* error = nullptr;
    MTL::CompileOptions* mtloptions = nullptr;
    NS::String* sourceCode = NS::String::string(shaderSource.c_str(), NS::StringEncoding::UTF8StringEncoding);
    MTL::Library* shaderLib = outputDeviec.outputDevice->device->newLibrary(sourceCode, mtloptions, &error);
    if (!shaderLib)
        return gnReturnError(GN_SHADER_FAILED_TO_COMPILE, error->localizedDescription()->utf8String());
    if (shaderLib->functionNames()->count() > 1)
        return gnReturnError(GN_SHADER_FAILED_TO_COMPILE, "More than one shader function in shader");

    shaderModule->shaderModule->shaderFunction = shaderLib->newFunction(reinterpret_cast<NS::String*>(shaderLib->functionNames()->object(0)));
    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyShaderModuleFn(gnShaderModule& shaderModule) {
    shaderModule.shaderModule->shaderFunction->release();
}

GN_EXPORT gnReturnCode gnBuildShaderFn(gnShader* shader) {
    return GN_SUCCESS;
}
