#pragma once

#include "BulletStream.h"
#include <string>
#include <unordered_map>
#include "../../Tema1.h"
#include "HealthBar.h"

namespace m1
{
	class Player : public Entity, public ICollidable
	{
	public:
		Player();
		Player(float xc, float yc);
		Player(float xc, float yc, float size, float angle);
		Player(float xc, float yc, float size, float angle, Tema1* world);
		~Player();

		BulletStream* bulletStream;
		int health = 10;

		void placeAt(float tx, float ty, float sx, float sy, float u) override;
		void shoot(BulletStream::shotPattern p);

		virtual std::vector<Shape*> getCollideShapes() override;
		virtual void ProcessCollision(ICollidable* other) override;

	private:
		Tema1* world;
		HealthBar* healthBar;
		float armAngleToOx = RADIANS(30);
		float armSize = sizeX / 3;
		float armContourSize = armSize * 1.3f;
		float bodyContourSize = sizeX * 1.1f;
		float armCenterOffset = sizeX / 2;
		float bulletOffset = sizeX;
		glm::vec3 bodyColor = glm::vec3(0, 0.6, 0);
		glm::vec3 armColor = glm::vec3(0.6, 1, 0.4);
		glm::vec3 bulletColor = glm::vec3(1.0 / 255, 1.0 / 60, 1.0 / 54);
		glm::vec3 contourColor = glm::vec3(0, 0, 0);
	};

}
