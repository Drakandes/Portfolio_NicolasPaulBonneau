#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "SoundBase.h"
#include <memory>
#include <iostream>
#include <list>
#include "GlobalFunction.h"

class SoundGestion
{
private:
	std::list < std::shared_ptr<SoundBase>> listSounds;
	std::vector<sf::String> ListStringMusicName;
	std::vector<int> ListMusicVolume;
	std::vector<sf::String> ListStringMusicToPlay;
	std::vector<int> ListMusicToPlayVolume;
	sf::Music music_playing;
	static SoundGestion *s_instance1;

	void UpdateMusic();
	void GetNewListMusic();
	void ChangeMusic();
public:
	SoundGestion();
	~SoundGestion();

	static void Initialize()
	{
		s_instance1 = new SoundGestion();
	}
	static SoundGestion *instance()
	{
		if (!s_instance1)
			s_instance1 = new SoundGestion;
		return s_instance1;
	}

	void AddSound(sf::String str_sound, float volume, bool is_looping);
	void Update();
};

