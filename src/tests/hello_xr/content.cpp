// Copyright (c) 2023, Paulo Gomes

#include "content.h"
#include "propertyutils.h"
#include "math.h"

void AddCubeGrid(std::vector<Cube>& cubes) {
    float cube_spacing = getProperty("debug.xr.cube.spacing", 1.0f);
    float cube_size = getProperty("debug.xr.cube.size", 0.25f);
    int grid_x = getProperty("debug.xr.grid.x", 10);
    int grid_y = getProperty("debug.xr.grid.y", 5);
    int grid_z = getProperty("debug.xr.grid.z", 10);

    for (int x = 0; x < grid_x; ++x) {
        for (int y = 0; y < grid_y; ++y) {
            for (int z = 0; z < grid_z; ++z) {
                XrPosef pose = Math::Pose::Translation(
                        {(x - grid_x / 2.0f) * cube_spacing,
                         (y - grid_y / 2.0f) * cube_spacing,
                         (z - grid_z / 2.0f) * cube_spacing});
                cubes.push_back(Cube{pose, {cube_size, cube_size, cube_size}});
            }
        }
    }
}
