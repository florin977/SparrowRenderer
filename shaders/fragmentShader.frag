#version 460 core

in vec2 uvCoord;
layout(binding = 0) uniform sampler2D diffuseTexture;
layout(binding = 1) uniform sampler2D specularTexture;
layout(binding = 2) uniform sampler2D normalTexture;

layout(binding = 3) uniform DirectionalLight {
    vec4 direction;
    vec4 color;
} light;

out vec4 fragColor;

void main() {
    fragColor = texture(diffuseTexture, uvCoord);
}