#version 320 es

in vec3 VertexPos;
in vec3 VertexColor;

out vec3 PSVertexColor;

uniform mat4 ModelViewProjection;

void main() {
   gl_Position = ModelViewProjection * vec4(VertexPos, 1.0);
   PSVertexColor = vec3(0.0, 1.0, 0.0);
}
