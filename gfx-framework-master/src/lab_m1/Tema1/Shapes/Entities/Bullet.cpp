#include "Bullet.h"
#include "MapEdges.h"
#include "Player.h"
#include "Obstacles.h"
#include "EnemyFly.h"
#include "../../Tema1.h"

using namespace std;
using namespace m1;

Bullet::Bullet()
{
}

Bullet::Bullet(float xc, float yc, glm::vec3 color, std::string name)
	:Rectangle(xc, yc, color, name)
{
	cType = collisionType::AABB;
}

Bullet::Bullet(float xc, float yc, float width, float height, float angle, glm::vec3 color, std::string name)
	:Rectangle(xc, yc, width, height, angle, color, name)
{
	cType = collisionType::AABB;
}

Bullet::~Bullet()
{
}

void Bullet::setVelocity(float v)
{
	velocity = v;
}

void Bullet::setMaxRange(float r)
{
	maxRange = r;
}

void Bullet::changeInTime(float deltaTimeSeconds)
{
	distanceTraveled += velocity * deltaTimeSeconds;
	this->moveForward(velocity * deltaTimeSeconds);
}

bool Bullet::isDone()
{
	return distanceTraveled > maxRange;
}

std::vector<Shape*> Bullet::getCollideShapes()
{
	std::vector<Shape*> hitBoxes;
	hitBoxes.push_back(this);
	return hitBoxes;
}

void Bullet::ProcessCollision(ICollidable* other)
{
	MapEdges* mapEdgesEntity = dynamic_cast<MapEdges*>(other);
	if (mapEdgesEntity != NULL)
	{
		// Make bullet disappear by capping out its distanceTraveled
		distanceTraveled += maxRange;
	}

	Obstacles* ObstaclesEntity = dynamic_cast<Obstacles*> (other);
	if (ObstaclesEntity != NULL)
	{
		// Make bullet disappear by capping out its distanceTraveled
		distanceTraveled += maxRange;
	}

	EnemyFly* enemyEntity = dynamic_cast<EnemyFly*> (other);
	if (enemyEntity != NULL)
	{
		// Make bullet disappear by capping out its distanceTraveled
		distanceTraveled += maxRange;
		Tema1::score++;
		printf("Enemy hit, score updated: %d\n", Tema1::score);
	}
}
