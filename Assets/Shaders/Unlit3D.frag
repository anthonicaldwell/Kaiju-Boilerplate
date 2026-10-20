#version 400 core

out vec4 fragColor;

uniform vec4 diffuseColor;

void main() {
    fragColor = diffuseColor;
}
