#include "Enemy.h"
#include "../Primitives/Circle.h"
#include "../Primitives/Rectangle.h"
#include "Bullet.h"
#include "Player.h"
#include "MapEdges.h"

using namespace std;
using namespace m1;


Enemy::Enemy()
{

}

Enemy::Enemy(float xc, float yc)
	: Enemy(xc, yc, 1, 0, 0.3f)
{
	cType = collisionType::AABB;
}

Enemy::Enemy(float xc, float yc, float size, float angle, float velocity)
	: Entity(xc, yc, size, size, angle)
{
	cType = collisionType::AABB;
	this->velocity = velocity;
}

Enemy::~Enemy()
{

}

void Enemy::changeInTime(float time)
{
	orientation = glm::atan2(player->yc - yc, player->xc - xc);
	this->placeAt(xc, yc, sizeX, sizeY, orientation);
	this->moveForward(time * velocity);
}

void Enemy::setPlayer(Player* player)
{
	this->player = player;
}

vector<Shape*> m1::Enemy::getCollideShapes()
{
	std::vector<Shape*> hitBoxes;
	hitBoxes.push_back(this);
	return hitBoxes;
}

void Enemy::ProcessCollision(ICollidable* other)
{
	Bullet* bulletEntity = dynamic_cast<Bullet*> (other);
	if (bulletEntity != NULL)
	{
		isDead = true;
		this->translate(-100.0f, -100.0f);
	}

	Player* playerEntity = dynamic_cast<Player*> (other);
	if (playerEntity != NULL)
	{
		isDead = true;
		this->translate(-100.0f, -100.0f);
	}

	MapEdges* mapEdgeEntity = dynamic_cast<MapEdges*> (other);
	if (mapEdgeEntity != NULL)
	{
		this->translate(lastXc - xc, lastYc - yc);
	}
}
