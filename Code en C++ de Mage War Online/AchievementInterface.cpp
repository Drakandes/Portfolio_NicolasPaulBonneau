#include "stdafx.h"
#include "AchievementInterface.h"

AchievementInterface::AchievementInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font crafting interface" << std::endl;
	}

#pragma region TextureInterfaceLoading
		if (true)
		{
			sf::Texture texture_of_interface;
			texture_of_interface.loadFromFile("AchievementInterfaceV1.png");
			ListTextureInterface.push_back(texture_of_interface);
		}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("AchievementInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
#pragma endregion TextureInterfaceLoading

	CreateListStringAchievementInformation();
	string_achievement = ListObjectsSingleton::instance()->GetListStringAchiements();

	interface_achievements = GlobalFunction::CreateSpriteWithoutOrigin(position_interface, size_interface, texture_interface);

	bool alternate = true;
	int holder = 0;
	for (int i = 0; i < number_achievement; i++)
	{
		if (alternate)
		{
			position_text_achievement[i] = sf::Vector2f(position_first_text_achievement.x, position_first_text_achievement.y + 30* holder);
		}
		else
		{
			position_text_achievement[i] = sf::Vector2f(position_first_text_achievement.x + 175, position_first_text_achievement.y + 30* holder);
			holder++;
		}
		alternate = !alternate;
		text_achievement[i] = GlobalFunction::CreateTextWithNoOrigin(position_text_achievement[i], string_achievement[i], font, 20);
	}

	text_name_interface = GlobalFunction::CreateText(position_name_interface, "Achievements", font, 34);
	text_name_interface.setFillColor(sf::Color::Color(108, 129, 197));
	text_name_interface.setStyle(sf::Text::Bold);
}

AchievementInterface::~AchievementInterface()
{
}

void AchievementInterface::Draw(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	text_name_interface.setPosition(position_view_player + position_name_interface);
	interface_achievements.setPosition(position_view_player + position_interface);

	window.draw(interface_achievements);
	window.draw(text_name_interface);

	for (int i = 0; i < number_achievement; i++)
	{
		text_achievement[i].setPosition(position_text_achievement[i] + position_view_player);
		window.draw(text_achievement[i]);
	}
}

void AchievementInterface::Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	std::vector<bool> listPossible = player->GetListPossibleAchiemevents();
	std::vector<bool> listSucceeded = player->GetListSucceededAchiemevents();

	for (int i = 0; i < number_achievement; i++)
	{
		if (!listSucceeded[i])
		{
			if (listPossible[i])
			{
				text_achievement[i].setFillColor(sf::Color::White);
			}
			else
			{
				text_achievement[i].setFillColor(sf::Color::Red);
			}
		}
		else
		{
			text_achievement[i].setFillColor(sf::Color::Green);
		}
	}

	CreateRectangleInformation(mouse_position, player->GetListValueReachedAchievements(),listPossible,listSucceeded);
}

void AchievementInterface::CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	if (clock_click.getElapsedTime().asSeconds() >= 0.15)
	{
		
	}
}

void AchievementInterface::CreateRectangleInformation(sf::Vector2f mouse_position, std::vector<float> listValueReached,std::vector<bool> listPossible, std::vector<bool> listSucceeded)
{
	for (int i = 0; i < number_achievement; i++)
	{
		if (text_achievement[i].getGlobalBounds().contains(mouse_position))
		{
			std::vector<int> listLetterSize;
			std::vector<sf::String> listString;
			std::vector<bool> listIfCentered;

			sf::String string1 = listStringAchievementInformation[i];
			listLetterSize.push_back(16);
			listIfCentered.push_back(false);
			listString.push_back(string1);

			if (listSucceeded[i])
			{
				if (language == English_E)
				{
					sf::String string2 = "You succeeded!";
					listString.push_back(string2);
				}
				else
				{
					sf::String string2 = "Vous avez réussi!";
					listString.push_back(string2);
				}
				listIfCentered.push_back(false);
				listLetterSize.push_back(16);
			}
			else if (!listPossible[i])
			{
				if (language == English_E)
				{
					sf::String string2 = "You Failed!";
					listString.push_back(string2);
				}
				else
				{
					sf::String string2 = "Vous avez échoué!";
					listString.push_back(string2);
				}
				listIfCentered.push_back(false);
				listLetterSize.push_back(16);
			}
			else
			{
				if (language == English_E)
				{
					sf::String string2 = "You are at ";
					string2 = GlobalFunction::InsertNumberToString(string2, listValueReached[i], string2.getSize());
					string2.insert(string2.getSize(), " !");
					listString.push_back(string2);
				}
				else
				{
					sf::String string2 = "Vous êtes à ";
					string2 = GlobalFunction::InsertNumberToString(string2, listValueReached[i], string2.getSize());
					string2.insert(string2.getSize(), " !");
					listString.push_back(string2);
				}
				listIfCentered.push_back(false);
				listLetterSize.push_back(16);
			}
			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);

		}
	}
}

