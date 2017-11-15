#include "stdafx.h"
#include "SkillInterface.h"

SkillInterface::SkillInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error with green flame in skillinterface" << std::endl;
	}

	if (!texture_upgrade_skill_level.loadFromFile("Upgrade_skill_level_icone.png"))
	{
		std::cout << "Error with texture upgrade skill level" << std::endl;
	}

	if (!texture_interface.loadFromFile("Skill_interface_background_v2.png"))
	{
		std::cout << "Error with texture skill interface" << std::endl;
	}

	if (!texture_skillbase_icone.loadFromFile("SkillBase_icone.png"))
	{
		std::cout << "Error while loading skillbase player icone in skill interface" << std::endl;
	}

	if (!texture_erase_skill.loadFromFile("Sprite_erase_skill.png"))
	{
		std::cout << "Error with texture erase skill interface" << std::endl;
	}

	if (!texture_fragment.loadFromFile("Skill_interface_fragment_icone.png"))
	{
		std::cout << "Error while loading fragment icone in skill_interface" << std::endl;
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("SkillInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("SkillInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("SkillRuneInterfaceV1.png");
		ListTextureInterface2.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("SkillRuneInterfaceV2.png");
		ListTextureInterface2.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("SkillFragmentInterfaceV1.png");
		ListTextureInterface3.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("SkillFragmentInterfaceV2.png");
		ListTextureInterface3.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
	texture_fragment = ListTextureInterface3[0];
	texture_rune_interface = ListTextureInterface2[0];
#pragma endregion TextureInterfaceLoading

	CreateSkillInterfaceRectangle();
	listAllSkill = ListObjectsSingleton::instance()->GetListSkill();
	listAllArmors = ListObjectsSingleton::instance()->GetListArmor();
	InitAllSkillIcone();

	rune_interface = GlobalFunction::CreateSpriteWithoutOrigin(sf::Vector2f(0, 0), size_rune_interface, texture_rune_interface);

	for (int i = 0; i < number_choice_rune; i++)
	{
		rect_rune[i] = GlobalFunction::CreateRectangle(size_rect_rune, position_first_rect_rune + sf::Vector2f(5 * i + i*size_rect_rune.x, 0));
		rect_rune[i].setFillColor(sf::Color::Color(0,0,0,240));
	}
}

SkillInterface::~SkillInterface()
{
}

void SkillInterface::CreateSkillInterfaceRectangle()
{
	skill_interface_rectangle = GlobalFunction::CreateSpriteWithoutOrigin(skill_interface_position, skill_interface_size, texture_interface);
	sf::Vector2f text_position{ 0,0 };

	rectangle_fragment_interface = GlobalFunction::CreateSpriteWithoutOrigin(position_fragment_interface,size_fragment_interface,texture_fragment);
	text_fragment_interface_name = GlobalFunction::CreateText(text_position, "Fragments", font, skill_interface_name_text_size);
	text_fragment_interface_name.setFillColor(sf::Color::Color(108, 129, 197));

	InitRectangleSkillIcone();
}

void SkillInterface::DrawToScreen(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	window.draw(skill_interface_rectangle);
	window.draw(sprite_second_interface_rectangle);
	window.draw(rectangle_fragment_interface);
	window.draw(text_fragment_interface_name);

	for (int number = 0; number < number_skill; number++)
	{
		window.draw(rectangle_skill_icone[number]);
		if (number < number_skill_player)
		{
			window.draw(rectangle_skill_icone_player[number]);
		}
		if (number < listAllSkill.size())
		{
			window.draw(sprite_skill_icone[number]);
		}
		if (number < player_skills_array.size() && player_skill_icone_created[number])
		{
			window.draw(sprite_skill_icone_player[number]);
		}
		if (number < number_different_fragment_type)
		{
			window.draw(text_number_fragment[number]);
		}
		window.draw(text_skill_level[number]);
		window.draw(sprite_upgrade_skill_level[number]);
	}

	window.draw(sprite_erase_skill);

	if (is_choosing_rune)
	{
		window.draw(rune_interface);
		for (int i = 0; i < number_choice_rune; i++)
		{
			window.draw(rect_rune[i]);
		}
	}
}

void SkillInterface::InitRectangleSkillIcone()
{
	for (int number = 0; number < number_skill; number++)
	{
		position_skill_icone[number] = sf::Vector2f(position_initial_skill_icone.x + size_skill_icone.x*holder.x + 25*holder.x, position_initial_skill_icone.y + size_skill_icone.y*holder.y + 25*holder.y);
		holder.x++;
		if (holder.x >= skill_icone_width)
		{
			holder.y++;
			holder.x = 0;
		}

		rectangle_skill_icone[number] = GlobalFunction::CreateSprite(position_skill_icone[number], size_skillbase_icone, texture_skillbase_icone);
	}

	for (int number = 0; number < number_skill_player; number++)
	{
		position_skill_icone_player[number] = sf::Vector2f(position_initial_skill_icone_player.x + size_skill_icone.x*holder_player.x + 25 * holder_player.x, position_initial_skill_icone_player.y + size_skill_icone.y*holder_player.y + 25 * holder_player.y);
		holder_player.y++;
		if (holder_player.y >= skill_icone_height)
		{
			holder_player.x++;
			holder_player.y = 0;
		}

		rectangle_skill_icone_player[number] = GlobalFunction::CreateSprite(position_skill_icone_player[number], size_skillbase_icone, texture_skillbase_icone);
	}
	position_erase_skill = sf::Vector2f(position_initial_skill_icone_player.x + size_skill_icone.x + 25, position_initial_skill_icone_player.y + size_skill_icone.y * 4 + 25 * 4);
	sprite_erase_skill = GlobalFunction::CreateSprite(position_erase_skill, size_skillbase_icone, texture_erase_skill);
	sprite_second_interface_rectangle = GlobalFunction::CreateSpriteWithoutOrigin(position_initial_second_rectangle, size_second_rectangle, texture_interface);
	sprite_second_interface_rectangle.setTextureRect(sf::IntRect(805, 80, size_second_rectangle.x, size_second_rectangle.y));
}

void SkillInterface::InitSkillPlayer(std::shared_ptr<Player> player)
{
	InitPlayerNumberFragments(player);

	player_skills_array = player->GetPlayerSkillArray();
	player_skills_level_array = player->GetPlayerSkillLevelArray();
	for (int number = 0; number < number_skill; number++)
	{
		if (number < player_skills_array.size())
		{
			if (!(player_skills_array[number] == -1))
			{
				texture_skill_icone_player[number] = listAllSkill[player_skills_array[number]]->ReturnSkillIconeTexture();
				sprite_skill_icone_player[number] = GlobalFunction::CreateSprite(position_skill_icone_player[number], size_skill_icone, texture_skill_icone_player[number]);
				player_skill_icone_created[number] = true;
			}
			else
			{
				sprite_skill_icone_player[number] = GlobalFunction::CreateSpriteWithoutTexture(position_skill_icone_player[number], size_skill_icone);
			}
		}
		position_skill_level[number] = sf::Vector2f(position_skill_icone[number].x - 18, position_skill_icone[number].y + 13);
		string_skill_level[number] = GlobalFunction::InsertNumberToString(string_skill_level[number], player_skills_level_array[number], string_skill_level[number].getSize());
		text_skill_level[number] = GlobalFunction::CreateText(position_skill_level[number], string_skill_level[number], font, character_size_skill_level);
		text_skill_level[number].setStyle(sf::Text::Bold);
		position_upgrade_skill_level[number] = sf::Vector2f(position_skill_icone[number].x + 25, position_skill_icone[number].y + 25);
		sprite_upgrade_skill_level[number] = GlobalFunction::CreateSprite(position_upgrade_skill_level[number],size_upgrade_skill_level, texture_upgrade_skill_level);
	}
}

void SkillInterface::InitPlayerNumberFragments(std::shared_ptr<Player> player)
{
	player_number_fragments = player->GetPlayerNumberFragments();

	for (int number = 0; number < number_different_fragment_type; number++)
	{
		position_number_fragment[number] = sf::Vector2f(position_initial_number_fragment.x, position_initial_number_fragment.y + 28 * number);
		string_number_fragment[number].insert(string_number_fragment[number].getSize(), GlobalFunction::GetTypeFragment(number));
		string_number_fragment[number] = GlobalFunction::InsertNumberToString(string_number_fragment[number], player_number_fragments[number], string_number_fragment[number].getSize());
		text_number_fragment[number] = GlobalFunction::CreateTextWithNoOrigin(position_number_fragment[number], string_number_fragment[number], font, character_size_number_fragment);
		text_number_fragment[number].setStyle(sf::Text::Bold);
		text_number_fragment[number].setFillColor(sf::Color::Color(108, 129, 197));
	}
}

void SkillInterface::InitAllSkillIcone()
{
	for (int number = 0; number < listAllSkill.size(); number++)
	{
		texture_skill_icone[number] = listAllSkill[number]->ReturnSkillIconeTexture();
		sprite_skill_icone[number] = GlobalFunction::CreateSprite(position_skill_icone[number], size_skill_icone, texture_skill_icone[number]);
	}
}

void SkillInterface::InteractionWithSkillInterface(sf::Vector2f mouse_position, sf::Vector2f position_view_player, std::shared_ptr<Player> player)
{
	UpdateSkillInterfacePlayerSkill();
	UpdatePlayerSkill(player);
	UpdatePlayerSkillLevel(player);
	UpdatePlayerNumberFragments(player);
	NewPlayerCurrentArmor(player);

	sf::Vector2f mouse_position_modified =  mouse_position - position_view_player;
	if (clock_click.getElapsedTime().asSeconds() >= 0.2)
	{
		if (!is_choosing_rune)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				for (int number = 0; number < player_skills_array.size(); number++)
				{
					if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_skill_icone_player[number], size_skill_icone) && slot_changing == -1 && number < listAllArmors[number_current_armor]->ReturnArmorNumberSkills())
					{
						if (number < listAllArmors[number_current_armor]->ReturnArmorNumberSkills() && player_skill_icone_created[number])
						{
							rectangle_skill_icone_player[number].setColor(sf::Color::Color(255, 255, 255, 000));
							sprite_skill_icone_player[number].setColor(sf::Color::Color(255, 255, 255, 100));
							slot_changing = number;
							clock_click.restart();
						}
						else
						{
							rectangle_skill_icone_player[number].setColor(sf::Color::Color(255, 255, 255, 100));
							sprite_skill_icone_player[number].setColor(sf::Color::Color(255, 255, 255, 100));
							slot_changing = number;
							clock_click.restart();
						}
						SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
					}
				}

				for (int number = 0; number < listAllSkill.size(); number++)
				{
					if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_skill_icone[number], size_skill_icone))
					{
						is_choosing_rune = true;
						rune_skill_related = number;
						rune_currently_using = player->GetCurrentRuneForSpecificSkill(rune_skill_related);

						current_position_rune_interface = mouse_position + sf::Vector2f(5, 5);
						rune_interface.setPosition(current_position_rune_interface);
						listAvailable = player->GetListRuneAvaiblable()[rune_skill_related];

						for (int i = 0; i < number_choice_rune; i++)
						{
							rect_rune[i].setPosition(current_position_rune_interface + position_first_rect_rune + sf::Vector2f(5 * i + i*size_rect_rune.x, 0));
							if( i != 0 && i - 1 == rune_currently_using)
							{ 
								rect_rune[i].setFillColor(sf::Color::Transparent);
							}
							else
							{
								rect_rune[i].setFillColor(sf::Color::Color(0, 0, 0, 75));
							}

							if(i != 0)
							{
								if (!listAvailable[i - 1])
								{
									rect_rune[i].setFillColor(sf::Color::Color(0, 0, 0, 150));
								}
							}
						}

						if (rune_currently_using == NoRune_E)
						{
							rect_rune[0].setFillColor(sf::Color::Transparent);
						}
						else
						{
							rect_rune[0].setFillColor(sf::Color::Color(0, 0, 0, 75));
						}

						SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
						clock_click.restart();
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (int number = 0; number < listAllSkill.size(); number++)
				{
					if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_upgrade_skill_level[number], size_upgrade_skill_level))
					{
						int type_fragment = GlobalFunction::GetTypeFragmentNeeded(player_skills_level_array[number]);

						if (player_skills_level_array[number] < number_different_fragment_type && !(type_fragment == -1))
						{
							if (GlobalFunction::GetNumberFragmentsNeeded(player_skills_level_array[number]) <= player_number_fragments[type_fragment])
							{
								player_number_fragments[type_fragment] = player_number_fragments[type_fragment] - GlobalFunction::GetNumberFragmentsNeeded(player_skills_level_array[number]);
								player_skills_level_array[number]++;
								FeatGestion::instance()->Action(F_SkillLeveled, 1);
								clock_click.restart();
								SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
							}
						}
					}
					else if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_skill_icone[number], size_skill_icone) && !(slot_changing == -1) && player_skills_level_array[number] > 0)
					{
						if (!GlobalFunction::CheckIfPlayerAlreadyHasSkill(number, player_skills_array))
						{
							rectangle_skill_icone_player[slot_changing].setColor(sf::Color::Color(255, 255, 255, 255));
							player_skills_array[slot_changing] = number;
							sprite_skill_icone_player[slot_changing].setColor(sf::Color::Color(255, 255, 255, 255));
							slot_changing = -1;
							clock_click.restart();
						}
						else
						{
							rectangle_skill_icone_player[slot_changing].setColor(sf::Color::Color(255, 255, 255, 255));
							sprite_skill_icone_player[slot_changing].setColor(sf::Color::Color(255, 255, 255, 255));
							slot_changing = -1;
							clock_click.restart();
						}
						SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
					}
					else if (sprite_erase_skill.getGlobalBounds().contains(mouse_position) && !(slot_changing == -1))
					{
						rectangle_skill_icone_player[slot_changing].setColor(sf::Color::Color(255, 255, 255, 150));
						player_skills_array[slot_changing] = -1;
						player_skill_icone_created[slot_changing] = false;
						sprite_skill_icone_player[slot_changing].setColor(sf::Color::Color(255, 255, 255, 150));
						slot_changing == -1;
						clock_click.restart();
						SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
					}

				}

				rectangle_skill_icone_player[slot_changing].setColor(sf::Color::Color(255, 255, 255, 255));
				sprite_skill_icone_player[slot_changing].setColor(sf::Color::Color(255, 255, 255, 255));
				slot_changing = -1;
				clock_click.restart();
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
			}
		}
		else
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (int i = 0; i < number_choice_rune; i++)
				{
					if (rect_rune[i].getGlobalBounds().contains(mouse_position))
					{
						if (i != 0)
						{
							player->ChangeRuneSpecificSkill(rune_skill_related, i - 1);
							SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
						}
						else
						{
							player->ChangeRuneSpecificSkill(rune_skill_related, NoRune_E);
							SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
						}
					}
				}
				is_choosing_rune = false;
				clock_click.restart();
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				is_choosing_rune = false;
				clock_click.restart();
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
			}
		}
	}

	SkillInterfaceGestionRectangleInformation(mouse_position, position_view_player, player);
	UpdateSkillInterfacePosition(position_view_player);

	GiveBackPlayerNewInformation(player);
}

