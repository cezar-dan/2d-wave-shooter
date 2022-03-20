#include "Shape.h"
#include "glm/ext.hpp"
#include "../transform2D.h"

using namespace std;
using namespace m1;

Shape::Shape()
{
}

Shape::Shape(float xc, float yc)
	: Shape(xc, yc, 1.0f, 1.0f, 0.0f)
{
}

Shape::Shape(float xc, float yc, float sizeX, float sizeY, float angle)
{
	this->placeAt(xc, yc, sizeX, sizeY, angle);
}

Shape::~Shape()
{
}

glm::vec2 Shape::getCornerCoords()
{
	return glm::vec2(xc - sizeX / 2, yc - sizeY / 2);
}

glm::mat3 Shape::getModelMatrix()
{
	return modelMatrix;
}

void Shape::setDefault()
{
	this->xc = 0;
	this->yc = 0;
	this->sizeX = 1;
	this->sizeY = 1;
	this->orientation = 0;
	this->modelMatrix = glm::mat3(1);
}

void Shape::placeAt(float tx, float ty, float sx, float sy, float u)
{
	this->setDefault();
	this->scale(sx, sy);
	this->rotate(u);
	this->translate(tx, ty);
}

void Shape::placeAt(Shape* at)
{
	placeAt(at->xc, at->yc, at->sizeX, at->sizeY, at->orientation);
}

void Shape::translate(float tx, float ty)
{
	lastXc = xc;
	lastYc = yc;

	xc += tx;
	yc += ty;
	modelMatrix = transform2D::Translate(tx, ty) * modelMatrix;
}

void Shape::scale(float sx, float sy)
{
	lastXc = xc;
	lastYc = yc;

	sizeX *= sx;
	sizeY *= sy;
	modelMatrix = transform2D::Scale(sx, sy) * modelMatrix;
	glm::vec3 coords = glm::vec3(xc, yc, 1);
	coords = modelMatrix * coords;
	xc = coords[0];
	yc = coords[1];
}

void Shape::rotate(float u)
{
	lastXc = xc;
	lastYc = yc;

	orientation += u;
	modelMatrix = transform2D::Rotate(u) * modelMatrix;
	glm::vec3 coords = glm::vec3(xc, yc, 1);
	coords = modelMatrix * coords;
	xc = coords[0];
	yc = coords[1];
}

void Shape::rotateAround(float x, float y, float u)
{
	this->translate(-x, -y);
	this->rotate(u);
	this->translate(x, y);
}

void Shape::moveForward(float distance)
{
	float initXc = xc, initYc = yc, initOrientation = orientation;
	this->rotateAround(initXc, initYc, -initOrientation);
	this->translate(distance, 0);
	this->rotateAround(initXc, initYc, initOrientation);

	lastXc = initXc;
	lastYc = initYc;
}

