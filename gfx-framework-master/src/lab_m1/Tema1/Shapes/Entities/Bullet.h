#pragma once

#include "../Primitives/Rectangle.h"
#include "../../ITimeDependant.h"
#include "../../ICollidable.h"

namespace m1
{
	class Bullet : public Rectangle, public ITimeDependant, public ICollidable
	{
	public:
		Bullet();
		Bullet(float xc, float yc, glm::vec3 color, std::string name);
		Bullet(float xc, float yc, float height, float width, float angle, glm::vec3 color, std::string name);
		~Bullet();

		void setVelocity(float v);
		void setMaxRange(float r);
		void changeInTime(float deltaTimeSeconds) override;
		bool isDone();

		virtual std::vector<Shape*> getCollideShapes() override;
		virtual void ProcessCollision(ICollidable* other) override;
	
	private:
		float velocity = 2.0f;
		float maxRange = 2.0f;
		float distanceTraveled = 0.0f;
	};
}
