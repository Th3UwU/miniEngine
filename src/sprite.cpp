#include "sprite.hpp"

#include <GL/glew.h>

Shader* spriteShader;
#include "shader.hpp"
#include "texture.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

static const GLfloat vertices[] =
{ 
	// Pos
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,

	// Tex Coords
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
};

static const GLuint indices[] =
{
	0, 1, 2,
	1, 2, 3,
};

Rectangle::Rectangle()
: pos(0.0f, 0.0f), size(0.0f, 0.0f)
{}

Rectangle::Rectangle(float x, float y, float w, float h)
: pos(x, y), size(w, h)
{}

Sprite::Sprite(Texture* texture)
: texture(texture), angle(0.0f)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(float) * 0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(float) * 8));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sprite::draw()
{
	GLfloat tWidth = GLfloat(texture->width);
	GLfloat tHeight = GLfloat(texture->height);

	GLfloat newTexCoords[] =
	{
		/* BL */ src.pos.x / tWidth,					src.pos.y / tHeight,
		/* BR */ (src.pos.x + src.size.x) / tWidth,		src.pos.y / tHeight,
		/* TL */ src.pos.x / tWidth,					(src.pos.y + src.size.y) / tHeight,
		/* TR */ (src.pos.x + src.size.x) / tWidth,		(src.pos.y + src.size.y) / tHeight,
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, sizeof(newTexCoords), newTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	mat4 model = mat4(1.0f);
	model = translate(model, vec3(dst.pos, 0.0f));
	model = rotate(model, radians(angle), vec3(0.0f, 0.0f, 1.0f));
	model = scale(model, vec3(dst.size, 1.0f));

	spriteShader->setValue("model", model);
	spriteShader->setValue("spriteColor", 1.0f, 1.0f, 1.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
	glBindVertexArray(0);
}
