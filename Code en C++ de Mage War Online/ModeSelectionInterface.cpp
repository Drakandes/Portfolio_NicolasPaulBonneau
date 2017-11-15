#include "stdafx.h"
#include "ModeSelectionInterface.h"

ModeSelectionInterface::ModeSelectionInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font player" << std::endl;
	}

	if (language == English_E)
	{
		string_gamemode[0] = "Childish";
		string_gamemode[1] = "Beginner";
		string_gamemode[2] = "Intermediate";
		string_gamemode[3] = "Expert";
		interface_name = GlobalFunction::CreateText(position_interface_name, "Choose your difficulty!", font, 34);
	}
	else
	{
		string_gamemode[0] = "Enfantin";
		string_gamemode[1] = "Débutant";
		string_gamemode[2] = "Intermédiare";
		string_gamemode[3] = "Expert";
		interface_name = GlobalFunction::CreateText(position_interface_name, "Choississez votre difficulté!", font, 34);
	}


	for (int i = 0; i < number_gamemodes; i++)
	{
		text_gamemode[i] = GlobalFunction::CreateText(position_first_gamemode + sf::Vector2f(0,100*i), string_gamemode[i], font, 20);
	}
}

ModeSelectionInterface::~ModeSelectionInterface()
{
}

bool ModeSelectionInterface::ChooseGameMode(sf::RenderWindow &window)
{
	sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();
	position_interface_name.x = window_size.x / 2;
	position_first_gamemode.x = window_size.x / 2;

	for (int i = 0; i < number_gamemodes; i++)
	{
		text_gamemode[i].setPosition(position_first_gamemode + sf::Vector2f(0, 100 * i));
	}

	window.clear();
	TextBoxGenerator::instance()->ClearList();

	sf::Vector2f mouse_position = GlobalFunction::GetMousePosition(window, sf::Vector2f(0, 0));
	for (int i = 0; i < number_gamemodes; i++)
	{
		if (text_gamemode[i].getGlobalBounds().contains(mouse_position))
		{
			DisplayTextInformation(mouse_position, i);
			text_gamemode[i].setFillColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				ListObjectsSingleton::instance()->ChangeGameMode(i);
				return false;
			}
		}
		else
		{
			text_gamemode[i].setFillColor(sf::Color::White);
		}
		window.draw(text_gamemode[i]);
	}

	TextBoxGenerator::instance()->DrawAllTextbox(window);
	window.draw(interface_name);
	window.display();

	return true;
}

void ModeSelectionInterface::DisplayTextInformation(sf::Vector2f mouse_position, int mode_displaying)
{
	if (mode_displaying == ChildishMode)
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "The monster's damage is reduced by 50%.";
			listString.push_back(string1);
		}
		else
		{
			sf::String string1 = "Les dégâts des monstres sont réduits de 50%";
			listString.push_back(string1);
		}

		listLetterSize.push_back(20);
		listIfCentered.push_back(false);

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
	else if (mode_displaying == BeginnerMode)
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "The monster's damage is reduced by 25%.";
			listString.push_back(string1);
		}
		else
		{
			sf::String string1 = "Les dégâts des monstres sont réduits de 25%";
			listString.push_back(string1);
		}

		listLetterSize.push_back(20);
		listIfCentered.push_back(false);

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
	else if (mode_displaying == IntermediateMode)
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "The monster's damage is reduced by 50%.";
			listString.push_back(string1);
		}
		else
		{
			sf::String string1 = "Les dégâts des monstres ne sont pas modifiés. C'est le mode par défaut.";
			listString.push_back(string1);
		}

		listLetterSize.push_back(20);
		listIfCentered.push_back(false);

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
	else if (mode_displaying == ExpertMode)
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "The monster's damage is increased by 25%.";
			listString.push_back(string1);
		}
		else
		{
			sf::String string1 = "Les dégâts des monstres sont augmentés de 25%";
			listString.push_back(string1);
		}

		listLetterSize.push_back(20);
		listIfCentered.push_back(false);

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
}
