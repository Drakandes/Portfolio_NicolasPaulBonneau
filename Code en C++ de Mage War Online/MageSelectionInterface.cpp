#include "stdafx.h"
#include "MageSelectionInterface.h"

MageSelectionInterface::MageSelectionInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font crafting interface" << std::endl;
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("MageSelectionInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("MageSelectionInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
#pragma endregion TextureInterfaceLoading

	if (!texture_erase_skill.loadFromFile("Sprite_erase_skill.png"))
	{
		std::cout << "Error with texture erase skill interface" << std::endl;
	}

	for (int i = 0; i < number_interface; i++)
	{
		position_interface[i] = sf::Vector2f(position_first_interface.x + size_interface.x*i + distance_between_interfaces*i, position_first_interface.y);
		interface_mage_selection[i] = GlobalFunction::CreateSpriteWithoutOrigin(position_interface[i], size_interface, texture_interface);

		position_name_interface[i] = position_first_name_interface + position_interface[i];
		text_name_interface[i] = GlobalFunction::CreateText(position_name_interface[i], "Name", font, 28);
		text_name_interface[i].setFillColor(sf::Color::Color(108, 129, 197));
		text_name_interface[i].setStyle(sf::Text::Bold);

		position_sprite_cancel[i] = position_first_sprite_cancel + position_interface[i];
		sprite_cancel[i] = GlobalFunction::CreateSprite(position_sprite_cancel[i], size_sprite_cancel, texture_erase_skill);

		for (int ii = 0; ii < 4; ii++)
		{
			position_text_attributes[i][ii] = sf::Vector2f(0, distance_between_text_attributes*ii ) + position_interface[i] + position_first_text_attributes;
			if (language == English_E)
			{
				text_attributes[i][ii] = GlobalFunction::CreateText(position_text_attributes[i][ii], "Attribute", font, 20);
			}
			else
			{
				text_attributes[i][ii] = GlobalFunction::CreateText(position_text_attributes[i][ii], "Attribute", font, 18);
			}
		}

		for (int ii = 0; ii < ListObjectsSingleton::instance()->number_characteristic; ii++)
		{
			ListCharacteristicMages[i].push_back(false);
			ListCharacteristicProsOrCons[i].push_back(0);
		}

		for (int ii = 0; ii < ListObjectsSingleton::instance()->number_drawback; ii++)
		{
			ListDrawbackMages[i].push_back(false);
		}
	}

	position_text_without_mage.x = position_interface[3].x;
	text_without_mage = GlobalFunction::CreateText(position_text_without_mage, "Start Without Mage Selection", font, 26);

	ListCharacteristicPros = ListObjectsSingleton::instance()->ListCharacteristicPros;
	ListCharacteristicCons = ListObjectsSingleton::instance()->ListCharacteristicCons;
	ListCharacteristicValue = ListObjectsSingleton::instance()->ListCharacteristicValue;
	ListDrawback = ListObjectsSingleton::instance()->ListDrawback;
	CreateListStringAttributeDescriptions();
	GetNewFiveMages();
}

MageSelectionInterface::~MageSelectionInterface()
{
}

void MageSelectionInterface::Draw(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	for (int i = 0; i < number_interface; i++)
	{
		if (displaying_interface[i])
		{
			text_name_interface[i].setPosition(position_view_player + position_name_interface[i]);
			interface_mage_selection[i].setPosition(position_view_player + position_interface[i]);
			sprite_cancel[i].setPosition(position_view_player + position_sprite_cancel[i]);

			window.draw(interface_mage_selection[i]);
			window.draw(text_name_interface[i]);
			window.draw(sprite_cancel[i]);

			for (int ii = 0; ii < 1 + number_interface_disabled; ii++)
			{
				text_attributes[i][ii].setPosition(position_view_player + position_text_attributes[i][ii]);
				window.draw(text_attributes[i][ii]);
			}
		}
	}

	if (number_interface_disabled <= 2)
	{
		text_without_mage.setPosition(position_view_player + position_text_without_mage);
		window.draw(text_without_mage);
	}
}

void MageSelectionInterface::Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	for (int i = 0; i < number_interface; i++)
	{
		if (displaying_interface[i])
		{
			text_attributes[i][0].setString(ListCharacteristicPros[ListCharacteristicGotten[i][0]]);
			text_attributes[i][0].setOrigin(text_attributes[i][0].getGlobalBounds().width / 2, text_attributes[i][0].getGlobalBounds().height / 2);
			text_attributes[i][1].setString(ListCharacteristicCons[ListCharacteristicGotten[i][1]]);
			text_attributes[i][1].setOrigin(text_attributes[i][1].getGlobalBounds().width / 2, text_attributes[i][1].getGlobalBounds().height / 2);
			text_attributes[i][2].setString(ListCharacteristicPros[ListCharacteristicGotten[i][2]]);
			text_attributes[i][2].setOrigin(text_attributes[i][2].getGlobalBounds().width / 2, text_attributes[i][2].getGlobalBounds().height / 2);
			text_attributes[i][3].setString(ListDrawback[drawback_gotten[i]]);
			text_attributes[i][3].setOrigin(text_attributes[i][3].getGlobalBounds().width / 2, text_attributes[i][3].getGlobalBounds().height / 2);
		}
	}

	CheckPlayerAction(player,mouse_position);
	CreateRectangleInformation(mouse_position);
}

