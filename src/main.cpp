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
#include "Game.h"

#define M_PI 3.141592653589793238462643383279502884197169399375105820

enum class AppState {
	MAIN_MENU,
	Game
};


int main() {
	// Inicjalizacja GLFW i okna
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
	glEnable(GL_DEPTH_TEST);

	// Inicjalizacja gry
	GameElements game = GameElements();
	AppState currentState = AppState::Game;
	std::cout << game.chuj << "\n";
	// Główna pętla
	while (!glfwWindowShouldClose(window)) {
		if (currentState == AppState::Game) {
			UpdateGameState(game, window);
			RenderScene(game, window);
			auto penis = glGetError();
			if (penis != 0)std::cout << penis << '\n';
		}

	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}