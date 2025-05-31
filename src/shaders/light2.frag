#version 330 core

out vec4 FragColor;

in vec4 color;

uniform vec4 lightColor;

void main()
{
	FragColor = 0.5 * lightColor + 0.5 * color;
}