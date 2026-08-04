#version 460 core

in vec4 outNormal;
in vec2 uvCoord;

layout(binding = 0) uniform sampler2D diffuseTexture;
layout(binding = 1) uniform sampler2D specularTexture;
layout(binding = 2) uniform sampler2D normalTexture;

layout(binding = 3) uniform DirectionalLight {
    vec4 position;
    vec4 color;
} light;

out vec4 fragColor;

void main() {
    vec4 objectColor = texture(diffuseTexture, uvCoord);
    
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.color.rgb;

    // light.position - world center ((0, 0, 0) in this case)
    vec3 direction = normalize(light.position.xyz);
    
    vec3 normal = normalize(outNormal.xyz);
    float diff = max(dot(direction, normal), 0.0);
    vec3 diffuse = diff * light.color.rgb;

    fragColor = vec4((ambient + diffuse) * objectColor.rgb, objectColor.a);

}