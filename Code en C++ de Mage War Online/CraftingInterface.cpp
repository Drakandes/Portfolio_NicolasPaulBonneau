#include "stdafx.h"
#include "CraftingInterface.h"

CraftingInterface::CraftingInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font crafting interface" << std::endl;
	}
	
	if (!texture_equipment.loadFromFile("EquipmentIconeX2.png"))
	{
		std::cout << "Error while loading equipment texture in crafting interface" << std::endl;
	}

	if (!texture_stick.loadFromFile("Stick.png"))
	{
		std::cout << "Error while loading stick texture in crafting interface" << std::endl;
	}

	if (!texture_button_decrease_ilvl.loadFromFile("Decrease_icone.png"))
	{
		std::cout << "Error while loading deccrease button texture in crafting interface" << std::endl;
	}

	if (!texture_button_increase_ilvl.loadFromFile("Increase_icone.png"))
	{
		std::cout << "Error while loading increase button texture in crafting interface" << std::endl;
	}

	if (!texture_magical_sand.loadFromFile("MagicSandX2.png"))
	{
		std::cout << "Error while loading magical sand texture in crafting interface" << std::endl;
	}

	if (!texture_ores[0].loadFromFile("IronX2.png"))
	{
		std::cout << "Error while loading ores texture in crafting interface" << std::endl;
	}
	if (!texture_ores[1].loadFromFile("RubyX2.png"))
	{
		std::cout << "Error while loading ores texture in crafting interface" << std::endl;
	}
	if (!texture_ores[2].loadFromFile("EmeraldX2.png"))
	{
		std::cout << "Error while loading ores texture in crafting interface" << std::endl;
	}
	if (!texture_ores[3].loadFromFile("TopazX2.png"))
	{
		std::cout << "Error while loading ores texture in crafting interface" << std::endl;
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("CraftingInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("CraftingInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
#pragma endregion TextureInterfaceLoading

	interface_crafting = GlobalFunction::CreateSpriteWithoutOrigin(position_interface,size_interface, texture_interface);

	if (language == English_E)
	{
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Crafting Menu", font, 32);
	}
	else
	{
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Menu d'Artisanat", font, 32);
	}

	text_name_interface.setFillColor(sf::Color::Color(108, 129, 197));
	text_name_interface.setStyle(sf::Text::Bold);
	item_preview = GlobalFunction::CreateSprite(position_weapon,size_item_preview, texture_equipment);
	item_preview.setTextureRect(sf::IntRect(size_weapon.x, row_weapon * size_weapon.y, size_weapon.x, size_weapon.y));
	stick = GlobalFunction::CreateSprite(position_stick, size_stick, texture_stick);
	text_stick = GlobalFunction::CreateText(position_text_stick, string_stick, font, size_normal_text);
	text_stick.setStyle(sf::Text::Bold);
	text_creation = GlobalFunction::CreateText(position_text_creation, string_creation, font, size_normal_text);
	text_creation.setFillColor(sf::Color::Color(178, 34, 34));
	text_creation.setStyle(sf::Text::Bold);

	text_ilvl_item = GlobalFunction::CreateText(position_ilvl_item, string_ilvl_item, font, size_normal_text-2);
	text_ilvl_item.setFillColor(sf::Color::Color(108, 129, 197));
	text_ilvl_item.setStyle(sf::Text::Bold);
	button_decrease_ilvl = GlobalFunction::CreateSprite(position_button_decrease_ilvl, size_button, texture_button_decrease_ilvl);
	button_increase_ilvl = GlobalFunction::CreateSprite(position_button_increase_ilvl, size_button, texture_button_increase_ilvl);
	button_decrease_sand = GlobalFunction::CreateSprite(position_button_decrease_sand, size_button, texture_button_decrease_ilvl);
	button_increase_sand = GlobalFunction::CreateSprite(position_button_increase_sand, size_button, texture_button_increase_ilvl);
	for (size_t i = 0; i < number_ores; i++)
	{
		ores[i] = GlobalFunction::CreateSprite(sf::Vector2f(position_first_ore.x, position_first_ore.y + ores_y_modifier*i), size_ores, texture_ores[i]);
		button_increase_ore[i] = GlobalFunction::CreateSprite(sf::Vector2f(position_first_button_increase.x, position_first_button_increase.y + ores_y_modifier*i),size_button,texture_button_increase_ilvl);
		button_decrease_ore[i] = GlobalFunction::CreateSprite(sf::Vector2f(position_first_button_decrease.x, position_first_button_decrease.y + ores_y_modifier*i), size_button, texture_button_decrease_ilvl);
		text_ores[i] = GlobalFunction::CreateText(sf::Vector2f(position_first_text_ores.x, position_first_text_ores.y + ores_y_modifier*i), string_ores[i], font, 16);
		text_ores[i].setFillColor(sf::Color::Color(108, 129, 197));
		text_ores[i].setStyle(sf::Text::Bold);
	}

	for (int i = 0; i < number_maximum_enchantments; i++)
	{
		text_weapon_bonus[i] = GlobalFunction::CreateText(position_first_weapon_bonus + sf::Vector2f(0, distance_between_weapon_bonus*i), string_weapon_bonus[i], font, 30);
		text_weapon_bonus[i].setStyle(sf::Text::Bold);
	}

	for (int i = 0; i < 3; i++)
	{
		text_talent_bonus[i] = GlobalFunction::CreateText(position_first_talent_bonus + sf::Vector2f(0, distance_between_talent_bonus*i), string_talent_bonus[i], font, 30);
		text_talent_bonus[i].setStyle(sf::Text::Bold);
	}

	magical_sand = GlobalFunction::CreateSprite(position_magical_sand, size_magical_sand, texture_magical_sand);
	text_magical_sand = GlobalFunction::CreateText(position_text_magical_sand, string_magical_sand, font, size_normal_text);
	text_magical_sand.setStyle(sf::Text::Bold);
	black_screen = GlobalFunction::CreateRectangle(size_black_screen, sf::Vector2f(0, 0));
	black_screen.setFillColor(color_black_screen);
	text_next = GlobalFunction::CreateText(position_text_next, string_next, font, 34);
	text_next.setStyle(sf::Text::Bold);

	PoolIronBonus.push_back(HpRecovery);
	PoolIronBonus.push_back(DefenseAddition);
	PoolIronBonus.push_back(HealthAddition);

	PoolIronBonus.push_back(DamageAddition);
	PoolIronBonus.push_back(LifeSteal);
	PoolIronBonus.push_back(AttackSpeedPercent);

	PoolIronBonus.push_back(StunReductionPercent);
	PoolIronBonus.push_back(CooldownReduction);
	PoolIronBonus.push_back(MovementSpeedPercent);

	PoolEmeraldBonus.push_back(HpRecovery);
	PoolEmeraldBonus.push_back(DefenseAddition);
	PoolEmeraldBonus.push_back(HealthAddition);

	PoolTopazBonus.push_back(StunReductionPercent);
	PoolTopazBonus.push_back(CooldownReduction);
	PoolTopazBonus.push_back(MovementSpeedPercent);

	PoolRubyBonus.push_back(DamageAddition);
	PoolRubyBonus.push_back(LifeSteal);
	PoolRubyBonus.push_back(AttackSpeedPercent);

	listAllTalents = ListObjectsSingleton::instance()->GetListTalent();
}

CraftingInterface::~CraftingInterface()
{
}

void CraftingInterface::Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	CreateRectangleInformation(mouse_position);
	CheckPlayerAction(player, mouse_position);

	std::vector<std::vector<int>> inventory_player = player->GetInventory();
	most_used_ore = GetMostUsedOre();

	stick_needed = 5 * item_level;
	sand_needed = 0;
	for (size_t i = 0; i < number_enchantment; i++)
	{
		sand_needed += i+1;
	}

	float current_number_stick = inventory_player[I_Material][IM_Stick];
	float current_magic_sand = inventory_player[I_Material][IM_MagicSand];
	string_stick.clear();
	string_stick = GlobalFunction::InsertNumberToString(string_stick, inventory_player[I_Material][IM_Stick], string_stick.getSize());
	sf::String string_holder = " / ";
	string_stick.insert(string_stick.getSize(),string_holder);
	string_stick = GlobalFunction::InsertNumberToString(string_stick, stick_needed, string_stick.getSize());
	text_stick.setString(string_stick);
	if (current_number_stick < stick_needed)
	{
		text_stick.setFillColor(sf::Color::Color(175, 69, 69));
	}
	else
	{
		text_stick.setFillColor(sf::Color::Color(81, 175, 69));
	}

	if (current_magic_sand < sand_needed)
	{
		text_magical_sand.setFillColor(sf::Color::Color(175,69,69));
	}
	else
	{
		text_magical_sand.setFillColor(sf::Color::Color(81, 175, 69));
	}

	string_ilvl_item.clear();
	if (language == English_E)
	{
		string_ilvl_item = "item level : ";
	}
	else
	{
		string_ilvl_item = "niveau de l'object : ";
		text_ilvl_item.setCharacterSize(17);
	}
	string_ilvl_item = GlobalFunction::InsertNumberToString(string_ilvl_item, item_level, string_ilvl_item.getSize());
	text_ilvl_item.setString(string_ilvl_item);
	text_ilvl_item.setOrigin(sf::Vector2f(text_ilvl_item.getGlobalBounds().width / 2, text_ilvl_item.getGlobalBounds().height / 2));

	for (size_t i = 0; i < number_ores; i++)
	{
		string_ores[i].clear();
		if (language == English_E)
		{
			string_ores[i] = "Currently using : ";
		}
		else
		{
			string_ores[i] = "Actuellement : ";
		}
		string_ores[i] = GlobalFunction::InsertNumberToString(string_ores[i], number_using_ores[i], string_ores[i].getSize());
		text_ores[i].setString(string_ores[i]);
		text_ores[i].setOrigin(sf::Vector2f(0, text_ilvl_item.getGlobalBounds().height / 2));
	}

	string_magical_sand.clear();
	string_magical_sand = GlobalFunction::InsertNumberToString(string_magical_sand, inventory_player[I_Material][IM_MagicSand], string_magical_sand.getSize());
	sf::String string_tmp = " / ";
	string_magical_sand.insert(string_magical_sand.getSize(), string_tmp);
	string_magical_sand = GlobalFunction::InsertNumberToString(string_magical_sand, sand_needed, string_magical_sand.getSize());
	text_magical_sand.setString(string_magical_sand);
	text_magical_sand.setOrigin(sf::Vector2f(text_magical_sand.getGlobalBounds().width / 2, text_magical_sand.getGlobalBounds().height / 2));

	CreateWeapon(player, mouse_position);
	ShowingCreatedWeapon(mouse_position);
}

