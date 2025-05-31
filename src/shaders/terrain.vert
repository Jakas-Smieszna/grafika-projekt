#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;


// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

out vec3 Normal;
out vec3 worldPos;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
    gl_Position = camMatrix * model * vec4(aPos, 1.0);
    worldPos = aPos;
    color = aColor;
    texCoord = aTex;
    Normal = aNormal;
}