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

	glEnable(GL_DEPTH_TEST);

	float i = 0.0;

	while (!glfwWindowShouldClose(window))
	{
		if (i > 192.0) i = 0.0;
		else i = i + 5.0;

		if (i < 102.0) game.lightColor = glm::vec4(0.f, 0.f, i * 0.02f, 1.0f);
		else game.lightColor = glm::vec4(0.f, 0.f, 2.0f - (i - 100.0f) * 0.02f, 1.0f);

		game.light2Model = glm::translate(game.light2Model, -game.light2Pos);
		game.light2Pos = glm::rotate(game.light2Pos, glm::radians(0.25f), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		game.light2Model = glm::translate(game.light2Model, game.light2Pos);
		game.cube2Model = glm::translate(game.cube2Model, game.cube2Pos);

		glClearColor(0.f, 1.00f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		game.camera.Inputs(window);
		game.camera.updateMatrix(45.0f, 0.1f, 100.0f);

		game.camera.updateMatrix(45.0f, 0.1f, 100.0f);

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
		glDrawElements(GL_TRIANGLES,indices.size() * sizeof(indices[0]) / sizeof(int), GL_UNSIGNED_INT, 0);


		game.lightShader.Activate();

		glUniform4f(glGetUniformLocation(game.lightShader.ID, "lightColor"), game.lightColor.x, game.lightColor.y, game.lightColor.z, game.lightColor.w);

		game.camera.Matrix(game.lightShader, "camMatrix");
		game.lightVAO.Bind();
		glDrawElements(GL_TRIANGLES,lightIndices.size() * sizeof(lightIndices[0]) / sizeof(int), GL_UNSIGNED_INT, 0);


		game.lightShader2.Activate();

		glUniformMatrix4fv(glGetUniformLocation(game.lightShader2.ID, "model"), 1, GL_FALSE, glm::value_ptr(game.light2Model));

		game.camera.Matrix(game.lightShader2, "camMatrix");
		game.light2VAO.Bind();
		glDrawElements(GL_TRIANGLES,lightIndices.size() * sizeof(lightIndices[0]) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	game.VAO1.Delete();
	game.VBO1.Delete();
	game.EBO1.Delete();
	game.lightVAO.Delete();
	game.lightVBO.Delete();
	game.lightEBO.Delete();
	game.light2VAO.Delete();
	game.light2VBO.Delete();
	game.light2EBO.Delete();
	//Teksturowo:
	game.tekstura1.Delete();
	game.tekstura2.Delete();
	//
	game.shaderProgram.Delete();
	game.lightShader.Delete();
	game.lightShader2.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}