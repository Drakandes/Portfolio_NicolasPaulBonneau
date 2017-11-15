#include "stdafx.h"
#include "InventoryInterface.h"

InventoryInterface::InventoryInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font crafting interface" << std::endl;
	}

	if (!texture_locked_icone.loadFromFile("LockedIcone.png"))
	{
		std::cout << "Error while loading locked icone texture in inventory interface" << std::endl;
	}

	if (!texture_equipped.loadFromFile("IconeEquipped.png"))
	{
		std::cout << "Error while loading equipped texture in inventory interface" << std::endl;
	}

	if (!texture_item.loadFromFile("EquipmentIcone.png"))
	{
		std::cout << "Error while loading items texture in inventory interface" << std::endl;
	}

#pragma region TextureInterfaceLoading
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("InventoryInterfaceV1.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("InventoryInterfaceV2.png");
		ListTextureInterface.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("InventoryEquipmentInterfaceV1.png");
		ListTextureInterface2.push_back(texture_of_interface);
	}
	if (true)
	{
		sf::Texture texture_of_interface;
		texture_of_interface.loadFromFile("InventoryEquipmentInterfaceV2.png");
		ListTextureInterface2.push_back(texture_of_interface);
	}

	texture_interface = ListTextureInterface[0];
	texture_interface_equipment = ListTextureInterface2[0];
#pragma endregion TextureInterfaceLoading

	interface_inventory = GlobalFunction::CreateSpriteWithoutOrigin(position_interface, size_interface, texture_interface);
	interface_equipment_inventory = GlobalFunction::CreateSpriteWithoutOrigin(position_interface_equipment, size_interface_equipment, texture_interface_equipment);

	/*if (language == English_E)
	{
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Inventory", font, 36);
	}
	else
	{
		text_name_interface = GlobalFunction::CreateText(position_name_interface, "Inventaire", font, 36);
	}
	text_name_interface.setFillColor(sf::Color::Color(108, 129, 197));
	text_name_interface.setStyle(sf::Text::Bold);*/

	text_health_potion = GlobalFunction::CreateText(position_health_potion, "0", font, 18);
	text_health_potion.setStyle(sf::Text::Bold);

	rect_mage = GlobalFunction::CreateRectangle(size_mage, position_mage);

	current_weapon = GlobalFunction::CreateSpriteWithoutOrigin(position_current_weapon, size_item, texture_item);
	current_weapon_equipped = GlobalFunction::CreateSpriteWithoutOrigin(position_current_weapon, size_item, texture_equipped);

	current_hat = GlobalFunction::CreateSpriteWithoutOrigin(position_current_hat, size_item, texture_item);
	current_hat_equipped = GlobalFunction::CreateSpriteWithoutOrigin(position_current_hat, size_item, texture_equipped);

	current_ring1 = GlobalFunction::CreateSpriteWithoutOrigin(position_current_ring1, size_item, texture_item);
	current_ring1_equipped = GlobalFunction::CreateSpriteWithoutOrigin(position_current_ring1, size_item, texture_equipped);

	current_ring2 = GlobalFunction::CreateSpriteWithoutOrigin(position_current_ring2, size_item, texture_item);
	current_ring2_equipped = GlobalFunction::CreateSpriteWithoutOrigin(position_current_ring2, size_item, texture_equipped);

	sf::Vector2i counter{ 0,0 };
	for (int i = 0; i < number_inventory_slot; i++)
	{
		listSlotType.push_back(false);
		position_item[i] = position_first_item + sf::Vector2f(counter.x*(size_item.x + 2), counter.y*(size_item.y + 2));
		sprite_item[i] = GlobalFunction::CreateSpriteWithoutOrigin(position_item[i], size_item, texture_item);
		counter.x++;
		if (counter.x == 15)
		{
			counter.x = 0;
			counter.y++;
		}
		slot_empty[i] = true;
	}

	sf::Vector2i counter_equipement{ 0,0 };
	for (int i = 0; i < number_all_equipments; i++)
	{
		position_equipment[i] = position_first_equipment + sf::Vector2f(counter_equipement.x * 61, counter_equipement.y * 56);
		rect_equipment[i] = GlobalFunction::CreateRectangle(size_equipment, position_equipment[i]);
		equipment_locked_icone[i] = GlobalFunction::CreateSpriteWithoutOrigin(position_equipment[i], size_equipment, texture_locked_icone);
		equipment_locked_icone[i].setColor(sf::Color::Color(255, 255, 255, 230));
		counter_equipement.y++;
		if (counter_equipement.y == 9)
		{
			counter_equipement.x++;
			counter_equipement.y = 0;
		}
	}

	for (int i = 0; i < number_maximum_equipments; i++)
	{
		current_equipment_equipped[i] = GlobalFunction::CreateSpriteWithoutOrigin(sf::Vector2f(0,0), size_item, texture_equipped);
	}

	text_number_equipment_equipped = GlobalFunction::CreateText(position_number_equipment_equipeed, "Test", font, 22);

	listAllArmors = ListObjectsSingleton::instance()->GetListArmor();
	listAllTalents = ListObjectsSingleton::instance()->GetListTalent();

	listScrollBonus = ListObjectsSingleton::instance()->GetListAchievementsBonus();
	ListCharacteristicPros = ListObjectsSingleton::instance()->ListCharacteristicPros;
	ListCharacteristicCons = ListObjectsSingleton::instance()->ListCharacteristicCons;
	ListCharacteristicValue = ListObjectsSingleton::instance()->ListCharacteristicValue;
	ListDrawback = ListObjectsSingleton::instance()->ListDrawback;
	CreateListStringAttributeDescriptions();

	CreateListEquipmentDescription();
}