void SkillInterface::SkillInterfaceGestionRectangleInformation(sf::Vector2f mouse_position, sf::Vector2f position_view_player, std::shared_ptr<Player> player)
{ 
	if (!is_choosing_rune)
	{
		sf::Vector2f mouse_position_modified = mouse_position - position_view_player;
		for (int number = 0; number < number_skill; number++)
		{
			if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_upgrade_skill_level[number], size_upgrade_skill_level))
			{
				std::vector<sf::String> listString;
				std::vector<int> listLetterSize;
				std::vector<bool> listIfCentered;
				sf::String string = GlobalFunction::GetFragmentNeededForSkillUpgrade(player_skills_level_array[number]);
				listString.push_back(string);
				listLetterSize.push_back(16);
				listIfCentered.push_back(false);
				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
			else if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position_modified, position_skill_icone[number], size_skill_icone) && number < listAllSkill.size())
			{
				GenerateTextBox(number, mouse_position, player_skills_level_array[number], player->GetCurrentClassPlayer());
			}
		}
		for (int i = 0; i < number_skill_player; i++)
		{
			if (sprite_skill_icone_player[i].getGlobalBounds().contains(mouse_position) && player_skill_icone_created[i])
			{
				std::vector<sf::String> listString;
				std::vector<int> listLetterSize;
				std::vector<bool> listIfCentered;

				listAllSkill[player_skills_array[i]]->ChangeSkillLevel(player_skills_level_array[player_skills_array[i]], 0, NoClass, NoRune_E);
				listString.push_back(listAllSkill[player_skills_array[i]]->GetStringSkillInformation(0));
				listLetterSize.push_back(16);
				listIfCentered.push_back(true);

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
		}
	}
	else
	{
		for (int i = 0; i < number_choice_rune; i++)
		{
			if (i != 0 && rect_rune[i].getGlobalBounds().contains(mouse_position))
			{
				std::vector<sf::String> listString;
				std::vector<int> listLetterSize;
				std::vector<bool> listIfCentered;

				listString.push_back(listAllSkill[rune_skill_related]->GetStringRuneBonus(i-1));
				listLetterSize.push_back(16);
				listIfCentered.push_back(true);

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
			if (i == 0 && rect_rune[i].getGlobalBounds().contains(mouse_position))
			{
				std::vector<sf::String> listString;
				std::vector<int> listLetterSize;
				std::vector<bool> listIfCentered;

				listString.push_back("No Rune");
				listLetterSize.push_back(16);
				listIfCentered.push_back(true);

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
		}
	}
}

void SkillInterface::GenerateTextBox(int skill_displaying, sf::Vector2f mouse_position, int skill_level, int class_player)
{
	if (skill_displaying <= listAllSkill.size())
	{
		std::vector<sf::String> listString;
		std::vector<int> listLetterSize;
		std::vector<bool> listIfCentered;
		sf::String long_string;
		/*for (size_t i = 0; i < listAllSkill[skill_displaying]->GetNumberStringSkillInformation(); i++)
		{
			listString.push_back(listAllSkill[skill_displaying]->GetStringSkillInformation(i));
			listLetterSize.push_back(16);
			if(i == 0)
			{
				listIfCentered.push_back(true);
			}
			else
			{
				listIfCentered.push_back(false);
			}

		}*/
		listAllSkill[skill_displaying]->ChangeSkillLevel(skill_level, 0, class_player,NoRune_E);
		listString.push_back(listAllSkill[skill_displaying]->GetStringSkillInformation(0));
		listLetterSize.push_back(20);
		listIfCentered.push_back(true);

		for (int i = 1; i < listAllSkill[skill_displaying]->GetNumberStringSkillInformation(); i++)
		{
			long_string += listAllSkill[skill_displaying]->GetStringSkillInformation(i);
		}

		listString.push_back(long_string);
		listLetterSize.push_back(16);
		listIfCentered.push_back(false);

		if (language == English_E)
		{
			listString.push_back(sf::String("<Right click on the skill to switch the rune.>"));
			listLetterSize.push_back(16);
			listIfCentered.push_back(false);
		}
		else
		{
			listString.push_back(sf::String("<Faites un clique droit sur le sort pour changer la rune.>"));
			listLetterSize.push_back(16);
			listIfCentered.push_back(false);
		}

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
}

void SkillInterface::UpdatePlayerNumberFragments(std::shared_ptr<Player> player)
{
	player_number_fragments = player->GetPlayerNumberFragments();
	for (int number = 0; number < number_different_fragment_type; number++)
	{
		string_number_fragment[number].clear();
		string_number_fragment[number].insert(string_number_fragment[number].getSize(), GlobalFunction::GetTypeFragment(number));
		string_number_fragment[number] = GlobalFunction::InsertNumberToString(string_number_fragment[number], player_number_fragments[number], string_number_fragment[number].getSize());
		text_number_fragment[number].setString(string_number_fragment[number]);
	}
}

void SkillInterface::UpdatePlayerSkillLevel(std::shared_ptr<Player> player)
{
	player_skills_level_array = player->GetPlayerSkillLevelArray();
	player_skills_level_increasement = player->GetPlayerSkillLevelIncreasement();
	for(int number = 0; number < number_skill; number++)
	{
		if (player_skills_level_increasement[number] > 0)
		{
			string_skill_level[number].clear();
			string_skill_level[number] = GlobalFunction::InsertNumberToString(string_skill_level[number], player_skills_level_array[number] + player_skills_level_increasement[number], string_skill_level[number].getSize());
			string_skill_level[number].insert(string_skill_level[number].getSize(), sf::String(" ("));
			string_skill_level[number] = GlobalFunction::InsertNumberToString(string_skill_level[number], player_skills_level_increasement[number], string_skill_level[number].getSize());
			string_skill_level[number].insert(string_skill_level[number].getSize(), sf::String(")"));
			text_skill_level[number].setString(string_skill_level[number]);
			text_skill_level[number].setFillColor(sf::Color::Color(12, 200, 62));
		}
		else
		{
			string_skill_level[number].clear();
			string_skill_level[number] = GlobalFunction::InsertNumberToString(string_skill_level[number], player_skills_level_array[number], string_skill_level[number].getSize());
			text_skill_level[number].setString(string_skill_level[number]);
			text_skill_level[number].setFillColor(sf::Color::White);
		}
	}
}

void SkillInterface::UpdateSkillInterfacePosition(sf::Vector2f position_view_player)
{
	skill_interface_rectangle.setPosition(skill_interface_position + position_view_player);
	sprite_second_interface_rectangle.setPosition(position_initial_second_rectangle + position_view_player);

	rectangle_fragment_interface.setPosition(position_fragment_interface.x + position_view_player.x, position_fragment_interface.y + position_view_player.y);
	sf::Vector2f rectangle_fragment_interface_position_holder = rectangle_fragment_interface.getPosition();
	text_fragment_interface_name.setPosition(rectangle_fragment_interface_position_holder.x + size_fragment_interface.x / 2, rectangle_fragment_interface_position_holder.y + text_fragment_interface_name.getGlobalBounds().height * 2 - 30);

	for (int number = 0; number < number_skill; number++)
	{
		if (number == 49)
		{
			rectangle_skill_icone[number].setColor(sf::Color::Color(255, 255, 255, 255));
		}
		rectangle_skill_icone[number].setPosition(sf::Vector2f(position_view_player.x + position_skill_icone[number].x, position_view_player.y + position_skill_icone[number].y));
		if (number < listAllSkill.size())
		{
			sprite_skill_icone[number].setPosition(sf::Vector2f(position_view_player.x + position_skill_icone[number].x, position_view_player.y + position_skill_icone[number].y));
		}

		if (number < number_skill_player)
		{
			rectangle_skill_icone_player[number].setPosition(sf::Vector2f(position_view_player.x + position_skill_icone_player[number].x, position_view_player.y + position_skill_icone_player[number].y));
			if (player_skill_icone_created[number])
			{
				sprite_skill_icone_player[number].setPosition(sf::Vector2f(position_view_player.x + position_skill_icone_player[number].x, position_view_player.y + position_skill_icone_player[number].y));
			}
			if (number >= listAllArmors[number_current_armor]->ReturnArmorNumberSkills())
			{
				rectangle_skill_icone_player[number].setColor(sf::Color::Color(255, 255, 255, 150));
			}
			else if (!(slot_changing == number) && number < listAllArmors[number_current_armor]->ReturnArmorNumberSkills())
			{
				rectangle_skill_icone_player[number].setColor(sf::Color::Color(255, 255, 255, 255));
			}
		}
		if (number < number_different_fragment_type)
		{
			text_number_fragment[number].setPosition(sf::Vector2f(position_number_fragment[number].x + position_view_player.x, position_number_fragment[number].y + position_view_player.y));
		}
		text_skill_level[number].setPosition(sf::Vector2f(position_view_player.x + position_skill_level[number].x, position_view_player.y + position_skill_level[number].y));
		sprite_upgrade_skill_level[number].setPosition(sf::Vector2f(position_view_player.x + position_upgrade_skill_level[number].x, position_view_player.y + position_upgrade_skill_level[number].y));
	}

	sprite_erase_skill.setPosition(position_erase_skill + position_view_player);
}

void SkillInterface::UpdatePlayerSkill(std::shared_ptr<Player> player)
{
	player_skills_array = player->GetPlayerSkillArray();
	UpdateSkillInterfacePlayerSkill();
}

void SkillInterface::UpdateSkillInterfacePlayerSkill()
{
	for (int number = 0; number < player_skills_array.size(); number++)
	{
		if (!(player_skills_array[number] == -1))
		{
			texture_skill_icone_player[number] = listAllSkill[player_skills_array[number]]->ReturnSkillIconeTexture();
			sprite_skill_icone_player[number].setTexture(texture_skill_icone_player[number]);
			player_skill_icone_created[number] = true;
		}
	}
}

void SkillInterface::NewPlayerCurrentArmor(std::shared_ptr<Player> player)
{
	number_current_armor = player->GetPlayerCurrentArmor();
}

void SkillInterface::GiveBackPlayerNewInformation(std::shared_ptr<Player> player)
{
	player->NewPlayerSkillArray(player_skills_array);
	player->NewPlayerSkillLevel(player_skills_level_array);
	player->NewPlayerNumberFragments(player_number_fragments);
}

void SkillInterface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];
	texture_fragment = ListTextureInterface3[style];
	texture_rune_interface = ListTextureInterface2[style];

	rune_interface.setTexture(texture_rune_interface);
	skill_interface_rectangle.setTexture(texture_interface);
	rectangle_fragment_interface.setTexture(texture_fragment);
}

