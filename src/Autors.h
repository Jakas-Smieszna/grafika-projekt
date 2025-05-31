#ifndef AUTORS_CLASS_H
#define AUTORS_CLASS_H
#include"State.h"

extern std::vector<GLfloat> autors_vertices;

extern std::vector<GLuint> autors_indices;

class AutorsElements {
public:
   Shader shaderProgram;

   GLuint VAO, VBO, EBO;

   Texture tekstura1;

   AutorsElements();
};

void RenderAutors(AutorsElements& autors, GLFWwindow* window, State& state);


#endif