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
	//Obrot na min
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
	//Obrot na maks
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


	//ODLEGLOSC DO CELU
	w0 = 46;
	vpom = glm::vec3((wskazowki[w0 * 11] + wskazowki[(w0 + 2) * 11]) / 2.0, (wskazowki[w0 * 11 + 1] + wskazowki[(w0 + 2) * 11 + 1]) / 2.0, (wskazowki[w0 * 11 + 2] + wskazowki[(w0 + 2) * 11 + 2]) / 2.0);
	//Cofniecie do zera
	for (int i = 0; i < 3; i++) {
		wskazowki[(w0 + i) * 11] = wskazowki[(w0 + i) * 11] - vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = wskazowki[(w0 + i) * 11 + 1] - vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = wskazowki[(w0 + i) * 11 + 2] - vpom.z;
	}
	//Obrot na maks
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


	//KIERUNEK NA START 90, czyli na prost (domyslnie)


	return 0;
}










//AKTUALIZUJ WSKAZOWKI I WSKAZYWANE PRZEZ NIE PARAMETRY
int AktualizujZmienne1(GLFWwindow* okno, Pakiet_Zmiennych* zmienne, GLfloat* wskazowki, GLfloat* korpus, GLfloat* lampa, GLfloat* zaplon, GLfloat* pusch, GLfloat* pusch_F, GLfloat* pusch_T, GLfloat* kule, GLfloat* zeg1, GLfloat* zeg2, GLfloat* zeg3, GLfloat* zeg4, GLfloat* man) {

	glm::vec3 vpom = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 vpom2 = glm::vec3(0.f, 0.f, 0.f);
	int w0 = 65;//pierwszy wierzcholek wskazowki

	//Zerowanie pozycji oraz kata
	//Przestaw_0_1_pojazd(zmienne, -1, wskazowki, korpus, lampa, zaplon, pusch, pusch_F, pusch_T, kule, zeg1, zeg2, zeg3, zeg4);//COFNIECIE WSP POJAZDU DO O(0,0,0)
	Zrotuj_0_1_pojazd(zmienne, -1, wskazowki, korpus, lampa, zaplon, pusch, pusch_F, pusch_T, kule, zeg1, zeg2, zeg3, zeg4, man);//COFNIECIE WSP POJAZDU DO O(0,0,0)


		//ZMIANA PREDKOSCI
	//[PRZYSPIESZANIE - W; ZWALNIANIE - S]
	//PRZYSPIESZANIE
	if ((glfwGetKey(okno, GLFW_KEY_W) == GLFW_PRESS) && zmienne->Predkosc < MAX_PREDKOSC && zmienne->Czas_przyspieszanie < MAX_PRZYSPIESZANIE) {

		zmienne->Czas_przyspieszanie = zmienne->Czas_przyspieszanie + 1;

	}

	//ZWALNIANIE
	if ((glfwGetKey(okno, GLFW_KEY_S) == GLFW_PRESS) && zmienne->Predkosc > 0.0 && zmienne->Czas_przyspieszanie > -MAX_PRZYSPIESZANIE) {

		zmienne->Czas_przyspieszanie = zmienne->Czas_przyspieszanie - 1;
		
	}

	//AUTOMATYCZNE WYRUWNYWANIE KIEROWNICY
	if (!(((glfwGetKey(okno, GLFW_KEY_W) == GLFW_PRESS) && zmienne->Predkosc < MAX_PREDKOSC) || ((glfwGetKey(okno, GLFW_KEY_S) == GLFW_PRESS) && zmienne->Predkosc > 0.0))) {
		
		if (zmienne->Czas_przyspieszanie > 0) zmienne->Czas_przyspieszanie = zmienne->Czas_przyspieszanie - 1;
		else if (zmienne->Czas_przyspieszanie < 0) zmienne->Czas_przyspieszanie = zmienne->Czas_przyspieszanie + 1;

	}

	//ZMIANA PREDKOSCI
	double predkosc0 = zmienne->Predkosc;
	zmienne->Predkosc = zmienne->Predkosc + double(zmienne->Czas_przyspieszanie) / 1800.0;
	if (zmienne->Predkosc > MAX_PREDKOSC) zmienne->Predkosc = MAX_PREDKOSC;
	if (zmienne->Predkosc < 0.0) zmienne->Predkosc = 0.0;
	if (zmienne->Energia < TOL)  zmienne->Predkosc = 0.0;

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

	//ZAPLON
	zaplon[2] = 12.0f +  zmienne->Predkosc / MAX_PREDKOSC * (-20.0f);

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
	float Delta_kat = 0.0f;

	//SKRECANIE [W LEWO - A; W PRAWO - D]
	if ((glfwGetKey(okno, GLFW_KEY_A) == GLFW_PRESS)) {

		Delta_kat = 0.01f * M_PI;

	}
	else if((glfwGetKey(okno, GLFW_KEY_D) == GLFW_PRESS)) {

		Delta_kat = -0.01f * M_PI;

	}
	glm::vec3 Kierunek0 = zmienne->Kierunek;
	zmienne->Pojazd_kat = fmod(zmienne->Pojazd_kat + Delta_kat, 2.0f * M_PI);
	zmienne->Kierunek = glm::rotate(zmienne->Kierunek, Delta_kat, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
	//KONIEC SKRECANIA


	
	//PRZESUNIECIE 
	zmienne->Biezaca_pozycja = zmienne->Biezaca_pozycja + float(zmienne->Predkosc) * zmienne->Kierunek;
	
	//ZMIANY ENERGII
	w0 = 11;
	double D_energia = 2.0 * zmienne->Predkosc + PASYWNE_ZUZYCIE_ENERGII;
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
		vpom2 = glm::rotate(vpom2, 1.95f * float(M_PI * (D_energia) / MAX_ENERGIA), glm::normalize(zmienne->Os_zegarow));
		wskazowki[(w0 + i) * 11] = vpom2.x + vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = vpom2.y + vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = vpom2.z + vpom.z;

	}



	//KIERUNEK DO CELU I DYSTANS - aktualizacja:
	double Odleglosc0 = zmienne->Odleglosc;
	glm::vec3 Kierunek_do_celu0 = zmienne->Kierunek_do_celu;
	zmienne->Kierunek_do_celu = glm::normalize(zmienne->Punkt_docelowy - zmienne->Biezaca_pozycja);
	zmienne->Odleglosc = glm::length(zmienne->Punkt_docelowy - zmienne->Biezaca_pozycja);
	if (zmienne->Odleglosc - MAX_ODLEGLOSC > -TOL) zmienne->Odleglosc = MAX_ODLEGLOSC;//Max na wskazniku

	//AKTUALIZACJA WSKAZOWKI ODLEGLOSCI
	w0 = 46; 
	double D_DYSTANS = zmienne->Odleglosc - Odleglosc0;
	//Obrot - wskazanie dystansu do celu:
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
		vpom2 = glm::rotate(vpom2, -1.95f * float(M_PI * (D_DYSTANS) / MAX_ODLEGLOSC), glm::normalize(zmienne->Os_zegarow));
		wskazowki[(w0 + i) * 11] = vpom2.x + vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = vpom2.y + vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = vpom2.z + vpom.z;

	}


	//AKTUALIZACJA WSKAZOWKI KIERUNKU
	w0 = 4;
	//Liczenie zmiany kierunku do celu jako kata w radianach
	double KAT = 0.0f * M_PI;

	glm::vec2 KDC0(Kierunek_do_celu0.x, Kierunek_do_celu0.z);
	glm::vec2 KDC1(zmienne->Kierunek_do_celu.x, zmienne->Kierunek_do_celu.z);

	if (abs(KDC0.y) < TOL) {
		if (KDC0.x > -TOL) KAT = KAT + M_PI * 0.5;
		else KAT = KAT + M_PI * 1.5;
	}
	else {
		if (KDC0.y > -TOL) KAT = KAT + acos(KDC0.x / (sqrt(KDC0.x * KDC0.x + KDC0.y * KDC0.y)));
		else KAT = KAT - acos(KDC0.x / (sqrt(KDC0.x * KDC0.x + KDC0.y * KDC0.y))) + 2.0 * M_PI;
	}

	if (abs(KDC1.y) < TOL) {
		if (KDC1.x > -TOL) KAT = KAT - M_PI * 0.5;
		else KAT = KAT - M_PI * 1.5;
	}
	else {
		if (KDC1.y > -TOL) KAT = KAT - acos(KDC1.x / (sqrt(KDC1.x * KDC1.x + KDC1.y * KDC1.y)));
		else KAT = KAT + acos(KDC1.x / (sqrt(KDC1.x * KDC1.x + KDC1.y * KDC1.y))) - 2.0 * M_PI;
	}

	glm::vec2 K0(Kierunek0.x, Kierunek0.z);
	glm::vec2 K1(zmienne->Kierunek.x, zmienne->Kierunek.z);

	if (abs(K0.y) < TOL) {
		if (K0.x > -TOL) KAT = KAT - M_PI * 0.5;
		else KAT = KAT - M_PI * 1.5;
	}
	else {
		if (K0.y > -TOL) KAT = KAT - acos(K0.x / (sqrt(K0.x * K0.x + K0.y * K0.y)));
		else KAT = KAT + acos(K0.x / (sqrt(K0.x * K0.x + K0.y * K0.y))) - 2.0 * M_PI;
	}

	if (abs(K1.y) < TOL) {
		if (K1.x > -TOL) KAT = KAT + M_PI * 0.5;
		else KAT = KAT + M_PI * 1.5;
	}
	else {
		if (K1.y > -TOL) KAT = KAT + acos(K1.x / (sqrt(K1.x * K1.x + K1.y * K1.y)));
		else KAT = KAT - acos(K1.x / (sqrt(K1.x * K1.x + K1.y * K1.y))) + 2.0 * M_PI;
	}

	//std::cout << "KAT = " << KAT << "\t Kierunek do celu [" << zmienne->Kierunek_do_celu.x << ", " << zmienne->Kierunek_do_celu.y << ", " << zmienne->Kierunek_do_celu.z <<"]\t" << "Kierunek [" << zmienne->Kierunek.x << ", " << zmienne->Kierunek.y << ", " << zmienne->Kierunek.z << "]\n";

	//Obrot - wskazanie kierunku:
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
		vpom2 = glm::rotate(vpom2, float(KAT), glm::normalize(zmienne->Os_zegarow));
		wskazowki[(w0 + i) * 11] = vpom2.x + vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = vpom2.y + vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = vpom2.z + vpom.z;

	}

	//POWROT DO POZYCJI NA MAPIE
	Zrotuj_0_1_pojazd(zmienne, 1, wskazowki, korpus, lampa, zaplon, pusch, pusch_F, pusch_T, kule, zeg1, zeg2, zeg3, zeg4, man);
	//Przestaw_0_1_pojazd(zmienne, 1, wskazowki, korpus, lampa, zaplon, pusch, pusch_F, pusch_T, kule, zeg1, zeg2, zeg3, zeg4);


	return 1;//pomyslne ukonczenie

}



