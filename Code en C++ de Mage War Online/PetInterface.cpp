#include "stdafx.h"
#include "PetInterface.h"

PetInterface::PetInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font  class menu interface" << std::endl;
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("PetInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("PetInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
#pragma endregion TextureInterfaceLoading

	if (!texture_locked.loadFromFile("LockedIconeLight.png"))
	{
		std::cout << "Error while loading interface pet locked icone texture" << std::endl;
	}

	if (!texture_pet_animation.loadFromFile("PetAnimation.png"))
	{
		std::cout << "Error while loading interface pet animation texture" << std::endl;
	}

	if (!texture_icone_pet.loadFromFile("PetIcone.png"))
	{
		std::cout << "Error while loading interface pet icone texture" << std::endl;
	}
	if (!texture_summoned.loadFromFile("IconeSummoned.png"))
	{
		std::cout << "Error while loading interface pet icone summoned texture" << std::endl;
	}

	interface_pet = GlobalFunction::CreateSpriteWithoutOrigin(position_interface, size_interface, texture_interface);

	if (language == English_E)
	{
		text_release = GlobalFunction::CreateText(position_text_release, "Release", font, 17);
		text_summon = GlobalFunction::CreateText(position_text_summon, "Summon", font, 17);
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Pet", font, 36);
	}
	else
	{
		text_release = GlobalFunction::CreateText(position_text_release, "Relâcher", font, 17);
		text_summon = GlobalFunction::CreateText(position_text_summon, "Invoquer", font, 17);
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Familier", font, 36);
	}
	text_name_interface.setFillColor(sf::Color::Color(108, 129, 197));

	sf::Vector2i counter(0, 0);
	for (int i = 0; i < number_maximum_pet; i++)
	{
		position_icone[i] = sf::Vector2f(size_icone.x*counter.x + 10* counter.x, size_icone.y*counter.y + 10 * counter.y) + position_interface + position_first_icone;
		sprite_icone_pet[i] = GlobalFunction::CreateSpriteWithoutOrigin(position_icone[i], size_icone, texture_icone_pet);
		counter.x++;
		if (counter.x == 2)
		{
			counter.x = 0;
			counter.y++;
		}
	}

	for (int i = 0; i < number_pet_attributes; i++)
	{
		position_text_attribute[i] = sf::Vector2f(0,distance_between_text_attribute*i) + position_first_text_attribute + position_interface;
		text_attributes[i] = GlobalFunction::CreateText(position_text_attribute[i], "Attribute", font, 14);

		position_rect_up[i] = sf::Vector2f(0, distance_between_rect_up*i) + position_first_rect_up + position_interface;
		rect_up_attribute[i] = GlobalFunction::CreateRectangle(size_rect_up, position_rect_up[i]);
	}

	sf::Vector2i counter2{ 0,0 };
	for (int i = 0; i < number_abilities_available; i++)
	{
		position_text_ability[i] = sf::Vector2f(145* counter2.x, 44* counter2.y) + position_first_text_ability + position_interface;
		text_ability[i] = GlobalFunction::CreateText(position_text_ability[i], "Ability", font, 13);

		position_rect_ability[i] = sf::Vector2f(145 * counter2.x, 44 * counter2.y) + position_first_rect_ability + position_interface;
		rect_ability[i] = GlobalFunction::CreateRectangle(size_rect_ability, position_rect_ability[i]);
		rect_ability[i].setFillColor(sf::Color::Color(0, 0, 0, 150));

		position_locked[i] = position_rect_ability[i];// +sf::Vector2f(size_rect_ability.x / 2, size_rect_ability.y / 2);
		sprite_locked[i] = GlobalFunction::CreateSprite(position_locked[i], size_locked, texture_locked);
		//sprite_locked[i].setColor(sf::Color::Color(255, 255, 255, 150));

		counter2.y++;
		if (counter2.y == 5)
		{
			counter2.y = 0;
			counter2.x++;
		}

		can_draw_locked[i] = true;
		can_draw_rect_ability[i] = true;
	}

	text_attributes_pts_left = GlobalFunction::CreateText(position_text_attribute_pts_left, "Attribute Left", font, 16);
	rect_exp_bar = GlobalFunction::CreateRectangle(size_exp_bar, position_rect_exp_bar);
	rect_exp_bar.setFillColor(sf::Color::Green);
	rect_full_exp_bar = GlobalFunction::CreateRectangle(size_exp_bar, position_rect_exp_bar);
	rect_full_exp_bar.setFillColor(sf::Color::Green);
	sprite_pet_animation = GlobalFunction::CreateSpriteWithoutOrigin(position_pet_animation, size_pet_animation, texture_pet_animation);
	text_level = GlobalFunction::CreateText(position_text_level, "Level 0 ", font, 20);
	sprite_summoned = GlobalFunction::CreateSpriteWithoutOrigin(sf::Vector2f(0, 0), size_icone, texture_summoned);

	CreateListStrings();
}

