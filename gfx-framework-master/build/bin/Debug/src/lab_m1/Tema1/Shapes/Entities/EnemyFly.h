#pragma once

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include <string>
#include <unordered_map>

namespace m1
{
	class EnemyFly : public Enemy
	{

	public:
		EnemyFly();
		EnemyFly(float xc, float yc);
		EnemyFly(float xc, float yc, float size, float angle, float velocity);
		~EnemyFly();


		void placeAt(float tx, float ty, float sx, float sy, float u) override;

	private:
		Player* player = NULL;

		float wingAngleToOx = RADIANS(-35);
		float wingOffsetOx = sizeY * -0.1f;
		float wingOffsetOy = sizeY * 0.1f;
		float bodyContourSizeX = sizeX * 1.1f;
		float bodyContourSizeY = sizeY * 1.1f;

		glm::vec3 wingColor = glm::vec3(128.0f / 255, 128.0f / 255, 128.0f / 255);
		glm::vec3 contourColor = glm::vec3(0, 0, 0);
	};

}
