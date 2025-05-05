#pragma once
#include <gryphn/gryphn_utils.h>
#include "gryphn_subpass.h"
#include "gryphn_render_pass_attchment.h"
#include "core/presentation_queue/gryphn_presentation_queue.h"

struct gnPlatformRenderPass;
struct gnOutputDevice;

typedef enum {
    GN_SHADER_READ, GN_PRESENTATION_QUEUE
} gnRenderPassTarget;

struct gnRenderPass {
ACCESS_LEVEL:
    gnPlatformRenderPass* renderpass = nullptr;
    gnList<gnSubpass*> subpasses;
    gnPresentationQueue* presentationQueue = nullptr;

    gnRenderpassAttachment* attachments = nullptr;
    int attachmentCount = 0;

    gnRenderPassTarget target;
public:
    gnRenderPass() {}
};

void gnRenderPassAddSubpass(gnRenderPass& renderPass, gnSubpass& subpass);
void gnRenderPassSetPresentationQueue(gnRenderPass& renderPass, gnPresentationQueue& presentationQueue);
void gnRenderPassSetAttachments(gnRenderPass& renderPass, int count, gnRenderpassAttachment* attachments);
void gnRenderPassSetTarget(gnRenderPass& renderPass, gnRenderPassTarget target);

inline gnReturnCode (*gnCreateRenderPass)(gnRenderPass* renderPass, const gnOutputDevice& outputDevice);
inline void (*gnDestroyRenderPass)(gnRenderPass& renderPass);
