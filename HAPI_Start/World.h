#pragma once
// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
using namespace HAPISPACE;
#include <vector>
#include "Sound.h"

class Graphics;
class Entity;

class World
{
private:
	Graphics* m_gfx{ nullptr };
	Sound* SE_explode = new Sound;
	Sound* SE_shoot = new Sound;

	int m_playerHealth{ 20 };
	
	int m_numBullets{ 100 };
	int m_numEnemy{ 10 };
	int m_numExplosions{ 100 };

	int m_playerVectorStartIndex{ 0 };
	int m_bulletsVectorStartIndex{ 0 };
	int m_enemyVectorStartIndex{ 0 };
	int m_explVectorStartIndex{ 0 };

	int m_delay{ 15 };
	int	m_currentDelay{ 0 }, m_currentTime{ 0 }, deadEnemies{ 0 };

	int m_currentScore{ 0 };

	std::vector<Entity*> m_entityVector;

	bool win{ false }, gameOver{ false };

	bool LoadLevel();
	void Update();
	void Reset();
public:
	World();
	~World();

	void Run();
};

