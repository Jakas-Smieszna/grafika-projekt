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
VBO1(vertices, vertices.size() * sizeof(vertices[0])),
EBO1(indices, indices.size() * sizeof(indices[0])),
parentDir(""), texPath("resources/"),
tekstura1((parentDir + texPath + "metal.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
tekstura2((parentDir + texPath + "Kotel1.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE),
lightShader("light.vert", "light.frag"),
lightVBO(lightVertices, lightVertices.size() * sizeof(lightVertices[0])), lightEBO(lightIndices, lightIndices.size() * sizeof(lightIndices[0])),
lightShader2("light.vert", "light.frag"),
light2VBO(lightVertices, lightVertices.size() * sizeof(lightVertices[0])), light2EBO(lightIndices, lightIndices.size() * sizeof(lightIndices[0])),
camera(1000, 800, glm::vec3(0.0f, 0.0f, 2.0f))
{
	VAO1.Bind();
	VBO1.Bind();
	EBO1.Bind();
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


	tekstura1.Bind();
	tekstura2.Bind();

	tekstura1.texUnit(shaderProgram, "texture0", 0);
	tekstura2.texUnit(shaderProgram, "texture1", 1);

	tekstura1.Unbind();
	tekstura2.Unbind();

	lightVAO.Bind();
	lightVBO.Bind();
	lightEBO.Bind();
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
	light2VBO.Bind();
	light2EBO.Bind();
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
	Texture tekstura1((parentDir + texPath + "metal.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	glBindTexture(GL_TEXTURE_2D, tekstura1.ID);

	Texture tekstura2((parentDir + texPath + "Kotel1.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
}



void UpdateGameState(GameElements& game, GLFWwindow* window, State &state)
{
	static float i = 0.0;
	if (i > 192.0) i = 0.0;
	else i = i + 5.0;

	if (i < 102.0) game.lightColor = glm::vec4(0.f, 0.f, i * 0.02f, 1.0f);
	else game.lightColor = glm::vec4(0.f, 0.f, 2.0f - (i - 100.0f) * 0.02f, 1.0f);

	game.light2Model = glm::translate(game.light2Model, -game.light2Pos);
	game.light2Pos = glm::rotate(game.light2Pos, glm::radians(0.25f), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
	game.light2Model = glm::translate(game.light2Model, game.light2Pos);
	game.cube2Model = glm::translate(game.cube2Model, game.cube2Pos);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		state = State::MenuState;
	}
	game.camera.Inputs(window);
	game.camera.updateMatrix(45.0f, 0.1f, 100.0f);
}

void RenderScene(GameElements& game, GLFWwindow* window)
{
	glClearColor(0.f, 1.00f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game.shaderProgram.Activate();

	glUniform4f(glGetUniformLocation(game.shaderProgram.ID, "lightColor"), game.lightColor.x, game.lightColor.y, game.lightColor.z, game.lightColor.w);
	glUniformMatrix4fv(glGetUniformLocation(game.shaderProgram.ID, "model2"), 1, GL_FALSE, glm::value_ptr(game.cube2Model));
	glUniform4f(glGetUniformLocation(game.shaderProgram.ID, "light2Color"), game.light2Color.x, game.light2Color.y, game.light2Color.z, game.light2Color.w);
	glUniform3f(glGetUniformLocation(game.shaderProgram.ID, "light2Pos"), game.light2Pos.x, game.light2Pos.y, game.light2Pos.z);
	//Teksturowo:
	game.tekstura1.Bind();
	game.tekstura2.Bind();

	glUniform3f(glGetUniformLocation(game.shaderProgram.ID, "camPos"), game.camera.Position.x, game.camera.Position.y, game.camera.Position.z);
	game.camera.Matrix(game.shaderProgram, "camMatrix");

	game.VAO1.Bind();
	glDrawElements(GL_TRIANGLES, indices.size() * sizeof(indices[0]) / sizeof(int), GL_UNSIGNED_INT, 0);


	game.lightShader.Activate();

	glUniform4f(glGetUniformLocation(game.lightShader.ID, "lightColor"), game.lightColor.x, game.lightColor.y, game.lightColor.z, game.lightColor.w);

	game.camera.Matrix(game.lightShader, "camMatrix");
	game.lightVAO.Bind();
	glDrawElements(GL_TRIANGLES, lightIndices.size() * sizeof(lightIndices[0]) / sizeof(int), GL_UNSIGNED_INT, 0);


	game.lightShader2.Activate();

	glUniformMatrix4fv(glGetUniformLocation(game.lightShader2.ID, "model"), 1, GL_FALSE, glm::value_ptr(game.light2Model));

	game.camera.Matrix(game.lightShader2, "camMatrix");
	game.light2VAO.Bind();
	glDrawElements(GL_TRIANGLES, lightIndices.size() * sizeof(lightIndices[0]) / sizeof(int), GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

