#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
};

#ifdef _WIN32
#define SHADER_RELPATH "shaders\\"
#elif __linux__
#ifdef DEBUG_BUILD
#define SHADER_RELPATH "out/build/linux-debug-x64/bin/shaders/"
#else
#define SHADER_RELPATH "out/build/linux-release-x64/bin/shaders/"
#endif
#else
#define SHADER_RELPATH ""
#endif

#endif