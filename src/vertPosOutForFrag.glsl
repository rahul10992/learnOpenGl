#version 330 core

layout(location = 0) in vec3 position;

out vec3 vectorPosition;

void main() {
    vectorPosition = position;
    gl_Position = vec4(position, 1.0);
}
