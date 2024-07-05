#version 330 core

out vec4 FragColor;

in vec3 vectorPosition;

void main() {
    FragColor = vec4(vectorPosition, 1.0);
}
