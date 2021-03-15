#pragma once
#include "Entity.h"
class EntityBullet : public Entity
{
public:
	EntityBullet(std::string spriteName, Vector2 spriteSize = Vector2(0.0f, 0.0f), Rectangle screenSize = Rectangle(0, 0, 0, 0));
	~EntityBullet();

	void Update() override final;
	ESide GetSide() const override final { return m_side; }
};

