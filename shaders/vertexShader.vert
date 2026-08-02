#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUvCoord;

layout(location = 0) uniform mat4 modelMatrix;

layout(binding = 0, std140) uniform cameraData {
    mat4 viewMatrix;
    mat4 projectionMatrix;
};

out vec2 uvCoord;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
    uvCoord = aUvCoord;
}