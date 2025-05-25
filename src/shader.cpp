
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

#include "shader.h"
#include "helper/debugutils.h"

std::string get_file_contents(const char* filename)
{	
	fs::path fpath = std::string{filename};
	std::ifstream in(
		(fs::is_symlink(fpath) ? fs::read_symlink(fpath) : fpath).string(),
		std::ios::binary);
  
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	eprintf("Failed to get contents of file '%s'", fpath.string().c_str());
	//throw(errno);
	return std::string{""};
}

std::string getShaderPath(const char* shaderName) {
	return std::string{SHADER_RELPATH} + std::string{shaderName};
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(getShaderPath(vertexFile).c_str());
	std::string fragmentCode = get_file_contents(getShaderPath(fragmentFile).c_str());

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLint status = 0;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);

		printf("%s: %s\n", vertexFile, &errorLog[0]);

		// Exit with failure.
		glDeleteShader(vertexShader); // Don't leak the shader.
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);

		printf("%s: %s\n", fragmentFile, &errorLog[0]);

		// Exit with failure.
		glDeleteShader(fragmentShader); // Don't leak the shader.
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}