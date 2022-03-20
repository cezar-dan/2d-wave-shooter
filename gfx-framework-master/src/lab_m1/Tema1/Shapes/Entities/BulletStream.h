#pragma once

#include "Entity.h"
#include "Bullet.h"
#include "BulletBar.h"
#include <string>
#include <unordered_map>

namespace m1
{
	class BulletStream : public Entity, public ITimeDependant
	{
	public:
		enum class shotPattern
		{
			STRAIGHT,
			SHOTGUN
		};

		BulletStream();
		BulletStream(float xc, float yc);
		BulletStream(float xc, float yc, float size, float angle);
		~BulletStream();

		void placeAt(float tx, float ty, float sx, float sy, float u) override;
		void translate(float tx, float ty) override;
		void scale(float sx, float sy) override;
		void rotate(float u) override;
		void rotateAround(float x, float y, float u) override;

		void shootStraight();
		void shootShotgun();

		void changeInTime(float deltaTimeSeconds) override;

		std::unordered_map<shotPattern, float> fireRate;
		std::unordered_map<shotPattern, float> tSinceLastFire;

		BulletBar* bulletBar;
		float bulletWidth = 0.15;
		float bulletHeight = 0.2;

	private:
		glm::vec3 bulletColor = glm::vec3(0, 0, 0);
	};

}
