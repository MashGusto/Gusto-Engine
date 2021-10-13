// Including external libraries
#include <iostream> // For printing output and taking input

// OpenGL includes
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// Including Project headers
#include "System/Definitions.h"
#include "System/Window.h"
#include "System/Shader.h"
#include "System/Texture.h"
#include "System/FileManager.h"
#include "Graphics/RigidBody.h"
#include "Graphics/Shape.h"
#include "System/Color.h"
#include "Physics/Space.h"

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
  int yOff = yOffset;
  Shader::setProjectionScale(Shader::getProjectionScale() + (yOffset * 10));
}

int main()
{
  // Initializing GLFW, and check for errors in the initialization
  if (!glfwInit())
  {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow *win = Window::createWindow("Prototype"); // Creating a fullscreen window, with given title
  Shader::setProjection(glm::ortho((float)-Window::width / Shader::getProjectionScale(), (float)Window::width / Shader::getProjectionScale(), (float)-Window::height / Shader::getProjectionScale(), (float)Window::height / Shader::getProjectionScale(), -1.f, 1.f));

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

  //Setting up ImGUI
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui_ImplGlfw_InitForOpenGL(win, true);
  ImGui_ImplOpenGL3_Init("#version 330 core");
  ImGui::StyleColorsDark();

  // Setting up FileManager
  FileManager::setImageDirectory("../res/images/");
  FileManager::setShaderDirectory("../res/shaders/");

  // Setting up Physics
  PhysicsSpace space(glm::vec2(0.f, -9.81f));
  space.setTerminalVelocity(glm::vec2(0.f, 0.f));
  space.setDeltaTime(DT);

  // Graphic components of the game
  RigidBody floor(glm::vec2(-10.f, -2.f), glm::vec2(20.f, 2.f), RigidBodyType::STATIC);
  floor.setTexture(FileManager::getImage("stone_floor.png"), 5.f);
  RigidBody player(glm::vec2(0.f, -1.f), glm::vec2(1.f, 1.f), RigidBodyType::DYNAMIC);
  player.setTexture(FileManager::getImage("red_ball.png"));
  player.setMass(1.f);

  std::vector<Shape *> shapes;
  Rectangle rect(glm::vec2(-5.f, 5.f), glm::vec2(2.f, 2.f), Color(0.f, 1.f, 1.f));
  shapes.push_back(&rect);
  Polygon circle(glm::vec2(5.f, 5.f), 1.f, 25, Color(0.f, 0.f, 1.f));
  shapes.push_back(&circle);

  space.addBody(&floor);
  space.addBody(&player);

  glClearColor(0.f, 0.f, 0.f, 1.f); // Set the background color to white

  // Enable background transparency in loading png textures
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  double lastTime = glfwGetTime();

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.6f, 1.f);
  static float f = 0.f;
  static int counter = 0;
  bool show_demo_window = true;
  bool show_another_window = false;

  glfwSetScrollCallback(win, scrollCallback);

  // Game loop
  while (!glfwWindowShouldClose(win))
  {
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

    // Clear the screen, to redraw the frame
    glClear(GL_COLOR_BUFFER_BIT);
    Window::setTitle(std::string("Prototype | " + std::to_string((int)ImGui::GetIO().Framerate) + " FPS").c_str());

    // Setting up a new ImGUI frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Toggling wireframe mode(Hold down 'p' to see the meshes)
    if (glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(win, GLFW_KEY_C) == GLFW_PRESS)
      system("clear");

    for (Shape *shape : shapes)
    {
      if (shape->selected)
      {
        Shape::Selected = true;
        break;
      }
      else
        Shape::Selected = false;
    }

    space.step();

    // Drawing ImGUI components
    ImGui::ColorEdit3("Background Color", (float *)&clear_color);

    // Drawing the graphical components
    floor.draw();
    player.draw();
    rect.draw();
    circle.draw();

    // Rendering ImGUI components
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(win); // Double-buffering
    glfwPollEvents();     // Process the inputs given to the window

    while (glfwGetTime() < lastTime + 1.f / (float)60.f)
      continue;

    lastTime += 1.f / (float)60.f;
  }

  // Closing ImGUI and GLFW
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate(); // Terminate GLFW after the window is closed
}