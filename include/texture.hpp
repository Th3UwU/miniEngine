#pragma once

typedef unsigned int GLuint;

class Texture
{
public:
	GLuint id;
	int width, height;

	Texture(const char* fileName);
	Texture(int width, int height);
	~Texture();
};