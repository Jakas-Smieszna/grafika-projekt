#include "StatusGry.h"

//USTAW WSKAZOWKI NA POZYCJACH POCZATKOWYCH
int InicjujZmienne1(GLFWwindow* okno, Pakiet_Zmiennych* zmienne, GLfloat* wskazowki) {
	
	glm::vec3 vpom = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 vpom2 = glm::vec3(0.f, 0.f, 0.f);
	int w0 = 65;//pierwszy wierzcholek wskazowki

	//PREDKOSC
	vpom = glm::vec3((wskazowki[w0 * 11] + wskazowki[(w0 + 2) * 11]) / 2.0, (wskazowki[w0 * 11 + 1] + wskazowki[(w0 + 2) * 11 + 1]) / 2.0, (wskazowki[w0 * 11 + 2] + wskazowki[(w0 + 2) * 11 + 2]) / 2.0);
	//Cofniecie do zera
	for (int i = 0; i < 3; i++) {
		wskazowki[(w0 + i) * 11] = wskazowki[(w0 + i) * 11] - vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = wskazowki[(w0 + i) * 11 + 1] - vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = wskazowki[(w0 + i) * 11 + 2] - vpom.z;
	}
	//Obrot
	for (int i = 0; i < 3; i++) {
		vpom2 = glm::vec3(
			wskazowki[(w0 + i) * 11],
			wskazowki[(w0 + i) * 11 + 1],
			wskazowki[(w0 + i) * 11 + 2]
		);
		vpom2 = glm::rotate(vpom2, 0.975f * float(M_PI), glm::normalize(zmienne->Os_zegarow));
		wskazowki[(w0 + i) * 11] = vpom2.x + vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = vpom2.y + vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = vpom2.z + vpom.z;

	}


	//ENERGIA
	w0 = 11;
	vpom = glm::vec3((wskazowki[w0 * 11] + wskazowki[(w0 + 2) * 11]) / 2.0, (wskazowki[w0 * 11 + 1] + wskazowki[(w0 + 2) * 11 + 1]) / 2.0, (wskazowki[w0 * 11 + 2] + wskazowki[(w0 + 2) * 11 + 2]) / 2.0);
	//Cofniecie do zera
	for (int i = 0; i < 3; i++) {
		wskazowki[(w0 + i) * 11] = wskazowki[(w0 + i) * 11] - vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = wskazowki[(w0 + i) * 11 + 1] - vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = wskazowki[(w0 + i) * 11 + 2] - vpom.z;
	}
	//Obrot
	for (int i = 0; i < 3; i++) {
		vpom2 = glm::vec3(
			wskazowki[(w0 + i) * 11],
			wskazowki[(w0 + i) * 11 + 1],
			wskazowki[(w0 + i) * 11 + 2]
		);
		vpom2 = glm::rotate(vpom2, -0.975f * float(M_PI), glm::normalize(zmienne->Os_zegarow));
		wskazowki[(w0 + i) * 11] = vpom2.x + vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = vpom2.y + vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = vpom2.z + vpom.z;

	}

	return 0;
}

