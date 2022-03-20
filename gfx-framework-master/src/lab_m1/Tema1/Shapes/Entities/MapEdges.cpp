#include "MapEdges.h"
#include "../Primitives/Rectangle.h"

using namespace std;
using namespace m1;

m1::MapEdges::MapEdges()
{
	cType = collisionType::AABB;
	primitives["center"] = new Rectangle(2.0f, 2.0f, 5.0f, 8.0f, 0.0f, centerColor, "rectangleCenter");
	primitives["topBorder"] = new Rectangle(2.0f, 6.0f, 5.2f, 0.2f, 0.0f, barrierColor, "rectangleBarrier");
	primitives["rightBorder"] = new Rectangle(4.5f, 2.0f, 0.2f, 8.0f, 0.0f, barrierColor, "rectangleBarrier");
	primitives["leftBorder"] = new Rectangle(-0.5f, 2.0f, 0.2f, 8.0f, 0.0f, barrierColor, "rectangleBarrier");
	primitives["bottomBorder"] = new Rectangle(2.0f, -2.0f, 5.2f, 0.2f, 0.0f, barrierColor, "rectangleBarrier");

	orderedPrimitives.push_back(primitives["topBorder"]);
	orderedPrimitives.push_back(primitives["rightBorder"]);
	orderedPrimitives.push_back(primitives["leftBorder"]);
	orderedPrimitives.push_back(primitives["bottomBorder"]);
	orderedPrimitives.push_back(primitives["center"]);
}

m1::MapEdges::~MapEdges()
{
}

void MapEdges::placeAt(float x, float ty, float sx, float sy, float u)
{
}

std::vector<Shape*> MapEdges::getCollideShapes()
{
	std::vector<Shape*> hitBoxes;
	hitBoxes.push_back(primitives["topBorder"]);
	hitBoxes.push_back(primitives["rightBorder"]);
	hitBoxes.push_back(primitives["leftBorder"]);
	hitBoxes.push_back(primitives["bottomBorder"]);
	return hitBoxes;
}

void MapEdges::ProcessCollision(ICollidable* other)
{
}
