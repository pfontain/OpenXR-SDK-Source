// Copyright (c) 2023, Paulo Gomes

#include "assetmanager.h"

#ifdef XR_USE_PLATFORM_ANDROID
#include <android/asset_manager_jni.h>

void LoadShaderSourcesIntoOptions(Options& options, JNIEnv* env, jobject activity) {
    jclass activityClass = env->GetObjectClass(activity);
    jmethodID activityClassGetAssets = env->GetMethodID(activityClass, "getAssets", "()Landroid/content/res/AssetManager;");
    jobject assetManagerJobject = env->CallObjectMethod(activity, activityClassGetAssets);

    Log::Write(Log::Level::Info, "AssetManager:");
    AAssetManager* assetManager = AAssetManager_fromJava(env, assetManagerJobject);
    AAssetDir* assetDir = AAssetManager_openDir(assetManager,"");

    // Assumes all files in root assets folder are shaders
    const char* filename;
    while ((filename = AAssetDir_getNextFileName(assetDir))) {
        std::string filenameMessage = "filename: ";
        filenameMessage += filename;
        Log::Write(Log::Level::Info, filenameMessage);
        AAsset* asset = AAssetManager_open(
                assetManager,
                filename,
                AASSET_MODE_BUFFER
        );

        if (!asset) {
            std::string warningMessage = "android_main unable to open asset ";
            warningMessage += filename;
            Log::Write(Log::Level::Warning,  warningMessage);
            continue;
        }

        // The source of all shaders is loaded into memory
        // TODO: If the combined size of all shader sources becomes large, read shader source on
        //  demand. On demand retrieval could rely on keeping a reference to the asset manager
        //  (env->NewGlobalRef(asset_manager))
        size_t length = AAsset_getLength(asset);
        auto buffer = reinterpret_cast<const char *>(AAsset_getBuffer(asset));
        if (!buffer) {
            std::string warningMessage = "android_main unable to access asset ";
            warningMessage += filename;
            Log::Write(Log::Level::Warning, warningMessage);
            continue;
        }

        // At least one reference to the options shared pointer is kept until the program exits
        // so the source is kept in memory as well.
        options.ShaderSources[filename] = std::string{buffer, length};

        Log::Write(Log::Level::Verbose, options.ShaderSources[filename]);
        AAsset_close(asset);
    }
}
#endif