void MageSelectionInterface::CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	if (clock_click.getElapsedTime().asSeconds() >= 0.5)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (int i = 0; i < number_interface; i++)
			{
				if (sprite_cancel[i].getGlobalBounds().contains(mouse_position))
				{
					displaying_interface[i] = false;
					number_interface_disabled++;
					clock_click.restart();
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);

					if (number_interface_disabled == 4)
					{
						int mage_selected;
						for (int ii = 0; ii < number_interface; ii++)
						{
							if (displaying_interface[ii])
							{
								mage_selected = ii;
								break;
							}
						}
						player->GivePlayerNewCharacteristic(ListCharacteristicMages[mage_selected], ListCharacteristicProsOrCons[mage_selected], ListDrawbackMages[mage_selected], ListNameMage[name_gotten[mage_selected]]);
						for (int ii = 0; ii < number_interface; ii++)
						{
							ListCharacteristicGotten[ii].clear();
							number_interface_disabled = 0;
							displaying_interface[ii] = true;
						}

						for (int ii = 0; ii < ListObjectsSingleton::instance()->number_characteristic; ii++)
						{
							ListCharacteristicMages[i].push_back(false);
							ListCharacteristicProsOrCons[i].push_back(0);
						}

						for (int ii = 0; ii < ListObjectsSingleton::instance()->number_drawback; ii++)
						{
							ListDrawbackMages[i].push_back(false);
						}

						GetNewFiveMages();

						SpawnPointGestion::instance()->PlayerRespawnGestion();
					}
				}
			}

			if (number_interface_disabled <= 2)
			{
				if (text_without_mage.getGlobalBounds().contains(mouse_position))
				{
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
					for (int i = 0; i < number_interface; i++)
					{
						for (int ii = 0; ii < number_interface; ii++)
						{
							ListCharacteristicGotten[ii].clear();
							number_interface_disabled = 0;
							displaying_interface[ii] = true;
						}

						ListCharacteristicMages[i].clear();
						ListCharacteristicProsOrCons[i].clear();
						for (int ii = 0; ii < ListObjectsSingleton::instance()->number_characteristic; ii++)
						{
							ListCharacteristicMages[i].push_back(false);
							ListCharacteristicProsOrCons[i].push_back(0);
						}

						ListDrawbackMages[i].clear();
						for (int ii = 0; ii < ListObjectsSingleton::instance()->number_drawback; ii++)
						{
							ListDrawbackMages[i].push_back(false);
						}
					}
					player->GivePlayerNewCharacteristic(ListCharacteristicMages[0], ListCharacteristicProsOrCons[0], ListDrawbackMages[0], ListNameMage[name_gotten[0]]);

					GetNewFiveMages();
					SpawnPointGestion::instance()->PlayerRespawnGestion();
				}
			}
		}
	}
}

void MageSelectionInterface::CreateRectangleInformation(sf::Vector2f mouse_position)
{
	for (int i = 0; i < number_interface; i++)
	{
		if (interface_mage_selection[i].getGlobalBounds().contains(mouse_position) && displaying_interface[i])
		{
			for (int ii = 0; ii < 4; ii++)
			{
				if (text_attributes[i][ii].getGlobalBounds().contains(mouse_position))
				{
					if (ii == 0 && 1 + number_interface_disabled >= 1)
					{
						std::vector<sf::String> listString;
						std::vector<int> listLetterSize;
						std::vector<bool> listIfCentered;

						sf::String str1 = ListCharacteristicProsDescription[ListCharacteristicGotten[i][0]];

						listString.push_back(str1);
						listLetterSize.push_back(16);
						listIfCentered.push_back(false);

						TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
					}
					else if (ii == 1 && 1 + number_interface_disabled >= 2)
					{
						std::vector<sf::String> listString;
						std::vector<int> listLetterSize;
						std::vector<bool> listIfCentered;

						sf::String str1 = ListCharacteristicConsDescription[ListCharacteristicGotten[i][1]];

						listString.push_back(str1);
						listLetterSize.push_back(16);
						listIfCentered.push_back(false);

						TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
					}
					else if (ii == 2 && 1 + number_interface_disabled >= 3)
					{
						std::vector<sf::String> listString;
						std::vector<int> listLetterSize;
						std::vector<bool> listIfCentered;

						sf::String str1 = ListCharacteristicProsDescription[ListCharacteristicGotten[i][2]];

						listString.push_back(str1);
						listLetterSize.push_back(16);
						listIfCentered.push_back(false);

						TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
					}
					else if (ii == 3 && 1 + number_interface_disabled >= 4)
					{
						std::vector<sf::String> listString;
						std::vector<int> listLetterSize;
						std::vector<bool> listIfCentered;

						sf::String str1 = ListDrawbackDescription[drawback_gotten[i]];

						listString.push_back(str1);
						listLetterSize.push_back(16);
						listIfCentered.push_back(false);

						TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
					}
				}
			}
		}
		else if (sprite_cancel[i].getGlobalBounds().contains(mouse_position))
		{
			std::vector<sf::String> listString;
			std::vector<int> listLetterSize;
			std::vector<bool> listIfCentered;

			if (language == English_E)
			{
				sf::String str1 = "Refuse to be this mage!";
				listString.push_back(str1);
			}
			else
			{
				sf::String str1 = "Refuser d'être ce mage!";
				listString.push_back(str1);
			}

			listLetterSize.push_back(16);
			listIfCentered.push_back(false);

			TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
		}
	}
}

