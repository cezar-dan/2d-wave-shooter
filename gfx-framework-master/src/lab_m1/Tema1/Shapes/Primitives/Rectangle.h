#pragma once

#include "Primitive.h"
namespace m1
{
	class Rectangle : public Primitive
	{
	public:
		Rectangle();
		Rectangle(float xc, float yc, glm::vec3 color, std::string name);
		Rectangle(float xc, float yc, float width, float height, float angle, glm::vec3 color, std::string name);
		Rectangle(float xc, float yc, float width, float height, float angle, glm::vec3 color, std::string name, bool fill);
		~Rectangle();

		static Mesh* Rectangle::genRectangleMesh(glm::vec3 color, std::string name, bool fill);
		void setMesh(std::string name, glm::vec3 color);
		void setFill(bool f);

	private:
		float width = 1;
		float height = 1;
		bool fill = true;
	};
}
