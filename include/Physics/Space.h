#pragma once

#include "Math/Vector.h"
#include "Sprites/Player.h"

#include <vector>

class PhysicsSpace
{
  private:
    std::vector<Player*> m_bodies;
    Vector2f m_gravity;

  public:
    PhysicsSpace(Vector2f gravity);
    void addBody(Player* body);
    void removeBody(Player* body);
    void step(float dt);
};
