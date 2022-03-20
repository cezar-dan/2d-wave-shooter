#include "Entity.h"
#include "glm/ext.hpp"

using namespace std;
using namespace m1;

Entity::Entity()
{
}

Entity::Entity(float xc, float yc)
	: Entity(xc, yc, 1, 1, 0)
{
}

Entity::Entity(float xc, float yc, float sizeX, float sizeY, float angle)
	:Shape(xc, yc, sizeX, sizeY, angle)
{
}

Entity::~Entity()
{
}


void Entity::translate(float tx, float ty)
{
	this->Shape::translate(tx, ty);
	for (auto& primitive : orderedPrimitives)
	{
		primitive->translate(tx, ty);
	}
}

void Entity::scale(float sx, float sy)
{
	this->Shape::scale(sx, sy);
	for (auto& primitive : orderedPrimitives)
	{
		primitive->scale(sx, sy);
	}
}

void Entity::rotate(float u)
{
	this->Shape::rotate(u);
	for (auto& primitive : orderedPrimitives)
	{
		primitive->rotate(u);
	}
}

void Entity::rotateAround(float x, float y, float u)
{
	this->Shape::rotateAround(x, y, u);
	for (auto& primitive : orderedPrimitives)
	{
		primitive->rotateAround(x, y, u);
	}
}

void Entity::moveForward(float distance)
{
	this->Shape::moveForward(distance);
	for (auto& primitive : orderedPrimitives)
	{
		primitive->moveForward(distance);
	}
}

bool Entity::getIsHUD()
{
	return isHUD;
}
