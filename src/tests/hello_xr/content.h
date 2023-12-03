// Copyright (c) 2023, Paulo Gomes

#pragma once

#include "common.h"
#include "graphicsplugin.h"
#include <vector>
#include <unordered_map>

// Add grid of cubes centered around the point (0, 0, 0) to the vector
void AddCubeGrid(std::vector<Cube>& cubes);

const char* GetShaderSource(
        const char* defaultShaderSource,
        const std::unordered_map<std::string, std::string>& shaderSources,
        const char* shaderFilenameProperty,
        const std::string& defaultShaderFilename);