void CraftingInterface::CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	if (clock_click.getElapsedTime().asSeconds() >= 0.15 && !showing_created_weapon)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (button_increase_ilvl.getGlobalBounds().contains(mouse_position))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
					item_level += 10;
				}
				else
				{
					item_level++;
				}
				if (item_level > 100)
				{
					item_level = 100;
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
			}
			if (button_decrease_ilvl.getGlobalBounds().contains(mouse_position))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
					item_level -= 10;
				}
				else
				{
					item_level--;
				}
				if (item_level <= 0)
				{
					item_level = 1;
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
			}
			for (size_t i = 0; i < number_ores; i++)
			{
				if (button_decrease_ore[i].getGlobalBounds().contains(mouse_position))
				{
					if (number_using_ores[i] > 0 && number_used_enchantments > 0)
					{
						number_using_ores[i]--;
						number_used_enchantments--;
						SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
					}
				}
				else if (button_increase_ore[i].getGlobalBounds().contains(mouse_position))
				{
					if (number_enchantment > number_used_enchantments)
					{
						number_using_ores[i]++;
						number_used_enchantments++;
						SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
					}
				}
			}

			if (button_increase_sand.getGlobalBounds().contains(mouse_position))
			{
				if (number_enchantment < number_maximum_enchantments)
				{
					number_enchantment++;
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				}
			}
			else if (button_decrease_sand.getGlobalBounds().contains(mouse_position))
			{
				if (number_enchantment > 0)
				{
					number_enchantment--;
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				}
			}
			clock_click.restart();
		}
	}
}

