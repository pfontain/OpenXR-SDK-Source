// Copyright (c) 2017-2023, The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0
#version 320 es

in lowp vec3 PSVertexColor;
out lowp vec4 FragColor;

void main() {
   FragColor = vec4(PSVertexColor, 1);
}
