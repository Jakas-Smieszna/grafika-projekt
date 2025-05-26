#include<iostream>
#include<vector>
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
#include"stb/stb_image.h"
//
#include"shader.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Kamera.h"
#include"Menu.h"

std::vector<GLfloat> menu_vertices = {
   -0.4f, 0.95f, 0.0f,
   0.4f, 0.95f, 0.0f,
   -0.4f, 0.55f, 0.0f,
   0.4f, 0.55f, 0.0f,
   -0.4f, 0.45f, 0.0f,
   0.4f, 0.45f, 0.0f,
   -0.4f, 0.05f, 0.0f,
   0.4f, 0.05f, 0.0f,
   -0.4f, -0.05f, 0.0f,
   0.4f, -0.05f, 0.0f,
   -0.4f, -0.45f, 0.0f,
   0.4f, -0.45f, 0.0f,
   -0.4f, -0.55f, 0.0f,
   0.4f, -0.55f, 0.0f,
   -0.4f, -0.95f, 0.0f,
   0.4f, -0.95f, 0.0f
};

std::vector <GLuint> menu_indices = {
   0, 1, 2,
   1, 2, 3,
   4, 5, 6,
   5, 6, 7,
   8, 9, 10,
   9, 10, 11,
   12, 13, 14,
   13, 14, 15
};

MenuElements::MenuElements() 
{


   vertexShader = glCreateShader(GL_VERTEX_SHADER);
   std::string vs_source = get_file_contents("menu_default.vert");
   const char* vertsh = vs_source.c_str();

   glShaderSource(vertexShader, 1, &vertsh, NULL);
   glCompileShader(vertexShader);
   

   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   std::string fs_source = get_file_contents("menu_default.frag");
   const char* fragsh = fs_source.c_str();
   glShaderSource(fragmentShader, 1, &fragsh, NULL);
   glCompileShader(fragmentShader);


   shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);

   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);

   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, menu_vertices.size() * sizeof(menu_vertices[0]), &menu_vertices[0], GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, menu_indices.size() * sizeof(menu_indices[0]), &menu_indices[0], GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderMenu(MenuElements &menu, GLFWwindow* window)
{

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         glUseProgram(menu.shaderProgram);

         glBindVertexArray(menu.VAO);

         glDrawElements(GL_TRIANGLES, menu_indices.size(), GL_UNSIGNED_INT, 0);

         glfwSwapBuffers(window);
         glfwPollEvents();

}