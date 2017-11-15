#include "stdafx.h"
#include "VendorInterface.h"

VendorInterface::VendorInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font crafting interface" << std::endl;
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("VendorInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("VendorInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
#pragma endregion TextureInterfaceLoading

	interface_vendor = GlobalFunction::CreateSpriteWithoutOrigin(position_interface, size_interface, texture_interface);

	text_name_interface = GlobalFunction::CreateText(position_name_interface, "Shop", font, 36);
	text_name_interface.setFillColor(sf::Color::Color(108, 129, 197));
	text_name_interface.setStyle(sf::Text::Bold);
	text_ilvl = GlobalFunction::CreateTextWithNoOrigin(position_text_ilvl, string_ilvl, font, 20);
	text_ilvl.setFillColor(sf::Color::Color(108, 129, 197));

	text_hat_cost = GlobalFunction::CreateTextWithNoOrigin(position_text_hat_cost, string_hat_cost, font, 20);
	text_hat_cost.setFillColor(sf::Color::Color(123, 141, 203));
	text_hat_cost.setStyle(sf::Text::Bold);
	rect_hat = GlobalFunction::CreateRectangle(size_hat, position_hat);
	rect_buy_hat = GlobalFunction::CreateRectangle(size_buy_hat, position_buy_hat);
	             
	rect_health_potion = GlobalFunction::CreateRectangle(size_health_potion, position_health_potion);
	rect_buy_health_potion = GlobalFunction::CreateRectangle(size_buy_health_potion, position_buy_health_potion);
	text_hp_pot_cost = GlobalFunction::CreateTextWithNoOrigin(position_text_hp_pot_cost, string_hp_pot_cost, font, 20);
	text_hp_pot_cost.setFillColor(sf::Color::Color(123, 141, 203));
	text_hp_pot_cost.setStyle(sf::Text::Bold);

	sprite_decrease_ilvl_hat = GlobalFunction::CreateCircleWithOrigin(position_decrease_ilvl_hat, rayon_increase_ilvl);
	sprite_increase_ilvl_hat = GlobalFunction::CreateCircleWithOrigin(position_increase_ilvl_hat, rayon_increase_ilvl);

	listAllSkill = ListObjectsSingleton::instance()->GetListSkill();
}

VendorInterface::~VendorInterface()
{
}

void VendorInterface::Draw(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	text_name_interface.setPosition(position_view_player + position_name_interface);
	interface_vendor.setPosition(position_view_player + position_interface);
	text_ilvl.setPosition(position_view_player + position_text_ilvl);
	text_hat_cost.setPosition(position_view_player + position_text_hat_cost);
	sprite_decrease_ilvl_hat.setPosition(position_view_player + position_decrease_ilvl_hat);
	sprite_increase_ilvl_hat.setPosition(position_view_player + position_increase_ilvl_hat);
	rect_hat.setPosition(position_view_player + position_hat);
	rect_buy_hat.setPosition(position_view_player + position_buy_hat);
	rect_health_potion.setPosition(position_view_player + position_health_potion);
	rect_buy_health_potion.setPosition(position_view_player + position_buy_health_potion);
	text_hp_pot_cost.setPosition(position_view_player + position_text_hp_pot_cost);

	window.draw(interface_vendor);
	window.draw(text_name_interface);
	window.draw(text_ilvl);
	window.draw(text_hat_cost);
	window.draw(text_hp_pot_cost);
}

void VendorInterface::Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	int player_money = player->GetMoney();

	string_ilvl.clear();
	string_ilvl = "ilvl : ";
	string_ilvl = GlobalFunction::InsertNumberToString(string_ilvl, hat_ilvl, string_ilvl.getSize());
	text_ilvl.setString(string_ilvl);
	text_ilvl.setOrigin(sf::Vector2f(text_ilvl.getGlobalBounds().width / 2, text_ilvl.getGlobalBounds().height / 2));

	hat_cost = hat_ilvl*(hat_cost_per_ilvl/5 + hat_cost_per_ilvl/5*4 * hat_ilvl/100);
	string_hat_cost.clear();
	string_hat_cost = GlobalFunction::InsertNumberToString(string_hat_cost, hat_cost, string_hat_cost.getSize());
	text_hat_cost.setString(string_hat_cost);
	text_hat_cost.setOrigin(sf::Vector2f(text_hat_cost.getGlobalBounds().width / 2, text_hat_cost.getGlobalBounds().height / 2));

	hp_pot_cost = player->GetPlayerLevel()*base_hp_pot_cost;
	string_hp_pot_cost.clear();
	string_hp_pot_cost = GlobalFunction::InsertNumberToString(string_hp_pot_cost, hp_pot_cost, string_hp_pot_cost.getSize());
	text_hp_pot_cost.setString(string_hp_pot_cost);
	text_hp_pot_cost.setOrigin(sf::Vector2f(text_hp_pot_cost.getGlobalBounds().width / 2, text_hp_pot_cost.getGlobalBounds().height / 2));

	CreateRectangleInformation(mouse_position, player_money);
	CheckPlayerAction(player, mouse_position,player_money);
}

