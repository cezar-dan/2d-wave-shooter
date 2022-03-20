#include "Primitive.h"
#include "glm/ext.hpp"

using namespace std;
using namespace m1;

std::unordered_map<std::string, Mesh*>* Primitive::meshes = NULL;

Primitive::Primitive()
{
}

Primitive::Primitive(float xc, float yc)
	: Shape(xc, yc)
{
}

Primitive::Primitive(float xc, float yc, float sizeX, float sizeY, float angle)
	: Shape(xc, yc, sizeX, sizeY, angle)
{
}

Primitive::~Primitive()
{
}

Mesh* Primitive::getMesh()
{
	return this->mesh;
}

void Primitive::addMeshToList() {
	if (mesh->GetMeshID())
	{
		(*meshes)[mesh->GetMeshID()] = mesh;
	}
}
