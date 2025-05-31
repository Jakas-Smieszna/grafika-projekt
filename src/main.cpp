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
#include"Menu.h"
#include"State.h"

#define M_PI 3.141592653589793238462643383279502884197169399375105820

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1200, 800, "Okno", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Blad przy wytwarzaniu okna" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	gladLoadGL();

	glViewport(0, 0, 1200, 800);
	
	glClear(GL_COLOR_BUFFER_BIT);//xD
	glfwSwapBuffers(window);//xD

	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GameElements game;
	MenuElements menu;

	State state = State::MenuState;

	glEnable(GL_DEPTH_TEST);


	


	while (!glfwWindowShouldClose(window))
	{
		if (state == State::PlayState)
		{
			UpdateGameState(game, window, state);
			RenderScene(game, window);
		}
		if (state == State::MenuState)
		{
			RenderMenu(menu, window, state);
		}
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
