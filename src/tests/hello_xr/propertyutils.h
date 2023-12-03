// Copyright (c) 2023, Paulo Gomes

#pragma once

// Get system property converted to type. Only fully supported for floats, ints and strings.
// If not found, return default value.
template <typename T>
T getProperty(const char *name, T defaultValue);
