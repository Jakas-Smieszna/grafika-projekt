#ifndef MENU_CLASS_H
#define MENU_CLASS_H
#include"State.h"

extern std::vector<GLfloat> menu_vertices;

extern std::vector<GLuint> menu_indices;

class MenuElements {
public:
   Shader shaderProgram;

   GLuint VAO, VBO, EBO;

   Texture tekstura1;
   Texture tekstura2;
   Texture tekstura3;
   Texture tekstura4;

   std::vector<Texture> tekstury_obrazu;
   MenuElements();
};

void RenderMenu(MenuElements &menu,GLFWwindow* window, State &state);


#endif