#pragma once
#define GRYPHN_INCLUDE

// core functionality
#include <core/src/instance/gryphn_instance.h>
#include <core/src/debugger/gryphn_debugger.h>
#include <core/src/output_device/gryphn_physical_output_device.h>
#include <core/src/window_surface/gryphn_surface.h>
#include <core/src/window_surface/gryphn_surface_create_functions.h>
#include <core/src/presentation_queue/gryphn_presentation_queue.h>
#include <core/src/shader_module/gryphn_shader_module.h>
#include <core/src/shader_module/gryphn_shader_layout.h>
#include <core/src/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h>
#include <core/src/renderpass/gryphn_render_pass_descriptor.h>
#include <core/src/framebuffer/gryphn_framebuffer.h>
#include <core/src/textures/gryphn_texture.h>
#include <core/src/command/command_pool/gryphn_command_pool.h>
#include <core/src/command/command_buffer/gryphn_command_buffer.h>
#include <core/src/command/commands/gryphn_command.h>
#include <core/src/renderpass/gryphn_render_pass.h>
#include <core/src/submit/gryphn_submit.h>
#include <core/src/present/gryphn_present.h>
#include <core/src/buffers/gryphn_buffer.h>
#include <core/src/uniforms/gryphn_uniform_pool.h>
#include <core/src/uniforms/gryphn_uniform.h>

// extenions
#include <extensions/synchronization/fence/gryphn_fence.h>
#include <extensions/synchronization/semaphore/gryphn_semaphore.h>
#include <extensions/synchronization/gryphn_synced_presentation_queue.h>
#include <extensions/synchronization/commands/gryphn_sync_submit.h>
