#include "Rectangle.h"
#include "glm/ext.hpp"

using namespace std;
using namespace m1;

Rectangle::Rectangle()
{

}

Rectangle::Rectangle(float xc, float yc, glm::vec3 color, std::string name)
    : Primitive(xc, yc)
{
    setMesh(name, color);
}

Rectangle::Rectangle(float xc, float yc, float width, float height, float angle, glm::vec3 color, std::string name)
    : Primitive(xc, yc, width, height, angle)
{
    setMesh(name, color);
}

Rectangle::Rectangle(float xc, float yc, float width, float height, float angle, glm::vec3 color, std::string name, bool fill)
    : Primitive(xc, yc, width, height, angle)
{
    this->fill = fill;
    setMesh(name, color);
}

Rectangle::~Rectangle()
{
}


Mesh* Rectangle::genRectangleMesh(glm::vec3 color, std::string name, bool fill)
{
    vector<VertexFormat> vertices_rectangle
    {
        VertexFormat(glm::vec3(-0.5, -0.5, 0), color, glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(0.5, -0.5, 0), color, glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(0.5, 0.5, 0), color, glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(-0.5, 0.5, 0), color, glm::vec3(0.2, 0.8, 0.6))
    };

    vector<unsigned int> indices_rectangle
    { 
        0, 1, 2, 3
    };

    Mesh* mesh = new Mesh(name);

    if (!fill)
    {
        mesh->SetDrawMode(GL_LINE_LOOP);
    }
    else
    {
        indices_rectangle.push_back(0);
        indices_rectangle.push_back(2);
        mesh->SetDrawMode(GL_TRIANGLES);
    }

    mesh->InitFromData(vertices_rectangle, indices_rectangle);
    return mesh;
}

void Rectangle::setMesh(string name, glm::vec3 color)
{
    if (Primitive::meshes->count(name) != 0)
    {
        this->mesh = Primitive::meshes->find(name)->second;
    }
    else
    {
        this->mesh = Rectangle::genRectangleMesh(color, name, fill);
        this->addMeshToList();
    }
}

void Rectangle::setFill(bool f)
{
    fill = f;
}
