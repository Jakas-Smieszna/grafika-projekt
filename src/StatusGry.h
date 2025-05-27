#ifndef STATUSGRY_H
#define STATUSGRY_H
#include<iostream>
#include<cstdlib>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#ifndef _STATUS_GRY_DEFKI_1_
#define _STATUS_GRY_DEFKI_1_
#define _JG_DL_RAM_MON_POJ_ 1.8027756377319946465596106337352//Wyliczona recznie dlugosc przeciwprostokatnej trojkata monitora
#define TOL 1e-12//Tolerancja
#define MAX_PREDKOSC 100.0
#define MAX_ENERGIA 100000.0
#define MAX_ODLEGLOSC 10000.0
#define M_PI 3.141592653589793238462643383279502884197169399375105820
#define MAX_PRZYSPIESZANIE 10
#define LICZBA_VERTICES_TABLIC 12
#endif // !_STATUS_GRY_DEFKI_1_

class Pakiet_Zmiennych {
	public:
	glm::vec3 Punkt_docelowy;//Cel podrozy - wspolzedne.
	glm::vec3 Biezaca_pozycja;//Pozycja pojazdu. Latwiej chyba bedzie przesuwac pojazd niz otaczajacy go teren.
	glm::vec3 Kierunek;//Zwrot poazdu. Wektor znormalizowany.
	glm::vec3 Kierunek_do_celu;//Kierunek do celu.
	double Predkosc;//Biezaca predkosc pojazdu.
	double Energia;//Biezaca energia pojazdu.
	double Odleglosc;//Odleglosc od celu //liczona z zawartych zmiennych - moze usune
	unsigned int Czas_klatki;//Liczba klatek od sytartu rozgrywki.
	double Skret_kat;//Obrot pojazdu w klatce

	int Czas_przyspieszanie;//Liczba klatek przyspieszania pojazdu.

	int Rozmiar_vertices[LICZBA_VERTICES_TABLIC]{};//Tabica z liczba wierzcholkow w kazdej tablicy wierzcholkow (na razie tylko pojazdu)

	glm::vec3 Os_zegarow;//Przechowuje wektor prostopadly do zegarow.

	//Konstruktor domyslny
	Pakiet_Zmiennych() {

		//LOSOWY KIERUNEK DO CELU
		srand(time(NULL));
		//Punkt_docelowy = glm::vec3(0.0f, 0.0f, float(MAX_ODLEGLOSC));
		Punkt_docelowy = glm::vec3(glm::rotate(glm::vec3(0.0f, 0.0f, float(MAX_ODLEGLOSC)), float(float(rand() % 36000)/36000.0f*2.0f*M_PI), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))));
		//STARTOWA POZYCJA
		Biezaca_pozycja = glm::vec3(0.f, 0.f, 0.f);
		//KIEUNEK
		Kierunek = glm::vec3(0.f, 0.f, 1.f);
		//KIERUNEK DO CELU - pierwszy na wporst, by automatycznie liczyc przy pierwszej aktualizacji
		Kierunek_do_celu = Kierunek;
		//Kierunek_do_celu = glm::normalize(Punkt_docelowy - Biezaca_pozycja);
		//STARTOWA PREDKOSC
		Predkosc = 0.0;
		//STARTOWA ENERGIA
		Energia = MAX_ENERGIA;
		//ODLEGLOSC - pierwsze liczenie
		Odleglosc = glm::length(Punkt_docelowy - Biezaca_pozycja);
		//CZAS W KLATKACH - zerowanie
		Czas_klatki = 0;
		//ZAKRECANIE - KAT
		Skret_kat = 0.0;

		//CZAS PRZYSPIESZENIA W KLATKACH - zerowanie
		Czas_przyspieszanie = 0;

		//OS ZEGAROW - zerowanie
		Os_zegarow = glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), -0.5880026035475675512456110806250854276017072460559243537260472078359201315933085f + float(-M_PI) / 2.0f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));

	}

};



int InicjujZmienne1(GLFWwindow* okno, Pakiet_Zmiennych* zmienne, GLfloat* wskazowki);
int AktualizujZmienne1(GLFWwindow* okno, Pakiet_Zmiennych* zmienne, GLfloat* wskazowki, GLfloat* korpus, GLfloat* lampa, GLfloat* zaplon, GLfloat* pusch, GLfloat* pusch_F, GLfloat* pusch_T, GLfloat* kule, GLfloat* zeg1, GLfloat* zeg2, GLfloat* zeg3, GLfloat* zeg4);
int Przestaw_0_1_pojazd(Pakiet_Zmiennych* zmienne, int zmiana, GLfloat* wskazowki, GLfloat* korpus, GLfloat* lampa, GLfloat* zaplon, GLfloat* pusch, GLfloat* pusch_F, GLfloat* pusch_T, GLfloat* kule, GLfloat* zeg1, GLfloat* zeg2, GLfloat* zeg3, GLfloat* zeg4);

#endif