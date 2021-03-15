#pragma once
#include "HAPI_lib.h"
#include "Rectangle.h"

using namespace HAPISPACE;

class Sprite
{
private:
	int m_width{ 0 }, m_height{ 0 }, m_frameWidth{ 0 }, m_frameHeight{ 0 }, m_maxFrame{ 0 }, m_frameDelay{ 0 }, m_direction{ 1 };
	int m_currentFrame{ 0 }, m_frameCounter{ 0 };
	bool m_visible{ true }, m_loop{ true };

	Vector2 m_spriteSize;

	BYTE* m_data{ nullptr };

public:
	Sprite();
	~Sprite();

	bool Load(const std::string& filename);
	bool LoadAnimated(const std::string& filename, int frameWidth, int frameHeight, int maxFrame, int frameDelay, int direction, bool loop = true, bool visible = true);
	void clipBlit(BYTE* dest, Rectangle& destRect, int posX, int posY);

	void drawImageFrame();
	void resetFrame();

	Vector2 getSpriteSize() { return m_spriteSize; }
};

