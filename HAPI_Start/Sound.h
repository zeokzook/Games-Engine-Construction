#pragma once
#include "HAPI_lib.h"

using namespace HAPISPACE;
#include "Rectangle.h"

class Sound
{
private:
	std::string m_filename;
public:
	Sound();
	~Sound();

	bool LoadSound(std::string filename);
	void PlaySound();
};

