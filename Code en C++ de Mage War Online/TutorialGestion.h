#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "TextBoxGenerator.h"
#include "Player.h"

class TutorialGestion
{
private:
	const static int number_tutorial = 6;
	static TutorialGestion *s_instance1;
	std::vector<sf::String> ListTextTutorial;
	sf::Vector2f position_tutorial{ 600,600 };
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	int number_tutorial_shown = 0;
	int tutorial_showing = T_WeaponCraft;

	std::shared_ptr<Player> pointer_player;

	std::vector<int> listLetterSize;
	std::vector<sf::String> listString;
	std::vector<bool> listIfCentered;

	bool tutorial_shown[number_tutorial]{ false,false,false,false,false,false };
	bool can_show_tutorial[number_tutorial]{ false,false,false,false,false,false };
	bool all_tutorial_shown = false;

	void CheckNewTutorial();
public:
	TutorialGestion();
	~TutorialGestion();

	static void Initialize()
	{
		s_instance1 = new TutorialGestion();
	}
	static TutorialGestion *instance()
	{
		if (!s_instance1)
			s_instance1 = new TutorialGestion;
		return s_instance1;
	}

	void GivePointerPlayer(std::shared_ptr<Player> player);
	void Update(sf::Vector2f position_view_player);
};

