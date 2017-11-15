#include "stdafx.h"
#include "TalentTreeInterface.h"

TalentTreeInterface::TalentTreeInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font  class menu interface" << std::endl;
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("TalentInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("TalentInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
#pragma endregion TextureInterfaceLoading

	listAllTalents = ListObjectsSingleton::instance()->GetListTalent();

	interface_talent = GlobalFunction::CreateSpriteWithoutOrigin(position_interface, size_interface, texture_interface);
	if (language == English_E)
	{
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Talent Tree", font, 36);
		text_reset = GlobalFunction::CreateText(position_text_reset, sf::String("Reset Talents"), font, 20);
	}
	else
	{
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Arbre de Talents", font, 34);
		text_reset = GlobalFunction::CreateText(position_text_reset, sf::String("Réinitialiser"), font, 20);
	}
	text_name_interface.setFillColor(sf::Color::Color(108, 129, 197));

	text_points_left = GlobalFunction::CreateText(position_text_points_left, sf::String("IND"), font, 28);

	float counter = 0;
	for (int i = 0; i < number_talent; i++)
	{
		if (i <= 2)
		{
			position_rect_talent[i] = sf::Vector2f{ position_first_rect_talent.x + 182 * i,position_first_rect_talent.y };
			rect_talent[i] = GlobalFunction::CreateRectangle(size_big_rect_talent, position_rect_talent[i]);
		}
		else if (i <= 8)
		{
			if (i % 2)
			{
				position_rect_talent[i] = sf::Vector2f{ position_first_rect_talent.x - 34 + 182 * std::ceil((counter / 3 - 1)),position_first_rect_talent.y + 78 };
				rect_talent[i] = GlobalFunction::CreateRectangle(size_small_rect_talent, position_rect_talent[i]);
			}
			else
			{
				position_rect_talent[i] = sf::Vector2f{ position_first_rect_talent.x + 45 + 182 * std::ceil(((counter-1) / 3 - 1)),position_first_rect_talent.y + 78 };
				rect_talent[i] = GlobalFunction::CreateRectangle(size_small_rect_talent, position_rect_talent[i]);
			}
		}
		else if (i <= 11)
		{
			position_rect_talent[i] = sf::Vector2f{ position_first_rect_talent.x + 2+ 182 * (counter - 9),position_first_rect_talent.y + 146 };
			rect_talent[i] = GlobalFunction::CreateRectangle(size_medium_rect_talent, position_rect_talent[i]);
		}
		else if (i <= 17)
		{
			if ((i - 9) % 2)
			{
				position_rect_talent[i] = sf::Vector2f{ position_first_rect_talent.x - 32 + 182 * std::ceil(((counter - 9) / 3 - 1)),position_first_rect_talent.y + 220 };
				rect_talent[i] = GlobalFunction::CreateRectangle(size_small_rect_talent, position_rect_talent[i]);
			}
			else
			{
				position_rect_talent[i] = sf::Vector2f{ position_first_rect_talent.x + 47 + 182 * std::ceil(((counter - 10) / 3 - 1)),position_first_rect_talent.y + 220 };
				rect_talent[i] = GlobalFunction::CreateRectangle(size_small_rect_talent, position_rect_talent[i]);
			}
		}
		else if (i <= 20)
		{
			position_rect_talent[i] = sf::Vector2f{ position_first_rect_talent.x + 2 + 182 * (counter - 18),position_first_rect_talent.y + 288 };
			rect_talent[i] = GlobalFunction::CreateRectangle(size_medium_rect_talent, position_rect_talent[i]);
		}
		else if (i <= 26)
		{
			if ((i - 18) % 2)
			{
				position_rect_talent[i] = sf::Vector2f{ position_first_rect_talent.x - 32 + 182 * std::ceil(((counter - 18) / 3 - 1)),position_first_rect_talent.y + 362 };
				rect_talent[i] = GlobalFunction::CreateRectangle(size_small_rect_talent, position_rect_talent[i]);
			}
			else
			{
				position_rect_talent[i] = sf::Vector2f{ position_first_rect_talent.x + 47 + 182 * std::ceil(((counter - 19) / 3 - 1)),position_first_rect_talent.y + 362 };
				rect_talent[i] = GlobalFunction::CreateRectangle(size_small_rect_talent, position_rect_talent[i]);
			}
		}
		else
		{
			position_rect_talent[i] = sf::Vector2f{ position_first_rect_talent.x + 2 + 182 * (counter - 27),position_first_rect_talent.y + 430 };
			rect_talent[i] = GlobalFunction::CreateRectangle(size_medium_rect_talent, position_rect_talent[i]);
		}

		if (i >= 3)
		{
			sf::String holder = "IND";
			position_text_talent[i] = position_rect_talent[i] + sf::Vector2f(rect_talent[i].getSize().x/2, rect_talent[i].getSize().y + 10);
			text_talent[i] = GlobalFunction::CreateText(position_text_talent[i], holder, font, 12);
		}

		rect_talent[i].setFillColor(sf::Color::Color(0, 0, 0, 100));
		array_rect_locked[i] = false;
		counter++;
	}
}

