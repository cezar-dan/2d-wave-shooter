#pragma once

#include <string>
#include <unordered_map>
#include "Entity.h"

namespace m1
{
	class BulletBar : public Entity
	{
	public:
		BulletBar(float straightFireRate, float shotgunFireRate);
		~BulletBar();

		void placeAt(float tx, float ty, float sx, float sy, float u) override;
		void updateShotgunBar(float timePassed);
		void updateStraightBar(float timePassed);
		void resetStraightTime();
		void resetShotgunTime();

	private:
		float straightFireRate, shotgunFireRate;

		glm::vec3 frameColor = glm::vec3(0, 0, 0);
		glm::vec3 fillColor = glm::vec3(255.0f / 255, 198.0f / 255, 26.0f / 255);
		float initScaleY = 1.2f;
	};

}
