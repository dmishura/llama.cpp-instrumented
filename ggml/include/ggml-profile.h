#pragma once

#include "ggml.h"
#include "ggml-backend.h"
#include <rangetap/rangetap.h>

// profiler stuff

// C/C++ compatibility
#ifdef __cplusplus
#define GGML_THREAD_LOCAL thread_local
#else
#define GGML_THREAD_LOCAL _Thread_local
#endif

struct ggml_profile_open_region {
RNTP_RangeHandle id;
int32_t layer;
int32_t region;
};

extern GGML_THREAD_LOCAL struct ggml_profile_open_region g_profile_open_region;

