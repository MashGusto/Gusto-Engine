#include "Physics/Space.h"
#include "Physics/Collision.h"

#include <algorithm>
#include <iostream>

PhysicsSpace::PhysicsSpace(glm::vec2 Gravity) : gravity(Gravity) {}

glm::vec2 PhysicsSpace::getGravity() { return gravity; }
glm::vec2 PhysicsSpace::getTerminalVelocity() { return terminalVelocity; }

float PhysicsSpace::getDeltaTime() { return dt; }

void PhysicsSpace::setTerminalVelocity(glm::vec2 TerminalVelocity) { terminalVelocity = TerminalVelocity; }
void PhysicsSpace::setDeltaTime(float DeltaTime) { dt = DeltaTime; }

void PhysicsSpace::addBody(RigidBody *body)
{
  bodies.push_back(body);
}

void PhysicsSpace::removeBody(RigidBody *body)
{
  if (!body)
    return;

  auto itr = std::find(bodies.begin(), bodies.end(), body);

  if (itr == bodies.end())
    return;

  bodies.erase(itr);
}

void PhysicsSpace::step()
{
  for (RigidBody *body : bodies)
  {
    if (body->type == RigidBodyType::DYNAMIC)
    {
      for (RigidBody *body2 : bodies)
      {
        if (body != body2)
        {
          Collision::checkRectCollision(body, body2);
        }
      }
      body->force += body->mass * gravity;

      body->velocity += body->force / body->mass * dt;

      if (terminalVelocity.y && body->velocity.y < terminalVelocity.y)
      {
        body->velocity = terminalVelocity;
      }

      if (body->getPosition().y + body->getScale().y < -2.f || body->collided)
      {
        body->velocity = glm::vec2(0.f, 0.f);
      }
      body->position += body->velocity * dt;

      body->force = glm::vec2(0.f, 0.f);
    }
  }
}
