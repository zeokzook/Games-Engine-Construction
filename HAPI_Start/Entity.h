#pragma once
// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
using namespace HAPISPACE;

#include "Vector2.h"
#include "Rectangle.h"
#include <string>

enum class ESide
{
	ePlayer,
	eEnemy,
	eNeutral
};

class Graphics;

class Entity
{
private:
	Vector2 m_position;
	Vector2 m_oldPosition;

protected:
	Rectangle m_rect, m_screenSize;
	Vector2 m_spriteSize;
	std::string m_spriteName;
	int m_health{ 1 };
	int m_damage{ 1 };
	int m_shootTime{ 250 };
	int m_fireDelay{ 250 };
	int m_frameNum{ 0 };
	int m_currentTime{ 0 };
	bool m_alive{ true };
	float m_speed{ 1.0f };
	ESide m_side{ ESide::eNeutral };

public:
	bool isFire{ false };

	Entity(std::string spriteName);
	virtual ~Entity();

	void Render(Graphics &gfx);

	void SetPosition(Vector2 newPos) { m_oldPosition = m_position;  m_position = newPos; }
	void SetSpeed(float newSpeed) { m_speed = newSpeed; }
	void SetAlive(bool alive) { m_alive = alive; }
	void SetSide(ESide newSide) { m_side = newSide; }
	void SetFireDelay(int newDelay) { m_fireDelay = newDelay; }
	void SetCurrentTime(int newTime) { m_currentTime = newTime; }
	void SetHealth(int newHealth) { m_health = newHealth; }
	void SetShootTime(int newTime) { m_shootTime = newTime; }

	Rectangle getEntityRect() { return m_rect = Rectangle((int)m_spriteSize.w, (int)m_spriteSize.h, m_position); }
	Vector2 getPosition() const { return m_position; }
	float getSpeed() const { return m_speed; }
	int getCurrentTime() const { return m_currentTime; }
	int getDamage() const { return m_damage; }
	int getHealth() const { return m_health; }
	std::string getName() const { return m_spriteName; }

	bool isAlive() { return m_alive; }

	void clampToScreen();
	void damaged(int damage);

	virtual void Update() = 0;
	virtual ESide GetSide() const = 0;
};