void VendorInterface::CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position,int player_money)
{
	if (clock_click.getElapsedTime().asSeconds() >= 0.15)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (sprite_increase_ilvl_hat.getGlobalBounds().contains(mouse_position))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
					hat_ilvl += 10;
				}
				else
				{
					hat_ilvl++;
				}
				if (hat_ilvl > 100)
				{
					hat_ilvl = 100;
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav",45,false);
				clock_click.restart();
			}
			else if (sprite_decrease_ilvl_hat.getGlobalBounds().contains(mouse_position))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
					hat_ilvl -= 10;
				}
				else
				{
					hat_ilvl--;
				}
				if (hat_ilvl <= 0)
				{
					hat_ilvl = 1;
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				clock_click.restart();
			}
			else if (rect_buy_hat.getGlobalBounds().contains(mouse_position))
			{
				if (player_money >= hat_cost)
				{
					player_money -= hat_cost;
					GivePlayerNewHat(player);

				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				clock_click.restart();
			}
			else if (rect_buy_health_potion.getGlobalBounds().contains(mouse_position))
			{
				if (player_money >= hp_pot_cost)
				{
					player_money -= hp_pot_cost;
					player->GivePlayerItem(I_Miscellaneous,IM_HealthPotion,1);
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				clock_click.restart();
			}
		}
	}
	player->NewPlayerMoney(player_money);
}

void VendorInterface::CreateRectangleInformation(sf::Vector2f mouse_position,int player_money) 
{
	if (rect_hat.getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "Wizard Hat";
			sf::String string2 = "Increase the bonus to damage, maximum health or armor from levels. Also increase the level of few skills, based on the item_lvl.";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listString.push_back(string1);
			listString.push_back(string2);
		}
		else
		{
			sf::String string1 = "Chapeau de Magicien";
			sf::String string2 = "Augmente le bonus aux dégâts, à l'armure ou à la vie totale par niveau. Augmente aussi le niveau de certains sorts, basé sur le niveau du chapeau.";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listString.push_back(string1);
			listString.push_back(string2);
		}

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
	else if (rect_buy_hat.getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "Buy 1 Wizard Hat for ";
			string1 = GlobalFunction::InsertNumberToString(string1, hat_cost, string1.getSize());
			string1.insert(string1.getSize(), sf::String(" gold."));
			sf::String string2 = "You currently have ";
			string2 = GlobalFunction::InsertNumberToString(string2, player_money, string2.getSize());
			string2.insert(string2.getSize(), sf::String(" gold."));
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listString.push_back(string1);
			listString.push_back(string2);
		}
		else
		{
			sf::String string1 = "Acheter un chapeau de magicien pour ";
			string1 = GlobalFunction::InsertNumberToString(string1, hat_cost, string1.getSize());
			string1.insert(string1.getSize(), sf::String(" pièces d'or."));
			sf::String string2 = "Vous avez présentement ";
			string2 = GlobalFunction::InsertNumberToString(string2, player_money, string2.getSize());
			string2.insert(string2.getSize(), sf::String(" pièces d'or."));
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listString.push_back(string1);
			listString.push_back(string2);
		}

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
	else if (rect_health_potion.getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "Health Potion";
			sf::String string2 = "Regenerate 40% of your maximum health over 10 seconds. Is only 25% effective when in combat. The price is based on your level.";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listString.push_back(string1);
			listString.push_back(string2);
		}
		else
		{
			sf::String string1 = "Potion de Vie";
			sf::String string2 = "Regénère 40% de votre vie totale en 10 secondes. Seulement 25% d'efficacité si vous êtes en combat. Le prix est basé sur votre niveau.";
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listString.push_back(string1);
			listString.push_back(string2);
		}

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
	else if (rect_buy_health_potion.getGlobalBounds().contains(mouse_position))
	{
		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		if (language == English_E)
		{
			sf::String string1 = "Buy 1 health potion for ";
			string1 = GlobalFunction::InsertNumberToString(string1, hp_pot_cost, string1.getSize());
			string1.insert(string1.getSize(), sf::String(" gold."));
			sf::String string2 = "You currently have ";
			string2 = GlobalFunction::InsertNumberToString(string2, player_money, string2.getSize());
			string2.insert(string2.getSize(), sf::String(" gold."));
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listString.push_back(string1);
			listString.push_back(string2);
		}
		else
		{
			sf::String string1 = "Acheter une potion de vie pour ";
			string1 = GlobalFunction::InsertNumberToString(string1, hp_pot_cost, string1.getSize());
			string1.insert(string1.getSize(), sf::String(" pièces d'or."));
			sf::String string2 = "Vous avez présentement ";
			string2 = GlobalFunction::InsertNumberToString(string2, player_money, string2.getSize());
			string2.insert(string2.getSize(), sf::String(" pièces d'or."));
			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);
			listString.push_back(string1);
			listString.push_back(string2);
		}

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
}