void CraftingInterface::Draw(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
#pragma region Sockets
	sf::Vector2i counter{ 0,0 };
	int socket_iron = number_using_ores[Self_Iron];
	int socket_ruby = number_using_ores[Self_Ruby];
	int socket_emerald = number_using_ores[Self_Emerald];
	int socket_topaz = number_using_ores[Self_Topaz];

	for (size_t i = 0; i < number_enchantment; i++)
	{
		sockets[i].setPosition(position_first_socket + sf::Vector2f(counter.x*(radius_socket * 2 + distance_between_socket), counter.y*(radius_socket * 2 + distance_between_socket)) + position_view_player);
		counter.x++;
		if (counter.x == 3)
		{
			counter.x = 0;
			counter.y++;
		}
		sockets[i].setRadius(radius_socket);
		sockets[i].setOrigin(radius_socket / 2, radius_socket / 2);

		if (socket_iron > 0)
		{
			sockets[i].setFillColor(sf::Color::Color(211, 211, 211));
			sockets[i].setOutlineColor(sf::Color::Color(169, 169, 169));
			sockets[i].setOutlineThickness(socket_thickness);
			socket_iron--;
		}
		else if (socket_ruby > 0)
		{
			sockets[i].setFillColor(sf::Color::Color(242, 17, 39));
			sockets[i].setOutlineColor(sf::Color::Color(187, 10, 30));
			sockets[i].setOutlineThickness(socket_thickness);
			socket_ruby--;
		}
		else if (socket_emerald > 0)
		{
			sockets[i].setFillColor(sf::Color::Color(6, 133, 35));
			sockets[i].setOutlineColor(sf::Color::Color(4, 93, 24));
			sockets[i].setOutlineThickness(socket_thickness);
			socket_emerald--;
		}
		else if (socket_topaz > 0)
		{
			sockets[i].setFillColor(sf::Color::Color(255, 206, 137));
			sockets[i].setOutlineColor(sf::Color::Color(255, 174, 59));
			sockets[i].setOutlineThickness(socket_thickness);
			socket_topaz--;
		}
		else
		{
			sockets[i].setFillColor(sf::Color::Color(112, 128, 144));
			sockets[i].setOutlineThickness(0);
		}
	}
#pragma endregion Sockets

	text_name_interface.setPosition(position_name_interface + position_view_player);
	item_preview.setPosition(position_weapon + position_view_player);
	item_preview.setTextureRect(sf::IntRect((most_used_ore + 1)* size_weapon.x, row_weapon * size_weapon.y, size_weapon.x, size_weapon.y));
	stick.setPosition(position_stick + position_view_player);
	text_stick.setPosition(position_text_stick + position_view_player);
	text_ilvl_item.setPosition(position_ilvl_item + position_view_player);
	text_creation.setPosition(position_text_creation + position_view_player);
	button_increase_ilvl.setPosition(position_button_increase_ilvl + position_view_player);
	button_decrease_ilvl.setPosition(position_button_decrease_ilvl + position_view_player);
	button_decrease_sand.setPosition(position_button_decrease_sand + position_view_player);
	black_screen.setPosition(position_view_player);
	button_increase_sand.setPosition(position_button_increase_sand + position_view_player);
	text_next.setPosition(position_text_next + position_view_player);

	for (int i = 0; i < number_maximum_enchantments; i++)
	{
		text_weapon_bonus[i].setPosition(position_first_weapon_bonus + sf::Vector2f(0, distance_between_weapon_bonus*i) + position_view_player);
	}

	for (size_t i = 0; i < number_ores; i++)
	{
		ores[i].setPosition(sf::Vector2f(position_first_ore.x, position_first_ore.y + ores_y_modifier*i) + position_view_player);
		text_ores[i].setPosition(sf::Vector2f(position_first_text_ores.x, position_first_text_ores.y + ores_y_modifier*i) + position_view_player);
		button_decrease_ore[i].setPosition(sf::Vector2f(position_first_button_decrease.x, position_first_button_decrease.y + ores_y_modifier*i) + position_view_player);
		button_increase_ore[i].setPosition(sf::Vector2f(position_first_button_increase.x, position_first_button_increase.y + ores_y_modifier*i) + position_view_player);
	}
	magical_sand.setPosition(position_magical_sand + position_view_player);
	text_magical_sand.setPosition(position_text_magical_sand + position_view_player);
	interface_crafting.setPosition(position_interface + position_view_player);

	window.draw(interface_crafting);
	window.draw(text_name_interface);
	window.draw(item_preview);
	window.draw(stick);
	window.draw(text_stick);
	window.draw(text_ilvl_item);
	window.draw(button_decrease_ilvl);
	window.draw(button_increase_ilvl);
	window.draw(text_creation);
	for (size_t i = 0; i < number_ores; i++)
	{
		window.draw(ores[i]);
		window.draw(text_ores[i]);
		window.draw(button_decrease_ore[i]);
		window.draw(button_increase_ore[i]);
	}
	window.draw(magical_sand);
	window.draw(text_magical_sand);
	window.draw(button_decrease_sand);
	window.draw(button_increase_sand);

	for (size_t i = 0; i < number_enchantment; i++)
	{
		window.draw(sockets[i]);
	}

	if (showing_created_weapon)
	{
		window.draw(black_screen);
		window.draw(text_next);
		item_preview.setPosition(position_weapon + position_view_player - sf::Vector2f(100,0));
		window.draw(item_preview);

		for (int i = 0; i < number_enchantment; i++)
		{
			window.draw(text_weapon_bonus[i]);
		}
		for (int i = 0; i < 3; i++)
		{
			window.draw(text_talent_bonus[i]);
		}
	}
}

