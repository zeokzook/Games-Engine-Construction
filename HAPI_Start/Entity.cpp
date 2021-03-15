#include "Entity.h"
#include "Graphics.h"

Entity::Entity(std::string spriteName) : m_spriteName(spriteName)
{
	m_side = ESide::eNeutral;
}

Entity::~Entity()
{
}

void Entity::Render(Graphics& gfx)
{
	gfx.Render(m_spriteName, (int)m_position.x, (int)m_position.y);
}

void Entity::clampToScreen()
{
	if (m_position.x < m_screenSize.left)
		m_position.x = 0;
	if (m_position.x + m_spriteSize.w > m_screenSize.right)
		m_position.x = m_screenSize.right - m_spriteSize.w;
	if (m_position.y < m_screenSize.top)
		m_position.y = 0;
	if (m_position.y + m_spriteSize.h > m_screenSize.bottom)
		m_position.y = m_screenSize.bottom - m_spriteSize.h;
}

void Entity::damaged(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
		m_alive = false;
}


