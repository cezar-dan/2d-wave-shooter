#include "Player.h"
#include "glm/ext.hpp"
#include "../Primitives/Circle.h"
#include "../Primitives/Rectangle.h"
#include "MapEdges.h"
#include "Obstacles.h"
#include "Enemy.h"
#include "../../transform2D.h"

using namespace std;
using namespace m1;


Player::Player()
{

}

Player::Player(float xc, float yc)
	: Player(xc, yc, 1, 0)
{

}

Player::Player(float xc, float yc, float size, float angle)
	: Entity(xc, yc, size, size, angle)
{
	isHUD = true;
	cType = collisionType::CIRCLE;

	primitives["body"] = new Circle(xc, yc, size, angle, bodyColor, "circleGreen1");
	primitives["bodyContour"] = new Circle(xc, yc, bodyContourSize, angle, contourColor, "circleBlack");
	primitives["leftArm"] = new Circle(xc + armCenterOffset, yc, armSize, 0, armColor, "circleGreen2");
	primitives["leftArmContour"] = new Circle(xc + armCenterOffset, yc, armContourSize, 0, contourColor, "circleBlack");
	primitives["rightArm"] = new Circle(xc + armCenterOffset, yc, armSize, 0, armColor, "circleGreen2");
	primitives["rightArmContour"] = new Circle(xc + armCenterOffset, yc, armContourSize, 0, contourColor, "circleBlack");
	
	// Position player arms
	primitives["leftArm"]->rotateAround(xc, yc, armAngleToOx + angle);
	primitives["leftArmContour"]->rotateAround(xc, yc, armAngleToOx + angle);
	primitives["rightArm"]->rotateAround(xc, yc, -armAngleToOx + angle);
	primitives["rightArmContour"]->rotateAround(xc, yc, -armAngleToOx + angle);

	orderedPrimitives.push_back(primitives["leftArm"]);
	orderedPrimitives.push_back(primitives["rightArm"]);
	orderedPrimitives.push_back(primitives["leftArmContour"]);
	orderedPrimitives.push_back(primitives["rightArmContour"]);
	orderedPrimitives.push_back(primitives["body"]);
	orderedPrimitives.push_back(primitives["bodyContour"]);

	healthBar = new HealthBar(2.0f, 3.6f);
	bulletStream = new BulletStream(xc + bulletOffset, yc, size, angle);
	this->healthBar->setMaxHealth(10);
}

Player::Player(float xc, float yc, float size, float angle, Tema1* world)
	: Player(xc, yc, size, angle)
{
	this->world = world;
	world->insertInEntityMap("playerBulletStream", this->bulletStream);
	world->insertInEntityMap("playerHealthBar", this->healthBar);
	world->insertInEntityMap("bulletBar", this->bulletStream->bulletBar);
}

Player::~Player()
{

}


void Player::placeAt(float tx, float ty, float sx, float sy, float u)
{
	this->Shape::placeAt(tx, ty, sx, sy, u);
	primitives["body"]->placeAt(tx, ty, sx, sy, u);
	primitives["bodyContour"]->placeAt(tx, ty, bodyContourSize, bodyContourSize, u);
	primitives["leftArm"]->placeAt(tx + armCenterOffset, ty, armSize, armSize, 0);
	primitives["rightArm"]->placeAt(tx + armCenterOffset, ty, armSize, armSize, 0);
	primitives["leftArmContour"]->placeAt(tx + armCenterOffset, ty, armContourSize, armContourSize, 0);
	primitives["rightArmContour"]->placeAt(tx + armCenterOffset, ty, armContourSize, armContourSize, 0);

	// Position player arms
	primitives["leftArm"]->rotateAround(xc, yc, armAngleToOx + u);
	primitives["rightArm"]->rotateAround(xc, yc, -armAngleToOx + u);
	primitives["leftArmContour"]->rotateAround(xc, yc, armAngleToOx + u);
	primitives["rightArmContour"]->rotateAround(xc, yc, -armAngleToOx + u);
}

void Player::shoot(BulletStream::shotPattern pattern)
{
	// As a shape, bulletStream is a point in front of the character
	bulletStream->placeAt(xc + bulletOffset, yc, 0, 0, 0);
	bulletStream->rotateAround(xc, yc, orientation);

	switch (pattern)
	{
	case BulletStream::shotPattern::STRAIGHT:
		bulletStream->shootStraight();
		break;
	case BulletStream::shotPattern::SHOTGUN:
		bulletStream->shootShotgun();
		break;
	}
}


std::vector<Shape*> m1::Player::getCollideShapes()
{
	std::vector<Shape*> hitBoxes;
	hitBoxes.push_back(this);
	return hitBoxes;
}


void Player::ProcessCollision(ICollidable* other)
{
	MapEdges* mapEdgesEntity = dynamic_cast<MapEdges*> (other);
	if (mapEdgesEntity != NULL)
	{
		this->world->translateHUD(lastXc - xc, lastYc - yc);
	}

	Obstacles* ObstaclesEntity = dynamic_cast<Obstacles*> (other);
	if (ObstaclesEntity != NULL)
	{
		this->world->translateHUD(lastXc - xc, lastYc - yc);
	}
	
	Enemy* enemyEntity = dynamic_cast<Enemy*> (other);
	if (enemyEntity != NULL)
	{
		this->health--;
		healthBar->decreaseHealth();
	}
}