PetInterface::~PetInterface()
{
}

void PetInterface::Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	std::vector<std::shared_ptr<PetBase>> listAllPets = player->GetListPets();
	number_player_current_pets = listAllPets.size();
	if (current_pet_checking != -1 && current_pet_checking < listAllPets.size())
	{
		current_pet.reset();
		current_pet = listAllPets[current_pet_checking];
	}
	else
	{
		current_pet.reset();
	}

#pragma region RelatedToAttributes

	if (current_pet != NULL)
	{
		std::vector<int> PetAttributes = current_pet->GetPetAttributes();
		std::vector<int> PetMaxAttributes = current_pet->GetPetMaxAttributes();
		int level_pet = current_pet->GetLevelPet();
		float points_left = level_pet * 2 - PetAttributes[0] - PetAttributes[1] - PetAttributes[2] - PetAttributes[3];
		sf::Vector2f pet_exp_expneeeded = current_pet->GetExpPet();
		rect_exp_bar.setSize(sf::Vector2f(size_exp_bar.x*pet_exp_expneeeded.x/ pet_exp_expneeeded.y, size_exp_bar.y));

		if (language == English_E)
		{
			sf::String str_pts_left = "Points left : ";
			str_pts_left = GlobalFunction::InsertNumberToString(str_pts_left, points_left, str_pts_left.getSize());
			text_attributes_pts_left.setString(str_pts_left);

			sf::String str_lvl = "Level ";
			str_lvl = GlobalFunction::InsertNumberToString(str_lvl, level_pet, str_lvl.getSize());
			text_level.setString(str_lvl);

			if (true)
			{
				sf::String str = "POW ";
				str = GlobalFunction::InsertNumberToString(str, PetAttributes[Power_E], str.getSize());
				str.insert(str.getSize(), "/");
				str = GlobalFunction::InsertNumberToString(str, PetMaxAttributes[Power_E], str.getSize());
				text_attributes[Power_E].setString(str);
			}

			if (true)
			{
				sf::String str = "WIS ";
				str = GlobalFunction::InsertNumberToString(str, PetAttributes[Wisdom_E], str.getSize());
				str.insert(str.getSize(), "/");
				str = GlobalFunction::InsertNumberToString(str, PetMaxAttributes[Wisdom_E], str.getSize());
				text_attributes[Wisdom_E].setString(str);
			}

			if (true)
			{
				sf::String str = "INT ";
				str = GlobalFunction::InsertNumberToString(str, PetAttributes[Intelligence_E], str.getSize());
				str.insert(str.getSize(), "/");
				str = GlobalFunction::InsertNumberToString(str, PetMaxAttributes[Intelligence_E], str.getSize());
				text_attributes[Intelligence_E].setString(str);
			}

			if (true)
			{
				sf::String str = "SPD ";
				str = GlobalFunction::InsertNumberToString(str, PetAttributes[Speed_E], str.getSize());
				str.insert(str.getSize(), "/");
				str = GlobalFunction::InsertNumberToString(str, PetMaxAttributes[Speed_E], str.getSize());
				text_attributes[Speed_E].setString(str);
			}
		}
		else
		{
			sf::String str_pts_left = "Points restant : ";
			str_pts_left = GlobalFunction::InsertNumberToString(str_pts_left, points_left, str_pts_left.getSize());
			text_attributes_pts_left.setString(str_pts_left);

			sf::String str_lvl = "Niveau ";
			str_lvl = GlobalFunction::InsertNumberToString(str_lvl, level_pet, str_lvl.getSize());
			text_level.setString(str_lvl);

			if (true)
			{
				sf::String str = "FOR	";
				str = GlobalFunction::InsertNumberToString(str, PetAttributes[Power_E], str.getSize());
				str.insert(str.getSize(), "/");
				str = GlobalFunction::InsertNumberToString(str, PetMaxAttributes[Power_E], str.getSize());
				text_attributes[Power_E].setString(str);
			}

			if (true)
			{
				sf::String str = "SAG	";
				str = GlobalFunction::InsertNumberToString(str, PetAttributes[Wisdom_E], str.getSize());
				str.insert(str.getSize(), "/");
				str = GlobalFunction::InsertNumberToString(str, PetMaxAttributes[Wisdom_E], str.getSize());
				text_attributes[Wisdom_E].setString(str);
			}

			if (true)
			{
				sf::String str = "INT	";
				str = GlobalFunction::InsertNumberToString(str, PetAttributes[Intelligence_E], str.getSize());
				str.insert(str.getSize(), "/");
				str = GlobalFunction::InsertNumberToString(str, PetMaxAttributes[Intelligence_E], str.getSize());
				text_attributes[Intelligence_E].setString(str);
			}

			if (true)
			{
				sf::String str = "AGI	";
				str = GlobalFunction::InsertNumberToString(str, PetAttributes[Speed_E], str.getSize());
				str.insert(str.getSize(), "/");
				str = GlobalFunction::InsertNumberToString(str, PetMaxAttributes[Speed_E], str.getSize());
				text_attributes[Speed_E].setString(str);
			}
		}
	}
	else
	{
		if (language == English_E)
		{
			sf::String str_pts_left = "Points left : ";
			text_attributes_pts_left.setString(str_pts_left);

			sf::String str_lvl = "Level ";
			text_level.setString(str_lvl);

			if (true)
			{
				sf::String str = "POW ";
				text_attributes[Power_E].setString(str);
			}

			if (true)
			{
				sf::String str = "WIS ";
				text_attributes[Wisdom_E].setString(str);
			}

			if (true)
			{
				sf::String str = "INT ";
				text_attributes[Intelligence_E].setString(str);
			}

			if (true)
			{
				sf::String str = "SPD ";
				text_attributes[Speed_E].setString(str);
			}
		}
		else
		{
			sf::String str_pts_left = "Points restant : ";
			text_attributes_pts_left.setString(str_pts_left);

			sf::String str_lvl = "Niveau ";
			text_level.setString(str_lvl);

			if (true)
			{
				sf::String str = "FOR	";
				text_attributes[Power_E].setString(str);
			}

			if (true)
			{
				sf::String str = "SAG	";
				text_attributes[Wisdom_E].setString(str);
			}

			if (true)
			{
				sf::String str = "INT	";
				text_attributes[Intelligence_E].setString(str);
			}

			if (true)
			{
				sf::String str = "AGI	";
				text_attributes[Speed_E].setString(str);
			}
		}
	}

#pragma endregion RelatedToAttributes

#pragma region PetIcones

	int player_current_pet_id = player->GetCurrentIdPet();
	current_pet_summoned = -1;
	for (int i = 0; i < listAllPets.size(); i++)
	{
		if (listAllPets[i]->GetPetId() == player_current_pet_id)
		{
			current_pet_summoned = i;
		}
		sprite_icone_pet[i].setTextureRect(sf::IntRect(size_icone.x*listAllPets[i]->GetTypePet(), 0, size_icone.x, size_icone.y));
	}
	if (current_pet_summoned != -1)
	{
		position_icone_summoned = position_icone[current_pet_summoned];
	}
	else
	{
		position_icone_summoned = sf::Vector2f(-1000, -1000);
	}
	listAllPets.clear();

	CreateRectangleInformation(mouse_position);
	CheckPlayerAction(player, mouse_position);

#pragma endregion PetIcones

#pragma region Abilities

	if (current_pet != NULL)
	{
		std::vector <sf::String>  listStringNameAbilites = current_pet->GetStringAbilityName();
		std::vector <sf::String>  listStringDescriptionAbilities = current_pet->GetStringAbilityDescription();
		std::vector<sf::Vector2i>  listPetSkillPossible = current_pet->GetAbitliesPossible();
		std::vector<int>  listPetSkillObtained = current_pet->GetAbitliesObtained();
		int level_pet = current_pet->GetLevelPet();

		for (int i = 0; i < 5; i++)
		{
			if (listPetSkillObtained[i] == 0)
			{
				can_draw_rect_ability[i + 5] = true;
				can_draw_rect_ability[i] = false;
			}
			else if (listPetSkillObtained[i] == 1)
			{
				can_draw_rect_ability[i] = true;
				can_draw_rect_ability[i + 5] = false;
			}
			else
			{
				can_draw_rect_ability[i] = true;
				can_draw_rect_ability[i + 5] = true;
			}

			text_ability[i].setString(listStringNameAbilites[listPetSkillPossible[i].x]);
			text_ability[i].setOrigin(text_ability[i].getGlobalBounds().width / 2, text_ability[i].getGlobalBounds().height / 2);
			text_ability[i + 5].setString(listStringNameAbilites[listPetSkillPossible[i].y]);
			text_ability[i + 5].setOrigin(text_ability[i + 5].getGlobalBounds().width / 2, text_ability[i].getGlobalBounds().height / 2);

			if (level_pet >= i * 5)
			{
				can_draw_locked[i] = false;
				can_draw_locked[i + 5] = false;
			}
			else
			{
				can_draw_locked[i] = true;
				can_draw_locked[i + 5] = true;
			}
		}
	}

#pragma endregion Abilities
}

void PetInterface::CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	if (clock_click.getElapsedTime().asSeconds() >= 0.5)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (current_pet != NULL)
			{
				std::vector<int> PetAttributes = current_pet->GetPetAttributes();
				std::vector<int> PetMaxAttributes = current_pet->GetPetMaxAttributes();
				int level_pet = current_pet->GetLevelPet();
				float points_left = level_pet * 2 - PetAttributes[0] - PetAttributes[1] - PetAttributes[2] - PetAttributes[3];

				if (points_left > 0)
				{
					for (int i = 0; i < number_pet_attributes; i++)
					{
						if (rect_up_attribute[i].getGlobalBounds().contains(mouse_position) && PetAttributes[i] < PetMaxAttributes[i])
						{
							PetAttributes[i]++;
							clock_click.restart();
							SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
						}
					}
				}

				current_pet->GetNewPetAttributes(PetAttributes);

				std::vector<sf::Vector2i>  listPetSkillPossible = current_pet->GetAbitliesPossible();
				std::vector<int>  listPetSkillObtained = current_pet->GetAbitliesObtained();

				for (int i = 0; i < 5; i++)
				{
					if (!can_draw_locked[i] && listPetSkillObtained[i] == -1)
					{
						if (rect_ability[i].getGlobalBounds().contains(mouse_position))
						{
							current_pet->SelectAbility(i, 0);
							SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
						}
						else if (rect_ability[i+5].getGlobalBounds().contains(mouse_position))
						{
							current_pet->SelectAbility(i, 1);
							SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
						}
					}
				}
			}

			std::vector<std::shared_ptr<PetBase>> listAllPets = player->GetListPets();
			for (int i = 0; i < listAllPets.size(); i++)
			{
				if (sprite_icone_pet[i].getGlobalBounds().contains(mouse_position))
				{
					current_pet_checking = i;
					clock_click.restart();
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				}
			}
			listAllPets.clear();

			if (text_summon.getGlobalBounds().contains(mouse_position))
			{
				if (current_pet_checking == current_pet_summoned)
				{
					player->ResetCurrentPet();
				}
				else
				{
					player->ChangeCurrentPet(current_pet_checking);
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				clock_click.restart();
			}
			else if (text_release.getGlobalBounds().contains(mouse_position))
			{
				if (current_pet_checking == current_pet_summoned)
				{
					player->ResetCurrentPet();
					player->DeleteAPet(current_pet_checking);
				}
				else
				{
					player->DeleteAPet(current_pet_checking);
				}
				SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				clock_click.restart();
			}
		}
	}
}

