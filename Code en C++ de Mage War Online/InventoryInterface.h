#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>
#include "ListObjectsSingleton.h"
#include "TextBoxGenerator.h"

class InventoryInterface
{
private:
	std::vector<sf::String> ListCharacteristicPros;
	std::vector<sf::String> ListCharacteristicProsDescription;
	std::vector<sf::String> ListCharacteristicCons;
	std::vector<sf::String> ListCharacteristicConsDescription;
	std::vector<float> ListCharacteristicValue{ 15,15,15,30,10,20,20,15,25,5,25,15,20,25,2 };
	std::vector<sf::String> ListDrawback;
	std::vector<sf::String> ListDrawbackDescription;
	std::vector<sf::String> ListNameMage;

	std::vector<sf::Texture> ListTextureInterface;
	std::vector<sf::Texture> ListTextureInterface2;

	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	static const int number_maximum_equipments = 10;
	static const int number_all_equipments = 12;
	static const int number_inventory_slot = 150;
	sf::Font font;
	std::vector<sf::String> listStringEquipmentDescription;
	std::vector<sf::String> listStringEquipmentName;
	std::vector<std::shared_ptr<TalentBase>> listAllTalents;
	std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors;
	std::vector<float> listScrollBonus;
	sf::Texture texture_equipped;
	sf::Clock clock_click;
	std::vector<int> listSlotType;
	std::vector<sf::Color> listColorRarityItemMiddle{sf::Color(133,133,133,215),sf::Color(69,178,75,215),sf::Color(174,178,69,215),sf::Color(69,102,178,215),sf::Color(196,124,51,215) };
	std::vector<sf::Color> listColorRarityItemAround{ sf::Color(133,133,133),sf::Color(69,178,75),sf::Color(174,178,69),sf::Color(69,102,178),sf::Color(196,124,51) };

	sf::Sprite interface_inventory;
	sf::Texture texture_interface;
	sf::Vector2f position_interface{ 150,75 };
	sf::Vector2f size_interface{ 955,577 };

	sf::RectangleShape rect_mage;
	sf::Vector2f size_mage{ 60,70 };
	sf::Vector2f position_mage{ sf::Vector2f(40,196) + position_interface };

	sf::Sprite interface_equipment_inventory;
	sf::Texture texture_interface_equipment;
	sf::Vector2f position_interface_equipment{ size_interface.x + position_interface.x + 25,75 };
	sf::Vector2f size_interface_equipment{ 171,577 };

	sf::Text text_name_interface;
	sf::Vector2f position_name_interface{ sf::Vector2f(592,53) + position_interface };

	sf::Texture texture_item;
	sf::Sprite sprite_item[number_inventory_slot];
	sf::Vector2f position_first_item{ sf::Vector2f(283,131)  + position_interface };
	sf::Vector2f size_item{ 40,40 };
	sf::Vector2f position_item[number_inventory_slot];
	bool slot_empty[number_inventory_slot];

	sf::Sprite current_weapon_equipped;
	sf::Sprite current_weapon;
	sf::Vector2f position_current_weapon{ sf::Vector2f(42,293) + position_interface };
	int current_weapon_slot = -1;
	bool slot_empty_current_weapon = true;

	sf::Sprite current_hat_equipped;
	sf::Sprite current_hat;
	sf::Vector2f position_current_hat{ sf::Vector2f(109,293) + position_interface };
	int current_hat_slot = -1;
	bool slot_empty_current_hat = true;

	sf::Sprite current_ring1_equipped;
	sf::Sprite current_ring1;
	sf::Vector2f position_current_ring1{ sf::Vector2f(109,349) + position_interface };
	int current_ring1_slot = -1;
	bool slot_empty_current_ring1 = true;

	sf::Sprite current_ring2_equipped;
	sf::Sprite current_ring2;
	sf::Vector2f position_current_ring2{ sf::Vector2f(42,349) + position_interface };
	int current_ring2_slot = -1;
	bool slot_empty_current_ring2 = true;

	sf::String string_health_potion;
	sf::Text text_health_potion;
	sf::Vector2f position_health_potion{ sf::Vector2f(143,260) + position_interface };

	sf::Sprite equipment_locked_icone[number_all_equipments];
	sf::Texture texture_locked_icone;
	sf::RectangleShape rect_equipment[number_all_equipments];
	sf::Vector2f position_equipment[number_all_equipments];
	sf::Vector2f position_first_equipment{ sf::Vector2f(37,69) + position_interface_equipment };
	sf::Vector2f size_equipment{ 40,40 };

	sf::Sprite current_equipment_equipped[number_maximum_equipments];
	int current_equipment_slot[number_maximum_equipments]{ 0,0,0,0,0,0,0,0,0,0 };
	bool slot_empty_equipment[number_maximum_equipments]{ true,true,true,true,true,true,true,true,true,true };

	sf::Text text_number_equipment_equipped;
	sf::String string_number_equipment_equipped;
	sf::Vector2f position_number_equipment_equipeed{sf::Vector2f(88,32) + position_interface_equipment};
	int number_equipment_equipped = 0;
	int number_equipment_player_can_equip = 0;

	std::vector<bool> listSucceededAchievements{ false, false, false, false, false, false, false, false, false, false, false, false };
	std::vector<bool> listEquippedScroll{ false,false,false,false,false,false,false,false,false,false,false,false };

	void CreateRectangleInformation(sf::Vector2f mouse_position, std::vector<std::shared_ptr<EquipmentBase>> listEquipment);
	void CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position, std::vector<std::shared_ptr<EquipmentBase>> listEquipment);
	void CreateListEquipmentDescription();
	void CreateListStringAttributeDescriptions();
	void CreateRectangleMageCharacteristic(sf::Vector2f mouse_position, std::shared_ptr<Player> &player);
public:
	InventoryInterface();
	~InventoryInterface();

	void Draw(sf::RenderWindow &window,sf::Vector2f position_view_player);
	void Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void UpdateStyleInterface(int style);
};

