#include<iostream>
#include<vector>
#include<cstdlib>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

//Teksturowo:
#include"Tekstury.h"
#include"stb/stb_image.h"
//
#include"shader.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Kamera.h"
#include"Game.h"


std::vector<GLfloat> vertices =
{
	//Pozycja XYZ			Kolory						Wspolrzedne tekstury ze zrodla 2D	Normalne wektory
	 //Front
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,		0.0f, 0.0f,								0.0f, 0.0f, -1.0f,
	-0.5f, 0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,								0.0f, 0.0f, -1.0f,
	 0.5f, 0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		1.0f, 1.0f,								0.0f, 0.0f, -1.0f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,								0.0f, 0.0f, -1.0f,
	 //Tyl
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,								0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		1.0f, 1.0f,								0.0f, 0.0f, 1.0f,
	 0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,								0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,		0.0f, 0.0f,								0.0f, 0.0f, 1.0f,
	 //Lewo
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,		0.0f, 0.0f,								1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,								1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		1.0f, 1.0f,								1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,								1.0f, 0.0f, 0.0f,
	//Prawo
	0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		1.0f, 0.0f,								-1.0f, 0.0f, 0.0f,
	0.5f, 0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		1.0f, 1.0f,								-1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,								-1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,		0.0f, 0.0f,								-1.0f, 0.0f, 0.0f,

	//Dó³
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,		0.0f, 0.0f,								0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,		0.0f, 5.0f,								0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,		5.0f, 5.0f,								0.0f, 1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,		5.0f, 0.0f,								0.0f, 1.0f, 0.0f,
	//Góra
	-0.5f, 0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,								0.0f, -1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 3.0f,								0.0f, -1.0f, 0.0f,
	0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		3.0f, 3.0f,								0.0f, -1.0f, 0.0f,
	0.5f, 0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		3.0f, 0.0f,								0.0f, -1.0f, 0.0f
};

std::vector<GLuint> indices =
{
	//Front:
	0, 1, 2,
	0, 2, 3,
	//Tyl:
	4, 5, 6,
	4, 6, 7,
	//Lewo:
	8, 9, 10,
	8, 10, 11,
	//Prawo:
	12, 13, 14,
	12, 14, 15,
	//Dol:
	16, 17, 18,
	19, 16, 18,
	//Gora:
	20, 21, 23,
	21, 23, 22
};

std::vector<GLfloat> lightVertices =
{ // COORDINATES //
	-0.1f, -0.1f, 0.1f,
	-0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, 0.1f
};

std::vector<GLuint> lightIndices =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


GameElements::GameElements() : shaderProgram("default.vert", "default.frag"),
VBO1(vertices, vertices.size() * sizeof(vertices)), EBO1(indices, indices.size() * sizeof(indices)),
parentDir(""), texPath("resources/"),
tekstura1((parentDir + texPath + "metal.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
tekstura2((parentDir + texPath + "Kotel1.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE),
lightShader("light.vert", "light.frag"), lightVBO(lightVertices, sizeof(lightVertices)), lightEBO(lightIndices, sizeof(lightIndices)),
lightShader2("light.vert", "light.frag"), light2VBO(lightVertices, sizeof(lightVertices)), light2EBO(lightIndices, sizeof(lightIndices)),
camera(1000, 800, glm::vec3(1.0f, 0.0f, 0.0f))
{
	VAO1.Bind();
	//Teksturowo:
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glBindTexture(GL_TEXTURE_2D, tekstura1.ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, tekstura2.ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	tekstura1.texUnit(shaderProgram, "texture1", 0);
	tekstura2.texUnit(shaderProgram, "texture2", 1);

	lightVAO.Bind();
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	lightColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
	cubeModel = glm::mat4(1.0f);
	cubeModel = glm::translate(cubeModel, cubePos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	light2VAO.Bind();
	light2VAO.LinkAttrib(light2VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	light2VAO.Unbind();
	light2VBO.Unbind();
	light2EBO.Unbind();

	light2Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	light2Pos = glm::vec3(0.0f, 0.0f, 1.2f);
	light2Model = glm::mat4(1.0f);
	light2Model = glm::translate(light2Model, light2Pos);
	cube2Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	cube2Model = glm::mat4(1.0f);
	cube2Model = glm::translate(cube2Model, cube2Pos);

	lightShader2.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader2.ID, "model"), 1, GL_FALSE, glm::value_ptr(light2Model));
	glUniform4f(glGetUniformLocation(lightShader2.ID, "lightColor"), light2Color.x, light2Color.y, light2Color.z, light2Color.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model2"), 1, GL_FALSE, glm::value_ptr(cube2Model));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "light2Color"), light2Color.x, light2Color.y, light2Color.z, light2Color.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "light2Pos"), light2Pos.x, light2Pos.y, light2Pos.z);
}