TalentTreeInterface::~TalentTreeInterface()
{

}

void TalentTreeInterface::Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	CanLevelTalent(player->GetPlayerArrayTalentPointsUsed());
	UpdateTextTalent(player->GetPlayerArrayTalentLevel(),player->GetPlayerArrayTalentIncreasement());
	CreateRectangleInformation(mouse_position);
	CheckPlayerAction(player, mouse_position);
}

void TalentTreeInterface::CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	std::vector<int> player_talent_level = player->GetPlayerArrayTalentLevel();
	std::vector<int> player_talent_points_used = player->GetPlayerArrayTalentPointsUsed();
	int player_maximum_talent_points = (player->GetPlayerLevel()-1)*2;

	sf::String str = "";
	str = GlobalFunction::InsertNumberToString(str, player_talent_points_used[AllPointsUsed_Self], str.getSize());
	str.insert(str.getSize(), sf::String(" / "));
	str = GlobalFunction::InsertNumberToString(str, player_maximum_talent_points, str.getSize());
	text_points_left.setString(str);

	if (text_reset.getGlobalBounds().contains(mouse_position))
	{
		text_reset.setFillColor(sf::Color::Color(108, 129, 197));
	}
	else
	{
		text_reset.setFillColor(sf::Color::Color(255, 255, 255));
	}

	if (player_maximum_talent_points > 0)
	{
		if (clock_click.getElapsedTime().asSeconds() >= 0.2)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (int i = 3; i < number_talent; i++)
				{
					int talent = i - 3;
					if (rect_talent[i].getGlobalBounds().contains(mouse_position) && player_talent_level[talent] < listAllTalents[talent]->GetMaxLevelTalent() && player_talent_points_used[AllPointsUsed_Self] < player_maximum_talent_points )
					{
						if (!array_rect_locked[i])
						{
							player_talent_level[talent]++;
							player_talent_points_used[listAllTalents[talent]->GetTypeTreeTalent()]++;
							player_talent_points_used[AllPointsUsed_Self]++;
							SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
							clock_click.restart();
						}
					}
				}

				if (text_reset.getGlobalBounds().contains(mouse_position))
				{
					for (int i = 3; i < number_talent; i++)
					{
						player_talent_level[i - 3] = 0;
					}
					player_talent_points_used[DamageTree_Self] = 0;
					player_talent_points_used[DefenseTree_Self] = 0;
					player_talent_points_used[UtilityTree_Self] = 0;
					player_talent_points_used[AllPointsUsed_Self] = 0;
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
					clock_click.restart();
				}
			}
		}
	}

	player->NewPlayerArrayTalentLevel(player_talent_level);
	player->NewPlayerArrayTalentPointsUsed(player_talent_points_used);
}