void AchievementInterface::CreateListStringAchievementInformation()
{
	if (language == English_E)
	{
		sf::String str1 = "Heal yourself for 10 000 without dying.";
		sf::String str2 = "Don't get damaged for the first 300 seconds of combat.";
		sf::String str3 = "Get out of breath 20 times without dying.";
		sf::String str4 = "Have 60 monsters displayed on your radar at the same time.";
		sf::String str5 = "Kill 100 monsters without dying.";
		sf::String str6 = "Reach the 5th map.";
		sf::String str7 = "Hit 500 monsters with a basic attack or a skill without dying.";
		sf::String str8 = "Reach level 10 without dying.";
		sf::String str9 = "Get 5 achievements.";
		sf::String str10 = "Spend 100 000 gold without dying.";
		sf::String str11 = "Level up 5 skills to level 2.";
		sf::String str12 = "Collect 75 material items without dying.";

		listStringAchievementInformation.push_back(str1);
		listStringAchievementInformation.push_back(str2);
		listStringAchievementInformation.push_back(str3);
		listStringAchievementInformation.push_back(str4);
		listStringAchievementInformation.push_back(str5);
		listStringAchievementInformation.push_back(str6);
		listStringAchievementInformation.push_back(str7);
		listStringAchievementInformation.push_back(str8);
		listStringAchievementInformation.push_back(str9);
		listStringAchievementInformation.push_back(str10);
		listStringAchievementInformation.push_back(str11);
		listStringAchievementInformation.push_back(str12);
	}
	else
	{
		sf::String str1 = "Se soigner de 10 000 points de vie sans mourir.";
		sf::String str2 = "Ne pas se faire endommager pendant les 300 premières sencondes en combat.";
		sf::String str3 = "Tomber hors de souffle 20 fois sans mourir.";
		sf::String str4 = "Avoir 60 monstres affichés sur votre radar em même temps.";
		sf::String str5 = "Tuer 100 monstres sans mourir.";
		sf::String str6 = "Atteindre la 5e carte.";
		sf::String str7 = "Toucher 500 monstres avec une attaque de base ou un sort sans mourir.";
		sf::String str8 = "Atteindre le niveau 10 sans mourir.";
		sf::String str9 = "Réussir 5 accomplissements.";
		sf::String str10 = "Utiliser 100 000  pièces d'or sans mourir.";
		sf::String str11 = "Avoir 5 sorts au niveau 2.";
		sf::String str12 = "Collecter 75 objets sans mourir.";

		listStringAchievementInformation.push_back(str1);
		listStringAchievementInformation.push_back(str2);
		listStringAchievementInformation.push_back(str3);
		listStringAchievementInformation.push_back(str4);
		listStringAchievementInformation.push_back(str5);
		listStringAchievementInformation.push_back(str6);
		listStringAchievementInformation.push_back(str7);
		listStringAchievementInformation.push_back(str8);
		listStringAchievementInformation.push_back(str9);
		listStringAchievementInformation.push_back(str10);
		listStringAchievementInformation.push_back(str11);
		listStringAchievementInformation.push_back(str12);
	}
}

void AchievementInterface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];
	interface_achievements.setTexture(texture_interface);
}