#version 460 core

in vec4 outNormal;
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
    vec4 objectColor = texture(diffuseTexture, uvCoord);
    
    float ambientStrength = 0.1;
    vec4 ambient = vec4(ambientStrength * light.color.rgb, 1.0);

    vec4 direction = normalize(-light.direction);
    vec4 normal = normalize(outNormal);
    float diff = max(dot(direction, normal), 0.0);

    vec4 finalColor = (ambient + diff) * objectColor;

    fragColor = vec4(finalColor.rgb, 1.0);
}