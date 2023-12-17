// Copyright (c) 2017-2023, The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "common.h"
#include "platformdata.h"
#include "platformplugin.h"

#ifdef XR_USE_PLATFORM_ANDROID

#include <time.h>

// TODO: Move to performance file
struct timespec operator-(struct timespec lhs, struct timespec rhs) {
    return {
        .tv_sec = lhs.tv_sec - rhs.tv_sec,
        .tv_nsec = lhs.tv_nsec - rhs.tv_nsec,
    };
}

// TODO: Move to performance file
double TimeInSeconds(const struct timespec& time) {
    return time.tv_sec + time.tv_nsec * 1e-9;
}

namespace {
struct AndroidPlatformPlugin : public IPlatformPlugin {
    AndroidPlatformPlugin(const std::shared_ptr<Options>& /*unused*/, const std::shared_ptr<PlatformData>& data) {
        instanceCreateInfoAndroid = {XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR};
        instanceCreateInfoAndroid.applicationVM = data->applicationVM;
        instanceCreateInfoAndroid.applicationActivity = data->applicationActivity;
    }

    std::vector<std::string> GetInstanceExtensions() const override { return {XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME}; }

    XrBaseInStructure* GetInstanceCreateExtension() const override { return (XrBaseInStructure*)&instanceCreateInfoAndroid; }

    void UpdateOptions(const std::shared_ptr<struct Options>& /*unused*/) override {}

    void UpdateDeltaTime() override {
        // TODO: Move timer logic to separate class.
        // TODO: Move FPS logic to separate class.
        // Timer and FPS logic could be shared with posix platform plugin.
        // VrApi is already providing FPS measurement.

        // TODO: Use chrono::steady_clock instead
        struct timespec currentTime;
        int result = clock_gettime(CLOCK_MONOTONIC, &currentTime);
        {
            // Prevent log spamming by only logging once for each sequence of consecutive failures.
            // TODO: Abstract as non spam log class.
            static bool loggedClockError = false;
            if (result == -1) {
                if (!loggedClockError) {
                    // TODO: Check errno
                    Log::Write(Log::Level::Warning, "Unable to get system time");
                    loggedClockError = true;
                    return;
                }
            }
            else {
                // Reset on success
                loggedClockError = false;
            }
        }

        if (m_isFirstFrame) {
            m_lastMeasureTime = currentTime;
            m_lastFrameTime = currentTime;
            m_isFirstFrame = false;
            return;
        }

        m_deltaTimeSeconds = TimeInSeconds(currentTime - m_lastFrameTime);
        m_lastFrameTime = currentTime;
        m_frameCountSinceLastMeasure++;

        struct timespec timeSinceLastMeasure = currentTime - m_lastMeasureTime;
        double timeSinceLastMeasureInSeconds = TimeInSeconds(timeSinceLastMeasure);
        if (timeSinceLastMeasureInSeconds > 1.0)
        {
            double fps = m_frameCountSinceLastMeasure / timeSinceLastMeasureInSeconds;

            // TODO: Use stringstream for better formatting
            Log::Write(Log::Level::Info, "FPS: " + std::to_string(fps));

            m_lastMeasureTime = currentTime;
            m_frameCountSinceLastMeasure = 0;
        }
    }

    std::optional<double> GetDeltaTime() override {
        return m_deltaTimeSeconds;
    }

    XrInstanceCreateInfoAndroidKHR instanceCreateInfoAndroid;

private:
    std::optional<double> m_deltaTimeSeconds;
    int m_frameCountSinceLastMeasure;
    bool m_isFirstFrame = true;
    struct timespec m_lastFrameTime;
    struct timespec m_lastMeasureTime;
};
}  // namespace

std::shared_ptr<IPlatformPlugin> CreatePlatformPlugin_Android(const std::shared_ptr<Options>& options,
                                                              const std::shared_ptr<PlatformData>& data) {
    return std::make_shared<AndroidPlatformPlugin>(options, data);
}
#endif
