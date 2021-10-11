#include "Physics/Collision.h"

void Collision::checkRectCollision(RigidBody *rect1, RigidBody *rect2)
{
    if (rect1->getPosition().x <= rect2->getPosition().x + rect2->getScale().x &&
        rect1->getPosition().x + rect1->getScale().x >= rect2->getPosition().x &&
        rect1->getPosition().y >= rect2->getPosition().y - rect2->getScale().y &&
        rect1->getPosition().y - rect1->getScale().y <= rect2->getPosition().y)
    {
        rect1->collided = true;
    }
    else
    {
        rect1->collided = false;
    }
}