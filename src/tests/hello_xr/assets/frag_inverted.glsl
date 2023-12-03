#version 320 es

precision highp float;
in lowp vec3 PSVertexColor;
out lowp vec4 FragColor;

void main() {
   vec3 invertedColor = vec3(1.0, 1.0, 1.0) - PSVertexColor;
   FragColor = vec4(invertedColor, 1);
}
