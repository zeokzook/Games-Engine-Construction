#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(std::string spriteName, Vector2 spriteSize, Rectangle screenSize) : Entity(spriteName)
{
	m_spriteSize = spriteSize;
	m_screenSize = screenSize;
	m_side = ESide::ePlayer;
}

EntityPlayer::~EntityPlayer()
{
}

void EntityPlayer::Update()
{
	Vector2 pos{ getPosition() };

	if (m_health <= 0) {
		m_alive = false;
	}

	int startTime = HAPI.GetTime();
	//Loading key data
	static const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();

	//Movement
	if (keyData.scanCode['W'] || keyData.scanCode[HK_UP]) //UP
		pos.y -= m_speed;
	
	if (keyData.scanCode['S'] || keyData.scanCode[HK_DOWN]) //DOWN
		pos.y += m_speed;
	
	if (keyData.scanCode['A'] || keyData.scanCode[HK_LEFT]) //LEFT
		pos.x -= m_speed;

	if (keyData.scanCode['D'] || keyData.scanCode[HK_RIGHT]) //RIGHT
		pos.x += m_speed;

	if (keyData.scanCode[HK_SPACE]) //FIRE
		if (m_currentTime > m_fireDelay) {
			m_currentTime = 0;
			isFire = true;
		}

	SetPosition(pos);

	clampToScreen();
}
