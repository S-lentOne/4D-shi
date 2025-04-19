#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    float w_offset;
} ubo;

layout(location = 0) in vec4 pos;
layout(location = 1) in vec3 color;

layout(location = 0) out vec3 fragColor;

void main() {
    // Apply 4D rotation and translation
    vec4 rotatedPos = ubo.model * pos;
    
    // Apply w-offset for 4D perspective
    float w = rotatedPos.w + ubo.w_offset;
    
    // Project from 4D to 3D using perspective projection
    vec3 projectedPos = rotatedPos.xyz / (1.0 + w);
    
    // Apply 3D view and projection
    gl_Position = ubo.proj * ubo.view * vec4(projectedPos, 1.0);
    
    // Pass color to fragment shader
    fragColor = color;
} 