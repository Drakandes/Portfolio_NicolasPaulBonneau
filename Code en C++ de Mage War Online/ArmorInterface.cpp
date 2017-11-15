#include "stdafx.h"
#include "ArmorInterface.h"
#include "ListObjectsSingleton.h"

ArmorInterface::ArmorInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error with green flame in skillinterface" << std::endl;
	}

	if (!texture_armors.loadFromFile("ArmorBase_icone.png"))
	{
		std::cout << "Error with loading all armor textures" << std::endl;
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("ArmorInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("ArmorInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
#pragma endregion TextureInterfaceLoading

	listAllArmors = ListObjectsSingleton::instance()->GetListArmor();


	if (language == English_E)
	{
		string_armor_interface_name = "Armors";
		string_buy_armor = "Buy";
	}
	else
	{
		string_armor_interface_name = "Armures";
		string_buy_armor = "Achat";
	}
}

ArmorInterface::~ArmorInterface()
{
	listAllArmors.clear();
}

void ArmorInterface::InitArmorInterface(std::shared_ptr<Player> player)
{
	player_money = player->GetMoney();
	rectangle_interface = GlobalFunction::CreateSpriteWithoutOrigin(position_rectangle_interface,size_armor_interface, texture_interface);
	text_armor_interface_name = GlobalFunction::CreateText(position_armor_interface_name, string_armor_interface_name, font, character_size_armor_interface_name);
	text_armor_interface_name.setFillColor(sf::Color::Color(108, 129, 197));
	rectangle_current_armor_icone = GlobalFunction::CreateSprite(position_current_armor_icone, size_armor_icone_for_cutting, texture_armors);
	rectangle_current_armor_icone.setTextureRect(sf::IntRect(size_armor_icone_for_cutting.x*number_current_armor, 0, size_armor_icone_for_cutting.x, size_armor_icone_for_cutting.y));

	for (int number = 0; number < number_of_armors; number++)
	{
		position_rectangle_armor_icone[number] = sf::Vector2f(position_initial_rectangle_armor_icone.x + 99* holder_armor_icone.x, position_initial_rectangle_armor_icone.y + holder_armor_icone.y * size_armor_icone.y * 3);
		rectangle_armor_icone[number] = GlobalFunction::CreateSprite(position_rectangle_armor_icone[number], size_armor_icone_for_cutting, texture_armors);
		rectangle_armor_icone[number].setTextureRect(sf::IntRect(size_armor_icone_for_cutting.x*number, 0, size_armor_icone_for_cutting.x, size_armor_icone_for_cutting.y));
		holder_armor_icone.x++;

		if (holder_armor_icone.x >= armor_disposition_width_height.x)
		{
			holder_armor_icone.x = 0;
			holder_armor_icone.y++;
		}

		position_rectangle_buy_armor[number] = sf::Vector2f(position_rectangle_armor_icone[number].x, position_rectangle_armor_icone[number].y + size_armor_icone.y - 5);
		position_text_buy_armor[number] = sf::Vector2f(position_rectangle_buy_armor[number].x, position_rectangle_buy_armor[number].y - 2);
		text_buy_armor[number] = GlobalFunction::CreateText(position_text_buy_armor[number], string_buy_armor, font, character_size_buy_armor);
		text_buy_armor[number].setFillColor(sf::Color::Black);
		rectangle_buy_armor[number] = GlobalFunction::CreateRectangleWithOrigin(size_buy_armor, position_rectangle_buy_armor[number], sf::Color::White);

		if (language == English_E)
		{

			string_equip_armor[number] = "Equip";
		}
		else
		{
			string_equip_armor[number] = "Vêtir";
		}
		position_rectangle_equip_armor[number] = sf::Vector2f(position_text_buy_armor[number].x, position_text_buy_armor[number].y + size_equip_armor.y + 5);
		position_text_equip_armor[number] = sf::Vector2f(position_rectangle_equip_armor[number].x, position_rectangle_equip_armor[number].y - 2);
		text_equip_armor[number] = GlobalFunction::CreateText(position_text_equip_armor[number], string_equip_armor[number], font, character_size_buy_armor);
		text_equip_armor[number].setFillColor(sf::Color::Black);
		rectangle_equip_armor[number] = GlobalFunction::CreateRectangleWithOrigin(size_equip_armor, position_rectangle_equip_armor[number], sf::Color::White);
	}
}

void ArmorInterface::UpdateArmorInterface(sf::Vector2f mouse_position, sf::Vector2f position_view_player)
{
	rectangle_interface.setPosition(sf::Vector2f(position_view_player.x + position_rectangle_interface.x, position_view_player.y + position_rectangle_interface.y));
	text_armor_interface_name.setPosition(sf::Vector2f(position_view_player.x + position_armor_interface_name.x, position_view_player.y + position_armor_interface_name.y));
	rectangle_current_armor_icone.setPosition(position_view_player + position_current_armor_icone);
	rectangle_current_armor_icone.setTextureRect(sf::IntRect(size_armor_icone_for_cutting.x*number_current_armor, 0, size_armor_icone_for_cutting.x, size_armor_icone_for_cutting.y));

	if (language == English_E)
	{
		string_player_money = "Gold: ";
	}
	else
	{
		string_player_money = "Pièces d'or: ";
	}
	string_player_money = GlobalFunction::InsertNumberToString(string_player_money, player_money, string_player_money.getSize());
	text_player_money = GlobalFunction::CreateText(position_text_player_money + position_view_player, string_player_money, font, character_size_player_money);

	for (int number = 0; number < number_of_armors; number++)
	{
		if (player_armor_array[number] == 1)
		{
			rectangle_armor_icone[number].setColor(sf::Color::Color(255,255,255,255));
		}
		else
		{
			rectangle_armor_icone[number].setColor(sf::Color::Color(255, 255, 255, 150));
		}
		rectangle_armor_icone[number].setPosition(sf::Vector2f(position_rectangle_armor_icone[number].x + position_view_player.x, position_rectangle_armor_icone[number].y+ position_view_player.y));
		rectangle_buy_armor[number].setPosition(sf::Vector2f(position_rectangle_buy_armor[number].x + position_view_player.x, position_rectangle_buy_armor[number].y + position_view_player.y));
		text_buy_armor[number].setPosition(sf::Vector2f(position_text_buy_armor[number].x + position_view_player.x, position_text_buy_armor[number].y + position_view_player.y));
		text_equip_armor[number].setPosition(position_text_equip_armor[number] + position_view_player);
		rectangle_equip_armor[number].setPosition(position_rectangle_equip_armor[number] + position_view_player);
	}
}

void ArmorInterface::DrawArmorInterface(sf::RenderWindow &window)
{
	window.draw(rectangle_interface);
	window.draw(text_armor_interface_name);
	window.draw(rectangle_current_armor_icone);
	window.draw(text_player_money);
	for (int number = 0; number < number_of_armors; number++)
	{
		//window.draw(rectangle_buy_armor[number]);
		window.draw(text_buy_armor[number]);
		window.draw(rectangle_armor_icone[number]);
		//window.draw(rectangle_equip_armor[number]);
		window.draw(text_equip_armor[number]);
	}
}

void ArmorInterface::InteractionArmorInterface(sf::Vector2f mouse_position, sf::Vector2f position_view_player, std::shared_ptr<Player> player)
{
	NewPlayerArmorArray(player);
	NewPlayerCurrentArmor(player);
	NewPlayerMoney(player);

	UpdateArmorInterface(mouse_position, position_view_player);

	mouse_position = mouse_position - position_view_player;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock_between_buying_armors.getElapsedTime().asSeconds() >= 0.1)
	{
		for (int number = 0; number < number_of_armors; number++)
		{
			if (player_armor_array[number] == 0)
			{
				if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position, position_rectangle_buy_armor[number], size_buy_armor))
				{
					if (player_money >= listAllArmors[number]->ReturnArmorPrice())
					{
						player_money = player_money - listAllArmors[number]->ReturnArmorPrice();
						player_armor_array[number]++;
						SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
						clock_between_buying_armors.restart();
					}
				}
			}
			else if (player_armor_array[number] == 1 && player->GetPlayerLevel() >= listAllArmors[number]->ReturnArmorLevelRequired())
			{
				if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position, position_rectangle_equip_armor[number], size_equip_armor))
				{
					number_current_armor = number;
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
					clock_between_buying_armors.restart();
				}
			}
		}
	}

	GestionRectangleInformation(mouse_position+position_view_player, position_view_player, player->GetPlayerLevel());
	GiveBackPlayerInformation(player);
}

