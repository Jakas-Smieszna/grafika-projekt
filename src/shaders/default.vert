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
out vec3 crntPos;
out vec3 crnt2Pos;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 model2;
uniform mat4 model3;

// Controls the scale of the vertices
uniform float scale;

void main()
{
crntPos = vec3(model * vec4(aPos, 1.0f));
crnt2Pos = vec3(model2 * vec4(aPos, 1.0f));
gl_Position = camMatrix * vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
//gl_Position = camMatrix * vec4(aPos, 1.0);
color = aColor;
texCoord = aTex;
Normal = aNormal;
}