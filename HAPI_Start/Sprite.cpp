#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite() {
	delete[]m_data;
}

bool Sprite::Load(const std::string& filename) {
	if (!HAPI.LoadTexture(filename, &m_data, m_width, m_height)) {
		HAPI.UserMessage("Failed to load texture!", "ERROR");
		return false;
	}

	m_spriteSize = Vector2(m_width, m_height);

	return true;
}

bool Sprite::LoadAnimated(const std::string& filename, int frameWidth, int frameHeight, int maxFrame, int frameDelay, int direction, bool loop, bool visible)
{
	if (!HAPI.LoadTexture(filename, &m_data, m_width, m_height)) {
		HAPI.UserMessage("Failed to load texture!", "ERROR");
		return false;
	}

	m_frameWidth = frameWidth;
	m_frameHeight = frameHeight;
	m_maxFrame = maxFrame;
	m_frameDelay = frameDelay;
	m_direction = direction;
	m_loop = loop;
	m_visible = visible;

	m_spriteSize = Vector2(m_frameWidth, m_frameHeight);

	return true;
}

void Sprite::clipBlit(BYTE* dest, Rectangle& destRect, int posX, int posY) {

	if (!m_visible) return;

	Rectangle sourceRect;

	if (m_maxFrame >= 1) 
	{
		drawImageFrame();
		if (!m_visible) return;

		sourceRect = Rectangle(0, m_frameWidth, 0, m_frameHeight);

		sourceRect.Translate(posX, posY);
		sourceRect.ClipTo(destRect);
		sourceRect.Translate(-posX, -posY);
	
		sourceRect.Translate(m_currentFrame * m_frameWidth, 0);
	}
	else 
	{
		sourceRect = Rectangle(0, m_width, 0, m_height);
		sourceRect.Translate(posX, posY);
		sourceRect.ClipTo(destRect);
		sourceRect.Translate(-posX, -posY);
	}

	if (posX < 0) posX = 0;
	if (posY < 0) posY = 0;

	BYTE* tempScr = dest + (posY * (size_t)destRect.Width() + posX) * 4;
	BYTE* tempTex = m_data + ((size_t)sourceRect.top * (size_t)sourceRect.Width() + (size_t)sourceRect.left) * 4;

	int increment = (destRect.Width() - sourceRect.Width())*4;
	int	texIncrement = (m_width - sourceRect.Width())*4;

	for (int y = 0; y < sourceRect.Height(); y++) 
	{
		for (int x = 0; x < sourceRect.Width(); x++) 
		{
			BYTE alpha = tempTex[3];

			if (alpha > 0) 
			{
				BYTE r = tempTex[0];
				BYTE g = tempTex[1];
				BYTE b = tempTex[2];

				if (alpha == 255) 
				{
					memcpy(tempScr, tempTex, 4);
				}
				else
				{
					tempScr[0] += ((alpha * (r - tempScr[0])) >> 8);
					tempScr[1] += ((alpha * (g - tempScr[1])) >> 8);
					tempScr[2] += ((alpha * (b - tempScr[2])) >> 8);
				}
			}
			tempTex += 4;
			tempScr += 4;
		}
		tempTex += texIncrement;
		tempScr += increment;
	}
}

void Sprite::drawImageFrame()
{
	m_frameCounter++;

	if (m_frameCounter > m_frameDelay) 
	{
		m_frameCounter = 0;

		if (m_direction == 1)
			m_currentFrame++; //Forwards
		else
			m_currentFrame--; //backwards
	}

	//check for looping
	if (m_direction == 1)
		if (m_currentFrame > m_maxFrame - 1)
			if (m_loop)
				m_currentFrame = 0;
			else
				m_visible = false;
		else
			if (m_currentFrame < 0)
				if (m_loop)
					m_currentFrame = m_maxFrame - 1;
				else
					m_visible = false;
}

void Sprite::resetFrame()
{
	m_currentFrame = 0;
	m_visible = true;
}
