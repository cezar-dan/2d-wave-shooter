#pragma once
#include "components/simple_scene.h"
#include <unordered_map>

namespace m1
{
	class Shape
	{
	public:
		Shape();
		Shape(float xc, float yc);
		Shape(float xc, float yc, float sizeX, float sizeY, float angle);
		~Shape();

		glm::mat3 modelMatrix = glm::mat3(1);
		float xc = 0, yc = 0, sizeX = 1, sizeY = 1, orientation = 0;
		float lastXc = 0, lastYc = 0;
		glm::vec2 getCornerCoords();

		glm::mat3 getModelMatrix();
		virtual void setDefault();
		virtual void placeAt(float tx, float ty, float sx, float sy, float u);
		virtual void placeAt(Shape* at);
		virtual void translate(float tx, float ty);
		virtual void scale(float sx, float sy);
		virtual void rotate(float u);
		virtual void rotateAround(float x, float y, float u);
		virtual void moveForward(float distance);
	};
}