//AKTUALIZUJ WSKAZOWKI I WSKAZYWANE PRZEZ NIE PARAMETRY
int AktualizujZmienne1(GLFWwindow* okno, Pakiet_Zmiennych* zmienne, GLfloat* wskazowki, GLfloat* korpus) {

	glm::vec3 vpom = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 vpom2 = glm::vec3(0.f, 0.f, 0.f);
	int w0 = 65;//pierwszy wierzcholek wskazowki




		//ZMIANA PREDKOSCI
	//PRZYSPIESZANIE
	if ((glfwGetKey(okno, GLFW_KEY_Q) == GLFW_PRESS) && zmienne->Predkosc < MAX_PREDKOSC && zmienne->Czas_przyspieszanie < MAX_PRZYSPIESZANIE) {

		zmienne->Czas_przyspieszanie = zmienne->Czas_przyspieszanie + 1;

	}

	//ZWALNIANIE
	if ((glfwGetKey(okno, GLFW_KEY_E) == GLFW_PRESS) && zmienne->Predkosc > 0.0 && zmienne->Czas_przyspieszanie > -MAX_PRZYSPIESZANIE) {

		zmienne->Czas_przyspieszanie = zmienne->Czas_przyspieszanie - 1;
		
	}

	//AUTOMATYCZNE WYRUWNYWANIE KIEROWNICY
	if (!(((glfwGetKey(okno, GLFW_KEY_Q) == GLFW_PRESS) && zmienne->Predkosc < MAX_PREDKOSC) || ((glfwGetKey(okno, GLFW_KEY_E) == GLFW_PRESS) && zmienne->Predkosc > 0.0))) {
		
		if (zmienne->Czas_przyspieszanie > 0) zmienne->Czas_przyspieszanie = zmienne->Czas_przyspieszanie - 1;
		else if (zmienne->Czas_przyspieszanie < 0) zmienne->Czas_przyspieszanie = zmienne->Czas_przyspieszanie + 1;

	}

	//ZMIANA PREDKOSCI
	double predkosc0 = zmienne->Predkosc;
	zmienne->Predkosc = zmienne->Predkosc + double(zmienne->Czas_przyspieszanie) / 120.0;
	if (zmienne->Predkosc > MAX_PREDKOSC) zmienne->Predkosc = MAX_PREDKOSC;
	if (zmienne->Predkosc < 0.0) zmienne->Predkosc = 0.0;

	//ZEGAR
	vpom = glm::vec3((wskazowki[w0 * 11] + wskazowki[(w0 + 2) * 11]) / 2.0, (wskazowki[w0 * 11 + 1] + wskazowki[(w0 + 2) * 11 + 1]) / 2.0, (wskazowki[w0 * 11 + 2] + wskazowki[(w0 + 2) * 11 + 2]) / 2.0);
	//Cofniecie do zera zegara
	for (int i = 0; i < 3; i++) {
		wskazowki[(w0 + i) * 11] = wskazowki[(w0 + i) * 11] - vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = wskazowki[(w0 + i) * 11 + 1] - vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = wskazowki[(w0 + i) * 11 + 2] - vpom.z;
	}
	//Obrot zegara
	for (int i = 0; i < 3; i++) {
		vpom2 = glm::vec3(
			wskazowki[(w0 + i) * 11],
			wskazowki[(w0 + i) * 11 + 1],
			wskazowki[(w0 + i) * 11 + 2]
		);
		vpom2 = glm::rotate(vpom2, -1.95f * float(M_PI * (zmienne->Predkosc - predkosc0) / MAX_PREDKOSC), glm::normalize(zmienne->Os_zegarow));
		wskazowki[(w0 + i) * 11] = vpom2.x + vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = vpom2.y + vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = vpom2.z + vpom.z;

	}

	//KIEROWNICA
	//Wsyuwanie/wysuwanie:
	w0 = 438;
	//Obecne przesuniecie
	float deltaY = korpus[(w0 + 3) * 11 + 1] - korpus[w0 * 11 + 1];
	float deltaZ = korpus[(w0 + 3) * 11 + 2] - korpus[w0 * 11 + 2];
	//Drag
	for (int i = 0; i < 4; i++) {
		korpus[(w0 + i * 4 + 2) * 11 + 1] = korpus[(w0 + i * 4 + 2) * 11 + 1] - deltaY + float(1.7 - 1.7 * 0.2 * (double(zmienne->Czas_przyspieszanie) / double(MAX_PRZYSPIESZANIE)));
		korpus[(w0 + i * 4 + 3) * 11 + 1] = korpus[(w0 + i * 4 + 3) * 11 + 1] - deltaY + float(1.7 - 1.7 * 0.2 * (double(zmienne->Czas_przyspieszanie) / double(MAX_PRZYSPIESZANIE)));
		korpus[(w0 + i * 4 + 2) * 11 + 2] = korpus[(w0 + i * 4 + 2) * 11 + 2] - deltaZ - float(2.9 - 2.9 * 0.2 * (double(zmienne->Czas_przyspieszanie) / double(MAX_PRZYSPIESZANIE)));
		korpus[(w0 + i * 4 + 3) * 11 + 2] = korpus[(w0 + i * 4 + 3) * 11 + 2] - deltaZ - float(2.9 - 2.9 * 0.2 * (double(zmienne->Czas_przyspieszanie) / double(MAX_PRZYSPIESZANIE)));
	}
	//reszta
	for (int i = 16; i < 550 - w0; i++) {
		korpus[(w0 + i) * 11 + 1] = korpus[(w0 + i) * 11 + 1] - deltaY + float(1.7 - 1.7 * 0.2 * (double(zmienne->Czas_przyspieszanie) / double(MAX_PRZYSPIESZANIE)));
		korpus[(w0 + i) * 11 + 2] = korpus[(w0 + i) * 11 + 2] - deltaZ - float(2.9 - 2.9 * 0.2 * (double(zmienne->Czas_przyspieszanie) / double(MAX_PRZYSPIESZANIE)));
	}
		//KONIEC ZMIANA PREDKOSCI



	//RUCH I ZMIANY ENERGII
	w0 = 11;
	zmienne->Biezaca_pozycja = zmienne->Biezaca_pozycja + float(zmienne->Predkosc) * zmienne->Kierunek;
	double D_energia = zmienne->Predkosc / 60000.0f;
	zmienne->Energia = zmienne->Energia - D_energia;
	//Obrot - wskazanie energii:
	vpom = glm::vec3((wskazowki[w0 * 11] + wskazowki[(w0 + 2) * 11]) / 2.0, (wskazowki[w0 * 11 + 1] + wskazowki[(w0 + 2) * 11 + 1]) / 2.0, (wskazowki[w0 * 11 + 2] + wskazowki[(w0 + 2) * 11 + 2]) / 2.0);
	//Cofniecie do zera
	for (int i = 0; i < 3; i++) {
		wskazowki[(w0 + i) * 11] = wskazowki[(w0 + i) * 11] - vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = wskazowki[(w0 + i) * 11 + 1] - vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = wskazowki[(w0 + i) * 11 + 2] - vpom.z;
	}
	//Obrot
	for (int i = 0; i < 3; i++) {
		vpom2 = glm::vec3(
			wskazowki[(w0 + i) * 11],
			wskazowki[(w0 + i) * 11 + 1],
			wskazowki[(w0 + i) * 11 + 2]
		);
		vpom2 = glm::rotate(vpom2, 1.95f * float(M_PI * (D_energia) / MAX_PREDKOSC), glm::normalize(zmienne->Os_zegarow));
		wskazowki[(w0 + i) * 11] = vpom2.x + vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = vpom2.y + vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = vpom2.z + vpom.z;

	}



	//KIERUNEK I DYSTANS - aktualizacja:
	zmienne->Kierunek = glm::normalize(zmienne->Punkt_docelowy - zmienne->Biezaca_pozycja);
	zmienne->Odleglosc = glm::length(zmienne->Punkt_docelowy - zmienne->Biezaca_pozycja);



	return 1;//pomyslne ukonczenie

}