#version 460 core

in vec2 uvCoord;
layout(binding = 0) uniform sampler2D diffuseTexture;

out vec4 fragColor;

void main() {
    fragColor = texture(diffuseTexture, uvCoord);
}