void CraftingInterface::CreateWeapon(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	bool can_create_weapon = CheckIfEnoughMaterial(player);

	std::vector<std::vector<int>> inventory_player = player->GetInventory();

	if (can_create_weapon)
	{
		text_creation.setFillColor(sf::Color::Color(81, 175, 69));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && text_creation.getGlobalBounds().contains(mouse_position) && clock_creation.getElapsedTime().asSeconds() >= 0.5)
		{
			SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);

			std::vector<int> listTypeBonus;
			std::vector<float> listBonus;
			std::vector<sf::Vector2f> listRangeBonus;
			std::vector<int> listTalentBonus;
			std::vector<int> listTalentLevelBonus;

			int socket_iron = number_using_ores[Self_Iron];
			int socket_ruby = number_using_ores[Self_Ruby];
			int socket_emerald = number_using_ores[Self_Emerald];
			int socket_topaz = number_using_ores[Self_Topaz];
			int rarity_item = GetRarityItem();

			int number_talent_bonus = 0;
			int holder = item_level;
			while (holder > 0)
			{
				if (holder - 33 >= 0)
				{
					number_talent_bonus++;
				}
				holder -= 33;
			}

#pragma region RarityGestion
			if (rarity_item >= Rare_E)
			{
				number_talent_bonus++;
			}
			if (rarity_item >= Uncommon_E)
			{
				socket_iron++;
			}
			if (rarity_item >= Rare_E)
			{
				int random_number = GlobalFunction::getRandomRange(1, 1000);
				std::vector<int> listException;
				if(random_number <= 333)
				{
					listException.push_back(Self_Emerald);
					socket_emerald++;
				}
				else if (random_number <= 666)
				{
					listException.push_back(Self_Ruby);
					socket_ruby++;
				}
				else
				{
					listException.push_back(Self_Topaz);
					socket_topaz++;
				}

				if (rarity_item >= Epic_E)
				{
					int socket_number = GlobalFunction::getRandomRangeWithUnknownException(1, 3, listException);
					listException.push_back(socket_number);
					if (socket_number == Self_Ruby)
					{
						socket_ruby++;
					}
					else if (socket_number == Self_Topaz)
					{
						socket_topaz++;
					}
					else if (socket_number == Self_Emerald)
					{
						socket_emerald++;
					}
					if (rarity_item == Legendary_E)
					{
						int socket_number = GlobalFunction::getRandomRangeWithUnknownException(1, 3, listException);
						if (socket_number == Self_Ruby)
						{
							socket_ruby++;
						}
						else if (socket_number == Self_Topaz)
						{
							socket_topaz++;
						}
						else if (socket_number == Self_Emerald)
						{
							socket_emerald++;
						}
					}
				}

				item_level += rarity_item * 5;
			}
#pragma endregion RarityGestion

			float bonus_stat = player->GetPlayerBonusCraftingStat();

			for (int i = 0; i < socket_iron; i++)
			{
				int type_bonus = PoolIronBonus[GlobalFunction::getRandomRange(1, PoolIronBonus.size()) - 1];
				sf::Vector2f range_bonus = GetRangeBonus(type_bonus, item_level);
				range_bonus = sf::Vector2f(range_bonus.x + bonus_stat*range_bonus.x / 100, range_bonus.y + bonus_stat*range_bonus.y / 100);
				float bonus = GlobalFunction::getRandomRangeIfFloat(range_bonus.x * 100, range_bonus.y * 100) / 100;
				listTypeBonus.push_back(type_bonus);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(range_bonus);
			}
			for (int i = 0; i < socket_ruby; i++)
			{
				int type_bonus = PoolRubyBonus[GlobalFunction::getRandomRange(1, PoolRubyBonus.size()) - 1];
				sf::Vector2f range_bonus = GetRangeBonus(type_bonus, item_level);
				range_bonus = sf::Vector2f(range_bonus.x + bonus_stat*range_bonus.x / 100, range_bonus.y + bonus_stat*range_bonus.y / 100);
				float bonus = GlobalFunction::getRandomRangeIfFloat(range_bonus.x * 100, range_bonus.y * 100) / 100;
				listTypeBonus.push_back(type_bonus);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(range_bonus);
			}
			for (int i = 0; i < socket_emerald; i++)
			{
				int type_bonus = PoolEmeraldBonus[GlobalFunction::getRandomRange(1, PoolEmeraldBonus.size()) - 1];
				sf::Vector2f range_bonus = GetRangeBonus(type_bonus, item_level);
				range_bonus = sf::Vector2f(range_bonus.x + bonus_stat*range_bonus.x / 100, range_bonus.y + bonus_stat*range_bonus.y / 100);
				float bonus = GlobalFunction::getRandomRangeIfFloat(range_bonus.x * 100, range_bonus.y * 100) / 100;
				listTypeBonus.push_back(type_bonus);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(range_bonus);
			}
			for (int i = 0; i < socket_topaz; i++)
			{
				int type_bonus = PoolTopazBonus[GlobalFunction::getRandomRange(1, PoolTopazBonus.size()) - 1];
				sf::Vector2f range_bonus = GetRangeBonus(type_bonus, item_level);
				range_bonus = sf::Vector2f(range_bonus.x + bonus_stat*range_bonus.x / 100, range_bonus.y + bonus_stat*range_bonus.y / 100);
				float bonus = GlobalFunction::getRandomRangeIfFloat(range_bonus.x * 100, range_bonus.y * 100) / 100;
				listTypeBonus.push_back(type_bonus);
				listBonus.push_back(bonus);
				listRangeBonus.push_back(range_bonus);
			}

			std::vector<sf::String> listTalentStringToWeapon;
			
			for (int i = 0; i < number_talent_bonus; i++)
			{
				int type_talent = GetTalentBonus();
				listTalentBonus.push_back(type_talent);
				listTalentLevelBonus.push_back(1);

				if (language == English_E)
				{
					sf::String string_holder = "+1 to ";
					string_holder = listAllTalents[type_talent]->GetStringSkillInformation(0);
					listTalentStringToWeapon.push_back(string_holder);
				}
				else
				{
					sf::String string_holder = "+1 à ";
					string_holder = listAllTalents[type_talent]->GetStringSkillInformation(0);
					listTalentStringToWeapon.push_back(string_holder);
				}
			}

			std::shared_ptr<E_Weapon> weapon = std::shared_ptr<E_Weapon>(new E_Weapon(language, ListObjectsSingleton::instance()->GetCurrentSave()));
			weapon->Init(item_level, listTypeBonus, listBonus, listRangeBonus,listTalentBonus,listTalentLevelBonus,most_used_ore, listTalentStringToWeapon, ListObjectsSingleton::instance()->GetNewIDEquipment(),rarity_item);
			player->GiveWeapon(weapon);
			weapon.reset();

			player->PlayerConsumedSomething(I_Material, IM_Stick, stick_needed);
			player->PlayerConsumedSomething(I_Material, IM_Iron, socket_iron);
			player->PlayerConsumedSomething(I_Material, IM_Ruby, socket_ruby);
			player->PlayerConsumedSomething(I_Material, IM_Emerald, socket_emerald);
			player->PlayerConsumedSomething(I_Material, IM_Topaz, socket_topaz);
			player->PlayerConsumedSomething(I_Material, IM_MagicSand, sand_needed);
			
			showing_created_weapon = true;
			CreateWeaponBonusText(listTypeBonus, listBonus, listRangeBonus,listTalentBonus,listTalentLevelBonus);
			clock_creation.restart();
		}
	}
	else
	{
		text_creation.setFillColor(sf::Color::Color(175, 69, 69));
	}
}

