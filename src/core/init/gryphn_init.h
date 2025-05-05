#pragma once
#include <gryphn/gryphn_utils.h>
#include <core/gryphn_rendering_api.h>

gnErrorCode gnInit(gnRenderingAPI RenderingAPI);
void gnDestroy();

inline gnString cachePath;
static void gnSetCachePath(const gnString& path) { cachePath = path; }
static const gnString& gnGetCachePath() { return cachePath; }