void MageSelectionInterface::GetNewFiveMages()
{
	int number_characteristic = ListObjectsSingleton::instance()->number_characteristic;
	std::vector<int> listExceptions[number_interface];
	std::vector<int> listExceptionsDrawback;

	for (int i = 0; i < number_interface; i++)
	{
		ListCharacteristicGotten[i].clear();

		int first_char;
		int second_char;
		int third_char;
		int first_drawback;

		int number1 = GlobalFunction::getRandomRange(1, number_characteristic);
		listExceptions[i].push_back(number1);
		first_char = number1 - 1;

		int number2 = GlobalFunction::getRandomRangeWithException(1, number_characteristic, listExceptions[i][0]);
		listExceptions[i].push_back(number2);
		second_char = number2 - 1;

		int number3 = GlobalFunction::getRandomRangeWithUnknownException(1, number_characteristic, listExceptions[i]);
		listExceptions[i].push_back(number3);
		third_char = number3 - 1;

		ListCharacteristicMages[i][first_char] = true;
		ListCharacteristicProsOrCons[i][first_char] = 1;
		ListCharacteristicGotten[i].push_back(first_char);

		ListCharacteristicMages[i][second_char] = true;
		ListCharacteristicProsOrCons[i][second_char] = -1;
		ListCharacteristicGotten[i].push_back(second_char);

		ListCharacteristicMages[i][third_char] = true;
		ListCharacteristicProsOrCons[i][third_char] = 1;
		ListCharacteristicGotten[i].push_back(third_char);

		int number4 = GlobalFunction::getRandomRangeWithUnknownException(1, ListObjectsSingleton::instance()->number_drawback,listExceptionsDrawback);
		listExceptionsDrawback.push_back(number4);
		first_drawback = number4 - 1;

		drawback_gotten[i] = first_drawback;
		ListDrawbackMages[i][first_drawback] = true;
	}

	std::vector<int> ListNameGotten;
	for (int i = 0; i < number_interface; i++)
	{
		int random_number = GlobalFunction::getRandomRangeWithUnknownException(1, 30,ListNameGotten);
		ListNameGotten.push_back(random_number);
		text_name_interface[i].setString(ListNameMage[random_number - 1]);
		text_name_interface[i].setOrigin(text_name_interface[i].getGlobalBounds().width / 2, text_name_interface[i].getGlobalBounds().height / 2);
		name_gotten[i] = random_number - 1;
	}
}

