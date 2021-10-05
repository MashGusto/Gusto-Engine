#pragma once

#include "Sprites/RigidBody.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Collision
{
    void checkRectCollision(RigidBody *rect1, RigidBody *rect2);
}