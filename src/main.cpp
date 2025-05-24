#include<iostream>
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
//
#include"Game.h"

#define M_PI 3.141592653589793238462643383279502884197169399375105820


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1000, 800, "Okno", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Blad przy wytwarzaniu okna" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 1000, 800);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GameElements game;

	game.VAO1.Bind();


	//Teksturowo:
	game.VAO1.LinkAttrib(game.VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	game.VAO1.LinkAttrib(game.VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	game.VAO1.LinkAttrib(game.VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	game.VAO1.LinkAttrib(game.VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	//

	/*game.VAO1.LinkVBO(game.VBO1, 0);*/

	game.VAO1.Unbind();
	game.VBO1.Unbind();
	game.EBO1.Unbind();

	std::string parentDir = "";
	std::string texPath = "resources/";

	Texture tekstura1((parentDir + texPath + "metal.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	glBindTexture(GL_TEXTURE_2D, tekstura1.ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	Texture tekstura2((parentDir + texPath + "Kotel1.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	glBindTexture(GL_TEXTURE_2D, tekstura2.ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



	tekstura1.texUnit(game.shaderProgram, "texture1", 0);
	tekstura2.texUnit(game.shaderProgram, "texture2", 1);


	//swiatlo:
	Shader lightShader("light.vert", "light.frag");
	VAO lightVAO;
	lightVAO.Bind();
	VBO lightVBO(lightVertices,lightVertices.size() * sizeof(lightVertices[0]));
	EBO lightEBO(lightIndices,lightIndices.size() * sizeof(lightIndices[0]));
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 cubeModel = glm::mat4(1.0f);
	cubeModel = glm::translate(cubeModel, cubePos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	game.shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(game.shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	glUniform4f(glGetUniformLocation(game.shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(game.shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	//swiatlo 2:
	Shader lightShader2("light.vert", "light.frag");
	VAO light2VAO;
	light2VAO.Bind();
	VBO light2VBO(lightVertices,lightVertices.size() * sizeof(lightVertices[0]));
	EBO light2EBO(lightIndices,lightIndices.size() * sizeof(lightIndices[0]));
	light2VAO.LinkAttrib(light2VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	light2VAO.Unbind();
	light2VBO.Unbind();
	light2EBO.Unbind();

	glm::vec4 light2Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 light2Pos = glm::vec3(0.0f, 0.0f, 1.2f);
	glm::mat4 light2Model = glm::mat4(1.0f);
	light2Model = glm::translate(light2Model, light2Pos);
	glm::vec3 cube2Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 cube2Model = glm::mat4(1.0f);
	cube2Model = glm::translate(cube2Model, cube2Pos);

	lightShader2.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader2.ID, "model"), 1, GL_FALSE, glm::value_ptr(light2Model));
	glUniform4f(glGetUniformLocation(lightShader2.ID, "lightColor"), light2Color.x, light2Color.y, light2Color.z, light2Color.w);
	game.shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(game.shaderProgram.ID, "model2"), 1, GL_FALSE, glm::value_ptr(cube2Model));
	glUniform4f(glGetUniformLocation(game.shaderProgram.ID, "light2Color"), light2Color.x, light2Color.y, light2Color.z, light2Color.w);
	glUniform3f(glGetUniformLocation(game.shaderProgram.ID, "light2Pos"), light2Pos.x, light2Pos.y, light2Pos.z);



	glEnable(GL_DEPTH_TEST);

	Camera camera(1000, 800, glm::vec3(0.0f, 0.0f, 2.0f));
	float i = 0.0;

	while (!glfwWindowShouldClose(window))
	{
		if (i > 192.0) i = 0.0;
		else i = i + 5.0;

		if (i < 102.0) lightColor = glm::vec4(0.f, 0.f, i * 0.02f, 1.0f);
		else lightColor = glm::vec4(0.f, 0.f, 2.0f - (i - 100.0f) * 0.02f, 1.0f);

		light2Model = glm::translate(light2Model, -light2Pos);
		light2Pos = glm::rotate(light2Pos, glm::radians(0.25f), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		light2Model = glm::translate(light2Model, light2Pos);
		cube2Model = glm::translate(cube2Model, cube2Pos);

		glClearColor(0.f, 1.00f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		game.shaderProgram.Activate();

		glUniform4f(glGetUniformLocation(game.shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniformMatrix4fv(glGetUniformLocation(game.shaderProgram.ID, "model2"), 1, GL_FALSE, glm::value_ptr(cube2Model));
		glUniform4f(glGetUniformLocation(game.shaderProgram.ID, "light2Color"), light2Color.x, light2Color.y, light2Color.z, light2Color.w);
		glUniform3f(glGetUniformLocation(game.shaderProgram.ID, "light2Pos"), light2Pos.x, light2Pos.y, light2Pos.z);
		//Teksturowo:
		game.tekstura1.Bind();
		game.tekstura2.Bind();

		glUniform3f(glGetUniformLocation(game.shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(game.shaderProgram, "camMatrix");

		game.VAO1.Bind();
		glDrawElements(GL_TRIANGLES,indices.size() * sizeof(indices[0]) / sizeof(int), GL_UNSIGNED_INT, 0);


		lightShader.Activate();

		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES,lightIndices.size() * sizeof(lightIndices[0]) / sizeof(int), GL_UNSIGNED_INT, 0);


		lightShader2.Activate();

		glUniformMatrix4fv(glGetUniformLocation(lightShader2.ID, "model"), 1, GL_FALSE, glm::value_ptr(light2Model));

		camera.Matrix(lightShader2, "camMatrix");
		light2VAO.Bind();
		glDrawElements(GL_TRIANGLES,lightIndices.size() * sizeof(lightIndices[0]) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	game.VAO1.Delete();
	game.VBO1.Delete();
	game.EBO1.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	light2VAO.Delete();
	light2VBO.Delete();
	light2EBO.Delete();
	//Teksturowo:
	game.tekstura1.Delete();
	game.tekstura2.Delete();
	//
	game.shaderProgram.Delete();
	lightShader.Delete();
	lightShader2.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}