#include "Graphics.h"
#include "Sprite.h"


Graphics::Graphics()
{
}

Graphics::~Graphics()
{
	for (auto& p : m_spriteMap) {
		delete p.second;
	}
}

bool Graphics::Initialise(int width, int height) {
	if (!HAPI.Initialise(width, height, "Milestone 3")) {
		HAPI.UserMessage("Failed to Intialise!", "ERROR");
		return false;
	}

	m_screenRect = Rectangle(width, height);

	//Getting screen pointer
	m_screen = HAPI.GetScreenPointer();
	return true;
}

bool Graphics::CreateSprite(const std::string& filename, const std::string& name, int frameWidth, int frameHeight, int maxFrame, int frameDelay, int direction, bool loop) {
	Sprite* newSprite = new Sprite;

	if (frameWidth != 0 && frameHeight != 0) {
		if (!newSprite->LoadAnimated(filename, frameWidth, frameHeight, maxFrame, frameDelay, direction, loop)) {
			delete newSprite;
			HAPI.UserMessage("Failed to load texture!", "ERROR");
			return false;
		}
	}
	else {
		if (!newSprite->Load(filename)) {
			delete newSprite;
			HAPI.UserMessage("Failed to load texture!", "ERROR");
			return false;
		}
	}

	m_spriteMap[name] = newSprite;

	return true;
}

void Graphics::ClearToColour(HAPI_TColour colour) {
	for (int i = 0; i < m_screenRect.Width() * m_screenRect.Height(); i++) {
		m_screen[(i * 4)] = colour.red;
		m_screen[(i * 4) + 1] = colour.green;
		m_screen[(i * 4) + 2] = colour.blue;
	}
}

Vector2 Graphics::getSpriteSize(const std::string& name)
{
	return m_spriteSize = m_spriteMap.at(name)->getSpriteSize();
}

void Graphics::Render(const std::string& name, int posX, int posY) const{
	
	if (m_spriteMap.find(name) == m_spriteMap.end())
	{
		HAPI.UserMessage(name + "does not exists!", "ERROR");
		return;
	}

	Rectangle destRect(0, m_screenRect.Width(), 0, m_screenRect.Height());
	m_spriteMap.at(name)->clipBlit(m_screen, destRect, posX, posY);
}

void Graphics::updateUI(int playerHealth, int score)
{
	HAPI.RenderText(m_screenRect.left, (m_screenRect.bottom - 20), HAPI_TColour::WHITE, "Health: " + std::to_string(playerHealth), 20);
	HAPI.RenderText(m_screenRect.left, m_screenRect.top, HAPI_TColour::WHITE, "Score: " + std::to_string(score), 20);
}

void Graphics::gameOverUI(int score, bool win)
{
	if(win)
		HAPI.RenderText(m_screenRect.right / 2 - 75, m_screenRect.bottom / 2 - 200, HAPI_TColour::WHITE, "You Win!", 40);
	else
		HAPI.RenderText(m_screenRect.right / 2 - 75, m_screenRect.bottom / 2 - 200, HAPI_TColour::WHITE, "You Lose", 40);

	HAPI.RenderText(m_screenRect.right / 2 - 50, m_screenRect.bottom / 2 - 150, HAPI_TColour::WHITE, "Score: " + std::to_string(score), 20);
	HAPI.RenderText(m_screenRect.right / 2 - 100, m_screenRect.bottom / 2 - 125, HAPI_TColour::WHITE, "Press ENTER to play again", 18);
	HAPI.RenderText(m_screenRect.right / 2 - 85, m_screenRect.bottom / 2 - 107, HAPI_TColour::WHITE, "Press ESC to play again", 18);

}

void Graphics::resetFrame(const std::string& name)
{
	m_spriteMap.at(name)->resetFrame();
}




