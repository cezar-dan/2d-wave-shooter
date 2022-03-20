#include "BulletBar.h"
#include "glm/ext.hpp"
#include "../Primitives/Rectangle.h"


using namespace std;
using namespace m1;


BulletBar::BulletBar(float straightFireRate, float shotgunFireRate)
	:Entity(0, 0)
{
	isHUD = true;
	this->straightFireRate = straightFireRate;
	this->shotgunFireRate = shotgunFireRate;
	isHUD = true;

	primitives["straightFrame"] = new Rectangle(-0.7f, 2.0f, 0.2f, 1.2f, 0.0f, frameColor, "bulletFrame", false);
	primitives["straightBar"] = new Rectangle(-0.7f, 2.0f, 0.2f, 1.2f, 0.0f, fillColor, "bulletBar", true);
	
	orderedPrimitives.push_back(primitives["straightFrame"]);
	orderedPrimitives.push_back(primitives["straightBar"]);

	primitives["shotgunFrame"] = new Rectangle(4.7f, 2.0f, 0.2f, 1.2f, 0.0f, frameColor, "bulletFrame", false);
	primitives["shotgunBar"] = new Rectangle(4.7f, 2.0f, 0.2f, 1.2f, 0.0f, fillColor, "bulletBar", true);

	orderedPrimitives.push_back(primitives["shotgunFrame"]);
	orderedPrimitives.push_back(primitives["shotgunBar"]);
}


BulletBar::~BulletBar()
{

}


void BulletBar::placeAt(float tx, float ty, float sx, float sy, float u)
{
}


void BulletBar::updateShotgunBar(float timePassed)
{
	float initXc = primitives["shotgunBar"]->xc, initYc = primitives["shotgunBar"]->yc;
	float newScaleY = ((shotgunFireRate - timePassed) * 1.2f) / shotgunFireRate;
	if (newScaleY < 0)
	{
		newScaleY = 0;
		primitives["shotgunBar"]->placeAt(initXc, initYc, 0.2f, initScaleY, 0.0f);
		return;
	}
	primitives["shotgunBar"]->placeAt(initXc, initYc, 0.2f, initScaleY - newScaleY, 0.0f);
}

void BulletBar::updateStraightBar(float timePassed)
{
	float initXc = primitives["straightBar"]->xc, initYc = primitives["straightBar"]->yc;
	float newScaleY = ((straightFireRate - timePassed) * 1.2f) / straightFireRate;
	if (newScaleY < 0)
	{
		newScaleY = 0;
		primitives["straightBar"]->placeAt(initXc, initYc, 0.2f, initScaleY, 0.0f);
		return;
	}
	primitives["straightBar"]->placeAt(initXc , initYc, 0.2f, initScaleY - newScaleY, 0.0f);
}

void BulletBar::resetStraightTime()
{
	this->setDefault();
	updateStraightBar(0);
}

void BulletBar::resetShotgunTime()
{
	this->setDefault();
	updateShotgunBar(0);
}
