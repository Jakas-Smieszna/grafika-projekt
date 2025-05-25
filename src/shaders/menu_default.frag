#version 330 core

out vec4 FragColor;

uniform vec3 menuColor;

void main()
{
    FragColor = vec4(menuColor, 1.0);
}
