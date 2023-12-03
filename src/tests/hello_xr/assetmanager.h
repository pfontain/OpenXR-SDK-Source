// Copyright (c) 2023, Paulo Gomes

#pragma once
#include "pch.h"
#include "common.h"
#include "options.h"

#ifdef XR_USE_PLATFORM_ANDROID
void LoadShaderSourcesIntoOptions(Options& options, JNIEnv* env, jobject activity);
#endif
