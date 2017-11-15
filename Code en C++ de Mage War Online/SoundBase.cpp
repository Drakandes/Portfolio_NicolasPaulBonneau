#include "stdafx.h"
#include "SoundBase.h"

SoundBase::SoundBase()
{
}

SoundBase::~SoundBase()
{
}

void SoundBase::Init(sf::String str_sound, float volume, bool is_looping)
{
	buffer;
	if (!buffer.loadFromFile(str_sound))
	{
		std::cout << "Error while loading " << str_sound.toAnsiString() << " sound." << std::endl;
	}

	sound;
	sound.setBuffer(buffer);
	sound.setVolume(volume);
	sound.setLoop(is_looping);
	sound.play();
}