InventoryInterface::~InventoryInterface()
{
}

void InventoryInterface::Draw(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
//	text_name_interface.setPosition(position_view_player + position_name_interface);
	interface_inventory.setPosition(position_view_player + position_interface);
	interface_equipment_inventory.setPosition(position_view_player + position_interface_equipment);
	text_number_equipment_equipped.setPosition(position_number_equipment_equipeed + position_view_player);
	current_weapon.setPosition(position_view_player + position_current_weapon);
	current_weapon_equipped.setPosition(position_item[current_weapon_slot] + position_view_player);
	current_hat.setPosition(position_view_player + position_current_hat);
	current_hat_equipped.setPosition(position_item[current_hat_slot] + position_view_player);
	current_ring1.setPosition(position_view_player + position_current_ring1);
	current_ring1_equipped.setPosition(position_item[current_ring1_slot] + position_view_player);
	current_ring2.setPosition(position_view_player + position_current_ring2);
	current_ring2_equipped.setPosition(position_item[current_ring2_slot] + position_view_player);
	text_health_potion.setPosition(position_view_player + position_health_potion);
	rect_mage.setPosition(position_mage + position_view_player); 

	window.draw(interface_inventory);
	window.draw(interface_equipment_inventory);
	//window.draw(text_name_interface);

	for (int i = 0; i < number_inventory_slot; i++)
	{
		sprite_item[i].setPosition(position_item[i] + position_view_player);
		if (!slot_empty[i])
		{
			window.draw(sprite_item[i]);
		}
	}

	for (int i = 0; i < number_all_equipments; i++)
	{
		rect_equipment[i].setPosition(position_equipment[i] + position_view_player);
		equipment_locked_icone[i].setPosition(position_equipment[i] + position_view_player);
		if (!listSucceededAchievements[i])
		{
			window.draw(equipment_locked_icone[i]);
		}
	}

	for (int i = 0; i < number_maximum_equipments; i++)
	{
		if (!slot_empty_equipment[i])
		{
			current_equipment_equipped[i].setPosition(position_equipment[current_equipment_slot[i]] + position_view_player);
			window.draw(current_equipment_equipped[i]);
		}
	}

	if (!slot_empty_current_weapon)
	{
		window.draw(current_weapon_equipped);
		window.draw(current_weapon);
	}
	if (!slot_empty_current_hat)
	{
		window.draw(current_hat_equipped);
		window.draw(current_hat);
	}
	if (!slot_empty_current_ring1)
	{
		window.draw(current_ring1_equipped);
		window.draw(current_ring1);
	}
	if (!slot_empty_current_ring2)
	{
		window.draw(current_ring2_equipped);
		window.draw(current_ring2);
	}

	window.draw(text_number_equipment_equipped);
	window.draw(text_health_potion);
}

