#version 460

layout(binding = 3) uniform DirectionalLight {
    vec4 position;
    vec4 color;
} light;

out vec4 fragColor;

void main() {
    fragColor = light.color;
}