void CraftingInterface::ShowingCreatedWeapon(sf::Vector2f mouse_position)
{
	if (showing_created_weapon)
	{
		if (text_next.getGlobalBounds().contains(mouse_position) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			showing_created_weapon = false;
		}
	}
}

bool CraftingInterface::CheckIfEnoughMaterial(std::shared_ptr<Player> &player)
{
	std::vector<std::vector<int>> inventory_player = player->GetInventory();

	if (!(inventory_player[I_Material][IM_Stick] >= stick_needed))
	{
		return false;
	}
	if (!(inventory_player[I_Material][IM_Iron] >= number_using_ores[Self_Iron]))
	{
		return false;
	}
	if (!(inventory_player[I_Material][IM_Ruby] >= number_using_ores[Self_Ruby]))
	{
		return false;
	}
	if (!(inventory_player[I_Material][IM_Emerald] >= number_using_ores[Self_Emerald]))
	{
		return false;
	}
	if (!(inventory_player[I_Material][IM_Topaz] >= number_using_ores[Self_Topaz]))
	{
		return false;
	}
	if (!(inventory_player[I_Material][IM_MagicSand] >= sand_needed))
	{
		return false;
	}
	if (number_used_enchantments != number_enchantment)
	{
		return false;
	}
	return true;
}

