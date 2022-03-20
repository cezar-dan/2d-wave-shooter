#pragma once

#include "Entity.h"
#include "../../ICollidable.h"
#include <string>
#include <unordered_map>

namespace m1
{
	class MapEdges : public Entity, public ICollidable
	{

	public:
		MapEdges();
		~MapEdges();

		void placeAt(float x, float ty, float sx, float sy, float u) override;

		virtual std::vector<Shape*> getCollideShapes() override;
		virtual void ProcessCollision(ICollidable* other) override;

	private:
		glm::vec3 barrierColor = glm::vec3(64.0f / 255, 102.0f / 255, 51.0f / 255);
		glm::vec3 centerColor = glm::vec3(66.0f / 255.0f, 245.0f / 255.0f, 242.0f / 255.0f);
	};

}
