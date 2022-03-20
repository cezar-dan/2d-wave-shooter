#pragma once

#include <string>
#include <unordered_map>
#include "Entity.h"

namespace m1
{
	class HealthBar : public Entity
	{
	public:
		HealthBar();
		HealthBar(float xc, float yc);
		~HealthBar();

		void placeAt(float tx, float ty, float sx, float sy, float u) override;
		void setMaxHealth(int maxHp);
		void decreaseHealth();

	private:
		float initHealthSizeX, initHealthSizeY;
		int maxHealth = 10;
		int health;

	};

}
