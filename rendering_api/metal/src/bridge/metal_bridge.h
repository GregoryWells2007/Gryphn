#pragma once

void mtlObjectCSetContentViewsLayer(void* window, void* layer);
void* mtlCreateContentView(void* targetWindow);
void mtlInitializeMetalLayer(void* layer, bool vsync);