sf::Vector2f CraftingInterface::GetRangeBonus(int type_bonus, float item_level)
{
	switch (type_bonus)
	{
	case DamageAddition :
		return sf::Vector2f(10 + (item_level - 1)*0.28 -3, 10 + (item_level - 1)*0.38+3);
	
	case AttackSpeedPercent:
		return sf::Vector2f(3.47 + (item_level - 1)*0.075 - 0.65, 3.47 + (item_level - 1)*0.075 + 0.65);

	case LifeSteal:
		return sf::Vector2f(1.04 + (item_level - 1)*0.0265 - 0.2, 1.04 + (item_level - 1)*0.0265 + 0.2);

	case HealthAddition:
		return sf::Vector2f(210 + (item_level-1)*4.88 - 30, 210 + (item_level - 1)*4.88 + 30);

	case DefenseAddition:
		return sf::Vector2f(3.24 + (item_level - 1)*0.0375 - 1.3, 3.24 + (item_level - 1)*0.0375 + 1.3);

	case HpRecovery:
		return sf::Vector2f(5.23 + (item_level - 1)*0.053 - 2, 5.23 + (item_level - 1)*0.053 + 2);

	case MovementSpeedPercent:
		return sf::Vector2f(3 + (item_level - 1)*0.03 - 1.3, 3 + (item_level - 1)*0.03 + 1.3);

	case CooldownReduction:
		return sf::Vector2f(4.5 + (item_level - 1)*0.0445- 1.9, 4.5 + (item_level - 1)*0.0445 + 1.9);

	case StunReductionPercent:
		return sf::Vector2f(3.24 + (item_level - 1)*0.0375 - 1.3, 3.24 + (item_level - 1)*0.0375 + 1.3);
	}
}

