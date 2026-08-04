#version 460

layout(location = 2) uniform vec3 lightColor;

out vec4 FragColor;

void main() {
    FragColor = vec4(lightColor, 1.0);
}