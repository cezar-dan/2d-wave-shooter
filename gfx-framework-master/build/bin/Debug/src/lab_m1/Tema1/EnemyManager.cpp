#include "EnemyManager.h"

using namespace std;
using namespace m1;

EnemyManager::EnemyManager(Tema1* w)
{
	world = w;
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::placeAt(float tx, float ty, float sx, float sy, float u)
{
}

void EnemyManager::changeInTime(float deltaTimeSeconds)
{
	cluster1LastSpawn += deltaTimeSeconds;
	cluster2LastSpawn += deltaTimeSeconds;
	cluster3LastSpawn += deltaTimeSeconds;
	if (cluster1LastSpawn > cluster1Cd)
	{
		spawnCluster1();
		cluster1LastSpawn = 0.0f;
	}

	if (cluster2LastSpawn > cluster2Cd)
	{
		spawnCluster2();
		cluster2LastSpawn = 0.0f;
	}

	if (cluster3LastSpawn > cluster3Cd)
	{
		spawnCluster3();
		cluster3LastSpawn = 0.0f;
	}

	vector<Entity*> updated;
	for (auto& entity : world->orderedEntities)
	{
		EnemyFly* enemyEntity = dynamic_cast<EnemyFly*>(entity);
		if (enemyEntity == NULL)
		{
			updated.push_back(entity);
		} 
		else
		{
			if (!enemyEntity->isDead)
			{
				updated.push_back(enemyEntity);
			} 
			else 
			{
				world->entities.erase(enemyEntity->key);
			}
		}
	}
	world->orderedEntities = updated;
}

void EnemyManager::spawnCluster1()
{
	float xSpawn = 1.0f, ySpawn = 5.2f;
	float deltaX = 0.6f, deltaY = 0.2f;

	int nrEnemies = rand() % 3 + 1;
	for (int i = 0; i < nrEnemies; ++i)
	{
		float lo = xSpawn - deltaX, hi = xSpawn + deltaX;
		float xEnemy = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));

		lo = ySpawn - deltaY;
		hi = ySpawn + deltaY;
		float yEnemy = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));

		lo = 0.2f;
		hi = 0.7f;
		float velocityEn = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));

		lo = 0.1f;
		hi = 0.18f;
		float sizeEn = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));

		EnemyFly* enemy = new EnemyFly(xEnemy, yEnemy, sizeEn, 0.0f, velocityEn);
		enemy->setPlayer(world->player);
		std::ostringstream ofs;
		ofs << enemy;
		const string key = ofs.str();
		enemy->key = key;
		world->insertInEntityMap(key, enemy);
	}

}

void EnemyManager::spawnCluster2()
{
	float xSpawn = 2.0f, ySpawn = -1.0f;
	float deltaX = 1.0f, deltaY = 0.3f;

	int nrEnemies = rand() % 3 + 2;
	for (int i = 0; i < nrEnemies; ++i)
	{
		float lo = xSpawn - deltaX, hi = xSpawn + deltaX;
		float xEnemy = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));

		lo = ySpawn - deltaY;
		hi = ySpawn + deltaY;
		float yEnemy = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));

		lo = 0.2f;
		hi = 0.7f;
		float velocityEn = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));

		lo = 0.1f;
		hi = 0.18f;
		float sizeEn = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));

		EnemyFly* enemy = new EnemyFly(xEnemy, yEnemy, sizeEn, 0.0f, velocityEn);
		enemy->setPlayer(world->player);
		std::ostringstream ofs;
		ofs << enemy;
		const string key = ofs.str();
		enemy->key = key;
		world->insertInEntityMap(key, enemy);
	}
}

void EnemyManager::spawnCluster3()
{

}
