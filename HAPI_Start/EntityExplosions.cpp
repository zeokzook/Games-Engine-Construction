#include "EntityExplosions.h"

EntityExplosions::EntityExplosions(std::string spriteName, Vector2 spriteSize, Rectangle screenSize) : Entity(spriteName)
{
	m_spriteSize = spriteSize;
	m_screenSize = screenSize;
	m_side = ESide::eNeutral;
}

EntityExplosions::~EntityExplosions()
{
}

void EntityExplosions::Update()
{
}
