// Including Project headers
#include "Components/Definitions.h"
#include "Components/Shader.h"
#include "Components/Texture.h"
#include "Components/FileManager.h"
#include "Sprites/RigidBody.h"
#include "Shapes/Rectangle.h"
#include "Shapes/Polygon.h"

#include "Containers/Color.h"
#include "Physics/Space.h"

// Including external libraries
#include <iostream> // For printing output and taking input

// OpenGL includes
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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

  // Initialize GLAD, and check for errors in the initialization
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Setting up FileManager
  FileManager::setImageDirectory("../res/images/");
  FileManager::setShaderDirectory("../res/shaders/");

  // Setting up Physics
  PhysicsSpace space(glm::vec2(0.f, -0.981f));
  space.setTerminalVelocity(glm::vec2(0.f, 0.f));
  space.setDeltaTime(DT);

  // Graphic components of the game
  RigidBody floor(glm::vec2(-1.f, -0.75f), glm::vec2(2.f, 0.25f), RigidBodyType::STATIC);
  floor.setTexture(FileManager::getImage("stone_floor.png"), 0.5f);
  RigidBody player(glm::vec2(0.f, 0.f), glm::vec2(0.1f, 0.1f), RigidBodyType::DYNAMIC);
  player.setTexture(FileManager::getImage("red_ball.png"));
  player.setMass(1.f);
  Rectangle rect(glm::vec2(-0.5f, 0.5f), glm::vec2(0.25f, 0.25f), Color(0.f, 1.f, 1.f));
  Polygon circle(glm::vec2(0.5f, 0.5f), 0.1f, 25, Color(0.f, 0.f, 1.f));

  space.addBody(&floor);
  space.addBody(&player);

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

    space.step();

    // Drawing the graphical components
    floor.draw(win);
    player.draw(win);
    rect.draw(win);
    circle.draw(win);

    glfwSwapBuffers(win); // Double-buffering
    glfwPollEvents();     // Process the inputs given to the window
  }

  glfwTerminate(); // Terminate GLFW after the window is closed
}