void MageSelectionInterface::CreateListStringAttributeDescriptions()
{
	if (language == English_E)
	{
		if (true)
		{
			sf::String str1 = "He has been training all his life to become the strongest mage. He can throw spells at an high velocity. All damage done is increased by ";
			str1 = GlobalFunction::InsertNumberToString(str1, ListCharacteristicValue[0], str1.getSize());
			str1.insert(str1.getSize(), "%.");

			sf::String str2 = "His skin is unique. It cannot get burnt and he doesn't feel cold. All damage received is decreased by ";
			str2 = GlobalFunction::InsertNumberToString(str2, ListCharacteristicValue[1], str2.getSize());
			str2.insert(str2.getSize(), "%.");

			sf::String str3 = "Nothing can stop him. He is young, ambitiousand and lively. Maximum health is increased by ";
			str3 = GlobalFunction::InsertNumberToString(str3, ListCharacteristicValue[2], str3.getSize());
			str3.insert(str3.getSize(), "%.");

			sf::String str4 = "He has traveled all around the round on foot in 3 weeks. A legend even says that he can run faster than a cheetah. Bonus movement speed while sprinting is increased by ";
			str4 = GlobalFunction::InsertNumberToString(str4, ListCharacteristicValue[3], str4.getSize());
			str4.insert(str4.getSize(), "%.");

			sf::String str5 = "He was born with only one leg. When he was 10 years old, an old mage gave him a magic leg with powerful attributes. Movement speed is increased by ";
			str5 = GlobalFunction::InsertNumberToString(str5, ListCharacteristicValue[4], str5.getSize());
			str5.insert(str5.getSize(), "%.");

			sf::String str6 = "He is indisputably one of the smartest apprentices. He is a quick learner and he never stop studying. All experience gained is increased by ";
			str6 = GlobalFunction::InsertNumberToString(str6, ListCharacteristicValue[5], str6.getSize());
			str6.insert(str6.getSize(), "%.");

			sf::String str7 = "His family is one of the richest in the kingdom. Everything he touches turn into gold. All gold gained is increased by ";
			str7 = GlobalFunction::InsertNumberToString(str7, ListCharacteristicValue[6], str7.getSize());
			str7.insert(str7.getSize(), "%.");

			sf::String str8 = "He was born with a unique powerful gift. He shines at manipulating magic. Attack speed is increased by ";
			str8 = GlobalFunction::InsertNumberToString(str8, ListCharacteristicValue[7], str8.getSize());
			str8.insert(str8.getSize(), "%.");

			sf::String str9 = "He is healthy and he recovers quickly from injuries. All healing is increased by ";
			str9 = GlobalFunction::InsertNumberToString(str9, ListCharacteristicValue[8], str9.getSize());
			str9.insert(str9.getSize(), "%.");

			sf::String str10 = "He has no mercy and he torns apart his ennemies. Lifesteal is raised by ";
			str10 = GlobalFunction::InsertNumberToString(str10, ListCharacteristicValue[9], str10.getSize());
			str10.insert(str10.getSize(), "%.");

			sf::String str11 = "He has a really good vision. He can detect ennemies at far away. The range of the radar is increased by ";
			str11 = GlobalFunction::InsertNumberToString(str11, ListCharacteristicValue[10], str11.getSize());
			str11.insert(str11.getSize(), "%.");

			sf::String str12 = "From the moment he was born to this day, he has spared all of his free time creating and crafting stuffs. The stats of every crafted weapon are increased by ";
			str12 = GlobalFunction::InsertNumberToString(str12, ListCharacteristicValue[11], str12.getSize());
			str12.insert(str12.getSize(), "%.");

			sf::String str13 = "He never stop moving or working. Sometime, in the middle of the night, he wakes up to complete some of the tasks he didn't finish during the day. Decrease the duration he is stunned by ";
			str13 = GlobalFunction::InsertNumberToString(str13, ListCharacteristicValue[12], str13.getSize());
			str13.insert(str13.getSize(), "%.");

			sf::String str14 = "He is a magician. Many of his tricks rely on moving his hands quickly to reveal objects. Decrease the time it takes to loot items by ";
			str14 = GlobalFunction::InsertNumberToString(str14, ListCharacteristicValue[13], str14.getSize());
			str14.insert(str14.getSize(), "%.");

			sf::String str15 = "He would never hurt a fly. Younger, he would gather flowers while the other kids were fighting together. Reduce the time it takes to be out of battle by ";
			str15 = GlobalFunction::InsertNumberToString(str15, ListCharacteristicValue[14], str15.getSize());
			str15.insert(str15.getSize(), " seconds.");

			ListCharacteristicProsDescription.push_back(str1);
			ListCharacteristicProsDescription.push_back(str2);
			ListCharacteristicProsDescription.push_back(str3);
			ListCharacteristicProsDescription.push_back(str4);
			ListCharacteristicProsDescription.push_back(str5);
			ListCharacteristicProsDescription.push_back(str6);
			ListCharacteristicProsDescription.push_back(str7);
			ListCharacteristicProsDescription.push_back(str8);
			ListCharacteristicProsDescription.push_back(str9);
			ListCharacteristicProsDescription.push_back(str10);
			ListCharacteristicProsDescription.push_back(str11);
			ListCharacteristicProsDescription.push_back(str12);
			ListCharacteristicProsDescription.push_back(str13);
			ListCharacteristicProsDescription.push_back(str14);
			ListCharacteristicProsDescription.push_back(str15);
		}

		if (true)
		{
			sf::String str1 = "He has the strength of a child and would lose against any other mage in a physical battle. All damage done is decreased by ";
			str1 = GlobalFunction::InsertNumberToString(str1, ListCharacteristicValue[0], str1.getSize());
			str1.insert(str1.getSize(), "%.");

			sf::String str2 = "Everytime something touches his skin, he feels a pain. He even have to protect himself from the sun. All damage received is increased by ";
			str2 = GlobalFunction::InsertNumberToString(str2, ListCharacteristicValue[1], str2.getSize());
			str2.insert(str2.getSize(), "%.");

			sf::String str3 = "He is getting weaker and weaker over the time. Some people even say he might die sooner than we think. Maximum health is decreased by ";
			str3 = GlobalFunction::InsertNumberToString(str3, ListCharacteristicValue[2], str3.getSize());
			str3.insert(str3.getSize(), "%.");

			sf::String str4 = "He can't run more than 400 meters without having to catch his breath. In fact, going upstair his an hard challenge for him. Bonus movement speed while sprinting is decreased by ";
			str4 = GlobalFunction::InsertNumberToString(str4, ListCharacteristicValue[3], str4.getSize());
			str4.insert(str4.getSize(), "%.");

			sf::String str5 = "He was born with difformed leg. It prevents him from running too fast. Movement speed is decreased by ";
			str5 = GlobalFunction::InsertNumberToString(str5, ListCharacteristicValue[4], str5.getSize());
			str5.insert(str5.getSize(), "%.");

			sf::String str6 = "He is the kind of guy that skips school to have fun with friends. He has difficulty learning new things. All experience gained is decreased by ";
			str6 = GlobalFunction::InsertNumberToString(str6, ListCharacteristicValue[5], str6.getSize());
			str6.insert(str6.getSize(), "%.");

			sf::String str7 = "His family is very poor and he have to give some of the gold he makes to his family so they can live. All gold gained is decreased by ";
			str7 = GlobalFunction::InsertNumberToString(str7, ListCharacteristicValue[6], str7.getSize());
			str7.insert(str7.getSize(), "%.");

			sf::String str8 = "Few months ago, he didn't know that magic was part of the world. He still have difficulties casting some spells. Attack speed is decreased by ";
			str8 = GlobalFunction::InsertNumberToString(str8, ListCharacteristicValue[7], str8.getSize());
			str8.insert(str8.getSize(), "%.");

			sf::String str9 = "He always have a cold, which take him a lot of energy to fight. It is very hard for him to recover from diseases or injuries. All healing is decreased by ";
			str9 = GlobalFunction::InsertNumberToString(str9, ListCharacteristicValue[8], str9.getSize());
			str9.insert(str9.getSize(), "%.");

			sf::String str10 = "He does what he have to do and he makes sure his target doesn't suffer. Lifesteal is reduced by ";
			str10 = GlobalFunction::InsertNumberToString(str10, ListCharacteristicValue[9], str10.getSize());
			str10.insert(str10.getSize(), "%.");

			sf::String str11 = "Since he is born, he can't see further than 10 meters. Younger, he had to be in front of the class to read on the board. The range of the radar is decreased by ";
			str11 = GlobalFunction::InsertNumberToString(str11, ListCharacteristicValue[10], str11.getSize());
			str11.insert(str11.getSize(), "%.");

			sf::String str12 = "He prefers to buy things instead of using his hand to make it. The stats of every crafted weapon are decreased by ";
			str12 = GlobalFunction::InsertNumberToString(str12, ListCharacteristicValue[11], str12.getSize());
			str12.insert(str12.getSize(), "%.");

			sf::String str13 = "If his parents didn't push him to become a powerful mage, he would have layed on his couch all his life. Increase the duration he is stunned by ";
			str13 = GlobalFunction::InsertNumberToString(str13, ListCharacteristicValue[12], str13.getSize());
			str13.insert(str13.getSize(), "%.");

			sf::String str14 = "He has difficulties picking up objects. Younger, he would always topple his glass of milk. Increase the time it takes to loot items by ";
			str14 = GlobalFunction::InsertNumberToString(str14, ListCharacteristicValue[13], str14.getSize());
			str14.insert(str14.getSize(), "%.");

			sf::String str15 = "He prefers to use his firsts before his mouth. Dominating and intimidating are what he does the best. Increase the time it takes to be out of battle by ";
			str15 = GlobalFunction::InsertNumberToString(str15, ListCharacteristicValue[14], str15.getSize());
			str15.insert(str15.getSize(), " seconds.");

			ListCharacteristicConsDescription.push_back(str1);
			ListCharacteristicConsDescription.push_back(str2);
			ListCharacteristicConsDescription.push_back(str3);
			ListCharacteristicConsDescription.push_back(str4);
			ListCharacteristicConsDescription.push_back(str5);
			ListCharacteristicConsDescription.push_back(str6);
			ListCharacteristicConsDescription.push_back(str7);
			ListCharacteristicConsDescription.push_back(str8);
			ListCharacteristicConsDescription.push_back(str9);
			ListCharacteristicConsDescription.push_back(str10);
			ListCharacteristicConsDescription.push_back(str11);
			ListCharacteristicConsDescription.push_back(str12);
			ListCharacteristicConsDescription.push_back(str13);
			ListCharacteristicConsDescription.push_back(str14);
			ListCharacteristicConsDescription.push_back(str15);
		}

		if (true)
		{
			sf::String str1 = "He is left handed. The problem? He is stubborn to use his right hand. All basic projectiles are deviated.";
			sf::String str2 = "Poor guy. Sometime, he has a lack of concentration and he starts to do something randomly. Has a chance to go the wrong way when moving.";
			sf::String str3 = "Few months ago, he fell out the stairs and broke his right leg at 3 places. Running is not possible.";
			sf::String str4 = "It is hard for him to analyse his environment. He can't terminate the distance between him and the objects around him. The radar is disabled.";
			sf::String str5 = "He is allergic to an ingredient in the potions. Younger, he would get dizzy after drinking a potion. Drinking potions might give you other unwanted effects.";
			sf::String str6 = "Since he was born, he can't see clearly, his vision is blurred. Everything on the screen is darker.";
			sf::String str7 = "Even though his parents tried to make him love it, he hates one of the magic school. You can't use randomly one of the classes.";
			sf::String str8 = "He was born near a waste processing plant and strange things happen to him like glowing in the dark. Has a chance to be teleported randomly near your location.";
			sf::String str9 = "We know almost nothing about this mage, only his name. The user interface is disabled.";
			sf::String str10 = "He was born with disfunctional genes. Sometime, he gets out of hand and he can't control himself. Has a chance to not cast skills.";

			ListDrawbackDescription.push_back(str1);
			ListDrawbackDescription.push_back(str2);
			ListDrawbackDescription.push_back(str3);
			ListDrawbackDescription.push_back(str4);
			ListDrawbackDescription.push_back(str5);
			ListDrawbackDescription.push_back(str6);
			ListDrawbackDescription.push_back(str7);
			ListDrawbackDescription.push_back(str8);
			ListDrawbackDescription.push_back(str9);
			ListDrawbackDescription.push_back(str10);
		}
	}
	else
	{
		if (true)
		{
			sf::String str1 = "Il s'est entraîné toute sa vie pour devenir le mage le plus fort. Il peut lancer des sorts à très grande vitesse. Tous les dégâts infligés sont augmentés de ";
			str1 = GlobalFunction::InsertNumberToString(str1, ListCharacteristicValue[0], str1.getSize());
			str1.insert(str1.getSize(), "%.");

			sf::String str2 = "Sa peau est unique. Elle ne peut être brûlée et elle est insensible au froid. Tous les dégâts reçus sont réduits de ";
			str2 = GlobalFunction::InsertNumberToString(str2, ListCharacteristicValue[1], str2.getSize());
			str2.insert(str2.getSize(), "%.");

			sf::String str3 = "Rien ne peut l'arrêter. Il est jeune, ambitieux et plein de vie. La vie totale est augmentée de ";
			str3 = GlobalFunction::InsertNumberToString(str3, ListCharacteristicValue[2], str3.getSize());
			str3.insert(str3.getSize(), "%.");

			sf::String str4 = "Il a fait le tour du monde à pied en 3 semaines. Les légendes racontent qu'il est plus rapide qu'un guépard. Le bonus de vitesse de déplacement pendant la course est augmenté de ";
			str4 = GlobalFunction::InsertNumberToString(str4, ListCharacteristicValue[3], str4.getSize());
			str4.insert(str4.getSize(), "%.");

			sf::String str5 = "Il est né avec seulement une jambe. Lorsqu'il avait 10 ans, un vieux mage lui a donné une jambe magique. La vitesse de déplacement est augmentée de ";
			str5 = GlobalFunction::InsertNumberToString(str5, ListCharacteristicValue[4], str5.getSize());
			str5.insert(str5.getSize(), "%.");

			sf::String str6 = "Il est incontestablement l'un des apprentis les plus intelligents. Il apprend très rapidement et il ne cesse d'étudier l'art de la magie. L'expérience reçu est augmenté de ";
			str6 = GlobalFunction::InsertNumberToString(str6, ListCharacteristicValue[5], str6.getSize());
			str6.insert(str6.getSize(), "%.");

			sf::String str7 = "Sa famille est l'une des plus riches du royaume. Chaque chose qu'il touche se change en or. La quantié de pièces d'or reçues est augmentée de ";
			str7 = GlobalFunction::InsertNumberToString(str7, ListCharacteristicValue[6], str7.getSize());
			str7.insert(str7.getSize(), "%.");

			sf::String str8 = "Il est né avec un don magique unique. Il excelle à manipuler et à créer la magie. La vitesse d'attaque est augmentée de ";
			str8 = GlobalFunction::InsertNumberToString(str8, ListCharacteristicValue[7], str8.getSize());
			str8.insert(str8.getSize(), "%.");

			sf::String str9 = "Il est en santé et il récupère très rapidement de ses blessures. Tous les soins reçus sont augmentés de ";
			str9 = GlobalFunction::InsertNumberToString(str9, ListCharacteristicValue[8], str9.getSize());
			str9.insert(str9.getSize(), "%.");

			sf::String str10 = "Il n'a aucune pitié et il déchire le corps de ses victimes. Le vol de vie est augmenté de ";
			str10 = GlobalFunction::InsertNumberToString(str10, ListCharacteristicValue[9], str10.getSize());
			str10.insert(str10.getSize(), "%.");

			sf::String str11 = "Il possède une très bonne vision. Il peut même détecter les ennemies qui se situent à de très grandes distances de lui. La porté du radar est augmentée de ";
			str11 = GlobalFunction::InsertNumberToString(str11, ListCharacteristicValue[10], str11.getSize());
			str11.insert(str11.getSize(), "%.");

			sf::String str12 = "Depuis le moment qu'il est né jusqu'à aurjoud'hui, il a passé tous ses temps libres à créer et à fabriquer des objets. Les attributs de tous les armes fabriquées sont augmentées de ";
			str12 = GlobalFunction::InsertNumberToString(str12, ListCharacteristicValue[11], str12.getSize());
			str12.insert(str12.getSize(), "%.");

			sf::String str13 = "Il ne cesse jamais de bouger ou de travailler.Parfois, il se réveille au milieu de la nuit afin de compléter certaines tâches qu'il n'a pu compléter pendant la journée. Réduit le temps des étourdissements de ";
			str13 = GlobalFunction::InsertNumberToString(str13, ListCharacteristicValue[12], str13.getSize());
			str13.insert(str13.getSize(), "%.");


			sf::String str14 = "Il est un magician. Plusieurs de ses tours de magie se basent sur la rapidité de ses mains afin de faire apparaître des objets. Réduit le temps qu'il faut pour ramasser un objet au sol de ";
			str14 = GlobalFunction::InsertNumberToString(str14, ListCharacteristicValue[13], str14.getSize());
			str14.insert(str14.getSize(), "%.");

			sf::String str15 = "Il ne ferait pas de mal à une mouche. Plus jeune, il ramassait des fleurs tandis que les autres enfants se battaient entre eux. Réduit le temps nécessaire afin d'être hors-combat de ";
			str15 = GlobalFunction::InsertNumberToString(str15, ListCharacteristicValue[14], str15.getSize());
			str15.insert(str15.getSize(), " secondes.");

			ListCharacteristicProsDescription.push_back(str1);
			ListCharacteristicProsDescription.push_back(str2);
			ListCharacteristicProsDescription.push_back(str3);
			ListCharacteristicProsDescription.push_back(str4);
			ListCharacteristicProsDescription.push_back(str5);
			ListCharacteristicProsDescription.push_back(str6);
			ListCharacteristicProsDescription.push_back(str7);
			ListCharacteristicProsDescription.push_back(str8);
			ListCharacteristicProsDescription.push_back(str9);
			ListCharacteristicProsDescription.push_back(str10);
			ListCharacteristicProsDescription.push_back(str11);
			ListCharacteristicProsDescription.push_back(str12);
			ListCharacteristicProsDescription.push_back(str13);
			ListCharacteristicProsDescription.push_back(str14);
			ListCharacteristicProsDescription.push_back(str15);
		}

		if (true)
		{
			sf::String str1 = "Il a la force d'un enfant et il perdrait contre n'importe quel autre mage dans un combat physique. Tous les dégâts infligés sont réduits de ";
			str1 = GlobalFunction::InsertNumberToString(str1, ListCharacteristicValue[0], str1.getSize());
			str1.insert(str1.getSize(), "%.");

			sf::String str2 = "Chaque fois que quelque chose le touche, il ressent une douleur aïgue. Il doit même se protéger en tout temps du soleil. Tous les dégâts reçus sont augmentés de ";
			str2 = GlobalFunction::InsertNumberToString(str2, ListCharacteristicValue[1], str2.getSize());
			str2.insert(str2.getSize(), "%.");

			sf::String str3 = "Il devient de plus en plus faible au fil du temps. Certaines personnes disent même qu'il pourrait mourir plus tôt qu'on le pense. La vie totale est réduite de ";
			str3 = GlobalFunction::InsertNumberToString(str3, ListCharacteristicValue[2], str3.getSize());
			str3.insert(str3.getSize(), "%.");

			sf::String str4 = "Il ne peut pas courir plus de 400 mètres sans devoir reprendre son souffle. En effet, monter les escaliers est un défi de taille pour lui. Le bonus de vitesse de déplacement pendat la course est réduite de ";
			str4 = GlobalFunction::InsertNumberToString(str4, ListCharacteristicValue[3], str4.getSize());
			str4.insert(str4.getSize(), "%.");

			sf::String str5 = "Il est né avec une jambe difforme. Cela l'empêche de se déplacer rapidement. La vitesse de déplacement est réduite de ";
			str5 = GlobalFunction::InsertNumberToString(str5, ListCharacteristicValue[4], str5.getSize());
			str5.insert(str5.getSize(), "%.");

			sf::String str6 = "Il est le genre d'apprenti à laisser tomber l'école pour aller s'amuser avec ses amis. Il a de la difficulté à apprendre des choses. L'expérience reçue est réduite de ";
			str6 = GlobalFunction::InsertNumberToString(str6, ListCharacteristicValue[5], str6.getSize());
			str6.insert(str6.getSize(), "%.");

			sf::String str7 = "Sa famille est très pauvre et il doit donner un peu des pièces d'or qu'il reçoit afin que sa famille puisse survivre. La quantité de pièces d'or reçues est réduite de ";
			str7 = GlobalFunction::InsertNumberToString(str7, ListCharacteristicValue[6], str7.getSize());
			str7.insert(str7.getSize(), "%.");

			sf::String str8 = "Quelques mois auparavant, il ne savait même pas que la magie faisait parti de ce monde. Il a encore de la difficulté à lancer certains sorts. La vitesse d'attaque est réduite de ";
			str8 = GlobalFunction::InsertNumberToString(str8, ListCharacteristicValue[7], str8.getSize());
			str8.insert(str8.getSize(), "%.");

			sf::String str9 = "Il a toujours le rhume, ce qui lui demande beaucoup d'énergie. Il est très difficile pour lui de guérir de ses blessures. Tous les soins reçus sont réduits de ";
			str9 = GlobalFunction::InsertNumberToString(str9, ListCharacteristicValue[8], str9.getSize());
			str9.insert(str9.getSize(), "%.");

			sf::String str10 = "Il fait ce qu'il a à faire et il s'assure que sa victime ne souffre pas. Le vol de vie est réduite de ";
			str10 = GlobalFunction::InsertNumberToString(str10, ListCharacteristicValue[9], str10.getSize());
			str10.insert(str10.getSize(), "%.");

			sf::String str11 = "Depuis qu'il est né, il ne peut voir à plus de 10 mètres devant lui. Plus jeune, il devait être à l'avant de la classe afin de pouvoir lire sur le tableau. La portée du radar est réduite de ";
			str11 = GlobalFunction::InsertNumberToString(str11, ListCharacteristicValue[10], str11.getSize());
			str11.insert(str11.getSize(), "%.");

			sf::String str12 = "Il préfère acheter quelque chose à la place de le fabriquer par lui-même. Les attributs de tous les armes fabriquées sont réduits de ";
			str12 = GlobalFunction::InsertNumberToString(str12, ListCharacteristicValue[11], str12.getSize());
			str12.insert(str12.getSize(), "%.");

			sf::String str13 = "Si ses parents ne l'auraient pas poussé à devenir un puissant mage, il aurait rester étendu sur son sofa toute sa vie. Augmente le temps des étourdissements de ";
			str13 = GlobalFunction::InsertNumberToString(str13, ListCharacteristicValue[12], str13.getSize());
			str13.insert(str13.getSize(), "%.");

			sf::String str14 = "Il a de la difficulté à prendre les objets. Plus jeune, il renversait toujours son verre de lait. Augmente le temps qu'il faut pour ramasser un objet au sol de ";
			str14 = GlobalFunction::InsertNumberToString(str14, ListCharacteristicValue[13], str14.getSize());
			str14.insert(str14.getSize(), "%.");

			sf::String str15 = "Il préfère utiliser ses poings avant sa bouche. Dominer et intimider sont ce qu'il fait de mieux. Réduit le temps nécessaire afin d'être hors-combat de ";
			str15 = GlobalFunction::InsertNumberToString(str15, ListCharacteristicValue[14], str15.getSize());
			str15.insert(str15.getSize(), " secondes.");

			ListCharacteristicConsDescription.push_back(str1);
			ListCharacteristicConsDescription.push_back(str2);
			ListCharacteristicConsDescription.push_back(str3);
			ListCharacteristicConsDescription.push_back(str4);
			ListCharacteristicConsDescription.push_back(str5);
			ListCharacteristicConsDescription.push_back(str6);
			ListCharacteristicConsDescription.push_back(str7);
			ListCharacteristicConsDescription.push_back(str8);
			ListCharacteristicConsDescription.push_back(str9);
			ListCharacteristicConsDescription.push_back(str10);
			ListCharacteristicConsDescription.push_back(str11);
			ListCharacteristicConsDescription.push_back(str12);
			ListCharacteristicConsDescription.push_back(str13);
			ListCharacteristicConsDescription.push_back(str14);
			ListCharacteristicConsDescription.push_back(str15);
		}

		if (true)
		{
			sf::String str1 = "Il est gauché. Le problème? Il est entêté à utiliser sa main droite. Toutes les attaques de base sont décalées.";
			sf::String str2 = "Pauvre type. Parfois, il manque tellement de concentration qu'il entame une activité sans le vouloir. Vous avez une chance d'aller dans la mauvaise direction.";
			sf::String str3 = "Il y a quelques mois, il est tombé dans les escaliers et il s'est cassé la jambe droite à trois endroits. Courir est impossible.";

			sf::String str4 = "Il est difficile pour lui d'analyser son environnement. Il n'est pas capable de se figurer à quelle distance de lui sont les objets qui l'entourent. Le radar est désactivé.";
			
			sf::String str5 = "Il est allergique à l'un des ingrédients dans les potions de vie. Plus jeune, il devenait étourdit après avoir consommé une potion. Boire une potion de vie risque d'avoir des effets secondaires.";

			sf::String str6 = "Depuis qu'il est né, il ne peut pas voir clairement, sa vision est embrouillée. Tous les objets de la carte sont plus sombres.";

			sf::String str7 = "Malgré la tenacité de ses parents, il n'a jamais aimé l'une des écoles de magie. Vous ne pouvez pas prendre au hasard l'une des classes.";

			sf::String str8 = "Il est né à proxmité d'une usine à déchets et plusieurs phénomènes étranges lui arrivent comme par exemple briller dans le noir. Vouss avez une chance de vous téléporter aléatoirement proche à proximité de votre position.";

			sf::String str9 = "Nous savons pratiquement rièn à propos de ce mage, seulement son nom. L'interface du joueur est désactivée.";

			sf::String str10 = "Il est né avec des disfonctionnements génétiques. Parfois, il devient frénétique et il n'est pas capable de se contrôler. Vous avez une chance de ne pas lancer vos sorts.";

			ListDrawbackDescription.push_back(str1);
			ListDrawbackDescription.push_back(str2);
			ListDrawbackDescription.push_back(str3);
			ListDrawbackDescription.push_back(str4);
			ListDrawbackDescription.push_back(str5);
			ListDrawbackDescription.push_back(str6);
			ListDrawbackDescription.push_back(str7);
			ListDrawbackDescription.push_back(str8);
			ListDrawbackDescription.push_back(str9);
			ListDrawbackDescription.push_back(str10);
		}
	}

	if (true)
	{
		sf::String str1 = "Bertrand";
		sf::String str2 = "George";
		sf::String str3 = "Louis";
		sf::String str4 = "Martin";
		sf::String str5 = "Florent";
		sf::String str6 = "Victor";
		sf::String str7 = "Damas";
		sf::String str8 = "Alfonse";
		sf::String str9 = "Alfred";
		sf::String str10 = "Albert";
		sf::String str11 = "Adam";
		sf::String str12 = "Bob";
		sf::String str13 = "Addelard";
		sf::String str14 = "Wilfrid";
		sf::String str15 = "Gustave";
		sf::String str16 = "Andre";
		sf::String str17 = "Anthony";
		sf::String str18 = "Auguste";
		sf::String str19 = "Benoît";
		sf::String str20 = "Dimitri";
		sf::String str21 = "Charles";
		sf::String str22 = "Lionel";
		sf::String str23 = "Nicholas";
		sf::String str24 = "Émilien";
		sf::String str25 = "Leonard";
		sf::String str26 = "Edmond";
		sf::String str27 = "Gaspard";
		sf::String str28 = "Gédeon";
		sf::String str29 = "Horasse";
		sf::String str30 = "Ector";

		ListNameMage.push_back(str1);
		ListNameMage.push_back(str2);
		ListNameMage.push_back(str3);
		ListNameMage.push_back(str4);
		ListNameMage.push_back(str5);
		ListNameMage.push_back(str6);
		ListNameMage.push_back(str7);
		ListNameMage.push_back(str8);
		ListNameMage.push_back(str9);
		ListNameMage.push_back(str10);
		ListNameMage.push_back(str11);
		ListNameMage.push_back(str12);
		ListNameMage.push_back(str13);
		ListNameMage.push_back(str14);
		ListNameMage.push_back(str15);
		ListNameMage.push_back(str16);
		ListNameMage.push_back(str17);
		ListNameMage.push_back(str18);
		ListNameMage.push_back(str19);
		ListNameMage.push_back(str20);
		ListNameMage.push_back(str21);
		ListNameMage.push_back(str22);
		ListNameMage.push_back(str23);
		ListNameMage.push_back(str24);
		ListNameMage.push_back(str25);
		ListNameMage.push_back(str26);
		ListNameMage.push_back(str27);
		ListNameMage.push_back(str28);
		ListNameMage.push_back(str29);
		ListNameMage.push_back(str30);
	}
}

void MageSelectionInterface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];

	for (int i = 0; i < number_interface; i++)
	{
		interface_mage_selection[i].setTexture(texture_interface);
	}
}