sf::String CraftingInterface::GetStringBonus(int type_bonus)
{
	if (language == English_E)
	{
		switch (type_bonus)
		{
		case DamageAddition:
			return sf::String(" damage  ( ");

		case AttackSpeedPercent:
			return sf::String("% attack speed  ( ");

		case LifeSteal:
			return sf::String("% lifesteal  ( ");

		case HealthAddition:
			return sf::String(" maximum health  ( ");

		case DefenseAddition:
			return sf::String(" armor  ( ");

		case HpRecovery:
			return sf::String("  health per second  ( ");

		case MovementSpeedPercent:
			return sf::String("% movement speed  ( ");

		case CooldownReduction:
			return sf::String("% cooldown reduction  ( ");

		case StunReductionPercent:
			return sf::String("% stun reduction  ( ");
		}
	}
	else
	{ 
		switch (type_bonus)
		{
		case DamageAddition:
			return sf::String(" dégâts  ( ");

		case AttackSpeedPercent:
			return sf::String("% vitesse d'attaque  ( ");

		case LifeSteal:
			return sf::String("% vol de vie  ( ");

		case HealthAddition:
			return sf::String(" vie totale  ( ");

		case DefenseAddition:
			return sf::String(" armure  ( ");

		case HpRecovery:
			return sf::String("  vie par seconde  ( ");

		case MovementSpeedPercent:
			return sf::String("% vitesse de déplacement  ( ");

		case CooldownReduction:
			return sf::String("% temps de latence  ( ");

		case StunReductionPercent:
			return sf::String("% réduction des étourdissements  ( ");
		}
	}
}

void CraftingInterface::CreateRectangleInformation(sf::Vector2f mouse_position)
{
	if (!showing_created_weapon)
	{
		if (ores[Self_Iron].getGlobalBounds().contains(mouse_position))
		{
			std::vector<int> listLetterSize;
			std::vector<sf::String> listString;
			std::vector<bool> listIfCentered;

			if (language == English_E)
			{
				sf::String string1 = "Iron ore";
				sf::String string2 = "Found when destroy rocks. Can be embedded into an empty socket. Provides a random bonus.";
				listString.push_back(string1);
				listString.push_back(string2);
			}
			else
			{
				sf::String string1 = "Minerai de fer";
				sf::String string2 = "Trouvé en détruisant des roches. Peut être intégré dans un emplacement pour les gemmes. Apporte un attribut aléatoire.";
				listString.push_back(string1);
				listString.push_back(string2);
			}


			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);

			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
		}
		else if (ores[Self_Ruby].getGlobalBounds().contains(mouse_position))
		{
			std::vector<int> listLetterSize;
			std::vector<sf::String> listString;
			std::vector<bool> listIfCentered;

			if (language == English_E)
			{
				sf::String string1 = "Ruby";
				sf::String string2 = "Found when destroy rocks. Can be embedded into an empty socket. Provides a bonus to damage, attack speed or lifesteal.";
				listString.push_back(string1);
				listString.push_back(string2);
			}
			else
			{
				sf::String string1 = "Rubis";
				sf::String string2 = "Trouvé en détruisant des roches. Peut être intégré dans un emplacement pour les gemmes. Apporte un bonus aux dégâts, à la vitesse d'attaque ou au vol de vie.";
				listString.push_back(string1);
				listString.push_back(string2);
			}

			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);


			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
		}
		else if (ores[Self_Emerald].getGlobalBounds().contains(mouse_position))
		{
			std::vector<int> listLetterSize;
			std::vector<sf::String> listString;
			std::vector<bool> listIfCentered;

			if (language == English_E)
			{
				sf::String string1 = "Emerald";
				sf::String string2 = "Found when destroy rocks. Can be embedded into an empty socket. Provides a bonus increasing maximum health, armor or regeneration.";
				listString.push_back(string1);
				listString.push_back(string2);
			}
			else
			{
				sf::String string1 = "Émeraude";
				sf::String string2 = "Trouvé en détruisant des roches. Peut être intégré dans un emplacement pour les gemmes.  Apporte un bonus à la vie totale, à l'armure ou à la regénération.";
				listString.push_back(string1);
				listString.push_back(string2);
			}

			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);


			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
		}
		else if (ores[Self_Topaz].getGlobalBounds().contains(mouse_position))
		{
			std::vector<int> listLetterSize;
			std::vector<sf::String> listString;
			std::vector<bool> listIfCentered;

			if (language == English_E)
			{
				sf::String string1 = "Topaz";
				sf::String string2 = "Found when destroy rocks. Can be embedded into an empty socket. Provides a bonus increasing movement speed, cooldown reduction or stun reduction.";
				listString.push_back(string1);
				listString.push_back(string2);
			}
			else
			{
				sf::String string1 = "Topaze";
				sf::String string2 = "Trouvé en détruisant des roches. Peut être intégré dans un emplacement pour les gemmes.  Apporte un bonus à la vitesse de déplacement, au temps de latence ou à la réduction des étourdissements.";
				listString.push_back(string1);
				listString.push_back(string2);
			}

			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);


			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
		}
		else if (stick.getGlobalBounds().contains(mouse_position))
		{
			std::vector<int> listLetterSize;
			std::vector<sf::String> listString;
			std::vector<bool> listIfCentered;

			if (language == English_E)
			{
				sf::String string1 = "Stick";
				sf::String string2 = "Found after destroying trees. Used to increase the item level when crafting a weapon.";
				listString.push_back(string1);
				listString.push_back(string2);
			}
			else
			{
				sf::String string1 = "Bâton";
				sf::String string2 = "Trouvé en détruisant des arbres. Utilisé pour hausser le niveau des armes lors de la fabrication d'une arme.";
				listString.push_back(string1);
				listString.push_back(string2);
			}

			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);


			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
		}
		else if (magical_sand.getGlobalBounds().contains(mouse_position))
		{
			std::vector<int> listLetterSize;
			std::vector<sf::String> listString;
			std::vector<bool> listIfCentered;

			if (language == English_E)
			{
				sf::String string1 = "Magic Sand";
				sf::String string2 = "Found after destroying cactus. Used to add sockets when crafting a weapon.";
				listString.push_back(string1);
				listString.push_back(string2);
			}
			else
			{
				sf::String string1 = "Sable Magique";
				sf::String string2 = "Trouvé en détruisant des cactus. Utilisé pour ajouter des emplacement pour les gemmes lors de la fabrication d'une arme.";
				listString.push_back(string1);
				listString.push_back(string2);
			}

			listLetterSize.push_back(16);
			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listIfCentered.push_back(false);


			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
		}
	}
}