void ArmorInterface::GestionRectangleInformation(sf::Vector2f mouse_position, sf::Vector2f position_view_player, int player_level)
{
	sf::Vector2f mouse_position_modified = mouse_position - position_view_player;
	for (int number = 0; number < number_of_armors; number++)
	{
		if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_rectangle_buy_armor[number], size_buy_armor) && (player_armor_array[number] == 0))
		{
			std::vector<sf::String> listString;
			std::vector<int> listLetterSize;
			std::vector<bool> listIfCentered;
			sf::String string_holder;

			if (language == English_E)
			{
				string_holder = "This armor costs ";
				string_holder = GlobalFunction::InsertNumberToString(string_holder, listAllArmors[number]->ReturnArmorPrice(), string_holder.getSize());
				string_holder.insert(string_holder.getSize(), " gold!");
				listString.push_back(string_holder);
			}
			else
			{
				string_holder = "Cette armure coûte ";
				string_holder = GlobalFunction::InsertNumberToString(string_holder, listAllArmors[number]->ReturnArmorPrice(), string_holder.getSize());
				string_holder.insert(string_holder.getSize(), " pièces d'or!");
				listString.push_back(string_holder);
			}

			listLetterSize.push_back(16);
			listIfCentered.push_back(false);

			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
		}
		else if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_rectangle_buy_armor[number], size_buy_armor))
		{
			std::vector<sf::String> listString;
			std::vector<int> listLetterSize;
			std::vector<bool> listIfCentered;
			sf::String string_holder;

			if (language == English_E)
			{
				string_holder = "You already have this armor! You can't buy it an other time.";
				listString.push_back(string_holder);
			}
			else
			{
				string_holder = "Vous avez déjà cette armure! Vous ne pouvez pas l'acheter de nouveau.";
				listString.push_back(string_holder);
			}

			listLetterSize.push_back(16);
			listIfCentered.push_back(false);

			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
		}
		else if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_rectangle_armor_icone[number], size_armor_icone))
		{
			GenerateTextBox(number, mouse_position);
		}
		else if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_rectangle_equip_armor[number], size_equip_armor))
		{
			if (number_current_armor == number)
			{
				std::vector<sf::String> listString;
				std::vector<int> listLetterSize;
				std::vector<bool> listIfCentered;
				sf::String string_holder;

				if (language == English_E)
				{
					string_holder = "You already have this armor equipped!";
					listString.push_back(string_holder);
				}
				else
				{
					string_holder = "Vous portez présentement cette armure!";
					listString.push_back(string_holder);
				}

				listLetterSize.push_back(16);
				listIfCentered.push_back(false);

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
			else if (player_level < listAllArmors[number]->ReturnArmorLevelRequired())
			{
				std::vector<sf::String> listString;
				std::vector<int> listLetterSize;
				std::vector<bool> listIfCentered;
				sf::String string_holder;

				if (language == English_E)
				{
					string_holder = "Your level is too low, you cannot equip this armor!";
					listString.push_back(string_holder);
				}
				else
				{ 
					string_holder = "Votre niveau est trop bas, vous ne pouvez pas équipper cette armure!";
					listString.push_back(string_holder);
				}

				listLetterSize.push_back(16);
				listIfCentered.push_back(false);

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
			else if (player_armor_array[number] == 1)
			{
				std::vector<sf::String> listString;
				std::vector<int> listLetterSize;
				std::vector<bool> listIfCentered;
				sf::String string_holder;

				if (language == English_E)
				{
					string_holder = "Switch ";
					string_holder.insert(string_holder.getSize(), listAllArmors[number_current_armor]->ReturnNameArmor());
					string_holder.insert(string_holder.getSize(), " with ");
					string_holder.insert(string_holder.getSize(), listAllArmors[number]->ReturnNameArmor());
					string_holder.insert(string_holder.getSize(), ".");
					listString.push_back(string_holder);
				}
				else
				{
					string_holder = "Changer ";
					string_holder.insert(string_holder.getSize(), listAllArmors[number_current_armor]->ReturnNameArmor());
					string_holder.insert(string_holder.getSize(), " pour ");
					string_holder.insert(string_holder.getSize(), listAllArmors[number]->ReturnNameArmor());
					string_holder.insert(string_holder.getSize(), ".");
					listString.push_back(string_holder);
				}

				listLetterSize.push_back(16);
				listIfCentered.push_back(false);

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
			else
			{
				std::vector<sf::String> listString;
				std::vector<int> listLetterSize;
				std::vector<bool> listIfCentered;
				sf::String string_holder;

				if (language == English_E)
				{
					string_holder = "You must buy the armor first before equipping it.";
					listString.push_back(string_holder);
				}
				else
				{
					string_holder = "Vous devez acheter l'armure avant de pouvoir l'équipper.";
					listString.push_back(string_holder);
				}

				listLetterSize.push_back(16);
				listIfCentered.push_back(false);

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
		}
	}
	if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_current_armor_icone, size_armor_icone) && !can_create_rectangle_information_buy_armor)
	{
		std::vector<sf::String> listString;
		std::vector<int> listLetterSize;
		std::vector<bool> listIfCentered;
		sf::String string_holder;

		if (language == English_E)
		{
			string_holder = "Armor currently equipped : ";
			string_holder.insert(string_holder.getSize(), listAllArmors[number_current_armor]->ReturnNameArmor());
			listString.push_back(string_holder);
		}
		else
		{
			string_holder = "Armure présentement équippée : ";
			string_holder.insert(string_holder.getSize(), listAllArmors[number_current_armor]->ReturnNameArmor());
			listString.push_back(string_holder);
		}

		listLetterSize.push_back(16);
		listIfCentered.push_back(false);

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
}

void ArmorInterface::NewPlayerArmorArray(std::shared_ptr<Player> player)
{
	player_armor_array = player->GetPlayerArmorArray();
}

void ArmorInterface::NewPlayerCurrentArmor(std::shared_ptr<Player> player)
{
	number_current_armor = player->GetPlayerCurrentArmor();
}

void ArmorInterface::NewPlayerMoney(std::shared_ptr<Player> player)
{
	player_money = player->GetMoney();
}

void ArmorInterface::GenerateTextBox(int armor_displaying, sf::Vector2f mouse_position)
{
	std::vector<sf::String> listString;
	std::vector<int> listLetterSize;
	std::vector<bool> listIfCentered;
	sf::String string_holder;

	listString.push_back(listAllArmors[armor_displaying]->ReturnNameArmor());
	listLetterSize.push_back(20);
	listIfCentered.push_back(true);

	listString.push_back(listAllArmors[armor_displaying]->ReturnArmorLevelRecommandedString());
	listLetterSize.push_back(16);
	listIfCentered.push_back(true);

	listString.push_back(sf::String(" "));
	listLetterSize.push_back(16);
	listIfCentered.push_back(false);

	if (language == English_E)
	{
		string_holder = "- There are ";
		string_holder = GlobalFunction::InsertNumberToString(string_holder, listAllArmors[armor_displaying]->ReturnAmorNumberGems(), string_holder.getSize());
		string_holder.insert(string_holder.getSize(), " slots for gems.");
		listString.push_back(string_holder);
		listLetterSize.push_back(16);
		listIfCentered.push_back(false);

		string_holder = "- The wearer can have up to ";
		string_holder = GlobalFunction::InsertNumberToString(string_holder, listAllArmors[armor_displaying]->ReturnArmorNumberSkills(), string_holder.getSize());
		string_holder.insert(string_holder.getSize(), " skills.");
		listString.push_back(string_holder);
		listLetterSize.push_back(16);
		listIfCentered.push_back(false);

		string_holder = "- This armor can support up to ";
		string_holder = GlobalFunction::InsertNumberToString(string_holder, listAllArmors[armor_displaying]->ReturnArmorNumberEquipments(), string_holder.getSize());
		string_holder.insert(string_holder.getSize(), " scrolls.");
		listString.push_back(string_holder);
		listLetterSize.push_back(16);
		listIfCentered.push_back(false);

		string_holder = "Armor bonus: ";
		string_holder.insert(string_holder.getSize(), listAllArmors[armor_displaying]->ReturnArmorBonusString());
		listString.push_back(string_holder);
		listLetterSize.push_back(16);
		listIfCentered.push_back(true);

	}
	else
	{
		string_holder = "- Il y a ";
		string_holder = GlobalFunction::InsertNumberToString(string_holder, listAllArmors[armor_displaying]->ReturnAmorNumberGems(), string_holder.getSize());
		string_holder.insert(string_holder.getSize(), " emplacement pour les gemmes.");
		listString.push_back(string_holder);
		listLetterSize.push_back(16);
		listIfCentered.push_back(false);

		string_holder = "- Le porteur peut avoir jusqu'à ";
		string_holder = GlobalFunction::InsertNumberToString(string_holder, listAllArmors[armor_displaying]->ReturnArmorNumberSkills(), string_holder.getSize());
		string_holder.insert(string_holder.getSize(), " sorts.");
		listString.push_back(string_holder);
		listLetterSize.push_back(16);
		listIfCentered.push_back(false);

		string_holder = "- Cette armure peut supporter jusqu'à ";
		string_holder = GlobalFunction::InsertNumberToString(string_holder, listAllArmors[armor_displaying]->ReturnArmorNumberEquipments(), string_holder.getSize());
		string_holder.insert(string_holder.getSize(), " manuscrits.");
		listString.push_back(string_holder);
		listLetterSize.push_back(16);
		listIfCentered.push_back(false);

		string_holder = "Bonus de l'armure: ";
		string_holder.insert(string_holder.getSize(), listAllArmors[armor_displaying]->ReturnArmorBonusString());
		listString.push_back(string_holder);
		listLetterSize.push_back(16);
		listIfCentered.push_back(true);
	}

	TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
}

void ArmorInterface::GiveBackPlayerInformation(std::shared_ptr<Player> player)
{
	player->NewPlayerCurrentArmor(number_current_armor);
	player->NewPlayerArmorArray(player_armor_array);
	player->NewPlayerMoney(player_money);
}

void ArmorInterface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];
	rectangle_interface.setTexture(texture_interface);
}