#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;


out vec3 color;
out vec2 texCoord;
out vec3 Normal;
out vec3 worldPos;

uniform mat4 camMatrix;
uniform mat4 model;

// light stuff
#define NUM_LIGHTS 4
uniform mat4 lightModel[NUM_LIGHTS];

void main()
{
    gl_Position = camMatrix * model * vec4(aPos, 1.0);
    worldPos = vec3(model * vec4(aPos, 1.0));
    color = aColor;
    texCoord = aTex;
    Normal = mat3(transpose(inverse(model))) * aNormal;
}