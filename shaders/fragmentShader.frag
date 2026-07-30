#version 460 core

in vec2 uvCoord;
uniform sampler2D sparrowTexture;

out vec4 fragColor;

int xorshift(in int value) {
    // Xorshift*32
    // Based on George Marsaglia's work: http://www.jstatsoft.org/v08/i14/paper
    value ^= value << 13;
    value ^= value >> 17;
    value ^= value << 5;
    return value;
}

int nextInt(inout int seed) {
    seed = xorshift(seed);
    return seed;
}

float nextFloat(inout int seed) {
    seed = xorshift(seed);
    
    return float(uint(seed)) / 4294967295.0;
}

float nextFloat(inout int seed, in float max) {
    return nextFloat(seed) * max;
}

void main() {
    int seed = gl_PrimitiveID + 1337;

    float R = nextFloat(seed);
    float G = nextFloat(seed);
    float B = nextFloat(seed);

    fragColor = texture(sparrowTexture, uvCoord);
}