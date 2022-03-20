#pragma once

#include "../Shape.h"
#include <string>

namespace m1
{
	class Primitive : public Shape
	{
	public:
		static std::unordered_map<std::string, Mesh*>* meshes;

		Primitive();
		Primitive(float xc, float yc);
		Primitive(float xc, float yc, float sizeX, float sizeY, float angle);
		~Primitive();

		virtual void setMesh(std::string name, glm::vec3 color) = 0;
		Mesh* getMesh();
		void addMeshToList();

	protected:
		Mesh* mesh = NULL;
	};
}
