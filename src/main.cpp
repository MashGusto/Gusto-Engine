#include "Components/Shader.h"
#include "Components/Texture.h"
#include "Components/FileManager.h"
#include "Sprites/Object.h"
#include "Sprites/Player.h"
#include "Shapes/Rectangle.h"
#include "Shapes/Polygon.h"
#include "Math/Vector.h"
#include "Math/Color.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WIN_WIDTH 600
#define WIN_HEIGHT 600

int main()
{
  if(!glfwInit())
  {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow* win = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Prototype", NULL, NULL);
  if(!win)
  {
    std::cout << "Failed to create Window" << std::endl;
    return -1;
  }
  glfwMakeContextCurrent(win);

  if(glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  Object floor(Vector2f(-1.f, -0.75f), Vector2f(2.f, 0.25f), FileManager::getImage("stone_floor.png"), 0.5f);

  Player player(Vector2f(0.f, 0.f), Vector2f(0.1f, 0.1f), FileManager::getImage("red_ball.png"), 1.f);

  Rectangle rect(Vector2f(-0.5f, 0.5f), Vector2f(0.25f, 0.25f), Color(0.f, 1.f, 1.f));
  Polygon circle(Vector2f(0.5f, 0.5f), 0.5f, 25, Color(0.f, 0.f, 1.f));
  
  glClearColor(1.f, 1.f, 1.f, 1.f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  while(!glfwWindowShouldClose(win))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    if(glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    floor.draw(win);

    player.draw(win);

    rect.draw(win);
    circle.draw(win);

    glfwSwapBuffers(win);
    glfwPollEvents();
  }

  glfwTerminate();
}
