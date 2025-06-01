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
in vec3 crnt3Pos;
in vec3 crntBIGPos;

// Gets the Texture Unit from the main function
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec4 light2Color;
uniform vec3 light2Pos;
uniform vec4 pushColor;
uniform vec3 pushPos;
uniform vec4 BIGlightColor;
uniform vec3 BIGlightPos;
uniform vec3 camPos;


void main()
{
	float ambient = 0.2f;
	vec3 normal = normalize(Normal);
	vec3 normal2 = normalize(Normal * -1.0f);

	vec3 lightDirection = normalize(lightPos - crntPos);
	vec3 lightDirection2 = normalize(light2Pos - crnt2Pos);
	vec3 lightDirection3 = normalize(pushPos - crnt3Pos);
	vec3 lightDirectionBIG = normalize(BIGlightPos - crntBIGPos);

	float diffuse = max(dot(normal, lightDirection), 0.0f);
	float diffuse2 = max(dot(normal, lightDirection2), 0.0f);
	float diffuse3 = max(dot(normal2, lightDirection3), 0.0f);
	float diffuseBIG = max(dot(normal, lightDirectionBIG), 0.0f);
	float specularLight = 0.50f;

	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 viewDirection2 = normalize(camPos - crnt2Pos);
	vec3 viewDirection3 = normalize(camPos - crnt3Pos);
	vec3 viewDirectionBIG = normalize(camPos - crntBIGPos);

	vec3 reflectionDirection = reflect(-lightDirection, normal);
	vec3 reflection2Direction = reflect(-lightDirection2, normal);
	vec3 reflection3Direction = reflect(-lightDirection3, normal2);
	vec3 reflectionBIGDirection = reflect(-lightDirectionBIG, normal);

	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specAmount2 = pow(max(dot(viewDirection2, reflection2Direction), 0.0f), 8);
	float specAmount3 = pow(max(dot(viewDirection3, reflection3Direction), 0.0f), 8);
	float specAmountBIG = pow(max(dot(viewDirectionBIG, reflectionBIGDirection), 0.0f), 8);
	
	float specular = specAmount * specularLight;
	float specular2 = specAmount2 * specularLight;
	float specular3 = specAmount3 * specularLight;
	float specularBIG = specAmountBIG * specularLight;

	//FragColor = vec4(color, 1.0f);
	FragColor = vec4(color, 1.0f) 
	* mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.55) 
	* (
		0.3f * lightColor * (diffuse + ambient + specular) 
		+ 0.3f * light2Color * (diffuse2 + ambient + specular2)
		+ 0.3f * pushColor * (diffuse3 + ambient + specular3)
		+ 1.0f * BIGlightColor * (diffuseBIG + ambient * 2.0f + specularBIG)
	);
	
	
	
	//FragColor = texture(tex0, texCoord);
	//* lightColor * (diffuse + ambient + specular);
	//* (0.5f * lightColor * (diffuse + ambient + specular) + 0.5 * light2Color * (diffuse2 + ambient + specular2))
}