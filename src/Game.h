#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include<vector>

//Teksturowo:
// POJAZD
extern std::vector<GLfloat> vertices;
extern std::vector<GLuint> indices;

//Na monitorze (odczyty):
extern std::vector<GLfloat> Mon_Vertices;
extern std::vector<GLuint> Mon_Indices;

//Swiatlo (lampa):
extern std::vector<GLfloat> lightVertices;
extern std::vector<GLuint> lightIndices;

//Swiatlo2 (zaplon):
extern std::vector<GLfloat> lightVertices2;
extern std::vector<GLuint> lightIndices2;

//Odpychanie centralne:
//-11z
extern std::vector<GLfloat> pushVertices[66 * 3 + 33 * 3 + 17 * 3 + 9 * 3 + 5 * 3];
extern std::vector<GLuint> pushIndices[66 * 3 + 33 * 3 * 2 + 17 * 3 * 2 + 9 * 3 * 2 + 5 * 3 * 2];

extern std::vector<GLfloat> pushVertices_front[66 * 3 + 33 * 3 + 17 * 3 + 9 * 3 + 5 * 3];
extern std::vector<GLfloat> pushVertices_tyl[66 * 3 + 33 * 3 + 17 * 3 + 9 * 3 + 5 * 3];

//Kule
//
extern std::vector<GLfloat> KulaVertices[2 * (66 * 3 + 33 * 3 + 17 * 3 + 9 * 3 + 5 * 3)];
extern std::vector<GLuint> KulaIndices[2 * (66 * 3 + 33 * 3 * 2 + 17 * 3 * 2 + 9 * 3 * 2 + 5 * 3 * 2)];

//Ramy wskazowek
extern std::vector<GLfloat>  Zeg1Vertices[130 * 11 + 65 * 11 + 130 * 11];
extern std::vector<GLuint> Zeg1Indices[130 * 3 + 65 * 3 + 130 * 3];

extern std::vector<GLfloat>  Zeg2Vertices[130 * 11 + 65 * 11 + 130 * 11];
extern std::vector<GLuint> Zeg2Indices[130 * 3 + 65 * 3 + 130 * 3];

extern std::vector<GLfloat>  Zeg3Vertices[130 * 11 + 65 * 11 + 130 * 11];
extern std::vector<GLuint> Zeg3Indices[130 * 3 + 65 * 3 + 130 * 3];

extern std::vector<GLfloat>  Zeg4Vertices[130 * 11 + 65 * 11 + 130 * 11];
extern std::vector<GLuint> Zeg4Indices[130 * 3 + 65 * 3 + 130 * 3];


class GameElements {
public:

	Pakiet_Zmiennych zmienne;//Cos mi extern nie dzialalo tutaj jak w poprzednim projekcie(JG)

	Shader shaderProgram;
	VAO VAO1;
	VBO VBO1;
	EBO EBO1;

	//std::string parentDir;
	//std::string texPath;

	Texture tekstura1;
	Texture tekstura2;


	//swiatlo:
	Shader lightShader;
	VAO lightVAO;
	VBO lightVBO;
	EBO lightEBO;

	glm::vec4 lightColor;
	glm::vec3 lightPos;
	glm::mat4 lightModel;
	glm::vec3 cubePos;
	glm::mat4 cubeModel;

	//swiatlo 2:
	Shader lightShader2;
	VAO light2VAO;
	VBO light2VBO;
	EBO light2EBO;

	glm::vec4 light2Color;
	glm::vec3 light2Pos;
	glm::mat4 light2Model;
	glm::vec3 cube2Pos;
	glm::mat4 cube2Model;

	Camera camera;
	GameElements(GLFWwindow* okno);

};

void UpdateGameState(GameElements& game, GLFWwindow* window);
void RenderScene(GameElements& game, GLFWwindow* window);

#endif // GAME_CLASS_H
