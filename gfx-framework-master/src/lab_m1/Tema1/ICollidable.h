#pragma once
#include "components/simple_scene.h"
#include "Shapes/Shape.h"
#include <vector>

namespace m1
{
    class ICollidable
    {
    public:
        enum class collisionType
        {
            AABB,
            CIRCLE
        };

        collisionType cType;
        virtual std::vector<Shape*> getCollideShapes() = 0;

        // using this function, we notify the object that it collided with something else
        virtual bool doesCollide(ICollidable* other);
        virtual void ProcessCollision(ICollidable* other) = 0;
    };
}

// Collisions: https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection