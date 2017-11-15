#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>
#include "ListObjectsSingleton.h"
#include "E_Weapon.h"
#include "TextBoxGenerator.h"

class CraftingInterface
{
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	enum SelfEnumOres{Self_Iron, Self_Ruby, Self_Emerald, Self_Topaz};
	std::vector<std::shared_ptr<TalentBase>> listAllTalents;
	static const int number_ores = 4;
	static const int number_maximum_enchantments = 9;
	static const int number_maximum_weapon_bonus = number_maximum_enchantments + 3;

	std::vector<sf::Texture> ListTextureInterface;

	sf::Font font;
	sf::Clock clock_click;
	sf::Clock clock_creation;
	std::vector<sf::Vector2f> RarityItemRange{ sf::Vector2f(39.5,17),sf::Vector2f(32.5,33),sf::Vector2f(15,25),sf::Vector2f(7.5,15),sf::Vector2f(3,10) };
	std::vector<int> PoolIronBonus;
	std::vector<int> PoolRubyBonus;
	std::vector<int> PoolEmeraldBonus;
	std::vector<int> PoolTopazBonus;
	std::vector<int> PoolRubyTalentBonus{ 0,1,6,9,10,15,18,19,24 };
	std::vector<int> PoolEmeraldTalentBonus{ 2,3,7,11,12,16,20,21,25 };
	std::vector<int> PoolTopazTalentBonus{ 4,5,8,13,14,17,22,23,26 };
	bool showing_created_weapon = false;
	int size_normal_text = 20;
	int most_used_ore = 0;

	sf::Text text_name_interface;
	sf::Vector2f position_name_interface{ 755,170 };
	sf::Texture texture_equipment;

	sf::Sprite item_preview;
	sf::Vector2f position_item_preview{ 470,455 };
	sf::Vector2f size_item_preview{ 125,200 };
	sf::Vector2f position_weapon{ 495,455 };
	sf::Vector2f size_weapon{ 80,80 };
	float item_level = 1; 
	int number_enchantment = 1;
	int row_weapon = 1;
	int number_used_enchantments = 0;

	sf::Sprite stick;
	sf::Texture texture_stick;
	sf::Vector2f size_stick{ 56,20 };
	sf::Vector2f position_stick{ position_item_preview.x - 60, position_item_preview.y - 75 - size_item_preview.y/2-30 };
	float stick_needed = 0;
	
	sf::Text text_stick;
	sf::String string_stick;
	sf::Vector2f position_text_stick{ position_stick.x + size_stick.x / 2 + 35,position_stick.y - 10};

	sf::Text text_ilvl_item;
	sf::String string_ilvl_item;
	sf::Vector2f position_ilvl_item{ position_item_preview.x ,position_item_preview.y  + 50 -30 };

	sf::Sprite button_increase_ilvl;
	sf::Sprite button_decrease_ilvl;
	sf::Texture texture_button_increase_ilvl;
	sf::Texture texture_button_decrease_ilvl;
	sf::Vector2f position_button_increase_ilvl{ position_text_stick.x + 50, position_item_preview .y - size_item_preview.y/2 - 77};
	sf::Vector2f position_button_decrease_ilvl{ position_text_stick.x  + 30, position_item_preview.y - size_item_preview.y / 2 - 77 };
	sf::Vector2f size_button{ 16,16 };

	sf::Sprite ores[number_ores];
	sf::Vector2f size_ores{ 40,32 };
	sf::Texture texture_ores[number_ores];
	sf::Vector2f position_first_ore{ position_item_preview.x + 190,position_item_preview.y - 50 - size_item_preview.y / 2 -30 };
	sf::Sprite button_increase_ore[number_ores];
	sf::Sprite button_decrease_ore[number_ores];
	sf::Vector2f position_first_text_ores{ position_first_ore.x + 35,position_first_ore.y - 0 };
	sf::Vector2f position_first_button_increase{ position_first_text_ores.x  + 208, position_first_text_ores.y + 1.5};
	sf::Vector2f position_first_button_decrease{ position_first_text_ores.x  + 180, position_first_text_ores.y + 1.5};
	sf::Text text_ores[number_ores];
	sf::String string_ores[number_ores];
	float ores_y_modifier = 85;
	float number_using_ores[number_ores]{ 0,0,0,0 };

	sf::Sprite magical_sand;
	sf::Texture texture_magical_sand;
	sf::Vector2f position_magical_sand{ position_item_preview.x + 590, position_item_preview.y - size_item_preview.y / 4 - 105};
	sf::Vector2f size_magical_sand{ 44,32 };
	sf::Text text_magical_sand;
	sf::String string_magical_sand;
	sf::Vector2f position_text_magical_sand{ position_magical_sand.x, position_magical_sand.y - size_magical_sand.y / 2 - 50 };
	int sand_needed = 1; 

	sf::Sprite button_increase_sand;
	sf::Sprite button_decrease_sand;
	sf::Vector2f position_button_increase_sand{ position_text_magical_sand.x + 15, position_text_magical_sand.y  + 30 };
	sf::Vector2f position_button_decrease_sand{ position_text_magical_sand.x - 15, position_text_magical_sand.y  + 30 };

	sf::CircleShape sockets[number_maximum_enchantments];
	float radius_socket = 20;
	float distance_between_socket = 12;
	sf::Vector2f position_first_socket{ position_magical_sand .x - radius_socket*3 - distance_between_socket,position_magical_sand.y + 100 };
	int socket_thickness = 4;

	sf::Text text_creation;
	sf::String string_creation = "Create Weapon";
	sf::Vector2f position_text_creation{ position_magical_sand.x - 20,position_magical_sand.y + 280 };

	sf::RectangleShape black_screen;
	sf::Vector2f size_black_screen{ 2500,2500};
	sf::Color color_black_screen{ 0, 0, 0, 230 };

	sf::Text text_next;
	sf::Vector2f position_text_next{ 800,675 };
	sf::String string_next = "Next";

	sf::Text text_weapon_bonus[number_maximum_weapon_bonus];
	sf::String string_weapon_bonus[number_maximum_weapon_bonus];
	sf::Vector2f position_first_weapon_bonus{ 800,150 };
	float distance_between_weapon_bonus = 35;

	sf::Text text_talent_bonus[3];
	sf::String string_talent_bonus[3];
	sf::Vector2f position_first_talent_bonus{ 1325,340 };
	float distance_between_talent_bonus = 60;

	sf::Sprite interface_crafting;
	sf::Texture texture_interface;
	sf::Vector2f position_interface{350,125};
	sf::Vector2f size_interface{ 800,500 };

	int GetMostUsedOre();
	int GetTalentBonus();
	int GetRarityItem();
public:
	CraftingInterface();
	~CraftingInterface();

	bool CanBeClosed() { return !showing_created_weapon; }
	void ShowingCreatedWeapon(sf::Vector2f mouse_position);
	sf::Vector2f GetRangeBonus(int type_bonus, float item_level);
	bool CheckIfEnoughMaterial(std::shared_ptr<Player> &player);
	void CreateWeapon(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void Draw(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void CreateWeaponBonusText(std::vector<int> listTypeBonus, std::vector<float> listBonus, std::vector<sf::Vector2f> listRangeBonus, std::vector<int> talent_bonus, std::vector<int> talent_level_bonus);
	sf::String GetStringBonus(int type_bonus);
	void CreateRectangleInformation(sf::Vector2f mouse_position);
	void UpdateStyleInterface(int style);
};

