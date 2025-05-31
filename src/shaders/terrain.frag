#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
in vec3 Normal;
in vec3 worldPos;

// Gets the Texture Unit from the main function
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec4 light2Color;
uniform vec3 light2Pos;
uniform vec3 camPos;


void main()
{
    //FragColor = color;
    FragColor = vec4(0.2, 0.5 - (worldPos.y + 5)/2, 0, 1);
}