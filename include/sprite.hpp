#pragma once

class Shader;
class Texture;
extern Shader* spriteShader;
typedef unsigned int GLuint;

#include <glm/glm.hpp>

struct Rectangle
{
	Rectangle();
	Rectangle(float x, float y, float w, float h);

	glm::vec2 pos;
	glm::vec2 size;
};

class Sprite
{
public:
	Texture* texture;
	GLuint VBO, VAO;

	Rectangle src, dst;
	float angle;

	Sprite(Texture* texture);
	void draw();
};