//Funkcja do przestawiania pojazdu do punktu poczatkowego i zerowej rotacji oraz do jego ponownego przesuwania na nowa pozycje i rotacje.
//zmiana = -1: wroc do O(0,0,0)
//zmiana = 1: wroc do Biezacej pozycji
int Przestaw_0_1_pojazd(Pakiet_Zmiennych* zmienne, int zmiana, GLfloat* monitor, GLfloat* korpus, GLfloat* lampa, GLfloat* zaplon, GLfloat* pusch, GLfloat* pusch_F, GLfloat* pusch_T, GLfloat* kule, GLfloat* zeg1, GLfloat* zeg2, GLfloat* zeg3, GLfloat* zeg4, GLfloat* man) {

	int DL1 = 11;
	int DL2 = 3;
	int DL3 = 7;


	//POZYCJA
	for (int i = 0; i < zmienne->Rozmiar_vertices[0]; i = i + DL1) {

		korpus[i] = korpus[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		korpus[i + 1] = korpus[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		korpus[i + 2] = korpus[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[1]; i = i + DL1) {

		monitor[i] = monitor[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		monitor[i + 1] = monitor[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		monitor[i + 2] = monitor[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[2]; i = i + DL2) {

		lampa[i] = lampa[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		lampa[i + 1] = lampa[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		lampa[i + 2] = lampa[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[3]; i = i + DL3) {

		zaplon[i] = zaplon[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		zaplon[i + 1] = zaplon[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		zaplon[i + 2] = zaplon[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[4]; i = i + DL2) {

		pusch[i] = pusch[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		pusch[i + 1] = pusch[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		pusch[i + 2] = pusch[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[5]; i = i + DL2) {

		kule[i] = kule[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		kule[i + 1] = kule[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		kule[i + 2] = kule[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[6]; i = i + DL1) {

		zeg1[i] = zeg1[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		zeg1[i + 1] = zeg1[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		zeg1[i + 2] = zeg1[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[7]; i = i + DL1) {

		zeg2[i] = zeg2[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		zeg2[i + 1] = zeg2[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		zeg2[i + 2] = zeg2[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[8]; i = i + DL1) {

		zeg3[i] = zeg3[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		zeg3[i + 1] = zeg3[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		zeg3[i + 2] = zeg3[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[9]; i = i + DL1) {

		zeg4[i] = zeg4[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		zeg4[i + 1] = zeg4[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		zeg4[i + 2] = zeg4[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[10]; i = i + DL2) {

		pusch_F[i] = pusch_F[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		pusch_F[i + 1] = pusch_F[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		pusch_F[i + 2] = pusch_F[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[11]; i = i + DL2) {

		pusch_T[i] = pusch_T[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		pusch_T[i + 1] = pusch_T[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		pusch_T[i + 2] = pusch_T[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[12]; i = i + DL1) {

		man[i] = man[i] + float(zmiana) * zmienne->Biezaca_pozycja.x;
		man[i + 1] = man[i + 1] + float(zmiana) * zmienne->Biezaca_pozycja.y;
		man[i + 2] = man[i + 2] + float(zmiana) * zmienne->Biezaca_pozycja.z;

	}
	//KONIEC POZYCJA

	return 1;

}



int Zrotuj_0_1_pojazd(Pakiet_Zmiennych* zmienne, int zmiana, GLfloat* monitor, GLfloat* korpus, GLfloat* lampa, GLfloat* zaplon, GLfloat* pusch, GLfloat* pusch_F, GLfloat* pusch_T, GLfloat* kule, GLfloat* zeg1, GLfloat* zeg2, GLfloat* zeg3, GLfloat* zeg4, GLfloat * man) {

	int DL1 = 11;
	int DL2 = 3;
	int DL3 = 7;

	glm::vec3 vpom(0.f, 0.f, 0.f);

	//KAT
	for (int i = 0; i < zmienne->Rozmiar_vertices[0]; i = i + DL1) {
		//Pozycja
		vpom = glm::vec3(
			korpus[i],
			korpus[i + 1],
			korpus[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		korpus[i] = vpom.x;
		korpus[i + 1] = vpom.y;
		korpus[i + 2] = vpom.z;
		//Wektory normalne
		vpom = glm::vec3(
			korpus[i + 8],
			korpus[i + 9],
			korpus[i + 10]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		korpus[i + 8] = vpom.x;
		korpus[i + 9] = vpom.y;
		korpus[i + 10] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[1]; i = i + DL1) {
		//pozycja
		vpom = glm::vec3(
			monitor[i],
			monitor[i + 1],
			monitor[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		monitor[i] = vpom.x;
		monitor[i + 1] = vpom.y;
		monitor[i + 2] = vpom.z;
		//wektory.n
		vpom = glm::vec3(
			monitor[i + 8],
			monitor[i + 9],
			monitor[i + 10]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		monitor[i + 8] = vpom.x;
		monitor[i + 9] = vpom.y;
		monitor[i + 10] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[2]; i = i + DL2) {
		//pozycja
		vpom = glm::vec3(
			lampa[i],
			lampa[i + 1],
			lampa[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		lampa[i] = vpom.x;
		lampa[i + 1] = vpom.y;
		lampa[i + 2] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[3]; i = i + DL3) {
		//pozycja
		vpom = glm::vec3(
			zaplon[i],
			zaplon[i + 1],
			zaplon[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		zaplon[i] = vpom.x;
		zaplon[i + 1] = vpom.y;
		zaplon[i + 2] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[4]; i = i + DL2) {
		//pozycja
		vpom = glm::vec3(
			pusch[i],
			pusch[i + 1],
			pusch[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		pusch[i] = vpom.x;
		pusch[i + 1] = vpom.y;
		pusch[i + 2] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[5]; i = i + DL2) {
		//pozycja
		vpom = glm::vec3(
			kule[i],
			kule[i + 1],
			kule[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		kule[i] = vpom.x;
		kule[i + 1] = vpom.y;
		kule[i + 2] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[6]; i = i + DL1) {
		//pozycja
		vpom = glm::vec3(
			zeg1[i],
			zeg1[i + 1],
			zeg1[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		zeg1[i] = vpom.x;
		zeg1[i + 1] = vpom.y;
		zeg1[i + 2] = vpom.z;
		//wektory.n
		vpom = glm::vec3(
			zeg1[i + 8],
			zeg1[i + 9],
			zeg1[i + 10]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		zeg1[i + 8] = vpom.x;
		zeg1[i + 9] = vpom.y;
		zeg1[i + 10] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[7]; i = i + DL1) {
		//pozycje
		vpom = glm::vec3(
			zeg2[i],
			zeg2[i + 1],
			zeg2[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		zeg2[i] = vpom.x;
		zeg2[i + 1] = vpom.y;
		zeg2[i + 2] = vpom.z;
		//wektory.n
		vpom = glm::vec3(
			zeg2[i + 8],
			zeg2[i + 9],
			zeg2[i + 10]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		zeg2[i + 8] = vpom.x;
		zeg2[i + 9] = vpom.y;
		zeg2[i + 10] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[8]; i = i + DL1) {
		//pozycja
		vpom = glm::vec3(
			zeg3[i],
			zeg3[i + 1],
			zeg3[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		zeg3[i] = vpom.x;
		zeg3[i + 1] = vpom.y;
		zeg3[i + 2] = vpom.z;
		//wektory.n
		vpom = glm::vec3(
			zeg3[i + 8],
			zeg3[i + 9],
			zeg3[i + 10]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		zeg3[i + 8] = vpom.x;
		zeg3[i + 9] = vpom.y;
		zeg3[i + 10] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[9]; i = i + DL1) {
		//pozycja
		vpom = glm::vec3(
			zeg4[i],
			zeg4[i + 1],
			zeg4[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		zeg4[i] = vpom.x;
		zeg4[i + 1] = vpom.y;
		zeg4[i + 2] = vpom.z;
		//wektory.n
		vpom = glm::vec3(
			zeg4[i + 8],
			zeg4[i + 9],
			zeg4[i + 10]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		zeg4[i + 8] = vpom.x;
		zeg4[i + 9] = vpom.y;
		zeg4[i + 10] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[10]; i = i + DL2) {
		//pozycja
		vpom = glm::vec3(
			pusch_F[i],
			pusch_F[i + 1],
			pusch_F[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		pusch_F[i] = vpom.x;
		pusch_F[i + 1] = vpom.y;
		pusch_F[i + 2] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[11]; i = i + DL2) {
		//pozycja
		vpom = glm::vec3(
			pusch_T[i],
			pusch_T[i + 1],
			pusch_T[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		pusch_T[i] = vpom.x;
		pusch_T[i + 1] = vpom.y;
		pusch_T[i + 2] = vpom.z;

	}
	for (int i = 0; i < zmienne->Rozmiar_vertices[12]; i = i + DL1) {
		//pozycja
		vpom = glm::vec3(
			man[i],
			man[i + 1],
			man[i + 2]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		man[i] = vpom.x;
		man[i + 1] = vpom.y;
		man[i + 2] = vpom.z;
		//wektory.n
		vpom = glm::vec3(
			man[i + 8],
			man[i + 9],
			man[i + 10]
		);
		vpom = glm::rotate(vpom, float(zmiana * zmienne->Pojazd_kat), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));
		man[i + 8] = vpom.x;
		man[i + 9] = vpom.y;
		man[i + 10] = vpom.z;

	}
	//KONIEC KAT

	return 1;

}







//USTAW WSKAZOWKI NA POZYCJACH POCZATKOWYCH
int ResetujZmienne1(GLFWwindow* okno, Pakiet_Zmiennych* zmienne, GLfloat* wskazowki) {

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
	//Obrot na min
	for (int i = 0; i < 3; i++) {
		vpom2 = glm::vec3(
			wskazowki[(w0 + i) * 11],
			wskazowki[(w0 + i) * 11 + 1],
			wskazowki[(w0 + i) * 11 + 2]
		);
		vpom2 = glm::rotate(vpom2, 0.975f * float(2.0 * M_PI * zmienne->Predkosc / MAX_PREDKOSC), glm::normalize(zmienne->Os_zegarow));
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
	//Obrot na maks
	for (int i = 0; i < 3; i++) {
		vpom2 = glm::vec3(
			wskazowki[(w0 + i) * 11],
			wskazowki[(w0 + i) * 11 + 1],
			wskazowki[(w0 + i) * 11 + 2]
		);
		vpom2 = glm::rotate(vpom2, -0.975f * float(2.0 * M_PI * (1.0 - zmienne->Energia / MAX_ENERGIA)), glm::normalize(zmienne->Os_zegarow));
		wskazowki[(w0 + i) * 11] = vpom2.x + vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = vpom2.y + vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = vpom2.z + vpom.z;

	}


	//ODLEGLOSC DO CELU
	w0 = 46;
	vpom = glm::vec3((wskazowki[w0 * 11] + wskazowki[(w0 + 2) * 11]) / 2.0, (wskazowki[w0 * 11 + 1] + wskazowki[(w0 + 2) * 11 + 1]) / 2.0, (wskazowki[w0 * 11 + 2] + wskazowki[(w0 + 2) * 11 + 2]) / 2.0);
	//Cofniecie do zera
	for (int i = 0; i < 3; i++) {
		wskazowki[(w0 + i) * 11] = wskazowki[(w0 + i) * 11] - vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = wskazowki[(w0 + i) * 11 + 1] - vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = wskazowki[(w0 + i) * 11 + 2] - vpom.z;
	}
	//Obrot na maks
	for (int i = 0; i < 3; i++) {
		vpom2 = glm::vec3(
			wskazowki[(w0 + i) * 11],
			wskazowki[(w0 + i) * 11 + 1],
			wskazowki[(w0 + i) * 11 + 2]
		);
		vpom2 = glm::rotate(vpom2, -0.975f * float(2.0 * M_PI * (1.0 - zmienne->Odleglosc / MAX_ODLEGLOSC)), glm::normalize(zmienne->Os_zegarow));
		wskazowki[(w0 + i) * 11] = vpom2.x + vpom.x;
		wskazowki[(w0 + i) * 11 + 1] = vpom2.y + vpom.y;
		wskazowki[(w0 + i) * 11 + 2] = vpom2.z + vpom.z;

	}




	////AKTUALIZACJA WSKAZOWKI KIERUNKU
	//COFANIE WSKAZOWKI KIERUNKU
	wskazowki[4 * 11] = 0.57;
	wskazowki[4 * 11 + 1] = 1.83475;
	wskazowki[4 * 11 + 2] = -0.424923;

	wskazowki[5 * 11] = 0.6;
	wskazowki[5 * 11 + 1] = 2.02889;
	wskazowki[5 * 11 + 2] = -0.133705;

	wskazowki[6 * 11] = 0.63;
	wskazowki[6 * 11 + 1] = 1.83475;
	wskazowki[6 * 11 + 2] = -0.424923;




	return 0;
}