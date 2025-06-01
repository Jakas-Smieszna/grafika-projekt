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
#include"Instruction.h"
#include"State.h"

std::vector<GLfloat> instruction_vertices = {
   -1.0f, 1.00f, 0.0f, 0.0f, 1.0f,
   1.0f, 1.00f, 0.0f, 1.0f, 1.0f,
   -1.0f, -1.00f, 0.0f, 0.0f, 0.0f,
   1.0f, -1.00f, 0.0f, 1.0f, 0.0f,
};

std::vector <GLuint> instruction_indices = {
   0, 1, 2,
   1, 2, 3,
};

InstructionElements::InstructionElements() :
   shaderProgram("menu_default.vert", "menu_default.frag"),
   tekstura1(("insj.png"), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE)
{
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);

   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, instruction_vertices.size() * sizeof(instruction_vertices[0]), &instruction_vertices[0], GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, instruction_indices.size() * sizeof(instruction_indices[0]), &instruction_indices[0], GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void RenderInstruction(InstructionElements& instruction, GLFWwindow* window, State& state)
{

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   instruction.shaderProgram.Activate();

   glBindVertexArray(instruction.VAO);

   instruction.tekstura1.texUnit(instruction.shaderProgram, "ourTexture", 0);
   instruction.tekstura1.Bind();
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0));

   glfwWaitEventsTimeout(0.1);

   if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
      double xpos, ypos;
      glfwGetCursorPos(window, &xpos, &ypos);

      int width, height;
      glfwGetWindowSize(window, &width, &height);

      // Konwersja pozycji kursora na wspó³rzêdne znormalizowane (-1 do 1)
      float x = (2.0f * xpos) / width - 1.0f;
      float y = 1.0f - (2.0f * ypos) / height;

      // Przycisk 1 (instruction): obszar od (0.5, 0.95) do (1.0, 0.55)
      if (x >= -1.0f && x <= 1.0f && y <= 1.00f && y >= -1.00f) {
         state = State::MenuState;
         //std::cout << "instruction clicked!" << std::endl;
      }
   }


   glfwSwapBuffers(window);
   glfwPollEvents();

}