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
#include"State.h"

std::vector<GLfloat> menu_vertices = {
   0.5f, 0.95f, 0.0f, 0.0f, 1.0f,
   1.0f, 0.95f, 0.0f, 1.0f, 1.0f,
   0.5f, 0.55f, 0.0f, 0.0f, 0.0f,
   1.0f, 0.55f, 0.0f, 1.0f, 0.0f,
   0.5f, 0.55f, 0.0f,0.0f, 1.0f,
   1.0f, 0.55f, 0.0f, 1.0f, 1.0f,
   0.5f, 0.15f, 0.0f, 0.0f, 0.0f,
   1.0f, 0.15f, 0.0f, 1.0f, 0.0f,
   0.5f, 0.15f, 0.0f,0.0f, 1.0f,
   1.0f, 0.15f, 0.0f, 1.0f, 1.0f,
   0.5f, -0.25f, 0.0f, 0.0f, 0.0f,
   1.0f, -0.25f, 0.0f, 1.0f, 0.0f,
   0.5f, -0.25f, 0.0f,0.0f, 1.0f,
   1.0f, -0.25f, 0.0f, 1.0f, 1.0f,
   0.5f, -0.65f, 0.0f, 0.0f, 0.0f,
   1.0f, -0.65f, 0.0f, 1.0f, 0.0f
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

MenuElements::MenuElements() : 
   shaderProgram("menu_default.vert", "menu_default.frag"),
   tekstura1(("start.png"), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
   tekstura2(("instrukcja.png"), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
   tekstura3(("wyniki.png"), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
   tekstura4(("wyjscie.png"), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE)
{
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);

   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, menu_vertices.size() * sizeof(menu_vertices[0]), &menu_vertices[0], GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, menu_indices.size() * sizeof(menu_indices[0]), &menu_indices[0], GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void RenderMenu(MenuElements &menu, GLFWwindow* window, State &state)
{

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   menu.shaderProgram.Activate();

   glBindVertexArray(menu.VAO);

   menu.tekstura1.texUnit(menu.shaderProgram, "ourTexture", 0);
   menu.tekstura1.Bind();
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0));
   menu.tekstura2.texUnit(menu.shaderProgram, "ourTexture", 0);
   menu.tekstura2.Bind();
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint)));
   menu.tekstura3.texUnit(menu.shaderProgram, "ourTexture", 0);
   menu.tekstura3.Bind();
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(GLuint)));
   menu.tekstura4.texUnit(menu.shaderProgram, "ourTexture", 0);
   menu.tekstura4.Bind();
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(GLuint)));

   if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
      double xpos, ypos;
      glfwGetCursorPos(window, &xpos, &ypos);

      int width, height;
      glfwGetWindowSize(window, &width, &height);

      // Konwersja pozycji kursora na wspó³rzêdne znormalizowane (-1 do 1)
      float x = (2.0f * xpos) / width - 1.0f;
      float y = 1.0f - (2.0f * ypos) / height;

      // Sprawdzenie, który przycisk zosta³ klikniêty
      // Przycisk 1 (Start): obszar od (0.5, 0.95) do (1.0, 0.55)
      if (x >= 0.5f && x <= 1.0f && y <= 0.95f && y >= 0.55f) {
         state = State::PlayState;
         std::cout << "Start clicked!" << std::endl;
      }
      // Przycisk 2 (Instrukcja): obszar od (0.5, 0.55) do (1.0, 0.15)
      else if (x >= 0.5f && x <= 1.0f && y <= 0.55f && y >= 0.15f) {
         std::cout << "Instructions clicked!" << std::endl;
      }
      // Przycisk 3 (Wyniki): obszar od (0.5, 0.15) do (1.0, -0.25)
      else if (x >= 0.5f && x <= 1.0f && y <= 0.15f && y >= -0.25f) {
         std::cout << "Scores clicked!" << std::endl;
      }
      // Przycisk 4 (Wyjœcie): obszar od (0.5, -0.25) do (1.0, -0.65)
      else if (x >= 0.5f && x <= 1.0f && y <= -0.25f && y >= -0.65f) {
         glfwSetWindowShouldClose(window, GLFW_TRUE);
         std::cout << "Exit clicked!" << std::endl;
      }
   }


   glfwSwapBuffers(window);
   glfwPollEvents();

}