#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	GLuint ID;
	EBO() {}
	EBO(GLuint* indices, GLsizeiptr size);
	EBO(std::vector<GLuint>& indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif