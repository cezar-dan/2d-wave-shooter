#pragma once

#include "Entity.h"
#include "../../ICollidable.h"

namespace m1
{
	class Obstacles : public Entity, public ICollidable
	{

	public:
		Obstacles();
		~Obstacles();

		void placeAt(float x, float ty, float sx, float sy, float u) override;

		virtual std::vector<Shape*> getCollideShapes() override;
		virtual void ProcessCollision(ICollidable* other) override;

	private:
		glm::vec3 treeTrunkColor = glm::vec3(102.0f / 255, 34.0f / 255, 0.0f / 255);
		glm::vec3 blackHoleColor = glm::vec3(50.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);
		glm::vec3 rockColor = glm::vec3(89.0f / 255.0f, 89.0f / 255.0f, 89.0f / 255.0f);
	};

}
