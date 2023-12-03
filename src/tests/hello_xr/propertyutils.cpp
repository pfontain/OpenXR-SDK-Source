// Copyright (c) 2023, Paulo Gomes

#include "propertyutils.h"
#include "pch.h"

template <typename T>
T getProperty(const char *name, T defaultValue) {
    (void)name;
    return defaultValue;
}

template <>
float getProperty(const char *name, float defaultValue) {
    auto propertyValue = defaultValue;

#ifdef XR_USE_PLATFORM_ANDROID
    // TODO: Use __system_property_read_callback instead
    char value[PROP_VALUE_MAX] = {};
    if (__system_property_get(name, value) != 0) {
        char *end{};
        float valueConverted = strtof(value, &end);
        if (value != end) {
            propertyValue = valueConverted;
        }
    }
#endif

    return propertyValue;
}

template <>
int getProperty(const char *name, int defaultValue) {
    auto propertyValue = defaultValue;

#ifdef XR_USE_PLATFORM_ANDROID
    // TODO: Use __system_property_read_callback instead
    char value[PROP_VALUE_MAX] = {};
    if (__system_property_get(name, value) != 0) {
        char *end;
        auto valueConverted = static_cast<int>(std::strtol(value, &end, 10));
        if (value != end) {
            propertyValue = valueConverted;
        }
    }
#endif

    return propertyValue;
}

// TODO: Refactor duplicate code with functions above
template <>
std::string getProperty(const char *name, std::string defaultValue) {
    auto propertyValue = defaultValue;

#ifdef XR_USE_PLATFORM_ANDROID
    // TODO: Use __system_property_read_callback instead
    char value[PROP_VALUE_MAX] = {};
    if (__system_property_get(name, value) != 0) {
        propertyValue = value;
    }
#endif

    return propertyValue;
}
