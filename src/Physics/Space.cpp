#include "Physics/Space.h"
#include "Physics/Collision.h"

#include <algorithm>
#include <iostream>

PhysicsSpace::PhysicsSpace(glm::vec2 gravity) : gravity(gravity) {}

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

void PhysicsSpace::step(float dt)
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
      if (body->getPosition().y + body->getScale().y < -1.f || body->collided)
      {
        body->velocity = glm::vec2(0.f, 0.f);
      }
      // std::cout << "Velocity: " << body->velocity.x << ", " << body->velocity.y << std::endl;
      body->position += body->velocity * dt;

      body->force = glm::vec2(0.f, 0.f);
    }
  }
}
