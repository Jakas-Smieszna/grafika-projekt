#ifndef GAME_CLASS_H
#define GAME_CLASS_H
//Teksturowo:
// Wierzcholki2
extern GLfloat vertices[];

// Przyporzadkowanie wierzcholkow do trojkatow2
extern GLuint indices[];

//Swiatlo:

extern GLfloat lightVertices[];

extern GLuint lightIndices[];

class GameElements {
public:
	Shader shaderProgram;
	VAO VAO1;
	VBO VBO1;
	EBO EBO1;

	std::string parentDir;
	std::string texPath;

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
	int chuj;
	GameElements();

};

void UpdateGameState(GameElements &game, GLFWwindow* window);

void RenderScene(GameElements &game, GLFWwindow* window);

#endif // GAME_CLASS_H