#pragma once
#include "HAPI_lib.h"

using namespace HAPISPACE;
#include <unordered_map>
#include "Rectangle.h"

class Sprite;

class Graphics
{
private:
	Rectangle m_screenRect;
	Vector2 m_spriteSize;

	BYTE* m_screen{ nullptr };

	std::unordered_map<std::string, Sprite*> m_spriteMap;
public:
	Graphics();
	~Graphics();

	bool Initialise(int width, int height);
	bool CreateSprite(const std::string& filename, const std::string& name, int frameWidth = 0, int frameHeight = 0, int maxFrame = 1, int frameDelay = 0, int direction = 1, bool loop = true);
	void ClearToColour(HAPI_TColour colour);

	Rectangle getScreenSize() { return m_screenRect; }
	Vector2 getSpriteSize(const std::string& name);

	void Render(const std::string& name, int posX, int posY) const;
	void updateUI(int playerHealth, int score);
	void gameOverUI(int score, bool win);
	void resetFrame(const std::string& name);
	
};