void TalentTreeInterface::Draw(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	interface_talent.setPosition(position_view_player + position_interface);
	text_name_interface.setPosition(position_view_player + position_name_interface);
	text_points_left.setPosition(position_text_points_left + position_view_player);
	text_reset.setPosition(position_text_reset + position_view_player);

	window.draw(interface_talent);
	window.draw(text_name_interface);
	window.draw(text_points_left);
	window.draw(text_reset);

	for (int i = 3; i < number_talent; i++)
	{
		text_talent[i].setPosition(position_text_talent[i] + position_view_player);
		rect_talent[i].setPosition(position_rect_talent[i] + position_view_player);

		if (array_rect_locked[i])
		{
			window.draw(text_talent[i]);
			window.draw(rect_talent[i]);
		}
		else
		{
			window.draw(text_talent[i]);
		}
	}
}

void TalentTreeInterface::CreateRectangleInformation(sf::Vector2f mouse_position)
{
	for (int i = 0; i < number_talent; i++)
	{
		if (rect_talent[i].getGlobalBounds().contains(mouse_position))
		{
			if (i == 0)
			{
				std::vector<int> listLetterSize;
				std::vector<sf::String> listString;
				std::vector<bool> listIfCentered;

				if (language == English_E)
				{
					sf::String string1 = "Damage Oriented Tree";
					listLetterSize.push_back(20);
					listIfCentered.push_back(true);
					listString.push_back(string1);
				}
				else
				{
					sf::String string1 = "Arbre concentré sur les dégâts";
					listLetterSize.push_back(20);
					listIfCentered.push_back(true);
					listString.push_back(string1);
				}

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
			else if (i == 1)
			{
				std::vector<int> listLetterSize;
				std::vector<sf::String> listString;
				std::vector<bool> listIfCentered;

				if (language == English_E)
				{
					sf::String string1 = "Defense Oriented Tree";
					listLetterSize.push_back(20);
					listIfCentered.push_back(true);
					listString.push_back(string1);
				}
				else
				{
					sf::String string1 = "Arbre concentré sur la défense";
					listLetterSize.push_back(20);
					listIfCentered.push_back(true);
					listString.push_back(string1);
				}


				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
			else if (i == 2)
			{
				std::vector<int> listLetterSize;
				std::vector<sf::String> listString;
				std::vector<bool> listIfCentered;

				if (language == English_E)
				{
					sf::String string1 = "Utility Oriented Tree";
					listLetterSize.push_back(20);
					listIfCentered.push_back(true);
					listString.push_back(string1);
				}
				else
				{
					sf::String string1 = "Arbre concentré sur l'utilité";
					listLetterSize.push_back(20);
					listIfCentered.push_back(true);
					listString.push_back(string1);
				}

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
			else
			{
				std::vector<int> listLetterSize;
				std::vector<sf::String> listString;
				std::vector<bool> listIfCentered;

				sf::String string1 = listAllTalents[i -3]->GetStringSkillInformation(0);
				sf::String string2 = listAllTalents[i -3]->GetStringSkillInformation(1);
				listLetterSize.push_back(16);
				listLetterSize.push_back(16);
				listIfCentered.push_back(true);
				listIfCentered.push_back(false);
				listString.push_back(string1);
				listString.push_back(string2);

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
		}
	}
}

void TalentTreeInterface::CanLevelTalent(std::vector<int> player_talent_points_used)
{
	for (int i = 3; i < number_talent; i++)
	{
		int talent = i - 3;
		int type_tree_talent = listAllTalents[talent]->GetTypeTreeTalent();
		int tier_talent = listAllTalents[talent]->GetTierTalent();

		if (type_tree_talent == DamageTree_Self)
		{
			if (tier_talent == 2)
			{
				if (player_talent_points_used[DamageTree_Self] >= 5 || player_talent_points_used[DefenseTree_Self] >= 16 || player_talent_points_used[UtilityTree_Self] >= 16)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 3)
			{
				if (player_talent_points_used[DamageTree_Self] >= 8 || player_talent_points_used[DefenseTree_Self] >= 21 || player_talent_points_used[UtilityTree_Self] >= 21)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 4)
			{
				if (player_talent_points_used[DamageTree_Self] >= 13 || player_talent_points_used[DefenseTree_Self] >= 24 || player_talent_points_used[UtilityTree_Self] >= 24)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 5)
			{
				if (player_talent_points_used[DamageTree_Self] >= 16)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 6)
			{
				if (player_talent_points_used[DamageTree_Self] >= 21)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
		}

		if (type_tree_talent == DefenseTree_Self)
		{
			if (tier_talent == 2)
			{
				if (player_talent_points_used[DefenseTree_Self] >= 5 || player_talent_points_used[DamageTree_Self] >= 16 || player_talent_points_used[UtilityTree_Self] >= 16)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 3)
			{
				if (player_talent_points_used[DefenseTree_Self] >= 8 || player_talent_points_used[DamageTree_Self] >= 21 || player_talent_points_used[UtilityTree_Self] >= 21)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 4)
			{
				if (player_talent_points_used[DefenseTree_Self] >= 13 || player_talent_points_used[DamageTree_Self] >= 24 || player_talent_points_used[UtilityTree_Self] >= 24)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 5)
			{
				if (player_talent_points_used[DefenseTree_Self] >= 16)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 6)
			{
				if (player_talent_points_used[DefenseTree_Self] >= 21)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
		}

		if (type_tree_talent == UtilityTree_Self)
		{
			if (tier_talent == 2)
			{
				if (player_talent_points_used[UtilityTree_Self] >= 5 || player_talent_points_used[DamageTree_Self] >= 16 || player_talent_points_used[DefenseTree_Self] >= 16)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 3)
			{
				if (player_talent_points_used[UtilityTree_Self] >= 8 || player_talent_points_used[DamageTree_Self] >= 21 || player_talent_points_used[DefenseTree_Self] >= 21)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 4)
			{
				if (player_talent_points_used[UtilityTree_Self] >= 13 || player_talent_points_used[DamageTree_Self] >= 24 || player_talent_points_used[DefenseTree_Self] >= 24)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 5)
			{
				if (player_talent_points_used[UtilityTree_Self] >= 16)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
			else if (tier_talent == 6)
			{
				if (player_talent_points_used[UtilityTree_Self] >= 21)
				{
					array_rect_locked[i] = false;
				}
				else
				{
					array_rect_locked[i] = true;
				}
			}
		}
	}
}

void TalentTreeInterface::UpdateTextTalent(std::vector<int> player_array_talent_level, std::vector<int> player_array_talent_increasement)
{
	for (int i = 3; i < number_talent; i++)
	{
		if (player_array_talent_increasement[i - 3] <= 0)
		{
			sf::String str = "";
			str = GlobalFunction::InsertNumberToString(str, player_array_talent_level[i - 3], str.getSize());
			str.insert(str.getSize(), sf::String(" / "));
			str = GlobalFunction::InsertNumberToString(str, listAllTalents[i - 3]->GetMaxLevelTalent(), str.getSize());
			text_talent[i].setString(str);
			text_talent[i].setFillColor(sf::Color::White);
		}
		else
		{
			sf::String str = "";
			str = GlobalFunction::InsertNumberToString(str, player_array_talent_level[i - 3], str.getSize());
			str.insert(str.getSize(), sf::String(" (+"));
			str = GlobalFunction::InsertNumberToString(str, player_array_talent_increasement[i - 3], str.getSize());
			str.insert(str.getSize(), sf::String(") / "));
			str = GlobalFunction::InsertNumberToString(str, listAllTalents[i - 3]->GetMaxLevelTalent(), str.getSize());
			text_talent[i].setString(str);
			text_talent[i].setFillColor(sf::Color::Color(33,156,65));
		}
	}
}

void TalentTreeInterface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];
	interface_talent.setTexture(texture_interface);
}


