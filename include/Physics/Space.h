#pragma once

#include "Sprites/RigidBody.h"

#include <vector>
#include <glm/glm.hpp>

class PhysicsSpace
{
private:
  std::vector<RigidBody *> bodies;
  glm::vec2 gravity;

  glm::vec2 terminalVelocity;
  float dt;

public:
  PhysicsSpace(glm::vec2 gravity);

  glm::vec2 getGravity();
  glm::vec2 getTerminalVelocity();
  float getDeltaTime();

  void setTerminalVelocity(glm::vec2 TerminalVelocity);
  void setDeltaTime(float DeltaTime);

  void addBody(RigidBody *body);
  void removeBody(RigidBody *body);

  void step();
};