void CraftingInterface::CreateWeaponBonusText(std::vector<int> listTypeBonus, std::vector<float> listBonus, std::vector<sf::Vector2f> listRangeBonus, std::vector<int> talent_bonus, std::vector<int> talent_level_bonus)
{
	for (int i = 0; i < number_enchantment; i++)
	{
		string_weapon_bonus[i].clear();
		string_weapon_bonus[i] = ("+");
		string_weapon_bonus[i] = GlobalFunction::InsertNumberToStringIfFloat(string_weapon_bonus[i], listBonus[i], string_weapon_bonus[i].getSize());
		string_weapon_bonus[i].insert(string_weapon_bonus[i].getSize(), GetStringBonus(listTypeBonus[i]));
		string_weapon_bonus[i] = GlobalFunction::InsertNumberToStringIfFloat(string_weapon_bonus[i], listRangeBonus[i].x, string_weapon_bonus[i].getSize());
		string_weapon_bonus[i].insert(string_weapon_bonus[i].getSize(), sf::String(" - "));
		string_weapon_bonus[i] = GlobalFunction::InsertNumberToStringIfFloat(string_weapon_bonus[i], listRangeBonus[i].y, string_weapon_bonus[i].getSize());
		string_weapon_bonus[i].insert(string_weapon_bonus[i].getSize(), sf::String(" )"));
		text_weapon_bonus[i].setString(string_weapon_bonus[i]);
		text_weapon_bonus[i].setOrigin(text_weapon_bonus[i].getGlobalBounds().width / 2, text_weapon_bonus[i].getGlobalBounds().height / 2);
	}

	for (int i = 0; i < 3; i++)
	{
		if (i + 1 <= talent_bonus.size())
		{
			string_talent_bonus[i] = listAllTalents[talent_bonus[i]]->GetStringSkillInformation(0);
			string_talent_bonus[i].insert(string_talent_bonus[i].getSize(), sf::String(" +1"));
			text_talent_bonus[i].setString(string_talent_bonus[i]);
			text_talent_bonus[i].setOrigin(text_talent_bonus[i].getGlobalBounds().width / 2, text_talent_bonus[i].getGlobalBounds().height / 2);
		}
		else
		{
			string_talent_bonus[i] = " ";
			text_talent_bonus[i].setString(string_talent_bonus[i]);
			text_talent_bonus[i].setOrigin(text_talent_bonus[i].getGlobalBounds().width / 2, text_talent_bonus[i].getGlobalBounds().height / 2);
		}
	}
}

int CraftingInterface::GetMostUsedOre()
{
	int most_used_ore = 0;
	int type_ore = Self_Iron;

	for (int i = 0; i < number_ores; i++)
	{
		if (number_using_ores[i] > most_used_ore)
		{
			most_used_ore = number_using_ores[i];
			type_ore = i;
		}
	}

	return type_ore;
}

int CraftingInterface::GetTalentBonus()
{
	if (most_used_ore == Self_Iron)
	{
		return GlobalFunction::getRandomRange(0, 26);
	}
	else if (most_used_ore == Self_Ruby)
	{
		return PoolRubyTalentBonus[GlobalFunction::getRandomRange(1, 9) - 1];
	}
	else if (most_used_ore == Self_Emerald)
	{
		return PoolEmeraldTalentBonus[GlobalFunction::getRandomRange(1, 9) - 1];
	}
	else if (most_used_ore == Self_Topaz)
	{
		return PoolTopazTalentBonus[GlobalFunction::getRandomRange(1, 9) - 1];
	}
}

int CraftingInterface::GetRarityItem()
{
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

void CraftingInterface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];
	interface_crafting.setTexture(texture_interface);
}
