#include "stdafx.h"
#include "GemInterface.h"
#include "ListObjectsSingleton.h"

GemInterface::GemInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error with green flame in skillinterface" << std::endl;
	}
	if (!texture_all_gems.loadFromFile("GemBase_icone.png"))
	{
		std::cout << "Error while loading gems texture in gem interface" << std::endl;
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("GemInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("GemInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
#pragma endregion TextureInterfaceLoading

	ListAllGems = ListObjectsSingleton::instance()->GetListGem();
}

GemInterface::~GemInterface()
{
	ListAllAtiveGems.clear();
	ListAllGems.clear();
}

void GemInterface::InitGemInterface(int current_language)
{
	language = current_language;
	string_gem_interface_name = language == English_E ? "Gems" : "Gemmes";
	string_buy_gem = language == English_E ? "Buy" : "Acheter";
	text_gem_interface_name = GlobalFunction::CreateText(position_gem_interface_name, string_gem_interface_name, font, character_size_gem_interface_name-5);
	text_gem_interface_name.setFillColor(sf::Color::Color(108, 129, 197));
	text_gem_interface_name.setStyle(sf::Text::Bold);
	rectangle_gem_interface = GlobalFunction::CreateSpriteWithoutOrigin(position_gem_interface,size_gem_interface, texture_interface);

	for (int number = 0; number < number_max_gem_in_bag; number++)
	{
		if (number < number_of_gems)
		{
			position_gem_sprite_icone[number] = sf::Vector2f(position_initial_gem_sprite_icone.x + size_gem_sprite_icone.x * 2 * holder_gem_sprite_icone_width.x, position_initial_gem_sprite_icone.y + size_gem_sprite_icone.y * 3.25 * holder_gem_sprite_icone_width.y - 0.5);
			holder_gem_sprite_icone_width.x++;
			if (holder_gem_sprite_icone_width.x == max_gem_sprite_icone_width)
			{
				holder_gem_sprite_icone_width.x = 0;
				holder_gem_sprite_icone_width.y++;
			}
			rectangle_gem_icone[number] = GlobalFunction::CreateSprite(position_gem_sprite_icone[number], size_gem_sprite_icone_for_cutting, texture_all_gems);
			rectangle_gem_icone[number].setTextureRect(sf::IntRect(size_gem_sprite_icone_for_cutting.x*number, 0, size_gem_sprite_icone_for_cutting.x, size_gem_sprite_icone_for_cutting.y));

			position_rectangle_buy_gem[number] = sf::Vector2f(position_gem_sprite_icone[number].x, position_gem_sprite_icone[number].y + size_gem_sprite_icone.y / 2 + size_buy_gem.y / 2 + 10);
			position_text_buy_gem[number] = sf::Vector2f(position_rectangle_buy_gem[number].x, position_rectangle_buy_gem[number].y - 2);
			text_buy_gem[number] = GlobalFunction::CreateText(position_text_buy_gem[number], string_buy_gem, font, character_size_buy_gem);
			text_buy_gem[number].setFillColor(sf::Color::Black);
			rectangle_buy_gem[number] = GlobalFunction::CreateRectangleWithOrigin(size_buy_gem, position_rectangle_buy_gem[number], sf::Color::White);

			position_initial_rectangle_buy_gem_of_tier[number] = sf::Vector2f(position_rectangle_buy_gem[number].x - size_buy_gem_of_tier.x / 2 - 2, position_rectangle_buy_gem[number].y + size_buy_gem_of_tier.y + 6);
			for (size_t i = 0; i < ListAllGems[number]->GetGemNumberTiers(); i++)
			{
				position_rectangle_buy_gem_of_tier[number][i] = sf::Vector2f(position_initial_rectangle_buy_gem_of_tier[number].x + size_buy_gem_of_tier.x*holder_buy_gem_of_tier[number].x + 3 * holder_buy_gem_of_tier[number].x, position_initial_rectangle_buy_gem_of_tier[number].y + size_buy_gem_of_tier.y*holder_buy_gem_of_tier[number].y + 3 * holder_buy_gem_of_tier[number].y - 5);
				holder_buy_gem_of_tier[number].x++;
				if (holder_buy_gem_of_tier[number].x >= max_buy_gem_of_tier_width)
				{
					holder_buy_gem_of_tier[number].x = 0;
					holder_buy_gem_of_tier[number].y++;
				}
				rectangle_buy_gem_of_tier[number][i] = GlobalFunction::CreateRectangleWithOrigin(size_buy_gem_of_tier, position_rectangle_buy_gem_of_tier[number][i], sf::Color::Blue);
				text_buy_gem_of_tier[number][i] = GlobalFunction::CreateText(position_rectangle_buy_gem_of_tier[number][i], sintrg_buy_gem_of_tier[i], font, character_size_buy_gem_of_tier);
			}
		}
		position_player_gem_icone[number] = sf::Vector2f(position_initial_player_gem_icone.x + size_gem_sprite_icone.x*holder_player_gem_icone.x + distance_between_player_gem_icone * holder_player_gem_icone.x, position_initial_player_gem_icone.y + size_gem_sprite_icone.y*holder_player_gem_icone.y + distance_between_player_gem_icone * holder_player_gem_icone.y);
		holder_player_gem_icone.x++;
		if (holder_player_gem_icone.x >= max_player_gem_icone_width)
		{
			holder_player_gem_icone.x = 0;
			holder_player_gem_icone.y++;
		}
		rectangle_player_gem_icone[number] = GlobalFunction::CreateSprite(position_player_gem_icone[number], size_gem_sprite_icone_for_cutting, texture_all_gems);
		rectangle_player_gem_icone[number].setTextureRect(sf::IntRect(size_gem_sprite_icone_for_cutting.x*8,0,size_gem_sprite_icone_for_cutting.x, size_gem_sprite_icone_for_cutting.y));
	}
}

void GemInterface::UpdateGemInterfacePosition(sf::Vector2f position_view_player, std::shared_ptr<Player> player)
{
	text_gem_interface_name.setPosition(position_view_player + position_gem_interface_name);
	rectangle_gem_interface.setPosition(position_view_player + position_gem_interface);

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

	int number_embedded_gems = 0;

	for (int number = 0; number < number_max_gem_in_bag; number++)
	{
		if (number < number_of_gems)
		{
			rectangle_gem_icone[number].setPosition(position_gem_sprite_icone[number] + position_view_player);
			rectangle_buy_gem[number].setPosition(position_rectangle_buy_gem[number] + position_view_player);
			text_buy_gem[number].setPosition(position_text_buy_gem[number] + position_view_player);
			for (size_t i = 0; i < ListAllGems[number]->GetGemNumberTiers(); i++)
			{
				rectangle_buy_gem_of_tier[number][i].setPosition(position_rectangle_buy_gem_of_tier[number][i] + position_view_player);
				text_buy_gem_of_tier[number][i].setPosition(position_rectangle_buy_gem_of_tier[number][i] + position_view_player);
			}
		}
		if (number < player_gem_array.size())
		{
			rectangle_player_gem_icone[number].setPosition(position_player_gem_icone[number] + position_view_player);
			rectangle_player_gem_icone[number].setTextureRect(sf::IntRect(size_gem_sprite_icone_for_cutting.x * player_gem_array[number].x, size_gem_sprite_icone_for_cutting.y * (player_gem_array[number].y-1), size_gem_sprite_icone_for_cutting.x, size_gem_sprite_icone_for_cutting.y));
			if (ListAllAtiveGems[number] == 0)
			{
				rectangle_player_gem_icone[number].setColor(sf::Color::Color(255, 255, 255, 150));
			}
			else
			{
				number_embedded_gems++;
				rectangle_player_gem_icone[number].setColor(sf::Color::Color(255, 255, 255, 255));
			}
		}
	}
	if (language == English_E)
	{
		string_number_gems_using = "You have ";
		string_number_gems_using = GlobalFunction::InsertNumberToString(string_number_gems_using, number_embedded_gems, string_number_gems_using.getSize());
		string_number_gems_using.insert(string_number_gems_using.getSize(), " embedded gems in your armor. Your armor has still ");
		string_number_gems_using = GlobalFunction::InsertNumberToString(string_number_gems_using, player->GetNumberTotalGemsUsable() - number_embedded_gems, string_number_gems_using.getSize());
		string_number_gems_using.insert(string_number_gems_using.getSize(), " slots left!");
		text_number_gems_using = GlobalFunction::CreateTextWithNoOrigin(position_text_number_gems_using + position_view_player, string_number_gems_using, font, 22);
		text_number_gems_using.setFillColor(sf::Color::Color(108, 129, 197));
		text_number_gems_using.setStyle(sf::Text::Bold);
	}
	else
	{
		string_number_gems_using = "Vous avez ";
		string_number_gems_using = GlobalFunction::InsertNumberToString(string_number_gems_using, number_embedded_gems, string_number_gems_using.getSize());
		string_number_gems_using.insert(string_number_gems_using.getSize(), " gemmes intégrées à votre armure. Il reste ");
		string_number_gems_using = GlobalFunction::InsertNumberToString(string_number_gems_using, player->GetNumberTotalGemsUsable() - number_embedded_gems, string_number_gems_using.getSize());
		string_number_gems_using.insert(string_number_gems_using.getSize(), " emplacements disponibles!");
		text_number_gems_using = GlobalFunction::CreateTextWithNoOrigin(position_text_number_gems_using + position_view_player, string_number_gems_using, font, 22);
		text_number_gems_using.setFillColor(sf::Color::Color(108, 129, 197));
		text_number_gems_using.setStyle(sf::Text::Bold);
	}
}

void GemInterface::DrawGemInterface(sf::RenderWindow &window)
{
	window.draw(rectangle_gem_interface);
	window.draw(text_gem_interface_name);
	window.draw(text_player_money);
	window.draw(text_number_gems_using);
	for (int number = 0; number < number_max_gem_in_bag; number++)
	{
		if (number < number_of_gems)
		{
			window.draw(rectangle_gem_icone[number]);
			window.draw(text_buy_gem[number]);
			if (can_draw_buy_gem_of_tier[number])
			{
				for (size_t i = 0; i < ListAllGems[number]->GetGemNumberTiers(); i++)
				{
				//	window.draw(rectangle_buy_gem_of_tier[number][i]);
					window.draw(text_buy_gem_of_tier[number][i]);
				}
			}
		}
		if (number < player_gem_array.size())
		{
			window.draw(rectangle_player_gem_icone[number]);
		}
	}
}

void GemInterface::GestionRectangleInformation(sf::Vector2f mouse_position, sf::Vector2f position_view_player)
{
	sf::Vector2f mouse_position_modified = mouse_position - position_view_player;
	for (int number = 0; number < number_max_gem_in_bag; number++)
	{
		if (number < number_of_gems)
		{
			if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_gem_sprite_icone[number], size_gem_sprite_icone))
			{
				std::vector<sf::String> listString;
				std::vector<int> listLetterSize;
				std::vector<bool> listIfCentered;
				sf::String string_holder;

				string_holder = ListAllGems[number]->GetStringGemName();


				listString.push_back(string_holder);
				listLetterSize.push_back(16);
				listIfCentered.push_back(false);

				for (size_t i = 1; i <= ListAllGems[number]->GetGemNumberTiers(); i++)
				{
					string_holder = "-";
					string_holder.insert(string_holder.getSize(), ListAllGems[number]->GetStringGemBonusForTier(i-1));

					listString.push_back(string_holder);
					listLetterSize.push_back(16);
					listIfCentered.push_back(false);
				}
				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
			else if (can_draw_buy_gem_of_tier[number])
			{
				for (size_t i = 0; i < ListAllGems[number]->GetGemNumberTiers(); i++)
				{
					if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_rectangle_buy_gem_of_tier[number][i], size_buy_gem_of_tier))
					{
						std::vector<sf::String> listString;
						std::vector<int> listLetterSize;
						std::vector<bool> listIfCentered;
						sf::String string_holder;

						if (language == English_E)
						{
							string_holder = "This ";
							string_holder.insert(string_holder.getSize(), ListAllGems[number]->GetStringGemName());
							string_holder.insert(string_holder.getSize(), " level ");
							string_holder = GlobalFunction::InsertNumberToString(string_holder, i + 1, string_holder.getSize());
							string_holder.insert(string_holder.getSize(), " costs ");
							string_holder = GlobalFunction::InsertNumberToString(string_holder, ListAllGems[number]->GetGemPriceForTier(i), string_holder.getSize());
							string_holder.insert(string_holder.getSize(), " gold.");
						}
						else
						{
							string_holder = "Cette ";
							string_holder.insert(string_holder.getSize(), ListAllGems[number]->GetStringGemName());
							string_holder.insert(string_holder.getSize(), " de niveau ");
							string_holder = GlobalFunction::InsertNumberToString(string_holder, i + 1, string_holder.getSize());
							string_holder.insert(string_holder.getSize(), " coûte ");
							string_holder = GlobalFunction::InsertNumberToString(string_holder, ListAllGems[number]->GetGemPriceForTier(i), string_holder.getSize());
							string_holder.insert(string_holder.getSize(), " pièces d'or.");
						}

						listString.push_back(string_holder);
						listLetterSize.push_back(16);
						listIfCentered.push_back(false);
						TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
					}
				}
			}
			else if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_rectangle_buy_gem[number], size_buy_gem))
			{
				std::vector<sf::String> listString;
				std::vector<int> listLetterSize;
				std::vector<bool> listIfCentered;
				sf::String string_holder;

				if (language == English_E)
				{
					string_holder = "Click here to buy a ";
					string_holder.insert(string_holder.getSize(), ListAllGems[number]->GetStringGemName());
				}
				else
				{
					string_holder = "Cliquer ici pour acheter une ";
					string_holder.insert(string_holder.getSize(), ListAllGems[number]->GetStringGemName());
				}

				listString.push_back(string_holder);
				listLetterSize.push_back(16);
				listIfCentered.push_back(false);
				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
		}
		if (number < player_gem_array.size())
		{
			if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_player_gem_icone[number], size_gem_sprite_icone))
			{
				std::vector<sf::String> listString;
				std::vector<int> listLetterSize;
				std::vector<bool> listIfCentered;
				sf::String string_holder;

				string_holder.clear();
				string_holder.insert(string_holder.getSize(), ListAllGems[player_gem_array[number].x]->GetStringGemName());
				if (language == English_E)
				{
					string_holder.insert(string_holder.getSize(), " level ");
				}
				else
				{
					string_holder.insert(string_holder.getSize(), " niveau ");
				}
				string_holder = GlobalFunction::InsertNumberToString(string_holder, player_gem_array[number].y, string_holder.getSize());

				listString.push_back(string_holder);
				listLetterSize.push_back(16);
				listIfCentered.push_back(false);
				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
		}
	}
}

