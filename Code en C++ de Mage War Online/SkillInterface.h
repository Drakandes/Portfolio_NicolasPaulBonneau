#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Text.h"
#include <iostream>
#include <list>
#include "GlobalFunction.h"
#include "ListObjectsSingleton.h"
#include "IncludeAllSkills.h"
#include "TextBoxGenerator.h"
#include "FeatGestion.h"

class SkillInterface
{
private:
	const static int number_skill = 50;
	const static int number_skill_player = 9;
	const static int number_rectangle_information = 5;
	const static int number_different_fragment_type = 5;
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();

	std::vector<sf::Texture> ListTextureInterface;
	std::vector<sf::Texture> ListTextureInterface2;
	std::vector<sf::Texture> ListTextureInterface3;

	int number_current_armor;
	sf::Font font;
	sf::Texture texture_upgrade_skill_level;
	sf::Texture texture_interface;
	sf::Texture texture_erase_skill;
	sf::Texture texture_fragment;
	sf::Texture texture_skillbase_icone;
	sf::Sprite skill_interface_rectangle;
	sf::Sprite sprite_second_interface_rectangle;
	sf::Sprite rectangle_fragment_interface;
	sf::Vector2f skill_interface_size{ 785, 500 };
	sf::Vector2f size_second_rectangle{171,398};
	sf::Vector2f size_fragment_interface{ 375,250 };
	sf::Vector2f skill_interface_position{ 100,100 };
	sf::Vector2f position_fragment_interface { skill_interface_size.x + skill_interface_position.x + size_second_rectangle.x + 50 ,skill_interface_position.y + skill_interface_size .y/2 - size_fragment_interface .y/2};
	sf::Vector2f position_initial_number_fragment{position_fragment_interface.x + 15, position_fragment_interface.y + 100 };
	sf::Text text_fragment_interface_name;
	int skill_interface_name_text_size = 48;
	sf::Vector2f size_skill_icone{ 50,50 };
	sf::Vector2f size_skillbase_icone{ 54,54 };
	sf::Vector2f position_initial_second_rectangle{ skill_interface_position + sf::Vector2f(805,skill_interface_size.y/2 - size_second_rectangle.y/2) };
	sf::Vector2f size_upgrade_skill_level{ 16,16 };
	sf::Vector2f position_initial_skill_icone{ sf::Vector2f(50,150)  + skill_interface_position };
	sf::Vector2f position_initial_skill_icone_player{ position_initial_second_rectangle.x + 45 ,position_initial_second_rectangle.y + 45 };
	sf::Vector2f position_skill_icone[number_skill];
	sf::Vector2f position_skill_icone_player[number_skill_player];
	sf::Vector2f position_skill_level[number_skill];
	sf::Vector2f position_upgrade_skill_level[number_skill];
	sf::Vector2f position_erase_skill;
	sf::Sprite rectangle_skill_icone[number_skill];
	sf::Sprite rectangle_skill_icone_player[number_skill_player];
	sf::Texture texture_skill_icone[number_skill];
	sf::Texture texture_skill_icone_player[number_skill_player];
	sf::Sprite sprite_skill_icone[number_skill];
	sf::Sprite sprite_skill_icone_player[number_skill_player];
	sf::Sprite sprite_erase_skill;
	sf::Vector2i holder{ 0,0 };
	sf::Vector2i holder_player{ 0,0 };
	std::vector<int> player_skills_array;
	std::vector<int> player_skills_level_array;
	std::vector<int> player_skills_level_increasement;
	std::vector<int> player_number_fragments;
	std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors;
	int skill_icone_width = 10;
	int skill_icone_height = 5;
	std::vector<std::shared_ptr<SkillBase>> listAllSkill;
	bool player_skill_icone_created[number_skill_player];
	int slot_changing = -1;
	sf::Clock clock_click;
	sf::String string_skill_level[number_skill];
	sf::Text text_skill_level[number_skill];
	sf::Sprite sprite_upgrade_skill_level[number_skill];
	int character_size_skill_level = 12;
	int character_size_number_fragment = 19;
	sf::RectangleShape rectangle_information;
	sf::String string_rectangle_information[number_rectangle_information];
	sf::Text text_rectangle_information[number_rectangle_information];
	sf::Vector2f position_rectangle_information;
	bool can_create_rectangle_information_skill_upgrade = false;
	sf::Text text_number_fragment[number_different_fragment_type];
	sf::String string_number_fragment[number_different_fragment_type];
	sf::Vector2f position_number_fragment[number_different_fragment_type];

	const static int number_choice_rune = 4;
	sf::Texture texture_rune_interface;
	sf::Sprite rune_interface;
	sf::Vector2f size_rune_interface{ 105,30 };
	sf::Vector2f current_position_rune_interface{ 0,0 };
	sf::RectangleShape rect_rune[number_choice_rune];
	sf::Vector2f position_first_rect_rune{5,5};
	sf::Vector2f size_rect_rune{ 20,20 };
	std::vector<bool> listAvailable;
	bool is_choosing_rune = false;
	int rune_skill_related = -1;
	int rune_currently_using;

public:
	SkillInterface();
	~SkillInterface();

	void GenerateTextBox(int skill_displaying, sf::Vector2f mouse_position, int skill_level, int class_player);
	void CreateSkillInterfaceRectangle();
	void DrawToScreen(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void InitRectangleSkillIcone();
	void UpdateSkillInterfacePosition(sf::Vector2f position_view_player);
	void UpdatePlayerSkill(std::shared_ptr<Player> player);
	void UpdateSkillInterfacePlayerSkill();
	void InitAllSkillIcone();
	void InteractionWithSkillInterface(sf::Vector2f mouse_position, sf::Vector2f position_view_player, std::shared_ptr<Player> player);
	void InitSkillPlayer(std::shared_ptr<Player> player);
	void SkillInterfaceGestionRectangleInformation(sf::Vector2f mouse_position, sf::Vector2f position_view_player, std::shared_ptr<Player> player);
	void InitPlayerNumberFragments(std::shared_ptr<Player> player);
	void UpdatePlayerNumberFragments(std::shared_ptr<Player> player);
	void UpdatePlayerSkillLevel(std::shared_ptr<Player> player);
	void NewPlayerCurrentArmor(std::shared_ptr<Player> player);
	void GiveBackPlayerNewInformation(std::shared_ptr<Player> player);
	void UpdateStyleInterface(int style);
};

