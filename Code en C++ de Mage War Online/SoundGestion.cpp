#include "stdafx.h"
#include "SoundGestion.h"

SoundGestion::SoundGestion()
{
	ListStringMusicName.push_back(sf::String("NeverGuess.ogg"));
	ListStringMusicName.push_back(sf::String("Wings.ogg"));
	//ListStringMusicName.push_back(sf::String("WelcomeChaos.ogg"));
	ListStringMusicName.push_back(sf::String("RisingSun.ogg"));
	ListStringMusicName.push_back(sf::String("LightDarknessDestruction.ogg"));
	ListStringMusicName.push_back(sf::String("KingBoss.ogg"));
	ListStringMusicName.push_back(sf::String("HeoresMarch.ogg"));
	ListStringMusicName.push_back(sf::String("FollowingYour.ogg"));
	ListStringMusicName.push_back(sf::String("EndlessSand.ogg"));
	ListStringMusicName.push_back(sf::String("DragonSlayer.ogg"));
	ListStringMusicName.push_back(sf::String("ChippyCloud.ogg"));
	ListStringMusicName.push_back(sf::String("ChipChippy.ogg"));
	ListStringMusicName.push_back(sf::String("BEAD.ogg"));
	ListStringMusicName.push_back(sf::String("01Combat.ogg"));

	ListMusicVolume.push_back(35);
	ListMusicVolume.push_back(35);
	//ListMusicVolume.push_back(65);
	ListMusicVolume.push_back(35);
	ListMusicVolume.push_back(35);
	ListMusicVolume.push_back(35);
	ListMusicVolume.push_back(35);
	ListMusicVolume.push_back(35);
	ListMusicVolume.push_back(35);
	ListMusicVolume.push_back(35);
	ListMusicVolume.push_back(35);
	ListMusicVolume.push_back(35);
	ListMusicVolume.push_back(35);
	ListMusicVolume.push_back(35);

	GetNewListMusic();
	ChangeMusic();
}

SoundGestion::~SoundGestion()
{
}

void SoundGestion::AddSound(sf::String str_sound, float volume, bool is_looping)
{
	std::shared_ptr<SoundBase> sound = std::shared_ptr<SoundBase>(new SoundBase());
	sound->Init(str_sound, volume, is_looping);
	sound->StartSound();
	listSounds.push_back(sound);
	sound.reset();
}

void SoundGestion::Update()
{
	std::list<std::shared_ptr<SoundBase>>::iterator i_sound = listSounds.begin();
	while (i_sound != listSounds.end())
	{
		sf::SoundSource::Status status_sound = (*i_sound)->GetStatusSound();
		if (status_sound == sf::SoundSource::Status::Stopped)
		{
			listSounds.erase(i_sound++);
		}
		else
		{
			i_sound++;
		}
	}

	UpdateMusic();
}

void SoundGestion::UpdateMusic()
{
	if (music_playing.getStatus() == sf::SoundSource::Stopped)
	{
		if (ListStringMusicToPlay.size() == 0)
		{
			GetNewListMusic();
		}

		ChangeMusic();
	}
}

void SoundGestion::GetNewListMusic()
{
	std::vector<sf::String> list_holder = ListStringMusicName;
	std::vector<int> list_holder2 = ListMusicVolume;

	while (list_holder.size() > 1)
	{
		int random_number = GlobalFunction::getRandomRange(1, list_holder.size()) - 1;
		ListStringMusicToPlay.push_back(list_holder[random_number]);
		ListMusicToPlayVolume.push_back(list_holder2[random_number]);
		list_holder.erase(list_holder.begin() + random_number);
		list_holder2.erase(list_holder2.begin() + random_number);
	}

	ListStringMusicToPlay.push_back(list_holder[0]);
	ListMusicToPlayVolume.push_back(list_holder2[0]);
}

void SoundGestion::ChangeMusic()
{
	music_playing.openFromFile(ListStringMusicToPlay[0]);
	music_playing.setVolume(ListMusicToPlayVolume[0]);
	std::cout << ListStringMusicToPlay[0].toAnsiString() << std::endl;
	ListStringMusicToPlay.erase(ListStringMusicToPlay.begin());
	ListMusicToPlayVolume.erase(ListMusicToPlayVolume.begin());
	music_playing.play();
}

SoundGestion* SoundGestion::s_instance1 = 0;