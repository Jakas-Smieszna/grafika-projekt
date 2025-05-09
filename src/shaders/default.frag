#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;
in vec3 crnt2Pos;

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
	float ambient = 0.20f;
	vec3 normal = normalize(Normal);
	vec3 normal2 = normalize(Normal * -1.0f);
	vec3 lightDirection = normalize(lightPos - crntPos);
	vec3 lightDirection2 = normalize(light2Pos - crnt2Pos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	float diffuse2 = max(dot(normal2, lightDirection2), 0.0f);
	float specularLight = 0.50f;

	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 viewDirection2 = normalize(camPos - crnt2Pos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	vec3 reflection2Direction = reflect(-lightDirection2, normal2);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specAmount2 = pow(max(dot(viewDirection2, reflection2Direction), 0.0f), 8);
	float specular = specAmount * specularLight;
	float specular2 = specAmount2 * specularLight;

	FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.55) * (0.5f * lightColor * (diffuse + ambient + specular) + 0.5 * light2Color * (diffuse2 + ambient + specular2));
	//FragColor = texture(tex0, texCoord);
	//* lightColor * (diffuse + ambient + specular);
	//* (0.5f * lightColor * (diffuse + ambient + specular) + 0.5 * light2Color * (diffuse2 + ambient + specular2))
}