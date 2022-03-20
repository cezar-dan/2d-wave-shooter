#include "BulletStream.h"
#include "../Primitives/Rectangle.h"
#include "MapEdges.h"

using namespace std;
using namespace m1;

BulletStream::BulletStream()
{
}

BulletStream::BulletStream(float xc, float yc)
	:BulletStream(xc, yc, 1, 0)
{
}

BulletStream::BulletStream(float xc, float yc, float size, float angle)
	:Entity(xc, yc, size, size, angle)
{	
	fireRate[shotPattern::STRAIGHT] = 0.5f;
	fireRate[shotPattern::SHOTGUN] = 5.0f;

	tSinceLastFire[shotPattern::STRAIGHT] = 0.5f;
	tSinceLastFire[shotPattern::SHOTGUN] = 5.0f;

	bulletBar = new BulletBar(fireRate[shotPattern::STRAIGHT], fireRate[shotPattern::SHOTGUN]);
}

BulletStream::~BulletStream()
{
}

void BulletStream::placeAt(float tx, float ty, float sx, float sy, float u)
{
	this->Shape::placeAt(tx, ty, sx, sy, u);
}

void BulletStream::translate(float tx, float ty)
{
	this->Shape::translate(tx, ty);
}

void BulletStream::scale(float sx, float sy)
{
	this->Shape::scale(sx, sy);
}

void BulletStream::rotate(float u)
{
	this->Shape::rotate(u);
}

void BulletStream::rotateAround(float x, float y, float u)
{
	this->Shape::rotateAround(x, y, u);
}


void BulletStream::shootStraight()
{
	if (tSinceLastFire[BulletStream::shotPattern::STRAIGHT] < fireRate[shotPattern::STRAIGHT])
	{
		return;
	}
	tSinceLastFire[BulletStream::shotPattern::STRAIGHT] = 0.0f;
	bulletBar->resetStraightTime();
	Bullet* bullet = new Bullet(xc, yc, bulletHeight, bulletWidth, orientation, bulletColor, "genericBullet");
	orderedPrimitives.push_back(bullet);
}

void BulletStream::shootShotgun()
{
	if (tSinceLastFire[BulletStream::shotPattern::SHOTGUN] < fireRate[shotPattern::SHOTGUN])
	{
		return;
	}
	tSinceLastFire[BulletStream::shotPattern::SHOTGUN] = 0.0f;
	bulletBar->resetShotgunTime();
	int nrBullets = std::rand() % 2 + 4;
	for (int i = 0; i < nrBullets; ++i)
	{
		float lo = RADIANS(-45), hi = RADIANS(45);
		float angle = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
		lo = 0.5f;
		hi = 1.25f;
		float range = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
		Bullet* bullet = new Bullet(xc, yc, bulletHeight / 1.5f, bulletWidth / 1.5f, orientation + angle, bulletColor, "genericBullet");
		bullet->setMaxRange(range);
		orderedPrimitives.push_back(bullet);
	}
}

void BulletStream::changeInTime(float deltaTimeSeconds)
{
	tSinceLastFire[BulletStream::shotPattern::STRAIGHT] += deltaTimeSeconds;
	tSinceLastFire[BulletStream::shotPattern::SHOTGUN] += deltaTimeSeconds;
	bulletBar->updateStraightBar(tSinceLastFire[shotPattern::STRAIGHT]);
	bulletBar->updateShotgunBar(tSinceLastFire[shotPattern::SHOTGUN]);
	vector<Primitive*> updated;
	for (auto& bullet : orderedPrimitives)
	{
		Bullet* blt = ((Bullet*)bullet);
		blt->changeInTime(deltaTimeSeconds);
		if (blt->isDone()) continue;
		updated.push_back(blt);
	}
	orderedPrimitives = updated;
}

