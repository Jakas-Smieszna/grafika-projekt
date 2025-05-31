#ifndef INSTRUCTION_CLASS_H
#define INSTRUCTION_CLASS_H
#include"State.h"

extern std::vector<GLfloat> instruction_vertices;

extern std::vector<GLuint> instruction_indices;

class InstructionElements {
public:
   Shader shaderProgram;

   GLuint VAO, VBO, EBO;

   Texture tekstura1;

   InstructionElements();
};

void RenderInstruction(InstructionElements& instruction, GLFWwindow* window, State& state);


#endif