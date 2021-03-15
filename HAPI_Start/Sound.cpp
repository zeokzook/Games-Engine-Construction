#include "Sound.h"

Sound::Sound()
{
}

Sound::~Sound()
{
}

bool Sound::LoadSound(std::string filename)
{
	m_filename = filename;

	if (!HAPI.LoadSound(m_filename)) {
		HAPI.UserMessage("Failed to load sound!", "ERROR");
		return false;
	}

	return true;
}

void Sound::PlaySound()
{
	HAPI.PlaySound(m_filename);
}
