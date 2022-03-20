#include "HealthBar.h"
#include "glm/ext.hpp"
#include "../Primitives/Circle.h"
#include "../Primitives/Rectangle.h"


using namespace std;
using namespace m1;


HealthBar::HealthBar()
{

}

HealthBar::HealthBar(float xc, float yc)
	: Entity(xc, yc)
{
	isHUD = true;
	primitives["frame"] = new Rectangle(xc, yc, 4.0f, 0.4f, 0.0f, glm::vec3(1,0,0), "healthFrame", false);
	primitives["health"] = new Rectangle(xc, yc, 3.9f, 0.30f, 0.0f, glm::vec3(1, 0, 0), "health", true);
	initHealthSizeX = 3.9f;
	initHealthSizeY = 0.3f;
	orderedPrimitives.push_back(primitives["frame"]);
	orderedPrimitives.push_back(primitives["health"]);
}

HealthBar::~HealthBar()
{

}


void HealthBar::placeAt(float tx, float ty, float sx, float sy, float u)
{
	this->Shape::placeAt(tx, ty, sx, sy, u);
	primitives["frame"]->placeAt(tx, ty, sx, sy, u);
	primitives["health"]->placeAt(tx, ty, sx, sy, u);
}

void HealthBar::setMaxHealth(int maxHp)
{
	maxHealth = maxHp;
	health = maxHp;
}

void HealthBar::decreaseHealth()
{
	--health;
	float initXc = primitives["health"]->xc, initYc = primitives["health"]->yc;
	float offset = initHealthSizeX / (float)(maxHealth);
	primitives["health"]->placeAt(initXc - offset / 2, initYc, health * offset, initHealthSizeY, 0);
	if (health == 0)
	{
		puts("YOU LOST");
		exit(0);
	}
}