void InventoryInterface::Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position)
{
	std::vector<std::shared_ptr<EquipmentBase>> listEquipment = player->GetListEquipment();
	std::shared_ptr<EquipmentBase> player_current_weapon;
	std::shared_ptr<EquipmentBase> player_current_hat;
	std::shared_ptr<EquipmentBase> player_current_ring1;
	std::shared_ptr<EquipmentBase> player_current_ring2;
	listSucceededAchievements = player->GetListSucceededAchiemevents();
	listEquippedScroll = player->GetPlayerListEquippedScroll();

	number_equipment_player_can_equip = listAllArmors[player->GetPlayerCurrentArmor()]->ReturnArmorNumberEquipments();
	if (listEquippedScroll[GetFiveAchiemevents])
	{
		number_equipment_player_can_equip += listScrollBonus[GetFiveAchiemevents];
	}
	number_equipment_equipped = 0;
	int counter_equipped_slot = 0;
	for (int i = 0; i < listEquippedScroll.size(); i++)
	{
		if (listEquippedScroll[i])
		{
			slot_empty_equipment[counter_equipped_slot] = false;
			current_equipment_slot[counter_equipped_slot] = i;
			counter_equipped_slot++;
			number_equipment_equipped++;
		}
	}

	for (int i = counter_equipped_slot; i < number_maximum_equipments; i++)
	{
		slot_empty_equipment[counter_equipped_slot] = true;
	}

	if (number_equipment_equipped > number_equipment_player_can_equip)
	{
		number_equipment_equipped = 0;
		for (int i = 0; i < listEquippedScroll.size(); i++)
		{
			listEquippedScroll[i] = false;
		}
	}

	string_number_equipment_equipped.clear();
	string_number_equipment_equipped = "";
	string_number_equipment_equipped = GlobalFunction::InsertNumberToString(string_number_equipment_equipped, number_equipment_equipped, string_number_equipment_equipped.getSize());
	string_number_equipment_equipped.insert(string_number_equipment_equipped.getSize(), " / ");
	string_number_equipment_equipped = GlobalFunction::InsertNumberToString(string_number_equipment_equipped, number_equipment_player_can_equip, string_number_equipment_equipped.getSize());
	text_number_equipment_equipped.setString(string_number_equipment_equipped);

	int current_weapon_id;
	player_current_weapon = player->GetCurrentWeapon();
	if (player_current_weapon != NULL)
	{
		current_weapon_id = player_current_weapon->GetIdEquipment();
		slot_empty_current_weapon = false;
		current_weapon.setTextureRect(sf::IntRect((player_current_weapon->GetTypeEquipment() + 1)*size_item.x, (player_current_weapon->GetCategoryEquipment())*size_item.y, size_item.x, size_item.y));
	}
	else
	{
		slot_empty_current_weapon = true;
	}

	int current_id_hat;
	player_current_hat = player->GetCurrentHat();
	if (player_current_hat != NULL)
	{
		current_id_hat = player_current_hat->GetIdEquipment();
		slot_empty_current_hat = false;
		current_hat.setTextureRect(sf::IntRect((player_current_hat->GetTypeEquipment() + 1)*size_item.x, (player_current_hat->GetCategoryEquipment())*size_item.y, size_item.x, size_item.y));
	}
	else
	{
		slot_empty_current_hat = true;
	}

	int current_id_ring1;
	player_current_ring1 = player->GetCurrentRing1();
	if (player_current_ring1 != NULL)
	{
		current_id_ring1 = player_current_ring1->GetIdEquipment();
		slot_empty_current_ring1 = false;
		current_ring1.setTextureRect(sf::IntRect(2*size_item.x, (player_current_ring1->GetCategoryEquipment())*size_item.y, size_item.x, size_item.y));
	}
	else
	{
		slot_empty_current_ring1 = true;
	}

	int current_id_ring2;
	player_current_ring2 = player->GetCurrentRing2();
	if (player_current_ring2 != NULL)
	{
		current_id_ring2 = player_current_ring2->GetIdEquipment();
		slot_empty_current_ring2 = false;
		current_ring2.setTextureRect(sf::IntRect(2 * size_item.x, (player_current_ring2->GetCategoryEquipment())*size_item.y, size_item.x, size_item.y));
	}
	else
	{
		slot_empty_current_ring2 = true;
	}

	int number_equipment = listEquipment.size();
	for (int i = 0; i < number_inventory_slot; i++)
	{
		if (i < number_equipment)
		{
			if (!slot_empty_current_weapon)
			{
				if (current_weapon_id == listEquipment[i]->GetIdEquipment())
				{
					current_weapon_slot = i;
				}
			}
			if (!slot_empty_current_hat)
			{
				if (current_id_hat == listEquipment[i]->GetIdEquipment())
				{
					current_hat_slot = i;
				}
			}
			if (!slot_empty_current_ring1)
			{
				if (current_id_ring1 == listEquipment[i]->GetIdEquipment())
				{
					current_ring1_slot = i;
				}
			}
			if (!slot_empty_current_ring2)
			{
				if (current_id_ring2 == listEquipment[i]->GetIdEquipment())
				{
					current_ring2_slot = i;
				}
			}
			listSlotType[i] = listEquipment[i]->GetCategoryEquipment();
			slot_empty[i] = false;
			sprite_item[i].setTextureRect(sf::IntRect((listEquipment[i]->GetTypeEquipment()+1)*size_item.x,(listEquipment[i]->GetCategoryEquipment())*size_item.y,size_item.x,size_item.y));
		}
		else
		{
			listSlotType[i] = BaseEquipment_E;
			slot_empty[i] = true;
		}
	}

	int number_health_potion = player->GetNumberSpecficItemInInventory(I_Miscellaneous, IM_HealthPotion);
	string_health_potion.clear();
	string_health_potion = "";
	string_health_potion = GlobalFunction::InsertNumberToString(string_health_potion, number_health_potion, string_health_potion.getSize());
	text_health_potion.setString(string_health_potion);

	CreateRectangleInformation(mouse_position, listEquipment);
	CreateRectangleMageCharacteristic(mouse_position, player);
	CheckPlayerAction(player, mouse_position, listEquipment);
}

