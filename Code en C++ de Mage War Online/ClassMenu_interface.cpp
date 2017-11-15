#include "stdafx.h"
#include "ClassMenu_interface.h"

ClassMenu_interface::ClassMenu_interface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font  class menu interface" << std::endl;
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("ClassMenuInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("ClassMenuInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
#pragma endregion TextureInterfaceLoading

	interface_class_menu = GlobalFunction::CreateSpriteWithoutOrigin(position_interface, size_interface, texture_interface);

	if (language == English_E)
	{
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Class Selection", font, 32);
	}
	else
	{
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Menu des Classes", font, 32);
	}
	text_name_interface.setFillColor(sf::Color::Color(108, 129, 197));

	sf::Vector2i counter(0,0);
	for (int i = 0; i < number_class; i++)
	{
		rect_class[i] = GlobalFunction::CreateRectangle(size_rect_class, position_first_rect_class + sf::Vector2f(position_between_rect_class*counter.x, counter.y*100));
		rect_class[i].setFillColor(sf::Color::Green);
		counter.x++;
		if (counter.x == 3)
		{
			counter.x = 0;
			counter.y++;
		}
	}
}

ClassMenu_interface::~ClassMenu_interface()
{
}

void ClassMenu_interface::Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	CreateRectangleInformation(mouse_position);
	CheckPlayerAction(player, mouse_position);

	
}

void ClassMenu_interface::CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	if (clock_click.getElapsedTime().asSeconds() >= 0.5)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			int current_class = player->GetCurrentClassPlayer();
			if (rect_class[ClassFire].getGlobalBounds().contains(mouse_position) && current_class != ClassFire)
			{
				if(player->GetPlayerListDrawback()[6])
				{
					if (player->GetClassPlayerCantUse() != ClassFire)
					{
						player->GivePlayerNewClass(ClassFire);
					}
				}
				else
				{
					player->GivePlayerNewClass(ClassFire);
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
			}
			else if (rect_class[ClassWater].getGlobalBounds().contains(mouse_position) && current_class != ClassWater)
			{
				if (player->GetPlayerListDrawback()[6])
				{
					if (player->GetClassPlayerCantUse() != ClassWater)
					{
						player->GivePlayerNewClass(ClassWater);
					}
				}
				else
				{
					player->GivePlayerNewClass(ClassWater);
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
			}
			else if (rect_class[ClassGrass].getGlobalBounds().contains(mouse_position) && current_class != ClassGrass)
			{
				if (player->GetPlayerListDrawback()[6])
				{
					if (player->GetClassPlayerCantUse() != ClassGrass)
					{
						player->GivePlayerNewClass(ClassGrass);
					}
				}
				else
				{
					player->GivePlayerNewClass(ClassGrass);
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
			}
			else if (rect_class[ClassRock].getGlobalBounds().contains(mouse_position) && current_class != ClassRock)
			{
				if (player->GetPlayerListDrawback()[6])
				{
					if (player->GetClassPlayerCantUse() != ClassRock)
					{
						player->GivePlayerNewClass(ClassRock);
					}
				}
				else
				{
					player->GivePlayerNewClass(ClassRock);
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
			}
		}
	}
}

void ClassMenu_interface::Draw(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	interface_class_menu.setPosition(position_view_player + position_interface);
	text_name_interface.setPosition(position_view_player + position_name_interface);

	window.draw(interface_class_menu);
	window.draw(text_name_interface);

	sf::Vector2i counter(0, 0);
	for (int i = 0; i < number_class; i++)
	{
		rect_class[i].setPosition(position_first_rect_class + sf::Vector2f(position_between_rect_class*counter.x, counter.y * 100)+ position_view_player);
		counter.x++;
		if (counter.x == 3)
		{
			counter.x = 0;
			counter.y++;
		}
	}
}

void ClassMenu_interface::CreateRectangleInformation(sf::Vector2f mouse_position)
{
	if(rect_class[ClassFire].getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "Class Fire Mage";
			sf::String string2 = "Fire mages have a powerful set of skills that allow the user to deal a great amount of damage overtime by igniting his targets. This is a pure damage class.";
			sf::String string4 = "Click on the class image to choose it!";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listIfCentered.push_back(true);
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string4);
		}
		else
		{
			sf::String string1 = "Classe Mage de Feu";
			sf::String string2 = "Les mages de feu ont un puissant ensemble de sorts qui permet des dégâts rapides ou bien à long terme par l'embrasement . Cette classe est dédiée aux dégâts.";
			sf::String string4 = "Cliquer sur l'image du mage pour choisir cette classe!";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listIfCentered.push_back(true);
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string4);
		}

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
	else if (rect_class[ClassWater].getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "Class Water Mage";
			sf::String string2 = "Water mages excel at controlling their targets while healing their allies. This is a support class.";
			sf::String string4 = "Click on the class image to choose it!";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listIfCentered.push_back(true);
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string4);
		}
		else
		{
			sf::String string1 = "Classe Mage d'Eau";
			sf::String string2 = "Les mages d'eau excellent dans le contrôle des cibles ennemies et dans la survie des joueurs alliés. Cette classe est dédiée aux soins et aux contrôles.";
			sf::String string4 = "Cliquer sur l'image du mage pour choisir cette classe!";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listIfCentered.push_back(true);
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string4);
		}

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
	else if (rect_class[ClassGrass].getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "Class Grass Mage";
			sf::String string2 = "Grass mages are flawless at absorbing damage and at increasing allies' armor. This is a tank-oriented class.";
			sf::String string4 = "Click on the class image to choose it!";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listIfCentered.push_back(true);
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string4);
		}
		else
		{
			sf::String string1 = "Class Mage d'Herbe";
			sf::String string2 = "Les mages d'herbe sont parfaits pour absorber les dégâts et améliorer la défense des joueurs alliés. Ils bénéficient aussi de plusieurs sorts de contrôle. Cette classe est dédiée à la défense et aux contrôles.";
			sf::String string4 = "Cliquer sur l'image du mage pour choisir cette classe!";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listIfCentered.push_back(true);
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string4);
		}

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
	else if (rect_class[ClassRock].getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "Class Rock Mage";
			sf::String string2 = "Rock mages excel at protecting themself to reduce damage or at avoiding it. They also focus on shields instead of maximum health. This is a tank-oriented class.";
			sf::String string4 = "Click on the class image to choose it!";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listIfCentered.push_back(true);
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string4);
		}
		else
		{
			sf::String string1 = "Classe Mage de Pierre";
			sf::String string2 = "Les mages de pierre excellent à se protéger pour réduire les dégâts ou bien à les éviter. Ils se concentrent aussi davantage sur le bouclier que sur la vie totale. Cette classe est dédiée à la défense.";
			sf::String string4 = "Cliquer sur l'image du mage pour choisir cette classe!";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listIfCentered.push_back(true);
			listString.push_back(string1);
			listString.push_back(string2);
			listString.push_back(string4);
		}

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
}

void ClassMenu_interface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];
	interface_class_menu.setTexture(texture_interface);
}
