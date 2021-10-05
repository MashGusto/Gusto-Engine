#pragma once

#include "Sprites/RigidBody.h"

#include <vector>
#include <glm/glm.hpp>

class PhysicsSpace
{
private:
  std::vector<RigidBody *> bodies;
  glm::vec2 gravity;

public:
  PhysicsSpace(glm::vec2 gravity);
  void addBody(RigidBody *body);
  void removeBody(RigidBody *body);
  void step(float dt);
};
