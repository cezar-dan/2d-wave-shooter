#pragma once

#include "Shapes/Entities/Entity.h"
#include "Shapes/Entities/EnemyFly.h"
#include "Tema1.h"
#include <vector>

namespace m1
{
	class EnemyManager : public Entity, public ITimeDependant
	{
	public:
		EnemyManager(Tema1* w);
		~EnemyManager();

		void placeAt(float tx, float ty, float sx, float sy, float u) override;
		void changeInTime(float deltaTimeSeconds) override;

		Tema1* world;

		float cluster1Cd = 3.0f, cluster1LastSpawn = 3.0f;
		float cluster2Cd = 5.0f, cluster2LastSpawn = 0.0f;
		float cluster3Cd = 10.0f, cluster3LastSpawn = 0.0f;

		void spawnCluster1();
		void spawnCluster2();
		void spawnCluster3();
	};
}