void VendorInterface::GivePlayerNewHat(std::shared_ptr<Player> &player)
{
	std::vector<int> listTypeBonus;
	std::vector<float> listBonus;
	std::vector<sf::Vector2f> listRangeBonus;
	std::vector<int> listSkillBonus;
	std::vector<int> listSkillLevelBonus;
	std::vector<sf::String> listStringSkillBonus;

	int type_hat = GlobalFunction::getRandomRange(1, 3);
	int bonus_with_ilvl = 50 + hat_ilvl * 250 / 100;

	int number_skill_bonus = 1;
	int holder = hat_ilvl;
	while (holder > 0)
	{
		if (holder - 25 >= 0)
		{
			number_skill_bonus++;
		}
		holder -= 25;
	}
	if (number_skill_bonus > 4)
	{
		number_skill_bonus = 4;
	}

	int rarity_item = GetRarityItem();

#pragma region RarityGestion
	bonus_with_ilvl += 15 * rarity_item;

	if (rarity_item >= Rare_E)
	{
		number_skill_bonus++;
	}
	if (rarity_item == Legendary_E)
	{
		number_skill_bonus++;
	}
#pragma endregion RarityGestion

#pragma region OffensiveHat
	if (type_hat == OffensiveHat_E)
	{
		if (hat_ilvl <= 33)
		{
			if (GlobalFunction::getRandomRange(1, 1000) <= 499)
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(DamagePerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			else
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(AttackSpeedPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
		}
		else if (hat_ilvl <= 66)
		{
			if (GlobalFunction::getRandomRange(1, 1000) <= 499)
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(DamagePerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			else
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(AttackSpeedPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}

			float min_bonus = bonus_with_ilvl*0.15 - bonus_with_ilvl*0.15*0.1;
			float max_bonus = bonus_with_ilvl*0.15 + bonus_with_ilvl*0.15*0.1;
			float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
			listTypeBonus.push_back(PoolAllBonus[GlobalFunction::getRandomRange(1, PoolAllBonus.size()) - 1]);
			listBonus.push_back(bonus);
			listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
		}
		else
		{
			if (GlobalFunction::getRandomRange(1, 1000) <= 499)
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(DamagePerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			else
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(AttackSpeedPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			for (int i = 0; i < 2; i++)
			{
				float min_bonus = bonus_with_ilvl*0.15 - bonus_with_ilvl*0.15*0.1;
				float max_bonus = bonus_with_ilvl*0.15 + bonus_with_ilvl*0.15*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(PoolAllBonus[GlobalFunction::getRandomRange(1, PoolAllBonus.size()) - 1]);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
		}
	}
#pragma endregion OffensiveHat

#pragma region DefensiveHat
	else if (type_hat == DefensiveHat_E)
	{
		if (hat_ilvl <= 33)
		{
			if (GlobalFunction::getRandomRange(1, 1000) <= 499)
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(HealthPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			else
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(ArmorPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
		}
		else if (hat_ilvl <= 66)
		{
			if (GlobalFunction::getRandomRange(1, 1000) <= 499)
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(HealthPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			else
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(ArmorPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}

			float min_bonus = bonus_with_ilvl*0.15 - bonus_with_ilvl*0.15*0.1;
			float max_bonus = bonus_with_ilvl*0.15 + bonus_with_ilvl*0.15*0.1;
			float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
			listTypeBonus.push_back(PoolAllBonus[GlobalFunction::getRandomRange(1, PoolAllBonus.size()) - 1]);
			listBonus.push_back(bonus);
			listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));

		}
		else
		{
			if (GlobalFunction::getRandomRange(1, 1000) <= 499)
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(HealthPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			else
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(ArmorPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			for (int i = 0; i < 2; i++)
			{
				float min_bonus = bonus_with_ilvl*0.15 - bonus_with_ilvl*0.15*0.1;
				float max_bonus = bonus_with_ilvl*0.15 + bonus_with_ilvl*0.15*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(PoolAllBonus[GlobalFunction::getRandomRange(1, PoolAllBonus.size()) - 1]);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
		}
	}
#pragma endregion DefensiveHat

#pragma region UtilityHat
	else if (type_hat == UtilityHat_E)
	{
		if (hat_ilvl <= 33)
		{
			if (GlobalFunction::getRandomRange(1, 1000) <= 499)
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(SpeedPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			else
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(CooldownRedutionPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
		}
		else if (hat_ilvl <= 66)
		{
			if (GlobalFunction::getRandomRange(1, 1000) <= 499)
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(SpeedPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			else
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(CooldownRedutionPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}

			float min_bonus = bonus_with_ilvl*0.15 - bonus_with_ilvl*0.15*0.1;
			float max_bonus = bonus_with_ilvl*0.15 + bonus_with_ilvl*0.15*0.1;
			float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
			listTypeBonus.push_back(PoolAllBonus[GlobalFunction::getRandomRange(1, PoolAllBonus.size()) - 1]);
			listBonus.push_back(bonus);
			listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));

		}
		else
		{
			if (GlobalFunction::getRandomRange(1, 1000) <= 499)
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(SpeedPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			else
			{
				float min_bonus = bonus_with_ilvl*0.75 - bonus_with_ilvl*0.75*0.1;
				float max_bonus = bonus_with_ilvl*0.75 + bonus_with_ilvl*0.75*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(CooldownRedutionPerLevel);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
			for (int i = 0; i < 2; i++)
			{
				float min_bonus = bonus_with_ilvl*0.15 - bonus_with_ilvl*0.15*0.1;
				float max_bonus = bonus_with_ilvl*0.15 + bonus_with_ilvl*0.15*0.1;
				float bonus = GlobalFunction::getRandomRangeIfFloat(min_bonus * 100, max_bonus * 100) / 100;
				listTypeBonus.push_back(PoolAllBonus[GlobalFunction::getRandomRange(1, PoolAllBonus.size()) - 1]);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(sf::Vector2f(min_bonus, max_bonus));
			}
		}
	}
#pragma endregion UtilityHat

#pragma region FireHat
	if (type_hat - 1 == ClassFire)
	{
		if (number_skill_bonus == 4)
		{
			for (int i = 0; i < 2; i++)
			{
				listSkillBonus.push_back(PoolFireSkill[GlobalFunction::getRandomRange(1, PoolFireSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}

			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(GlobalFunction::getRandomRange(1, NUMBERSKILL) - 1);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
		else if(number_skill_bonus == 3)
		{
			for (int i = 0; i < 2; i++)
			{
				listSkillBonus.push_back(PoolFireSkill[GlobalFunction::getRandomRange(1, PoolFireSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}

			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(GlobalFunction::getRandomRange(1, NUMBERSKILL) - 1);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
		else
		{
			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(PoolFireSkill[GlobalFunction::getRandomRange(1, PoolFireSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
	}
#pragma endregion FireHat

#pragma region GrassHat
	else if (type_hat - 1 == ClassGrass)
	{
		if (number_skill_bonus == 4)
		{
			for (int i = 0; i < 2; i++)
			{
				listSkillBonus.push_back(PoolGrassSkill[GlobalFunction::getRandomRange(1, PoolGrassSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}

			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(GlobalFunction::getRandomRange(1, NUMBERSKILL) - 1);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
		else if (number_skill_bonus == 3)
		{
			for (int i = 0; i < 2; i++)
			{
				listSkillBonus.push_back(PoolGrassSkill[GlobalFunction::getRandomRange(1, PoolGrassSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}

			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(GlobalFunction::getRandomRange(1, NUMBERSKILL) - 1);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
		else
		{
			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(PoolGrassSkill[GlobalFunction::getRandomRange(1, PoolGrassSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
	}
#pragma endregion GrassHat

#pragma region WaterHat
	else if (type_hat - 1 == ClassWater)
	{
		if (number_skill_bonus == 4)
		{
			for (int i = 0; i < 2; i++)
			{
				listSkillBonus.push_back(PoolWaterSkill[GlobalFunction::getRandomRange(1, PoolWaterSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}

			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(GlobalFunction::getRandomRange(1, NUMBERSKILL) - 1);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
		else if (number_skill_bonus == 3)
		{
			for (int i = 0; i < 2; i++)
			{
				listSkillBonus.push_back(PoolWaterSkill[GlobalFunction::getRandomRange(1, PoolWaterSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}

			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(GlobalFunction::getRandomRange(1, NUMBERSKILL) - 1);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
		else
		{
			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(PoolWaterSkill[GlobalFunction::getRandomRange(1, PoolWaterSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
	}
#pragma endregion WaterHat

#pragma region RockHat
	else if (type_hat - 1 == ClassRock)
	{
		if (number_skill_bonus == 4)
		{
			for (int i = 0; i < 2; i++)
			{
				listSkillBonus.push_back(PoolRockSkill[GlobalFunction::getRandomRange(1, PoolRockSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}

			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(GlobalFunction::getRandomRange(1, NUMBERSKILL) - 1);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
		else if (number_skill_bonus == 3)
		{
			for (int i = 0; i < 2; i++)
			{
				listSkillBonus.push_back(PoolRockSkill[GlobalFunction::getRandomRange(1, PoolRockSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}

			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(GlobalFunction::getRandomRange(1, NUMBERSKILL) - 1);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
		else
		{
			while (number_skill_bonus > 0)
			{
				listSkillBonus.push_back(PoolRockSkill[GlobalFunction::getRandomRange(1, PoolRockSkill.size()) - 1]);
				if (GlobalFunction::getRandomRange(1, 1000) <= 499)
				{
					listSkillLevelBonus.push_back(number_skill_bonus);
				}
				else
				{
					listSkillLevelBonus.push_back(number_skill_bonus - 1 > 0 ? number_skill_bonus - 1 : 1);
				}
				number_skill_bonus--;
			}
		}
	}
#pragma endregion RockHat


	for (int i = 0; i < listSkillBonus.size(); i++)
	{
		sf::String string;
		string = ("+");
		string = GlobalFunction::InsertNumberToString(string, listSkillLevelBonus[i], string.getSize());
		if (language == English_E)
		{
			string.insert(string.getSize(), sf::String(" to "));
		}
		else
		{
			string.insert(string.getSize(), sf::String(" à "));
		}
		listAllSkill[listSkillBonus[i]]->ChangeSkillLevel(0, 0, ClassFire, NoRune_E);
		string.insert(string.getSize(), listAllSkill[listSkillBonus[i]]->GetStringSkillInformation(0));
		listStringSkillBonus.push_back(string);
	}

	std::shared_ptr<E_WizardHat> hat = std::shared_ptr<E_WizardHat>(new E_WizardHat(language,ListObjectsSingleton::instance()->GetCurrentSave()));
	hat->Init(hat_ilvl,listTypeBonus,listBonus,listRangeBonus,listSkillBonus,listSkillLevelBonus, listStringSkillBonus,type_hat,ListObjectsSingleton::instance()->GetNewIDEquipment(),rarity_item);
	player->GiveHat(hat);
	hat.reset();
}

int VendorInterface::GetRarityItem()
{
	int item_level = hat_ilvl;
	float percent_item_level_max = static_cast<float>(item_level - 1) / 100;
	float percent_item_level_min = static_cast<float>(101 - item_level) / 100;
	float modifier = 100000;
	float random_number = GlobalFunction::getRandomRange(1, modifier);
	float percent_passed = 0;

	for (int i = 0; i < RarityItemRange.size(); i++)
	{
		float chance = (RarityItemRange[i].x*percent_item_level_min + RarityItemRange[i].y*percent_item_level_max) / 100 * modifier;
		if (percent_passed + chance > random_number)
		{
			return i;
		}
		else
		{
			percent_passed += chance;
		}
	}

	return Legendary_E;
}

void VendorInterface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];
	interface_vendor.setTexture(texture_interface);
}
