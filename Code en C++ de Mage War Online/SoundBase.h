#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class SoundBase
{
private:
	sf::Sound sound;
	sf::SoundBuffer buffer;
 
public:
	SoundBase();
	~SoundBase();

	void Init(sf::String str_sound, float volume, bool is_looping);
	sf::SoundSource::Status GetStatusSound() { return sound.getStatus(); }
	sf::Time GetTimePlayed() { return sound.getPlayingOffset(); }
	void StartSound() { sound.play(); }
};

