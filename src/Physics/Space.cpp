#include "Physics/Space.h"

#include <algorithm>
#include <iostream>

PhysicsSpace::PhysicsSpace(Vector2f gravity) : m_gravity(gravity) {}

void PhysicsSpace::addBody(Player *body)
{
  m_bodies.push_back(body);
}

void PhysicsSpace::removeBody(Player *body)
{
  if (!body)
    return;

  auto itr = std::find(m_bodies.begin(), m_bodies.end(), body);

  if (itr == m_bodies.end())
    return;

  m_bodies.erase(itr);
}

void PhysicsSpace::step(float dt)
{
  for (Player *body : m_bodies)
  {
    body->m_force += m_gravity * body->m_mass;

    body->m_velocity += body->m_force / body->m_mass * dt;
    body->m_position += body->m_velocity * dt;

    body->m_force = Vector2f(0.f, 0.f);
  }
}
