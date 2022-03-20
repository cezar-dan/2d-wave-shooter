#include "Circle.h"
#include "glm/ext.hpp"

using namespace std;
using namespace m1;

Circle::Circle()
{

}

Circle::Circle(float xc, float yc, glm::vec3 color, std::string name)
	: Primitive(xc, yc)
{
    setMesh(name, color);
}

Circle::Circle(float xc, float yc, float sizeX, float sizeY, float angle, glm::vec3 color, std::string name)
	: Primitive(xc, yc, sizeX, sizeY, angle)
{
    setMesh(name, color);
}

Circle::Circle(float xc, float yc, float size, float angle, glm::vec3 color, std::string name)
    : Circle(xc, yc, size, size, angle, color, name)
{
}

Circle::~Circle()
{
}


Mesh* Circle::genCircleMesh(int step, glm::vec3 color, std::string name)
{
    vector<VertexFormat> vertices_ellipse
    {
        VertexFormat(glm::vec3(0, 0, 0), color, glm::vec3(0.2, 0.8, 0.6))
    };

    for (int i = 0; i <= step; ++i)
    {
        float theta = (float)(i * 360) / step - 180;
        float x = 0.5f * glm::cos(glm::radians(theta));
        float y = 0.5f * glm::sin(glm::radians(theta));
        vertices_ellipse.push_back(VertexFormat(glm::vec3(x, y, 0), color, glm::vec3(0.2, 0.8, 0.6)));
    }


    vector<unsigned int> indices_ellipse = { 0 };
    for (int i = 1; i <= step + 1; ++i)
    {
        indices_ellipse.push_back(i);
    }

    Mesh* mesh = new Mesh(name);
    mesh->SetDrawMode(GL_TRIANGLE_FAN);
    mesh->InitFromData(vertices_ellipse, indices_ellipse);
    return mesh;
}

void Circle::setMesh(string name, glm::vec3 color)
{
    if (Primitive::meshes->count(name) != 0)
    {
        this->mesh = Primitive::meshes->find(name)->second;
    }
    else
    {
        this->mesh = Circle::genCircleMesh(36, color, name);
        this->addMeshToList();
    }
}
