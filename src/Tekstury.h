#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shader.h"
class Texture {
public:
	GLuint ID;
	GLenum GLTexType;
	std::string type;

	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum
		pixelType);
	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};

#ifdef _WIN32
#define TEXTURE_RELPATH "resources\\"
#elif __linux__

#ifdef DEBUG_BUILD
#define TEXTURE_RELPATH "out/build/linux-debug-x64/bin/resources/"
#else
#define TEXTURE_RELPATH "out/build/linux-release-x64/bin/resources/"
#endif // DEBUG_BUILD

#else
#define TEXTURE_RELPATH ""
#endif // _WIN32

#endif // TEXTURE_CLASS_H