void GemInterface::InteractionGemInterface(sf::Vector2f mouse_position, sf::Vector2f position_view_player, std::shared_ptr<Player> player)
{
	NewPlayerMoney(player);
	NewPlayerGemArray(player);

	UpdateGemInterfacePosition(position_view_player, player);

	mouse_position = mouse_position - position_view_player;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock_between_buying_gem.getElapsedTime().asSeconds() >= 0.1)
	{
		for (int number = 0; number < (ListAllAtiveGems.size() > number_of_gems ? ListAllAtiveGems.size() : number_of_gems); number++)
		{
			if (number < number_of_gems)
			{
				if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position, position_rectangle_buy_gem[number], size_buy_gem) && !can_draw_buy_gem_of_tier[number])
				{
					can_draw_buy_gem_of_tier[number] = true;
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				}
				else if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position, position_rectangle_buy_gem[number], size_buy_gem) && can_draw_buy_gem_of_tier[number])
				{
					can_draw_buy_gem_of_tier[number] = false;
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				}
				else if (can_draw_buy_gem_of_tier[number])
				{
					for (size_t i = 0; i < ListAllGems[number]->GetGemNumberTiers(); i++)
					{
						if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position, position_rectangle_buy_gem_of_tier[number][i], size_buy_gem_of_tier) && player_gem_array.size() < 200)
						{
							int nothing = 0;
							can_draw_buy_gem_of_tier[number] = false;
							player_money -= ListAllGems[number]->GetGemPriceForTier(i);
							sf::Vector2f new_gem{ static_cast<float>(number), static_cast<float>(i + 1) };
							player_gem_array.push_back(new_gem);
							ListAllAtiveGems.push_back(nothing);
							clock_between_buying_gem.restart();
							SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
						}
					}
				}
			}
			if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position, position_player_gem_icone[number], size_gem_sprite_icone) && number < player_gem_array.size())
			{
				int number_embedded_gems = 0;
				for (int holder = 0; holder < ListAllAtiveGems.size(); holder++)
				{
					if (ListAllAtiveGems[holder] == 1)
					{
						number_embedded_gems++;
						SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
					}
				}
				if (number_embedded_gems < player->GetNumberTotalGemsUsable())
				{
					ListAllAtiveGems[number] = 1;
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				}
			}
		}
		clock_between_buying_gem.restart();
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && clock_between_buying_gem.getElapsedTime().asSeconds() >= 0.1)
	{
		for (int number = 0; number < ListAllAtiveGems.size(); number++)
		{
			if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position, position_player_gem_icone[number], size_gem_sprite_icone))
			{
					ListAllAtiveGems[number] = 0;
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
			}
		}
	}

	GestionRectangleInformation(mouse_position + position_view_player, position_view_player);
	GiveBackPlayerInformation(player);
}

void GemInterface::NewPlayerMoney(std::shared_ptr<Player> player)
{
	player_money = player->GetMoney();
}

void GemInterface::NewPlayerGemArray(std::shared_ptr<Player> player)
{
	player_gem_array = player->GetPlayerGemArray();
	ListAllAtiveGems = player->GetPlayerActiveGemArray();
}

void GemInterface::GiveBackPlayerInformation(std::shared_ptr<Player> player)
{
	player->NewPlayerMoney(player_money);
	player->NewPlayerGemArray(player_gem_array);
	player->NewPlayerActiveGemArray(ListAllAtiveGems);
}

void GemInterface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];
	rectangle_gem_interface.setTexture(texture_interface);
}