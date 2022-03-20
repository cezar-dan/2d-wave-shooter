#pragma once

#include "Entity.h"
#include "Player.h"
#include "../../ITimeDependant.h"
#include <string>
#include <unordered_map>

namespace m1
{
	class Enemy : public Entity, public ITimeDependant, public ICollidable
	{

	public:
		Enemy();
		Enemy(float xc, float yc);
		Enemy(float xc, float yc, float size, float angle, float velocity);
		~Enemy();


		void changeInTime(float time) override;
		void setPlayer(Player* player);
		float velocity = 0.2f;
		bool isDead = false;
		std::string key;

		virtual std::vector<Shape*> getCollideShapes() override;
		virtual void ProcessCollision(ICollidable* other) override;

	private:
		Player* player = NULL;
	};

}
