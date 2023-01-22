#include "game.hpp"

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "sprite.hpp"
#include "texture.hpp"

using namespace glm;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Game::Game()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);

	window = glfwCreateWindow(800, 600, "Test 2D", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();

	glfwSetKeyCallback(window, keyCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glViewport(0, 0, 800, 600);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	projection = ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

	spriteShader = new Shader("../shader/sprite.vert", "../shader/sprite.frag", "../shader/sprite.geom");
	spriteShader->use();
	spriteShader->setValue("image", 0);
	spriteShader->setValue("projection", projection);

	texture = new Texture("../res/smb.png");
	
	sprTest = new Sprite(texture);
	sprTest->dst = Rectangle(0.0f, 0.0f, 16.0f * 8.0f, 34.0f * 8.0f);
	sprTest->src = Rectangle(72.0f, 172.0f, 16.0f, 34.0f);
}

Game::~Game()
{
	glfwTerminate();
}

void Game::update()
{

}

void Game::draw()
{
	sprTest->draw();
}

void Game::loop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		update();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		draw();
		glfwSwapBuffers(window);
	}
}