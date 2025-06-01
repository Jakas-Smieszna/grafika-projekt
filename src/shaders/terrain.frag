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
uniform vec3 camPos;
#define NUM_LIGHTS 4
uniform vec3 lightPos[NUM_LIGHTS];
uniform vec4 lightColor[NUM_LIGHTS];

uniform mat4 model;

void main()
{
    //FragColor = color;
    vec4 heightColor = vec4(0.2, 0.5 - (worldPos.y + 5)/2, 0, 1);
    vec3 normal = normalize(Normal);
    float ambient = 0.2;
    float specular[NUM_LIGHTS];
    float diffuse[NUM_LIGHTS];
    for(int i = 0; i < NUM_LIGHTS; i++) {
        vec3 lightDir = normalize(lightPos[i] - worldPos);
        diffuse[i] = max(dot(normal, lightDir), 0.0);
        vec3 viewDir = normalize(camPos - worldPos);
        vec3 reflDir = reflect(-lightDir, normal);
        float specAmount = pow(max(dot(viewDir, reflDir), 0), 8);
        specular[i] = specAmount * 0.5;
    }
    FragColor = heightColor * (
        1 * lightColor[0] * (diffuse[0] + 0*ambient + specular[0]) +
        1 * lightColor[1] * (diffuse[1] + 0*ambient + specular[1]) +
        1 * lightColor[2] * (diffuse[2] + 0*ambient + specular[2]) +
        0.8 * lightColor[3] * (diffuse[3] + ambient + specular[3])
    );

    //FragColor = vec4(normal, 1.0);

}