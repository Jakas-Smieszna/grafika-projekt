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
#include "mesh.h"
#include"stb/stb_image.h"
//
#include"shader.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Kamera.h"
#include "terrainGenerator.h"
#include "helper/tsqueue.h"
//
#include"Game.h"
#include"Menu.h"

// Teksturowo:
// Wierzcholki2
#include"Zegary.h"
#include"StatusGry.h"

//#define M_PI 3.141592653589793238462643383279502884197169399375105820
#define _JG_DL_RAM_MON_POJ_ 1.8027756377319946465596106337352//Wyliczona recznie dlugosc przeciwprostokatnej trojkata monitora
#define TOL 1e-12//Tolerancja

enum State {
	PlayState,
	MenuState
};


int main()
{

	int WINDOW_HEIGHT = 800;
	int WINDOW_WIDTH = 1000;
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Igla w lesie JG MF MG", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Blad przy wytwarzaniu okna." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	GameElements game(window);
	MenuElements menu;

	//DO PRZENIESIENIA W PRZYSZLOSCI. POLECAM ZAMIANE FRAZ W WORDZIE.
	{
		//Inicjacja
		//KOLOR: KADLUB
		for (int i = 3; i < sizeof(game.vertices) / sizeof(GLfloat); i = i + 11) {
			game.vertices[i] = 0.67f;
			game.vertices[i + 1] = 0.67f;
			game.vertices[i + 2] = 0.67f;
		}

		//MONITOR
//WYZNACZANIE POZYCJI GORNEJ RAMKI ZA POMOCA ROTACJI WEKTOROW
		glm::vec3 vec3pom = glm::vec3(0.0f, 0.0f, 0.0f);
		int start = 582;
		for (int i = 0; i < 12; i++) {
			vec3pom = glm::vec3(
				game.vertices[(start + i) * 11],
				game.vertices[(start + i) * 11 + 1],
				game.vertices[(start + i) * 11 + 2]);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.vertices[(start + i) * 11 + 1] = vec3pom.y;
			game.vertices[(start + i) * 11 + 2] = vec3pom.z;
			vec3pom = glm::vec3(0.0f, 0.0f, _JG_DL_RAM_MON_POJ_ / 2.0f);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.vertices[(start + i) * 11 + 1] = game.vertices[(start + i) * 11 + 1] + vec3pom.y + 1.6f;
			game.vertices[(start + i) * 11 + 2] = game.vertices[(start + i) * 11 + 2] + vec3pom.z - 11.75f;
		}
		//WYZNACZANIE POZYCJI DOLNEJ RAMKI ZA POMOCA ROTACJI WEKTOROW
		start = 594;
		for (int i = 0; i < 12; i++) {
			vec3pom = glm::vec3(
				game.vertices[(start + i) * 11],
				game.vertices[(start + i) * 11 + 1],
				game.vertices[(start + i) * 11 + 2]);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.vertices[(start + i) * 11 + 1] = vec3pom.y;
			game.vertices[(start + i) * 11 + 2] = vec3pom.z;
			vec3pom = glm::vec3(0.0f, 0.0f, -_JG_DL_RAM_MON_POJ_ / 2.0f);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.vertices[(start + i) * 11 + 1] = game.vertices[(start + i) * 11 + 1] + vec3pom.y + 1.6f;
			game.vertices[(start + i) * 11 + 2] = game.vertices[(start + i) * 11 + 2] + vec3pom.z - 11.75f;
		}
		//WYZNACZANIE POZYCJI LEWEJ I PRAWEJ RAMKI ZA POMOCA ROTACJI WEKTOROW
		start = 606;
		for (int i = 0; i < 24; i++) {
			if (abs(game.vertices[(start + i) * 11]) > 1.05f) {
				vec3pom = glm::vec3(
					game.vertices[(start + i) * 11],
					game.vertices[(start + i) * 11 + 1],
					game.vertices[(start + i) * 11 + 2] * _JG_DL_RAM_MON_POJ_ / 2.0f);
			}
			else {
				vec3pom = glm::vec3(
					game.vertices[(start + i) * 11],
					game.vertices[(start + i) * 11 + 1],
					game.vertices[(start + i) * 11 + 2] * (_JG_DL_RAM_MON_POJ_ - 0.2f) / 2.0f);
			}
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.vertices[(start + i) * 11 + 1] = vec3pom.y + 1.6f;
			game.vertices[(start + i) * 11 + 2] = vec3pom.z - 11.75f;
		}
		//WYZNACZANIE POZYCJI WSKAZOWKI KIERUNKU
		for (int i = 0; i < 7; i++) {
			vec3pom = glm::vec3(
				game.Mon_Vertices[(i) * 11],
				game.Mon_Vertices[(i) * 11 + 1],
				game.Mon_Vertices[(i) * 11 + 2]);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Mon_Vertices[(i) * 11] = vec3pom.x + 0.6f;
			game.Mon_Vertices[(i) * 11 + 1] = vec3pom.y;
			game.Mon_Vertices[(i) * 11 + 2] = vec3pom.z;
			vec3pom = glm::vec3(0.0f, 0.0f, (_JG_DL_RAM_MON_POJ_ - 0.2f) / 4.0f);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Mon_Vertices[(i) * 11 + 1] = game.Mon_Vertices[(i) * 11 + 1] + vec3pom.y + 1.6f;
			game.Mon_Vertices[(i) * 11 + 2] = game.Mon_Vertices[(i) * 11 + 2] + vec3pom.z - 11.75f;
		}
		//WYZNACZANIE POZYCJI WSKAZOWKI ENERGII
		for (int i = 7; i < 22; i++) {
			vec3pom = glm::vec3(
				game.Mon_Vertices[(i) * 11],
				game.Mon_Vertices[(i) * 11 + 1],
				game.Mon_Vertices[(i) * 11 + 2]);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Mon_Vertices[(i) * 11] = vec3pom.x + 0.6f;
			game.Mon_Vertices[(i) * 11 + 1] = vec3pom.y;
			game.Mon_Vertices[(i) * 11 + 2] = vec3pom.z;
			vec3pom = glm::vec3(0.0f, 0.0f, -(_JG_DL_RAM_MON_POJ_ - 0.2f) / 4.0f);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Mon_Vertices[(i) * 11 + 1] = game.Mon_Vertices[(i) * 11 + 1] + vec3pom.y + 1.6f;
			game.Mon_Vertices[(i) * 11 + 2] = game.Mon_Vertices[(i) * 11 + 2] + vec3pom.z - 11.75f;
		}
		//WYZNACZANIE POZYCJI ROZY KIERUNKOW POD WSKAZNIK KIERUNKU
		for (int i = 22; i < 42; i++) {
			vec3pom = glm::vec3(
				game.Mon_Vertices[(i) * 11],
				game.Mon_Vertices[(i) * 11 + 1],
				game.Mon_Vertices[(i) * 11 + 2]);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Mon_Vertices[(i) * 11] = vec3pom.x + 0.6f;
			game.Mon_Vertices[(i) * 11 + 1] = vec3pom.y;
			game.Mon_Vertices[(i) * 11 + 2] = vec3pom.z;
			vec3pom = glm::vec3(0.0f, 0.0f, (_JG_DL_RAM_MON_POJ_ - 0.2f) / 4.0f);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Mon_Vertices[(i) * 11 + 1] = game.Mon_Vertices[(i) * 11 + 1] + vec3pom.y + 1.6f;
			game.Mon_Vertices[(i) * 11 + 2] = game.Mon_Vertices[(i) * 11 + 2] + vec3pom.z - 11.75f;
		}
		//WYZNACZANIE POZYCJI WSKAZOWKI ODLEGLOSCI
		for (int i = 42; i < 61; i++) {
			vec3pom = glm::vec3(
				game.Mon_Vertices[(i) * 11],
				game.Mon_Vertices[(i) * 11 + 1],
				game.Mon_Vertices[(i) * 11 + 2]);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Mon_Vertices[(i) * 11] = vec3pom.x - 0.6f;
			game.Mon_Vertices[(i) * 11 + 1] = vec3pom.y;
			game.Mon_Vertices[(i) * 11 + 2] = vec3pom.z;
			vec3pom = glm::vec3(0.0f, 0.0f, (_JG_DL_RAM_MON_POJ_ - 0.2f) / 4.0f);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Mon_Vertices[(i) * 11 + 1] = game.Mon_Vertices[(i) * 11 + 1] + vec3pom.y + 1.6f;
			game.Mon_Vertices[(i) * 11 + 2] = game.Mon_Vertices[(i) * 11 + 2] + vec3pom.z - 11.75f;
		}
		//WYZNACZANIE POZYCJI WSKAZOWKI PREDKOSCI
		for (int i = 61; i < 77; i++) {
			vec3pom = glm::vec3(
				game.Mon_Vertices[(i) * 11],
				game.Mon_Vertices[(i) * 11 + 1],
				game.Mon_Vertices[(i) * 11 + 2]);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Mon_Vertices[(i) * 11] = vec3pom.x - 0.6f;
			game.Mon_Vertices[(i) * 11 + 1] = vec3pom.y;
			game.Mon_Vertices[(i) * 11 + 2] = vec3pom.z;
			vec3pom = glm::vec3(0.0f, 0.0f, -(_JG_DL_RAM_MON_POJ_ - 0.2f) / 4.0f);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Mon_Vertices[(i) * 11 + 1] = game.Mon_Vertices[(i) * 11 + 1] + vec3pom.y + 1.6f;
			game.Mon_Vertices[(i) * 11 + 2] = game.Mon_Vertices[(i) * 11 + 2] + vec3pom.z - 11.75f;
		}


		//RAMY "ZEGAROW"

		glm::vec3 vec3A = glm::normalize(glm::vec3(0.0f, 1.5f, -1.0f));
		//Pozycja
		game.Zeg1Vertices[(130 + 65) * 11 + 0] = 0.0f;
		game.Zeg1Vertices[(130 + 65) * 11 + 1] = 0.003f;
		game.Zeg1Vertices[(130 + 65) * 11 + 2] = 0.0f;
		//Kolor
		game.Zeg1Vertices[(130 + 65) * 11 + 3] = 0.25f;
		game.Zeg1Vertices[(130 + 65) * 11 + 4] = 0.25f;
		game.Zeg1Vertices[(130 + 65) * 11 + 5] = 0.25f;
		//Tekstury
		game.Zeg1Vertices[(130 + 65) * 11 + 6] = 0.0f;
		game.Zeg1Vertices[(130 + 65) * 11 + 7] = 0.0f;
		//Wektor ormalny
		game.Zeg1Vertices[(130 + 65) * 11 + 8] = vec3A.x;
		game.Zeg1Vertices[(130 + 65) * 11 + 9] = vec3A.y;
		game.Zeg1Vertices[(130 + 65) * 11 + 10] = vec3A.z;

		float Przesuniecie_tekstura_zegar = 0.0f;

		vec3pom = glm::vec3(0.0f, 0.02f, 0.4f);
		for (int i = 0; i < 130 * 11; i = i + 11) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 128.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			//Pozycja
			game.Zeg1Vertices[i] = vec3pom.x;
			game.Zeg1Vertices[i + 1] = vec3pom.y;
			game.Zeg1Vertices[i + 2] = vec3pom.z;
			//Kolor
			game.Zeg1Vertices[i + 3] = 0.5f;
			game.Zeg1Vertices[i + 4] = 0.5f;
			game.Zeg1Vertices[i + 5] = 0.5f;
			//Tekstura
			game.Zeg1Vertices[i + 6] = vec3pom.z + Przesuniecie_tekstura_zegar;
			game.Zeg1Vertices[i + 7] = vec3pom.x + Przesuniecie_tekstura_zegar;
			//Wektor normalny
			game.Zeg1Vertices[i + 8] = vec3A.x;
			game.Zeg1Vertices[i + 9] = vec3A.y;
			game.Zeg1Vertices[i + 10] = vec3A.z;

		}
		vec3pom = glm::vec3(0.0f, 0.02f, 0.35f);
		for (int i = 130 * 11; i < 130 * 11 + 65 * 11; i = i + 11) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 64.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			//Pozycja
			game.Zeg1Vertices[i] = vec3pom.x;
			game.Zeg1Vertices[i + 1] = vec3pom.y;
			game.Zeg1Vertices[i + 2] = vec3pom.z;
			//Kolor
			game.Zeg1Vertices[i + 3] = 0.5f;
			game.Zeg1Vertices[i + 4] = 0.5f;
			game.Zeg1Vertices[i + 5] = 0.5f;
			//Tekstura
			game.Zeg1Vertices[i + 6] = vec3pom.x + Przesuniecie_tekstura_zegar;
			game.Zeg1Vertices[i + 7] = vec3pom.z + Przesuniecie_tekstura_zegar;
			//Wektor normalny
			game.Zeg1Vertices[i + 8] = vec3A.x;
			game.Zeg1Vertices[i + 9] = vec3A.y;
			game.Zeg1Vertices[i + 10] = vec3A.z;
		}
		//TARCZA
		float kat = 0.0f;
		vec3pom = glm::vec3(0.0f, 0.003f, 0.395f);
		for (int i = 130 * 11 + 66 * 11; i < 130 * 11 + 66 * 11 + 129 * 11; i = i + 11) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 128.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			//Pozycja
			game.Zeg1Vertices[i] = vec3pom.x;
			game.Zeg1Vertices[i + 1] = vec3pom.y;
			game.Zeg1Vertices[i + 2] = vec3pom.z;
			//Kolor
			kat = kat + 360.0f / 128.0f;

			//PRAWY - NIEBIESKI
			if (kat < 180.0 - TOL) game.Zeg1Vertices[i + 5] = 0.75f * kat / 180.0f;
			else game.Zeg1Vertices[i + 5] = 0.0f;

			//SRODEK - ZIELEN
			if (kat < 90.0 + TOL) game.Zeg1Vertices[i + 4] = 0.5f - 0.5f * (kat / 90.0f);
			else if (kat > 270.0 - TOL) game.Zeg1Vertices[i + 4] = 0.5f * (kat - 270.0f) / 90.0f;
			else game.Zeg1Vertices[i + 4] = 0.0f;

			//LEWY - CZERWONY
			if (kat > 180.0 + TOL) game.Zeg1Vertices[i + 3] = 0.25f - 0.25f * (kat - 180.0f) / 180.0f;
			else game.Zeg1Vertices[i + 3] = 0.0f;

			//Tekstura
			game.Zeg1Vertices[i + 6] = vec3pom.x + Przesuniecie_tekstura_zegar + 0.395f;
			game.Zeg1Vertices[i + 7] = vec3pom.z + Przesuniecie_tekstura_zegar + 0.395f;
			//Wektor normalny
			game.Zeg1Vertices[i + 8] = vec3A.x;
			game.Zeg1Vertices[i + 9] = vec3A.y;
			game.Zeg1Vertices[i + 10] = vec3A.z;

		}

		int inkr = 0;
		int inkr2 = 0;
		for (int j = 0; j < (129 + 65) * 3; j = j + 9) {
			game.Zeg1Indices[j] = inkr;
			game.Zeg1Indices[j + 1] = inkr + 1;
			game.Zeg1Indices[j + 2] = 129 + inkr2;
			game.Zeg1Indices[j + 3] = 129 + inkr2;
			game.Zeg1Indices[j + 4] = inkr + 1;
			game.Zeg1Indices[j + 5] = 129 + inkr2 + 1;
			game.Zeg1Indices[j + 6] = inkr + 1;
			game.Zeg1Indices[j + 7] = 129 + inkr2 + 1;
			game.Zeg1Indices[j + 8] = inkr + 2;
			inkr = inkr + 2;
			inkr2 = inkr2 + 1;
		}
		//TARCZA
		inkr = 0;
		for (int j = (130 + 66) * 3; j < (130 + 65 + 129) * 3; j = j + 3) {
			game.Zeg1Indices[j] = 130 + 66 + inkr;
			game.Zeg1Indices[j + 1] = 130 + 65;
			game.Zeg1Indices[j + 2] = 130 + 66 + inkr + 1;
			inkr = inkr + 1;
		}

		//KLONOWANIE ZEGAROW
		for (int i = 0; i < sizeof(game.Zeg1Vertices) / sizeof(float); i++) {
			game.Zeg2Vertices[i] = game.Zeg1Vertices[i];
			game.Zeg3Vertices[i] = game.Zeg1Vertices[i];
			game.Zeg4Vertices[i] = game.Zeg1Vertices[i];
		}
		for (int i = 0; i < sizeof(game.Zeg1Indices) / sizeof(int); i++) {
			game.Zeg2Indices[i] = game.Zeg1Indices[i];
			game.Zeg3Indices[i] = game.Zeg1Indices[i];
			game.Zeg4Indices[i] = game.Zeg1Indices[i];
		}
		//USUWANIE GRADIENTU Z TARCZY KIERUNKU
		for (int i = 130 * 11 + 66 * 11; i < 130 * 11 + 66 * 11 + 129 * 11; i = i + 11) {
			game.Zeg1Vertices[i + 3] = 0.25f;
			game.Zeg1Vertices[i + 4] = 0.25f;
			game.Zeg1Vertices[i + 5] = 0.25f;
		}


		//WYZNACZANIE POZYCJI RAMY ZEGARA - KIERUNEK
		for (int i = 0; i < sizeof(game.Zeg1Vertices) / sizeof(float) / 11; i++) {
			vec3pom = glm::vec3(
				game.Zeg1Vertices[(i) * 11],
				game.Zeg1Vertices[(i) * 11 + 1],
				game.Zeg1Vertices[(i) * 11 + 2]);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Zeg1Vertices[(i) * 11] = vec3pom.x + 0.6f;
			game.Zeg1Vertices[(i) * 11 + 1] = vec3pom.y;
			game.Zeg1Vertices[(i) * 11 + 2] = vec3pom.z;
			vec3pom = glm::vec3(0.0f, 0.0f, (_JG_DL_RAM_MON_POJ_ - 0.2f) / 4.0f);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Zeg1Vertices[(i) * 11 + 1] = game.Zeg1Vertices[(i) * 11 + 1] + vec3pom.y + 1.6f;
			game.Zeg1Vertices[(i) * 11 + 2] = game.Zeg1Vertices[(i) * 11 + 2] + vec3pom.z - 11.75f;

		}

		//WYZNACZANIE POZYCJI RAMY ZEGARA - ENERGIA
		for (int i = 0; i < sizeof(game.Zeg2Vertices) / sizeof(float) / 11; i++) {
			vec3pom = glm::vec3(
				game.Zeg2Vertices[(i) * 11],
				game.Zeg2Vertices[(i) * 11 + 1],
				game.Zeg2Vertices[(i) * 11 + 2]);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Zeg2Vertices[(i) * 11] = vec3pom.x + 0.6f;
			game.Zeg2Vertices[(i) * 11 + 1] = vec3pom.y;
			game.Zeg2Vertices[(i) * 11 + 2] = vec3pom.z;
			vec3pom = glm::vec3(0.0f, 0.0f, -(_JG_DL_RAM_MON_POJ_ - 0.2f) / 4.0f);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Zeg2Vertices[(i) * 11 + 1] = game.Zeg2Vertices[(i) * 11 + 1] + vec3pom.y + 1.6f;
			game.Zeg2Vertices[(i) * 11 + 2] = game.Zeg2Vertices[(i) * 11 + 2] + vec3pom.z - 11.75f;

		}

		//WYZNACZANIE POZYCJI RAMY ZEGARA - ODLEGLOSC
		for (int i = 0; i < sizeof(game.Zeg3Vertices) / sizeof(float) / 11; i++) {
			vec3pom = glm::vec3(
				game.Zeg3Vertices[(i) * 11],
				game.Zeg3Vertices[(i) * 11 + 1],
				game.Zeg3Vertices[(i) * 11 + 2]);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Zeg3Vertices[(i) * 11] = vec3pom.x - 0.6f;
			game.Zeg3Vertices[(i) * 11 + 1] = vec3pom.y;
			game.Zeg3Vertices[(i) * 11 + 2] = vec3pom.z;
			vec3pom = glm::vec3(0.0f, 0.0f, (_JG_DL_RAM_MON_POJ_ - 0.2f) / 4.0f);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Zeg3Vertices[(i) * 11 + 1] = game.Zeg3Vertices[(i) * 11 + 1] + vec3pom.y + 1.6f;
			game.Zeg3Vertices[(i) * 11 + 2] = game.Zeg3Vertices[(i) * 11 + 2] + vec3pom.z - 11.75f;

		}

		//WYZNACZANIE POZYCJI RAMY ZEGARA - PREDKOSC
		for (int i = 0; i < sizeof(game.Zeg4Vertices) / sizeof(float) / 11; i++) {
			vec3pom = glm::vec3(
				game.Zeg4Vertices[(i) * 11],
				game.Zeg4Vertices[(i) * 11 + 1],
				game.Zeg4Vertices[(i) * 11 + 2]);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Zeg4Vertices[(i) * 11] = vec3pom.x - 0.6f;
			game.Zeg4Vertices[(i) * 11 + 1] = vec3pom.y;
			game.Zeg4Vertices[(i) * 11 + 2] = vec3pom.z;
			vec3pom = glm::vec3(0.0f, 0.0f, -(_JG_DL_RAM_MON_POJ_ - 0.2f) / 4.0f);
			vec3pom = glm::rotate(vec3pom, -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			game.Zeg4Vertices[(i) * 11 + 1] = game.Zeg4Vertices[(i) * 11 + 1] + vec3pom.y + 1.6f;
			game.Zeg4Vertices[(i) * 11 + 2] = game.Zeg4Vertices[(i) * 11 + 2] + vec3pom.z - 11.75f;

		}



		//POLKULE
		game.pushVertices[0] = 0.f;
		game.pushVertices[1] = -0.35f;
		game.pushVertices[2] = 0.f;

		//int j = 0;
		//glm::vec3 vec3pom = glm::vec3(0.0f, 0.0f, 1.0f);
		/*for (int i = 3; i < 66 * 3; i = i + 3) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 64.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			game.pushVertices[i] = vec3pom.x;
			game.pushVertices[i + 1] = vec3pom.y;
			game.pushVertices[i + 2] = vec3pom.z;

			game.pushIndices[i - 3] = j + 1;
			game.pushIndices[i - 2] = j + 2;
			game.pushIndices[i - 1] = 0;
			j = j + 1;
		}*/

		vec3pom = glm::vec3(0.0f, 0.0f, 1.0f);
		for (int i = 3; i < 66 * 3; i = i + 3) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 64.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			game.pushVertices[i] = vec3pom.x;
			game.pushVertices[i + 1] = vec3pom.y;
			game.pushVertices[i + 2] = vec3pom.z;
		}
		vec3pom = glm::vec3(0.0f, -0.15f, 0.8f);
		for (int i = 66 * 3; i < 66 * 3 + 33 * 3; i = i + 3) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 32.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			game.pushVertices[i] = vec3pom.x;
			game.pushVertices[i + 1] = vec3pom.y;
			game.pushVertices[i + 2] = vec3pom.z;
		}
		vec3pom = glm::vec3(0.0f, -0.25f, 0.6f);
		for (int i = 66 * 3 + 33 * 3; i < 66 * 3 + 33 * 3 + 17 * 3; i = i + 3) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 16.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			game.pushVertices[i] = vec3pom.x;
			game.pushVertices[i + 1] = vec3pom.y;
			game.pushVertices[i + 2] = vec3pom.z;
		}
		vec3pom = glm::vec3(0.0f, -0.30f, 0.4f);
		for (int i = 66 * 3 + 33 * 3 + 17 * 3; i < 66 * 3 + 33 * 3 + 17 * 3 + 9 * 3; i = i + 3) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 8.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			game.pushVertices[i] = vec3pom.x;
			game.pushVertices[i + 1] = vec3pom.y;
			game.pushVertices[i + 2] = vec3pom.z;
		}
		vec3pom = glm::vec3(0.0f, -0.33f, 0.2f);
		for (int i = 66 * 3 + 33 * 3 + 17 * 3 + 9 * 3; i < 66 * 3 + 33 * 3 + 17 * 3 + 9 * 3 + 5 * 3; i = i + 3) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 4.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			game.pushVertices[i] = vec3pom.x;
			game.pushVertices[i + 1] = vec3pom.y;
			game.pushVertices[i + 2] = vec3pom.z;
		}

		inkr = 1;
		inkr2 = 0;
		for (int j = 0; j < (65 + 33) * 3; j = j + 9) {
			game.pushIndices[j] = inkr;
			game.pushIndices[j + 1] = inkr + 1;
			game.pushIndices[j + 2] = 65 + inkr2;
			game.pushIndices[j + 3] = 65 + inkr2;
			game.pushIndices[j + 4] = inkr + 1;
			game.pushIndices[j + 5] = 65 + inkr2 + 1;
			game.pushIndices[j + 6] = inkr + 1;
			game.pushIndices[j + 7] = 65 + inkr2 + 1;
			game.pushIndices[j + 8] = inkr + 2;
			inkr = inkr + 2;
			inkr2 = inkr2 + 1;


			/*std::cout << game.pushIndices[j] << "\t" << game.pushVertices[game.pushIndices[j] * 3] << "\t" << game.pushVertices[game.pushIndices[j] * 3 + 1] << "\t" << game.pushVertices[game.pushIndices[j] * 3 + 2] <<  "\n";
			std::cout << game.pushIndices[j + 1] << "\t" << game.pushVertices[game.pushIndices[j + 1] * 3] << "\t" << game.pushVertices[game.pushIndices[j + 1] * 3 + 1] << "\t" << game.pushVertices[game.pushIndices[j + 1] * 3 + 2] << "\n";
			std::cout << game.pushIndices[j + 2] << "\t" << game.pushVertices[game.pushIndices[j + 2] * 3] << "\t" << game.pushVertices[game.pushIndices[j + 2] * 3 + 1] << "\t" << game.pushVertices[game.pushIndices[j + 2] * 3 + 2] << "\n";
			std::cout << game.pushIndices[j + 3] << "\t" << game.pushVertices[game.pushIndices[j + 3] * 3] << "\t" << game.pushVertices[game.pushIndices[j + 3] * 3 + 1] << "\t" << game.pushVertices[game.pushIndices[j + 3] * 3 + 2] << "\n";
			std::cout << game.pushIndices[j + 4] << "\t" << game.pushVertices[game.pushIndices[j + 4] * 3] << "\t" << game.pushVertices[game.pushIndices[j + 4] * 3 + 1] << "\t" << game.pushVertices[game.pushIndices[j + 4] * 3 + 2] << "\n";
			std::cout << game.pushIndices[j + 5] << "\t" << game.pushVertices[game.pushIndices[j + 5] * 3] << "\t" << game.pushVertices[game.pushIndices[j + 5] * 3 + 1] << "\t" << game.pushVertices[game.pushIndices[j + 5] * 3 + 2] << "\n";
			std::cout << game.pushIndices[j + 6] << "\t" << game.pushVertices[game.pushIndices[j + 6] * 3] << "\t" << game.pushVertices[game.pushIndices[j + 6] * 3 + 1] << "\t" << game.pushVertices[game.pushIndices[j + 6] * 3 + 2] << "\n";
			std::cout << game.pushIndices[j + 7] << "\t" << game.pushVertices[game.pushIndices[j + 7] * 3] << "\t" << game.pushVertices[game.pushIndices[j + 7] * 3 + 1] << "\t" << game.pushVertices[game.pushIndices[j + 7] * 3 + 2] << "\n";
			std::cout << game.pushIndices[j + 8] << "\t" << game.pushVertices[game.pushIndices[j + 8] * 3] << "\t" << game.pushVertices[game.pushIndices[j + 8] * 3 + 1] << "\t" << game.pushVertices[game.pushIndices[j + 8] * 3 + 2] << "\n";
			std::cout << "\n\n";*/
		}

		inkr = 0;
		inkr2 = 0;
		for (int j = (65 + 33) * 3; j < (65 + 2 * 33 + 17) * 3; j = j + 9) {
			game.pushIndices[j] = 65 + inkr;
			game.pushIndices[j + 1] = 65 + inkr + 1;
			game.pushIndices[j + 2] = 98 + inkr2;
			game.pushIndices[j + 3] = 98 + inkr2;
			game.pushIndices[j + 4] = 65 + inkr + 1;
			game.pushIndices[j + 5] = 98 + inkr2 + 1;
			game.pushIndices[j + 6] = 65 + inkr + 1;
			game.pushIndices[j + 7] = 98 + inkr2 + 1;
			game.pushIndices[j + 8] = 65 + inkr + 2;
			inkr = inkr + 2;
			inkr2 = inkr2 + 1;
		}
		inkr = 0;
		inkr2 = 0;
		for (int j = (65 + 33 * 2 + 17) * 3; j < (65 + 2 * 33 + 2 * 17 + 9) * 3; j = j + 9) {
			game.pushIndices[j] = 98 + inkr;
			game.pushIndices[j + 1] = 98 + inkr + 1;
			game.pushIndices[j + 2] = 115 + inkr2;
			game.pushIndices[j + 3] = 115 + inkr2;
			game.pushIndices[j + 4] = 98 + inkr + 1;
			game.pushIndices[j + 5] = 115 + inkr2 + 1;
			game.pushIndices[j + 6] = 98 + inkr + 1;
			game.pushIndices[j + 7] = 115 + inkr2 + 1;
			game.pushIndices[j + 8] = 98 + inkr + 2;
			inkr = inkr + 2;
			inkr2 = inkr2 + 1;
		}
		inkr = 0;
		inkr2 = 0;
		for (int j = (65 + 33 * 2 + 2 * 17 + 9) * 3; j < (65 + 2 * 33 + 2 * 17 + 2 * 9 + 5) * 3; j = j + 9) {
			game.pushIndices[j] = 115 + inkr;
			game.pushIndices[j + 1] = 115 + inkr + 1;
			game.pushIndices[j + 2] = 124 + inkr2;
			game.pushIndices[j + 3] = 124 + inkr2;
			game.pushIndices[j + 4] = 115 + inkr + 1;
			game.pushIndices[j + 5] = 124 + inkr2 + 1;
			game.pushIndices[j + 6] = 115 + inkr + 1;
			game.pushIndices[j + 7] = 124 + inkr2 + 1;
			game.pushIndices[j + 8] = 115 + inkr + 2;
			inkr = inkr + 2;
			inkr2 = inkr2 + 1;
		}
		inkr = 0;
		inkr2 = 0;
		for (int j = (65 + 33 * 2 + 2 * 17 + 9 * 2 + 5) * 3; j < (65 + 2 * 33 + 2 * 17 + 2 * 9 + 2 * 5) * 3; j = j + 3) {
			game.pushIndices[j] = 124 + inkr;
			game.pushIndices[j + 1] = 124 + inkr + 1;
			game.pushIndices[j + 2] = 0;
			inkr = inkr + 1;
		}

		//Tworzenie zblizonych o innej skali/polozeniu
		for (int i = 0; i < 66 * 3 + 33 * 3 + 17 * 3 + 9 * 3 + 5 * 3; i = i + 3) {
			game.pushVertices_front[i] = game.pushVertices[i] * 0.5;//x
			game.pushVertices_front[i + 1] = game.pushVertices[i + 1] * 0.5;//y
			game.pushVertices_front[i + 2] = game.pushVertices[i + 2] * 0.5;//z

			game.pushVertices_tyl[i] = game.pushVertices[i] * 1.2;//x
			game.pushVertices_tyl[i + 1] = game.pushVertices[i + 1] * 1.2;//y
			game.pushVertices_tyl[i + 2] = game.pushVertices[i + 2] * 1.2;//z
		}




		//KULA

		game.KulaVertices[0] = 0.f;
		game.KulaVertices[1] = -0.6f;
		game.KulaVertices[2] = 0.f;
		int J = 130;
		int X = 390;
		int G = 579;
		game.KulaVertices[X] = 0.f;
		game.KulaVertices[X + 1] = 0.6f;
		game.KulaVertices[X + 2] = 0.f;

		vec3pom = glm::vec3(0.0f, 0.0f, 0.6f);
		glm::vec3 vec3pom_kopia = vec3pom;
		for (int i = 3; i < 66 * 3; i = i + 3) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 64.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			game.KulaVertices[i] = vec3pom.x;
			game.KulaVertices[i + 1] = vec3pom.y;
			game.KulaVertices[i + 2] = vec3pom.z;

			game.KulaVertices[X + i] = vec3pom.x;
			game.KulaVertices[X + i + 1] = -1.f * vec3pom.y;
			game.KulaVertices[X + i + 2] = vec3pom.z;
		}
		vec3pom = glm::rotate(vec3pom_kopia, glm::radians(90.0f / 5.0f), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		vec3pom_kopia = vec3pom;
		for (int i = 66 * 3; i < 66 * 3 + 33 * 3; i = i + 3) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 32.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			game.KulaVertices[i] = vec3pom.x;
			game.KulaVertices[i + 1] = vec3pom.y;
			game.KulaVertices[i + 2] = vec3pom.z;

			game.KulaVertices[X + i] = vec3pom.x;
			game.KulaVertices[X + i + 1] = -1.f * vec3pom.y;
			game.KulaVertices[X + i + 2] = vec3pom.z;
		}
		vec3pom = glm::rotate(vec3pom_kopia, glm::radians(90.0f / 5.0f), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		vec3pom_kopia = vec3pom;
		for (int i = 66 * 3 + 33 * 3; i < 66 * 3 + 33 * 3 + 17 * 3; i = i + 3) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 16.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			game.KulaVertices[i] = vec3pom.x;
			game.KulaVertices[i + 1] = vec3pom.y;
			game.KulaVertices[i + 2] = vec3pom.z;

			game.KulaVertices[X + i] = vec3pom.x;
			game.KulaVertices[X + i + 1] = -1.f * vec3pom.y;
			game.KulaVertices[X + i + 2] = vec3pom.z;
		}
		vec3pom = glm::rotate(vec3pom_kopia, glm::radians(90.0f / 5.0f), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		vec3pom_kopia = vec3pom;
		for (int i = 66 * 3 + 33 * 3 + 17 * 3; i < 66 * 3 + 33 * 3 + 17 * 3 + 9 * 3; i = i + 3) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 8.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			game.KulaVertices[i] = vec3pom.x;
			game.KulaVertices[i + 1] = vec3pom.y;
			game.KulaVertices[i + 2] = vec3pom.z;

			game.KulaVertices[X + i] = vec3pom.x;
			game.KulaVertices[X + i + 1] = -1.f * vec3pom.y;
			game.KulaVertices[X + i + 2] = vec3pom.z;
		}
		vec3pom = glm::rotate(vec3pom_kopia, glm::radians(90.0f / 5.0f), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		vec3pom_kopia = vec3pom;
		for (int i = 66 * 3 + 33 * 3 + 17 * 3 + 9 * 3; i < 66 * 3 + 33 * 3 + 17 * 3 + 9 * 3 + 5 * 3; i = i + 3) {
			vec3pom = glm::rotate(vec3pom, glm::radians(360.0f / 4.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
			game.KulaVertices[i] = vec3pom.x;
			game.KulaVertices[i + 1] = vec3pom.y;
			game.KulaVertices[i + 2] = vec3pom.z;

			game.KulaVertices[X + i] = vec3pom.x;
			game.KulaVertices[X + i + 1] = -1.f * vec3pom.y;
			game.KulaVertices[X + i + 2] = vec3pom.z;
		}

		inkr = 1;
		inkr2 = 0;
		for (int j = 0; j < (65 + 33) * 3; j = j + 9) {
			game.KulaIndices[j] = inkr;
			game.KulaIndices[j + 1] = inkr + 1;
			game.KulaIndices[j + 2] = 65 + inkr2;
			game.KulaIndices[j + 3] = 65 + inkr2;
			game.KulaIndices[j + 4] = inkr + 1;
			game.KulaIndices[j + 5] = 65 + inkr2 + 1;
			game.KulaIndices[j + 6] = inkr + 1;
			game.KulaIndices[j + 7] = 65 + inkr2 + 1;
			game.KulaIndices[j + 8] = inkr + 2;

			game.KulaIndices[G + j] = J + inkr;
			game.KulaIndices[G + j + 1] = J + inkr + 1;
			game.KulaIndices[G + j + 2] = J + 65 + inkr2;
			game.KulaIndices[G + j + 3] = J + 65 + inkr2;
			game.KulaIndices[G + j + 4] = J + inkr + 1;
			game.KulaIndices[G + j + 5] = J + 65 + inkr2 + 1;
			game.KulaIndices[G + j + 6] = J + inkr + 1;
			game.KulaIndices[G + j + 7] = J + 65 + inkr2 + 1;
			game.KulaIndices[G + j + 8] = J + inkr + 2;

			inkr = inkr + 2;
			inkr2 = inkr2 + 1;



			/*std::cout << game.KulaIndices[G + j] << "\t" << game.KulaVertices[game.KulaIndices[G + j] * 3] << "\t" << game.KulaVertices[game.KulaIndices[G + j] * 3 + 1] << "\t" << game.KulaVertices[game.KulaIndices[G + j] * 3 + 2] << "\n";
			std::cout << game.KulaIndices[G + j + 1] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 1] * 3] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 1] * 3 + 1] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 1] * 3 + 2] << "\n";
			std::cout << game.KulaIndices[G + j + 2] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 2] * 3] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 2] * 3 + 1] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 2] * 3 + 2] << "\n";
			std::cout << game.KulaIndices[G + j + 3] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 3] * 3] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 3] * 3 + 1] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 3] * 3 + 2] << "\n";
			std::cout << game.KulaIndices[G + j + 4] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 4] * 3] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 4] * 3 + 1] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 4] * 3 + 2] << "\n";
			std::cout << game.KulaIndices[G + j + 5] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 5] * 3] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 5] * 3 + 1] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 5] * 3 + 2] << "\n";
			std::cout << game.KulaIndices[G + j + 6] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 6] * 3] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 6] * 3 + 1] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 6] * 3 + 2] << "\n";
			std::cout << game.KulaIndices[G + j + 7] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 7] * 3] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 7] * 3 + 1] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 7] * 3 + 2] << "\n";
			std::cout << game.KulaIndices[G + j + 8] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 8] * 3] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 8] * 3 + 1] << "\t" << game.KulaVertices[game.KulaIndices[G + j + 8] * 3 + 2] << "\n";
			std::cout << "\n\n";*/

		}


		inkr = 0;
		inkr2 = 0;
		for (int j = (65 + 33) * 3; j < (65 + 2 * 33 + 17) * 3; j = j + 9) {
			game.KulaIndices[j] = 65 + inkr;
			game.KulaIndices[j + 1] = 65 + inkr + 1;
			game.KulaIndices[j + 2] = 98 + inkr2;
			game.KulaIndices[j + 3] = 98 + inkr2;
			game.KulaIndices[j + 4] = 65 + inkr + 1;
			game.KulaIndices[j + 5] = 98 + inkr2 + 1;
			game.KulaIndices[j + 6] = 65 + inkr + 1;
			game.KulaIndices[j + 7] = 98 + inkr2 + 1;
			game.KulaIndices[j + 8] = 65 + inkr + 2;

			game.KulaIndices[G + j] = J + 65 + inkr;
			game.KulaIndices[G + j + 1] = J + 65 + inkr + 1;
			game.KulaIndices[G + j + 2] = J + 98 + inkr2;
			game.KulaIndices[G + j + 3] = J + 98 + inkr2;
			game.KulaIndices[G + j + 4] = J + 65 + inkr + 1;
			game.KulaIndices[G + j + 5] = J + 98 + inkr2 + 1;
			game.KulaIndices[G + j + 6] = J + 65 + inkr + 1;
			game.KulaIndices[G + j + 7] = J + 98 + inkr2 + 1;
			game.KulaIndices[G + j + 8] = J + 65 + inkr + 2;
			inkr = inkr + 2;
			inkr2 = inkr2 + 1;
		}
		inkr = 0;
		inkr2 = 0;
		for (int j = (65 + 33 * 2 + 17) * 3; j < (65 + 2 * 33 + 2 * 17 + 9) * 3; j = j + 9) {
			game.KulaIndices[j] = 98 + inkr;
			game.KulaIndices[j + 1] = 98 + inkr + 1;
			game.KulaIndices[j + 2] = 115 + inkr2;
			game.KulaIndices[j + 3] = 115 + inkr2;
			game.KulaIndices[j + 4] = 98 + inkr + 1;
			game.KulaIndices[j + 5] = 115 + inkr2 + 1;
			game.KulaIndices[j + 6] = 98 + inkr + 1;
			game.KulaIndices[j + 7] = 115 + inkr2 + 1;
			game.KulaIndices[j + 8] = 98 + inkr + 2;

			game.KulaIndices[G + j] = J + 98 + inkr;
			game.KulaIndices[G + j + 1] = J + 98 + inkr + 1;
			game.KulaIndices[G + j + 2] = J + 115 + inkr2;
			game.KulaIndices[G + j + 3] = J + 115 + inkr2;
			game.KulaIndices[G + j + 4] = J + 98 + inkr + 1;
			game.KulaIndices[G + j + 5] = J + 115 + inkr2 + 1;
			game.KulaIndices[G + j + 6] = J + 98 + inkr + 1;
			game.KulaIndices[G + j + 7] = J + 115 + inkr2 + 1;
			game.KulaIndices[G + j + 8] = J + 98 + inkr + 2;
			inkr = inkr + 2;
			inkr2 = inkr2 + 1;
		}
		inkr = 0;
		inkr2 = 0;
		for (int j = (65 + 33 * 2 + 2 * 17 + 9) * 3; j < (65 + 2 * 33 + 2 * 17 + 2 * 9 + 5) * 3; j = j + 9) {
			game.KulaIndices[j] = 115 + inkr;
			game.KulaIndices[j + 1] = 115 + inkr + 1;
			game.KulaIndices[j + 2] = 124 + inkr2;
			game.KulaIndices[j + 3] = 124 + inkr2;
			game.KulaIndices[j + 4] = 115 + inkr + 1;
			game.KulaIndices[j + 5] = 124 + inkr2 + 1;
			game.KulaIndices[j + 6] = 115 + inkr + 1;
			game.KulaIndices[j + 7] = 124 + inkr2 + 1;
			game.KulaIndices[j + 8] = 115 + inkr + 2;

			game.KulaIndices[G + j] = J + 115 + inkr;
			game.KulaIndices[G + j + 1] = J + 115 + inkr + 1;
			game.KulaIndices[G + j + 2] = J + 124 + inkr2;
			game.KulaIndices[G + j + 3] = J + 124 + inkr2;
			game.KulaIndices[G + j + 4] = J + 115 + inkr + 1;
			game.KulaIndices[G + j + 5] = J + 124 + inkr2 + 1;
			game.KulaIndices[G + j + 6] = J + 115 + inkr + 1;
			game.KulaIndices[G + j + 7] = J + 124 + inkr2 + 1;
			game.KulaIndices[G + j + 8] = J + 115 + inkr + 2;
			inkr = inkr + 2;
			inkr2 = inkr2 + 1;
		}
		inkr = 0;
		inkr2 = 0;
		for (int j = (65 + 33 * 2 + 2 * 17 + 9 * 2 + 5) * 3; j < (65 + 2 * 33 + 2 * 17 + 2 * 9 + 2 * 5) * 3; j = j + 3) {
			game.KulaIndices[j] = 124 + inkr;
			game.KulaIndices[j + 1] = 124 + inkr + 1;
			game.KulaIndices[j + 2] = 0;

			game.KulaIndices[G + j] = J + 124 + inkr;
			game.KulaIndices[G + j + 1] = J + 124 + inkr + 1;
			game.KulaIndices[G + j + 2] = J + 0;
			inkr = inkr + 1;
		}

		//KONIEC KULA


		//KONIEC MODYFIKACJI TABLIC V/I

	}

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	State state = State::PlayState;

	glEnable(GL_DEPTH_TEST);

	 
	while (!glfwWindowShouldClose(window))
	{
		if (state == State::PlayState)
		{
			UpdateGameState(game, window);
			RenderScene(game, window);
		}
		if (state == State::MenuState)
		{
			//UpdateMenuState(window);
			RenderMenu(menu, window);
		}
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	light2VAO.Delete();
	light2VBO.Delete();
	light2EBO.Delete();
	pushVAO.Delete();
	pushVBO.Delete();
	pushEBO.Delete();
	KulaVAO.Delete();
	KulaVBO.Delete();
	KulaEBO.Delete();
	VAO_Mon.Delete();
	VBO_Mon.Delete();
	EBO_Mon.Delete();
	VAO_Zeg1.Delete();
	VBO_Zeg1.Delete();
	EBO_Zeg1.Delete();
	VAO_Zeg2.Delete();
	VBO_Zeg2.Delete();
	EBO_Zeg2.Delete();
	VAO_Zeg3.Delete();
	VBO_Zeg3.Delete();
	EBO_Zeg3.Delete();
	VAO_Zeg4.Delete();
	VBO_Zeg4.Delete();
	EBO_Zeg4.Delete();

	//Teksturowo:
	tekstura1.Delete();
	tekstura2.Delete();
	//
	shaderProgram.Delete();
	lightShader.Delete();
	lightShader2.Delete();
	pushShader.Delete();
	KulaShader.Delete();
	Mon_Program.Delete();
	Zeg1_Program.Delete();
	Zeg2_Program.Delete();
	Zeg3_Program.Delete();
	Zeg4_Program.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}