#pragma once

#include <vector>
#include "../Shape.h"
#include "../Primitives/Primitive.h"

namespace m1
{
	class Entity : public Shape
	{
	public:
		Entity();
		Entity(float xc, float yc);
		Entity(float xc, float yc, float sizeX, float sizeY, float angle);
		~Entity();

		std::unordered_map<std::string, Primitive*> primitives;
		// std::unordered_map<std::string, Entity*> entities;
		std::vector<Primitive*> orderedPrimitives;

		virtual void placeAt(float tx, float ty, float sx, float sy, float u) = 0;
		virtual void translate(float tx, float ty) override;
		virtual void scale(float sx, float sy) override;
		virtual void rotate(float u) override;
		virtual void rotateAround(float x, float y, float u) override;
		virtual void moveForward(float distance) override;
		bool getIsHUD();

	protected:
		bool isHUD = false;

	};
}
