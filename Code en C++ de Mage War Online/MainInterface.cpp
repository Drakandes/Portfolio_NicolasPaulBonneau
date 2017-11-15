#include "stdafx.h"
#include "MainInterface.h"


MainInterface::MainInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error" << std::endl;
	}
}

MainInterface::~MainInterface()
{
}

void MainInterface::Init(int current_language)
{
	language = current_language;
	game_name_text.setString("Mage War Online");

	game_name_text.setCharacterSize(96);
	game_name_text.setFont(font);
	game_name_text.setOrigin(sf::Vector2f(game_name_text.getGlobalBounds().width/2, game_name_text.getGlobalBounds().height / 2));
	game_name_text.setPosition(sf::Vector2f(800, 150));

	if (language == English_E)
	{
		play_text.setString("Play");
	}
	else
	{
		play_text.setString("Jouer");
	}
	play_text.setCharacterSize(60);
	play_text.setFont(font);
	play_text.setOrigin(sf::Vector2f(play_text.getGlobalBounds().width / 2, play_text.getGlobalBounds().height / 2));
	play_text.setPosition(sf::Vector2f(250, 550));

	if (language == English_E)
	{
		control_text.setString("Controls");
	}
	else
	{
		control_text.setString("Contrôles");
	}
	control_text.setCharacterSize(60);
	control_text.setFont(font);
	control_text.setOrigin(sf::Vector2f(control_text.getGlobalBounds().width / 2, control_text.getGlobalBounds().height / 2));
	control_text.setPosition(sf::Vector2f(750, 550));

	if (language == English_E)
	{
		exit_text.setString("Exit");
	}
	else
	{
		exit_text.setString("Quitter");
	}
	exit_text.setCharacterSize(60);
	exit_text.setFont(font);
	exit_text.setOrigin(sf::Vector2f(exit_text.getGlobalBounds().width / 2, exit_text.getGlobalBounds().height / 2));
	exit_text.setPosition(sf::Vector2f(1350, 550));
}

void MainInterface::DrawToScreen(sf::RenderWindow &window)
{
	sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();
	exit_text.setPosition(window_size.x - 250, 550);
	control_text.setPosition(window_size.x / 2, 550);
	play_text.setPosition(250, 550);
	game_name_text.setPosition(window_size.x / 2, 150);

	window.draw(game_name_text);
	window.draw(play_text);
	window.draw(control_text);
	window.draw(exit_text);
}

sf::String MainInterface::Interaction(sf::RenderWindow &window)
{
	sf::String interaction;
	sf::Vector2f mouse_position(sf::Mouse::getPosition(window));
	sf::RectangleShape mouse_rectangle;
	mouse_rectangle.setSize(sf::Vector2f(1, 1));
	mouse_rectangle.setPosition(mouse_position);

	if (mouse_rectangle.getGlobalBounds().intersects(exit_text.getGlobalBounds()))
	{
		exit_text.setCharacterSize(72);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			interaction = "Exit";
		}
		else
		{
			interaction = "nothing";
		}
		return interaction;
	}
	else
	{
		exit_text.setCharacterSize(60);
	}

	if (mouse_rectangle.getGlobalBounds().intersects(play_text.getGlobalBounds()))
	{
		play_text.setCharacterSize(72);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			interaction = "Play";
		}
		else
		{
			interaction = "nothing";
		}
		return interaction;
	}
	else
	{
		play_text.setCharacterSize(60);
	}

	if (mouse_rectangle.getGlobalBounds().intersects(control_text.getGlobalBounds()))
	{
		control_text.setCharacterSize(72);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			interaction = "Controls";
		}
		else
		{
			interaction = "nothing";
		}
		return interaction;
	}
	else
	{
		control_text.setCharacterSize(60);
	}
	
	interaction = "nothing";
	return interaction;
}

