#ifndef MENU_CLASS_H
#define MENU_CLASS_H

extern std::vector<GLfloat> menu_vertices;

extern std::vector<GLuint> menu_indices;

class MenuElements {
public:
   GLuint vertexShader;
   GLuint fragmentShader;

   GLuint shaderProgram;

   GLuint VAO, VBO, EBO;

   MenuElements();
};

void RenderMenu(MenuElements &menu,GLFWwindow* window);


#endif