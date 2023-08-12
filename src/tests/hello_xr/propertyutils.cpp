// Copyright (c) 2023, Paulo Gomes

#include "propertyutils.h"
#include "pch.h"

template <typename T>
T getProperty(const char *name, T default_value) {
    (void)name;
    return default_value;
}

template <>
float getProperty(const char *name, float default_value) {
    auto property_value = default_value;

#ifdef XR_USE_PLATFORM_ANDROID
    // TODO: Use __system_property_read_callback instead
    char value[PROP_VALUE_MAX] = {};
    if (__system_property_get(name, value) != 0) {
        char *end{};
        float value_converted = strtof(value, &end);
        if (value != end) {
            property_value = value_converted;
        }
    }
#endif

    return property_value;
}

template <>
int getProperty(const char *name, int default_value) {
    auto property_value = default_value;

#ifdef XR_USE_PLATFORM_ANDROID
    // TODO: Use __system_property_read_callback instead
    char value[PROP_VALUE_MAX] = {};
    if (__system_property_get(name, value) != 0) {
        char *end;
        auto value_converted = static_cast<int>(std::strtol(value, &end, 10));
        if (value != end) {
            property_value = value_converted;
        }
    }
#endif

    return property_value;
}
