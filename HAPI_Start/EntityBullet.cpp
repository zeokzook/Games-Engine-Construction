#include "EntityBullet.h"

EntityBullet::EntityBullet(std::string spriteName, Vector2 spriteSize, Rectangle screenSize) : Entity(spriteName)
{
	m_spriteSize = spriteSize;
	m_screenSize = screenSize;
}

EntityBullet::~EntityBullet()
{
}

void EntityBullet::Update()
{
	Vector2 pos{ getPosition() };

	if (m_health <= 0) {
		m_alive = false;
	}

	if (m_alive)
		if (m_side == ESide::eEnemy)
			pos.y += m_speed;
		else if (m_side == ESide::ePlayer)
			pos.y -= m_speed;

	if ((pos.y > m_screenSize.bottom || pos.y < 0 - m_spriteSize.h) && m_alive)
		m_alive = false;

	SetPosition(pos);
}
