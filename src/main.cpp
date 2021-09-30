// Including Project headers
#include "Components/Shader.h"
#include "Components/Texture.h"
#include "Components/FileManager.h"
#include "Sprites/Object.h"
#include "Sprites/Player.h"
#include "Shapes/Rectangle.h"
#include "Shapes/Polygon.h"
#include "Math/Vector.h"
#include "Math/Color.h"
#include "Physics/Space.h"

// Including external libraries
#include <iostream> // For printing output and taking input

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Defining the width and height of the window
#define WIN_WIDTH 600
#define WIN_HEIGHT 600

int main()
{
  // Initializing GLFW, and check for errors in the initialization
  if (!glfwInit())
  {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow *win = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Prototype", NULL, NULL); // Creating the window, with given width, height, and title

  // Checking for errors in the creation of the window
  if (!win)
  {
    std::cout << "Failed to create Window" << std::endl;
    return -1;
  }
  glfwMakeContextCurrent(win); // Makes the window the current context

  // Initialize GLEW, and check for errors in the initialization
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  // Setting up FileManager
  FileManager::setImageDirectory("../assets/images/");
  FileManager::setShaderDirectory("../include/Shaders/");

  // Setting up Physics
  PhysicsSpace space(Vector2f(0.001f, -0.0000981f));

  // Graphic components of the game
  Object floor(Vector2f(-1.f, -0.75f), Vector2f(2.f, 0.25f), FileManager::getImage("stone_floor.png"), 0.5f);
  Player player(Vector2f(0.f, 0.f), Vector2f(0.1f, 0.1f), 0.01f, FileManager::getImage("red_ball.png"), 1.f);
  space.addBody(&player);
  Rectangle rect(Vector2f(-0.5f, 0.5f), Vector2f(0.25f, 0.25f), Color(0.f, 1.f, 1.f));
  Polygon circle(Vector2f(0.5f, 0.5f), 0.1f, 25, Color(0.f, 0.f, 1.f));

  glClearColor(1.f, 1.f, 1.f, 1.f); // Set the background color to white

  // Enable background transparency in loading png textures
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Game loop
  while (!glfwWindowShouldClose(win))
  {
    // Clear the screen, to redraw the frame
    glClear(GL_COLOR_BUFFER_BIT);

    // Toggling wireframe mode(Hold down 'p' to see the meshes)
    if (glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    space.step((float)1 / 60);

    // Drawing the graphical components
    floor.draw(win);
    player.draw(win);
    rect.draw(win);
    circle.draw(win);

    glfwSwapBuffers(win); // Double-buffering
    glfwPollEvents();     // Process the inputs
  }

  glfwTerminate(); // Terminate GLFW after the window is closed
}