void PetInterface::Draw(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	interface_pet.setPosition(position_view_player + position_interface);
	text_name_interface.setPosition(position_view_player + position_name_interface);
	rect_exp_bar.setPosition(position_view_player + position_rect_exp_bar);
	rect_full_exp_bar.setPosition(position_view_player + position_rect_exp_bar);
	sprite_pet_animation.setPosition(position_view_player + position_pet_animation);
	text_attributes_pts_left.setPosition(position_view_player + position_text_attribute_pts_left);
	text_level.setPosition(position_view_player + position_text_level);
	text_release.setPosition(position_view_player + position_text_release);
	text_summon.setPosition(position_view_player + position_text_summon);

	window.draw(interface_pet);
	window.draw(text_name_interface);
	window.draw(rect_exp_bar);
	window.draw(text_level);
	window.draw(text_release);
	window.draw(text_summon);
	window.draw(text_attributes_pts_left);

	for (int i = 0; i < number_player_current_pets; i++)
	{
		sprite_icone_pet[i].setPosition(position_view_player + position_icone[i]);
		window.draw(sprite_icone_pet[i]);
	}

	for (int i = 0; i < number_pet_attributes; i++)
	{
		rect_up_attribute[i].setPosition(position_view_player + position_rect_up[i]);

		text_attributes[i].setPosition(position_view_player + position_text_attribute[i]);
		window.draw(text_attributes[i]);
	}

	for (int i = 0; i < number_abilities_available; i++)
	{
		text_ability[i].setPosition(position_view_player + position_text_ability[i]);
		window.draw(text_ability[i]);

		rect_ability[i].setPosition(position_view_player + position_rect_ability[i]);
		if (can_draw_rect_ability[i])
		{
			window.draw(rect_ability[i]);
		}

		sprite_locked[i].setPosition(position_view_player + position_locked[i]);
		if (can_draw_locked[i])
		{
			window.draw(sprite_locked[i]);
		}
	}

	if (current_pet != NULL)
	{
		sprite_summoned.setPosition(position_view_player + position_icone_summoned);
		window.draw(sprite_summoned);

		if (clock_animation.getElapsedTime().asSeconds() >= timer_animation)
		{
			if (source == 4)
			{
				source = 0;
				timer_animation = 0.2;
			}
			sprite_pet_animation.setTextureRect(sf::IntRect(size_pet_animation.x*source, size_pet_animation.y*current_pet->GetTypePet(), size_pet_animation.x, size_pet_animation.y));
			source++;
			if (source == 4)
			{
				timer_animation = 2.5;
			}
			clock_animation.restart();
		}
		window.draw(sprite_pet_animation);
	}
}

