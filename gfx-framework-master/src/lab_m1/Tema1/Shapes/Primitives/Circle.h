#pragma once

#include "Primitive.h"
namespace m1
{
	class Circle : public Primitive
	{
	public:
		Circle();
		Circle(float xc, float yc, glm::vec3 color, std::string name);
		Circle(float xc, float yc, float size, float angle, glm::vec3 color, std::string name);
		Circle(float xc, float yc, float sizeX, float sizeY, float angle, glm::vec3 color, std::string name);
		~Circle();

		static Mesh* Circle::genCircleMesh(int step, glm::vec3 color, std::string name);
		void setMesh(std::string name, glm::vec3 color);

	};
}
