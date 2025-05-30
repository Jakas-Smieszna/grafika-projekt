#ifndef MENU_CLASS_H
#define MENU_CLASS_H

extern std::vector<GLfloat> menu_vertices;

extern std::vector<GLuint> menu_indices;

class MenuElements {
public:
   Shader shaderProgram;

   GLuint VAO, VBO, EBO;

   std::string parentDir;
   std::string texPath;

   Texture tekstura1;
   Texture tekstura2;
   Texture tekstura3;
   Texture tekstura4;

   MenuElements();
};

void RenderMenu(MenuElements &menu,GLFWwindow* window);


#endif