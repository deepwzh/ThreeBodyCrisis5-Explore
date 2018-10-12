#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture2D
{
public:
	GLuint ID;
	GLuint Width, Height; 
	GLuint Internal_Format; 
	GLuint Image_Format;
	GLuint Wrap_S;
	GLuint Wrap_T;
	GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
	GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels
	Texture2D();
	void Generate(GLuint width, GLuint height, unsigned char* data);
	void Bind() const;
};

#endif