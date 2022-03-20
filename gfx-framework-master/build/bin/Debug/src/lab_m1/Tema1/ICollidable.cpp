#include "ICollidable.h"
#include "glm/ext.hpp"

using namespace std;
using namespace m1;

bool ICollidable::doesCollide(ICollidable* other)
{
	if (this->cType == collisionType::AABB && other->cType == collisionType::AABB)
	{
		vector<Shape*> thisShapes = this->getCollideShapes();
		vector<Shape*> otherShapes = other->getCollideShapes();

		for (auto& thisShape : thisShapes)
		{
			for (auto& otherShape : otherShapes)
			{

				glm::vec2 thisCornerCoords = thisShape->getCornerCoords();
				glm::vec2 otherCornerCoords = otherShape->getCornerCoords();

				bool collisionX = thisCornerCoords[0] + thisShape->sizeX >= otherCornerCoords[0] &&
					otherCornerCoords[0] + otherShape->sizeX >= thisCornerCoords[0];

				bool collisionY = thisCornerCoords[1] + thisShape->sizeY >= otherCornerCoords[1] &&
					otherCornerCoords[1] + otherShape->sizeY >= thisCornerCoords[1];


				if (collisionX && collisionY)
				{
					return true;
				}
			}
		}
	}

	else if (this->cType == collisionType::AABB && other->cType == collisionType::CIRCLE)
	{
		return other->doesCollide(this);
	}

	else if (this->cType == collisionType::CIRCLE && other->cType == collisionType::AABB)
	{
		vector<Shape*> thisShapes = this->getCollideShapes();
		vector<Shape*> otherShapes = other->getCollideShapes();

		for (auto& thisShape : thisShapes)
		{
			for (auto& otherShape : otherShapes)
			{
				// Get center point circle
				glm::vec2 center = glm::vec2(thisShape->xc, thisShape->yc);

				// Calculate AABB info
				glm::vec2 aabbHalfExtents(otherShape->sizeX / 2.0f, otherShape->sizeY / 2.0f);
				glm::vec2 aabbCenter(otherShape->xc, otherShape->yc);

				// Get difference vector between both centers
				glm::vec2 difference = center - aabbCenter;
				glm::vec2 clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);

				// Add clamped value to AABB_center and we get the value of box closest to circle
				glm::vec2 closest = aabbCenter + clamped;

				// Retrieve vector between center circle and closest point AABB and check if length <= radius
				difference = closest - center;
				if (glm::length(difference) < thisShape->sizeX / 2.0) return true;
			}
		}
	}
	return false;
}
