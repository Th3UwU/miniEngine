#pragma once

#include <glm/glm.hpp>
typedef struct GLFWwindow GLFWwindow;

class Sprite;
class Texture;

class Game
{
public:
	GLFWwindow* window;
	glm::mat4 projection;

	Texture* texture;
	Sprite* sprTest;

	Game();
	~Game();

	void update();
	void draw();
	void loop();
};