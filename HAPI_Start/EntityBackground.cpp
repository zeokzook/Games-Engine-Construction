#include "EntityBackground.h"

EntityBackground::EntityBackground(std::string spriteName, Vector2 spriteSize, Rectangle screenSize) : Entity(spriteName)
{
	m_spriteSize = spriteSize;
	m_screenSize = screenSize;
	m_side = ESide::eNeutral;
}

EntityBackground::~EntityBackground()
{
}

void EntityBackground::Update()
{
	Vector2 pos{ getPosition() };

	if (pos.y >= m_screenSize.Height())
		pos.y = -m_spriteSize.h-(m_spriteSize.h - m_screenSize.Height());

	pos.y++;

	SetPosition(pos);
}
