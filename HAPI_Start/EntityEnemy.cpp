#include "EntityEnemy.h"
#include <time.h>

EntityEnemy::EntityEnemy(std::string spriteName, Vector2 spriteSize, Rectangle screenSize) : Entity(spriteName)
{
	m_spriteSize = spriteSize;
	m_screenSize = screenSize;
	m_side = ESide::eEnemy;
}

EntityEnemy::~EntityEnemy()
{
}

void EntityEnemy::Update()
{
	Vector2 pos{ getPosition() };

	if (m_health <= 0)
		m_alive = false;

	if (m_alive) {
		pos.y++;

		if (m_currentTime > m_shootTime + m_fireDelay) {
			m_currentTime = 0;
			isFire = true;
		}
	}

	if (pos.y >= m_screenSize.bottom)
		pos.y = -m_spriteSize.h;

	SetPosition(pos);
}
