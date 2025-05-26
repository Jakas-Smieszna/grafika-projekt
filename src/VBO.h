#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>
#include <vector>
#include "shader.h"
#include "vertex.h"

class VBO
{
public:
	GLuint ID;
	VBO() {}
	VBO(GLfloat* vertices, GLsizeiptr size);
	VBO(std::vector<Vertex>& vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif