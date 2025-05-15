#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "helper/debugutils.h"
#include <cstdio>
#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	GLuint ID;
	EBO() {eprintf("EBO initialized with no arguments at line %u", __LINE__);}
	EBO(GLuint* indices, GLsizeiptr size);
	EBO(std::vector<GLuint> &indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif