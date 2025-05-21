#include"Tekstury.h"
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum
	pixelType)
{
	GLTexType = texType;
	int widthImg, heightImg, numColCh;

	// Ścieżka do tekstury automatycznie w dobrym folderze.
	std::string fpath = std::string{TEXTURE_RELPATH} + std::string{image}; 

	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(fpath.c_str(), &widthImg, &heightImg, &numColCh, 0);
	if(!bytes) {
		eprintf("Unable to load texture '%s'", fpath.c_str());
	} else {
		dbgprintf("Loaded texture '%s'", fpath.c_str());
	}
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);
	
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// Dodatkowe linie dla GL_CLAMP_TO_BORDER
	float flatColor[] = {0.35f, 0.0f, 0.75f, 0.2f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType,
		bytes);
		
	glGenerateMipmap(texType);
	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}
void Texture::Bind()
{
	glBindTexture(GLTexType, ID);
}
void Texture::Unbind()
{
	glBindTexture(GLTexType, 0);
}
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}