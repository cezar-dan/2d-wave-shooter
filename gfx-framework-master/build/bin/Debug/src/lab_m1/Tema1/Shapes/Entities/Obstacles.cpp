#include "Obstacles.h"
#include "../Primitives/Rectangle.h"
#include "../Primitives/Circle.h"

using namespace std;
using namespace m1;

m1::Obstacles::Obstacles()
{
	cType = collisionType::AABB;
	primitives["treeTrunk1"] = new Rectangle(1.0f, 4.0f, 1.0f, 0.5f, 0.0f, treeTrunkColor, "treeTrunk");
	primitives["treeTrunk2"] = new Rectangle(0.9f, 4.2f, 0.2f, 0.7f, 0.0f, treeTrunkColor, "treeTrunk");
	primitives["blackHole1"] = new Circle(1.1f, 4.0f, 0.3f, 0.2f, 0.0f, blackHoleColor, "blackHole");
	primitives["treeTrunk3"] = new Rectangle(3.3f, 3.2f, 0.6f, 1.65f, 0.0f, treeTrunkColor, "treeTrunk");
	primitives["treeTrunk4"] = new Rectangle(3.0f, 0.1f, 0.8f, 1.7f, 0.0f, treeTrunkColor, "treeTrunk");
	primitives["rock1"] = new Rectangle(3.1f, 5.2f, 0.3f, 0.3f, 0.0f, rockColor, "rectRock");
	primitives["rock2"] = new Rectangle(0.5f, 1.8f, 0.3f, 0.4f, 0.0f, rockColor, "rectRock");
	primitives["rock3"] = new Rectangle(0.7f, -0.7f, 0.5f, 0.5f, 0.0f, rockColor, "rectRock");

	orderedPrimitives.push_back(primitives["blackHole1"]);
	orderedPrimitives.push_back(primitives["treeTrunk1"]);
	orderedPrimitives.push_back(primitives["treeTrunk2"]);
	orderedPrimitives.push_back(primitives["treeTrunk3"]);
	orderedPrimitives.push_back(primitives["treeTrunk4"]);
	orderedPrimitives.push_back(primitives["rock1"]);
	orderedPrimitives.push_back(primitives["rock2"]);
	orderedPrimitives.push_back(primitives["rock3"]);
}

m1::Obstacles::~Obstacles()
{
}

void Obstacles::placeAt(float x, float ty, float sx, float sy, float u)
{
}

std::vector<Shape*> Obstacles::getCollideShapes()
{
	std::vector<Shape*> hitBoxes;
	for (auto& primitive : orderedPrimitives)
	{
		hitBoxes.push_back(primitive);
	}
	return hitBoxes;
}

void Obstacles::ProcessCollision(ICollidable* other)
{
}