void PetInterface::CreateRectangleInformation(sf::Vector2f mouse_position)
{
	for (int i = 0; i < number_pet_attributes; i++)
	{
		if (text_attributes[i].getGlobalBounds().contains(mouse_position))
		{
			std::vector<int> listLetterSize;
			std::vector<sf::String> listString;
			std::vector<bool> listIfCentered;

			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listString.push_back(listStringAttributesPet[i]);

			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
		}
	}

	if (rect_full_exp_bar.getGlobalBounds().contains(mouse_position))
	{
		if (current_pet != NULL)
		{
			sf::Vector2f pet_exp_expneeeded = current_pet->GetExpPet();

			std::vector<int> listLetterSize;
			std::vector<sf::String> listString;
			std::vector<bool> listIfCentered;

			sf::String str;
			str = GlobalFunction::InsertNumberToString(str, pet_exp_expneeeded.x, str.getSize());
			str.insert(str.getSize(), " / ");
			str = GlobalFunction::InsertNumberToString(str, pet_exp_expneeeded.y, str.getSize());
			if (language == English_E)
			{
				str.insert(str.getSize(), " experience points.");
			}
			else
			{
				str.insert(str.getSize(), " points d'experience.");
			}

			listLetterSize.push_back(16);
			listIfCentered.push_back(true);
			listString.push_back(str);

			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
		}
	}

	if (current_pet != NULL)
	{
		std::vector <sf::String>  listStringDescriptionAbilities = current_pet->GetStringAbilityDescription();
		std::vector<sf::Vector2i>  listPetSkillPossible = current_pet->GetAbitliesPossible();

		for (int i = 0; i < 5; i++)
		{
			if (rect_ability[i].getGlobalBounds().contains(mouse_position))
			{
				std::vector<int> listLetterSize;
				std::vector<sf::String> listString;
				std::vector<bool> listIfCentered;

				listLetterSize.push_back(16);
				listIfCentered.push_back(true);
				listString.push_back(listStringDescriptionAbilities[listPetSkillPossible[i].x]);

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
			else if (rect_ability[i + 5].getGlobalBounds().contains(mouse_position))
			{
				std::vector<int> listLetterSize;
				std::vector<sf::String> listString;
				std::vector<bool> listIfCentered;

				listLetterSize.push_back(16);
				listIfCentered.push_back(true);
				listString.push_back(listStringDescriptionAbilities[listPetSkillPossible[i].y]);

				TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
			}
		}
	}
}

void PetInterface::CreateListStrings()
{
	if (language == English_E)
	{
		if (true)
		{
			sf::String string_att = "POW (power) increase the value of the pet's abilities by 5% for each point.";
			listStringAttributesPet.push_back(string_att);
		}
		if (true)
		{
			sf::String string_att = "WIS (wisdom) reduce the level required to summon the pet by 1 for each point. Also reduce the pet's cooldown by 0.25 second for each point.";
			listStringAttributesPet.push_back(string_att);
		}
		if (true)
		{
			sf::String string_att = "INT (intelligence) increase the precision of pet's abilities.";
			listStringAttributesPet.push_back(string_att);
		}
		if (true)
		{
			sf::String string_att = "SPD (speed) increase the movement speed of the pet by 10% for each point.";
			listStringAttributesPet.push_back(string_att);
		}
	}
	else
	{ 
		if (true)
		{
			sf::String string_att = "FOR (force) augmente la valeur des habiletés du familer de 5% par point investi.";
			listStringAttributesPet.push_back(string_att);
		}
		if (true)
		{
			sf::String string_att = "SAG (sagesse) diminue le niveau requis pour invoquer le familier de 1 par point investi. Réduit aussi le temps de latence du familier de 0.25 seconde par point investi.";
			listStringAttributesPet.push_back(string_att);
		}
		if (true)
		{
			sf::String string_att = "INT (intelligence) augmente la précision des habiletés du familier.";
			listStringAttributesPet.push_back(string_att);
		}
		if (true)
		{
			sf::String string_att = "AGI (agileté) augmente la vitesse de déplacement du familier de 10% par point investi.";
			listStringAttributesPet.push_back(string_att);
		}
	}
}

void PetInterface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];
	interface_pet.setTexture(texture_interface);
}