void InventoryInterface::CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position, std::vector<std::shared_ptr<EquipmentBase>> listEquipment)
{
	if (clock_click.getElapsedTime().asSeconds() >= 0.15)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (interface_equipment_inventory.getGlobalBounds().contains(mouse_position))
			{
				for (int i = 0; i < number_all_equipments; i++)
				{
					if (listEquippedScroll[i])
					{
						if (rect_equipment[i].getGlobalBounds().contains(mouse_position))
						{
							listEquippedScroll[i] = false;
							SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
							for (int ii = 0; ii < number_maximum_equipments; ii++)
							{
								if (current_equipment_slot[ii] == i)
								{
									slot_empty_equipment[ii] = true;
									break;
								}
							}
						}
					}
				}
			}
			else
			{
				if (sprite_item[current_weapon_slot].getGlobalBounds().contains(mouse_position))
				{
					player->ResetCurrentWeapon();
					current_weapon_slot = -1;
					clock_click.restart();
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				}
				else if (sprite_item[current_hat_slot].getGlobalBounds().contains(mouse_position))
				{
					player->ResetCurrentHat();
					current_hat_slot = -1;
					clock_click.restart();
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				}
				else if (sprite_item[current_ring1_slot].getGlobalBounds().contains(mouse_position))
				{
					player->ResetCurrentRing1();
					current_ring1_slot = -1;
					clock_click.restart();
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				}
				else if (sprite_item[current_ring2_slot].getGlobalBounds().contains(mouse_position))
				{
					player->ResetCurrentRing2();
					current_ring2_slot = -1;
					clock_click.restart();
					SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (interface_equipment_inventory.getGlobalBounds().contains(mouse_position))
			{
				if (number_equipment_equipped < number_equipment_player_can_equip)
				{
					for (int i = 0; i < number_all_equipments; i++)
					{
						if (!listEquippedScroll[i])
						{
							if (rect_equipment[i].getGlobalBounds().contains(mouse_position))
							{
								listEquippedScroll[i] = true;
								SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
								for (int ii = 0; ii < number_maximum_equipments; ii++)
								{
									if (slot_empty_equipment[ii])
									{
										current_equipment_slot[ii] = i;
										slot_empty_equipment[ii] = false;
										break;
									}
								}
							}
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < number_inventory_slot; i++)
				{
					if (i < listEquipment.size())
					{
						if (sprite_item[i].getGlobalBounds().contains(mouse_position))
						{
							if (listSlotType[i] == WeaponEquipment_E)
							{
								if (i != current_weapon_slot)
								{
									current_weapon_slot = i;
									player->ChangeCurrentWeapon(i);
									clock_click.restart();
									SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
								}
							}
							else if (listSlotType[i] == WizardHatEquipment_E)
							{
								if (i != current_hat_slot)
								{
									current_hat_slot = i;
									player->ChangeCurrentHat(i);
									clock_click.restart();
									SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
								}
							}
							else if (listSlotType[i] == RingEquipment_E)
							{
								if (i != current_ring1_slot && i != current_ring2_slot)
								{
									if (current_ring2_slot != -1)
									{
										current_ring1_slot = i;
										player->ChangeCurrentRing1(i);
										clock_click.restart();
										SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
									}
									else
									{
										current_ring2_slot = i;
										player->ChangeCurrentRing2(i);
										clock_click.restart();
										SoundGestion::instance()->AddSound("SoundMenuClick.wav", 45, false);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	player->NewPlayerListEquippedScroll(listEquippedScroll);
}

void InventoryInterface::CreateRectangleInformation(sf::Vector2f mouse_position, std::vector<std::shared_ptr<EquipmentBase>> listEquipment)
{
	if (interface_equipment_inventory.getGlobalBounds().contains(mouse_position))
	{
		for (int i = 0; i < number_all_equipments; i++)
		{
			if (rect_equipment[i].getGlobalBounds().contains(mouse_position))
			{
				if (listSucceededAchievements[i])
				{
					std::vector<int> listLetterSize;
					std::vector<sf::String> listString;
					std::vector<bool> listIfCentered;

					if (language == English_E)
					{
						sf::String string1 = listStringEquipmentName[i];
						string1.insert(string1.getSize(), "'s scroll");
						listLetterSize.push_back(20);
						listIfCentered.push_back(true);
						listString.push_back(string1);
					}
					else
					{
						sf::String string1 = "Manuscrit du ";
						string1.insert(string1.getSize(), listStringEquipmentName[i]);
						listLetterSize.push_back(20);
						listIfCentered.push_back(true);
						listString.push_back(string1);
					}

					sf::String string2 = listStringEquipmentDescription[i];
					listLetterSize.push_back(16);
					listIfCentered.push_back(false);
					listString.push_back(string2);

					TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
				}
				else
				{
					std::vector<int> listLetterSize;
					std::vector<sf::String> listString;
					std::vector<bool> listIfCentered;

					if (language == English_E)
					{
						sf::String string1 = "You have not unlocked this scroll yet.";
						listString.push_back(string1);

					}
					else
					{
						sf::String string1 = "Vous n'avez pas encore obtenu ce manuscrit.";
						listString.push_back(string1);
					}

					listLetterSize.push_back(20);
					listIfCentered.push_back(true);

					TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < number_inventory_slot; i++)
		{
			if (i < listEquipment.size())
			{
				if (sprite_item[i].getGlobalBounds().contains(mouse_position))
				{

					std::vector<int> listLetterSize;
					std::vector<sf::String> listString;
					std::vector<bool> listIfCentered;

					sf::String string1;
					int category_item = listEquipment[i]->GetCategoryEquipment();
					if (category_item == WeaponEquipment_E)
					{
						if (language == English_E)
						{
							string1 = sf::String("Weapon");
						}
						else
						{
							string1 = sf::String("Arme");
						}
						string1.insert(string1.getSize(), sf::String(" ( "));
						string1 = GlobalFunction::InsertNumberToString(string1, listEquipment[i]->GetILvl(), string1.getSize());
						string1.insert(string1.getSize(), sf::String(" iLvl )"));
					}
					else if (category_item == RingEquipment_E)
					{
						if (language == English_E)
						{
							string1 = sf::String("Ring");
						}
						else
						{
							string1 = sf::String("Anneau");
						}
						string1.insert(string1.getSize(), sf::String(" ( "));
						string1 = GlobalFunction::InsertNumberToString(string1, listEquipment[i]->GetILvl(), string1.getSize());
						string1.insert(string1.getSize(), sf::String(" iLvl )"));
					}
					else if (category_item == WizardHatEquipment_E)
					{
						if (language == English_E)
						{
							string1 = sf::String("Wizard Hat");
						}
						else
						{
							string1 = sf::String("Chapeau de magicien");
						}
						string1.insert(string1.getSize(), sf::String(" ( "));
						string1 = GlobalFunction::InsertNumberToString(string1, listEquipment[i]->GetILvl(), string1.getSize());
						string1.insert(string1.getSize(), sf::String(" iLvl )"));
					}
					listLetterSize.push_back(20);
					listIfCentered.push_back(true);
					listString.push_back(string1);

					sf::String string_rarity = GlobalFunction::GetRarityString(listEquipment[i]->GetRarityItem(), language);
					listLetterSize.push_back(18);
					listIfCentered.push_back(true);
					listString.push_back(string_rarity);

					std::vector<sf::String> listStringFromWeapon = listEquipment[i]->GetListStringEquipment();
					for (int holder = 0; holder < listStringFromWeapon.size(); holder++)
					{
						listLetterSize.push_back(16);
						listIfCentered.push_back(false);
						listString.push_back(listStringFromWeapon[holder]);
					}

					if (i == current_weapon_slot || i == current_hat_slot)
					{
						if (language == English_E)
						{
							sf::String string1 = "Currently Equipped";
							listLetterSize.push_back(14);
							listIfCentered.push_back(true);
							listString.push_back(string1);
						}
						else
						{
							sf::String string1 = "Présentement équippé";
							listLetterSize.push_back(14);
							listIfCentered.push_back(true);
							listString.push_back(string1);
						}
					}

					int rarity_item = listEquipment[i]->GetRarityItem();

					TextBoxGenerator::instance()->GenerateOneTextBoxWithColor(listString, listIfCentered, listLetterSize, mouse_position,listColorRarityItemMiddle[rarity_item],listColorRarityItemAround[rarity_item]);
				}
			}
		}
	}
}

void InventoryInterface::CreateRectangleMageCharacteristic(sf::Vector2f mouse_position, std::shared_ptr<Player> &player)
{
	if (rect_mage.getGlobalBounds().contains(mouse_position))
	{
		std::vector<bool> ListDrawbackMage = player->GetPlayerListDrawback();
		std::vector<bool> ListCharac = player->GetPlayerListCharacteristic();
		std::vector<int> ListCharacProsOrcons = player->GetPlayerListCharacteristicProsOrCons();

		std::vector<int> listLetterSize;
		std::vector<sf::String> listString;
		std::vector<bool> listIfCentered;

		listIfCentered.push_back(true);
		listString.push_back(player->GetNameMage());
		listLetterSize.push_back(20);

		for (int i = 0; i < ListCharac.size(); i++)
		{
			if (ListCharac[i])
			{
				if (ListCharacProsOrcons[i] == 1)
				{
					listIfCentered.push_back(true);
					listString.push_back(ListCharacteristicPros[i]);
					listLetterSize.push_back(18);

					listIfCentered.push_back(false);
					listString.push_back(ListCharacteristicProsDescription[i]);
					listLetterSize.push_back(16);
				}
				else
				{
					listIfCentered.push_back(true);
					listString.push_back(ListCharacteristicCons[i]);
					listLetterSize.push_back(18);

					listIfCentered.push_back(false);
					listString.push_back(ListCharacteristicConsDescription[i]);
					listLetterSize.push_back(16);
				}
			}
		}

		for (int i = 0; i < ListDrawback.size(); i++)
		{
			if (ListDrawbackMage[i])
			{
				listIfCentered.push_back(true);
				listString.push_back(ListDrawback[i]);
				listLetterSize.push_back(18);

				listIfCentered.push_back(false);
				listString.push_back(ListDrawbackDescription[i]);
				listLetterSize.push_back(16);
			}
		}

		TextBoxGenerator::instance()->GenerateOneTextBox(listString, listIfCentered, listLetterSize, mouse_position);
	}
}

void InventoryInterface::CreateListEquipmentDescription()
{
	listStringEquipmentName = ListObjectsSingleton::instance()->GetListStringAchiements();

	if (language == English_E)
	{
		sf::String str1 = "When out of battle, heal for ";
		str1 = GlobalFunction::InsertNumberToString(str1, listScrollBonus[TotalHealOneRun], str1.getSize());
		str1.insert(str1.getSize(), "% of your maximum health each second.");

		sf::String str2 = "Each ";
		str2 = GlobalFunction::InsertNumberToString(str2, listScrollBonus[NoDamageWhileCombat], str2.getSize());
		str2.insert(str2.getSize(), " seconds, you are immune to any damage or crowd control for 3 seconds.");

		sf::String str3 = "You are sprinting ";
		str3 = GlobalFunction::InsertNumberToString(str3, listScrollBonus[OutOfSprintOneRun], str3.getSize());
		str3.insert(str3.getSize(), "% faster.");

		sf::String str4 = "Increase the range of your radar by ";
		str4 = GlobalFunction::InsertNumberToString(str4, listScrollBonus[MonsterOnRadar], str4.getSize());
		str4.insert(str4.getSize(), "%.");

		sf::String str5 = "Increase your overall damage by ";
		str5 = GlobalFunction::InsertNumberToString(str5, listScrollBonus[MonsterKilledOneRun], str5.getSize());
		str5.insert(str5.getSize(), "%.");

		sf::String str6 = "Increase your overall health and your overall armor by ";
		str6 = GlobalFunction::InsertNumberToString(str6, listScrollBonus[MapFifthReached], str6.getSize());
		str6.insert(str6.getSize(), "%.");

		sf::String str7 = "Increase the range of your projectile by ";
		str7 = GlobalFunction::InsertNumberToString(str7, listScrollBonus[MonsterHitOneRun], str7.getSize());
		str7.insert(str7.getSize(), "%.");

		sf::String str8 = "Increase the experience you received by ";
		str8 = GlobalFunction::InsertNumberToString(str8, listScrollBonus[ReachLevelTen], str8.getSize());
		str8.insert(str8.getSize(), "%.");

		sf::String str9 = "Increase the number of scrolls you can have at the same time by ";
		str9 = GlobalFunction::InsertNumberToString(str9, listScrollBonus[GetFiveAchiemevents], str9.getSize());
		str9.insert(str8.getSize(), ".");

		sf::String str10 = "Increase the amount of gold you received by ";
		str10 = GlobalFunction::InsertNumberToString(str10, listScrollBonus[SpendGoldOneRun], str10.getSize());
		str10.insert(str10.getSize(), "%.");

		sf::String str11 = "Increase the number of fragments you receive by 5 to 10 fragments.";

		sf::String str12 = "You have ";
		str12 = GlobalFunction::InsertNumberToString(str12, listScrollBonus[CollectMaterialOneRun], str12.getSize());
		str12.insert(str12.getSize(), "% chance to get a second material when you loot it. ");


		listStringEquipmentDescription.push_back(str1);
		listStringEquipmentDescription.push_back(str2);
		listStringEquipmentDescription.push_back(str3);
		listStringEquipmentDescription.push_back(str4);
		listStringEquipmentDescription.push_back(str5);
		listStringEquipmentDescription.push_back(str6);
		listStringEquipmentDescription.push_back(str7);
		listStringEquipmentDescription.push_back(str8);
		listStringEquipmentDescription.push_back(str9);
		listStringEquipmentDescription.push_back(str10);
		listStringEquipmentDescription.push_back(str11);
		listStringEquipmentDescription.push_back(str12);
	}
	else
	{
		sf::String str1 = "Lorsque vous êtes hors-combat, vous vous soignez pour ";
		str1 = GlobalFunction::InsertNumberToString(str1, listScrollBonus[TotalHealOneRun], str1.getSize());
		str1.insert(str1.getSize(), "% de sa vie totale par seconde.");

		sf::String str2 = "À chaque ";
		str2 = GlobalFunction::InsertNumberToString(str2, listScrollBonus[NoDamageWhileCombat], str2.getSize());
		str2.insert(str2.getSize(), " secondes, vous êtes immunisé aux effets de contrôle et aux dégâts pendant 3 secondes.");

		sf::String str3 = "Vous courez ";
		str3 = GlobalFunction::InsertNumberToString(str3, listScrollBonus[OutOfSprintOneRun], str3.getSize());
		str3.insert(str3.getSize(), "% plus vite.");

		sf::String str4 = "Augmente la porte de votre radar de ";
		str4 = GlobalFunction::InsertNumberToString(str4, listScrollBonus[MonsterOnRadar], str4.getSize());
		str4.insert(str4.getSize(), "%.");

		sf::String str5 = "Augmente vos dégâts totaux de ";
		str5 = GlobalFunction::InsertNumberToString(str5, listScrollBonus[MonsterKilledOneRun], str5.getSize());
		str5.insert(str5.getSize(), "%.");

		sf::String str6 = "Augmente votre vie totale et votre armure totale de ";
		str6 = GlobalFunction::InsertNumberToString(str6, listScrollBonus[MapFifthReached], str6.getSize());
		str6.insert(str6.getSize(), "%.");

		sf::String str7 = "Augmente la portée de vos projectiles de ";
		str7 = GlobalFunction::InsertNumberToString(str7, listScrollBonus[MonsterHitOneRun], str7.getSize());
		str7.insert(str7.getSize(), "%.");

		sf::String str8 = "Augmente l'expérience que vous recevez de ";
		str8 = GlobalFunction::InsertNumberToString(str8, listScrollBonus[ReachLevelTen], str8.getSize());
		str8.insert(str8.getSize(), "%.");

		sf::String str9 = "Augmente le nombre de manuscrits que vous pouvez porter de ";
		str9 = GlobalFunction::InsertNumberToString(str9, listScrollBonus[GetFiveAchiemevents], str9.getSize());
		str9.insert(str8.getSize(), ".");

		sf::String str10 = "Augmente la quantité de pièces d'or que vous recevez de ";
		str10 = GlobalFunction::InsertNumberToString(str10, listScrollBonus[SpendGoldOneRun], str10.getSize());
		str10.insert(str10.getSize(), "%.");

		sf::String str11 = "Augmente la quantité de fragments que vous recevez de 5 à 10.";

		sf::String str12 = "Vous avez ";
		str12 = GlobalFunction::InsertNumberToString(str12, listScrollBonus[CollectMaterialOneRun], str12.getSize());
		str12.insert(str12.getSize(), "% de chance d'avoir un objet deux fois lorsque vous ramasser des objets.");


		listStringEquipmentDescription.push_back(str1);
		listStringEquipmentDescription.push_back(str2);
		listStringEquipmentDescription.push_back(str3);
		listStringEquipmentDescription.push_back(str4);
		listStringEquipmentDescription.push_back(str5);
		listStringEquipmentDescription.push_back(str6);
		listStringEquipmentDescription.push_back(str7);
		listStringEquipmentDescription.push_back(str8);
		listStringEquipmentDescription.push_back(str9);
		listStringEquipmentDescription.push_back(str10);
		listStringEquipmentDescription.push_back(str11);
		listStringEquipmentDescription.push_back(str12);
	}
}

void InventoryInterface::CreateListStringAttributeDescriptions()
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

			sf::String str10 = "Il est né avec des disfonctionnements génétiques. Parfois, il devient frénétique et il n'eest pas capable de se contrôler. Vous avez une chance de ne pas lancer vos sorts.";

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

void InventoryInterface::UpdateStyleInterface(int style)
{
	texture_interface = ListTextureInterface[style];
	interface_inventory.setTexture(texture_interface);

	texture_interface_equipment = ListTextureInterface2[style];
	interface_equipment_inventory.setTexture(texture_interface_equipment);
}

