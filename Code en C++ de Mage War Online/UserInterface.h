#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Text.h"
#include <iostream>
#include <list>
#include "MainInterface.h"
#include "ControlsInterface.h"
#include "SkillInterface.h"
#include "PlayerInformationInterface.h"
#include "ArmorInterface.h"
#include "GemInterface.h"
#include "CraftingInterface.h"
#include "ClassMenu_interface.h"
#include "TalentTreeInterface.h"
#include "InventoryInterface.h"
#include "VendorInterface.h"
#include "ControlsInterface.h"
#include "AchievementInterface.h"
#include "MageSelectionInterface.h"
#include "PetInterface.h"
#include "FeatInterface.h"

class UserInterface
{
private:
	bool is_playing = false;
	bool is_exiting = false;
	bool is_controls = false;
	bool display_panel = false;
	GemInterface gem_interface;
	MainInterface main_interface;
	CraftingInterface crafting_interface;
	ControlsInterface controls_interface;
	SkillInterface skill_interface;
	ArmorInterface armor_interface;
	TalentTreeInterface talent_interface;
	ClassMenu_interface class_menu_interface;
	PlayerInformationInterface player_information_interface;
	InventoryInterface inventory_interface;
	VendorInterface vendor_interface;
	ControlsInterface control_interface_in_game;
	AchievementInterface achievement_interface;
	MageSelectionInterface mage_selection_interface;
	PetInterface pet_interface;
	FeatInterface feat_interface;
	sf::Clock clock_toggle_interface;
	int language;
	int current_style_interface = 0;

	std::vector<sf::Texture> ListTextureInterface;

	const static int number_interface = 13;
	sf::Font font;
	sf::Texture texture_panel;
	std::vector<sf::String> ListNameInterfaces;
	sf::Sprite sprite_name_panel[number_interface];
	sf::Text text_name_panel[number_interface];
	sf::Vector2f size_panel{150,45};
	sf::Vector2f position_first_panel{ -size_panel.x * 2 - 35, 350};
	int size_letter_panel = 20;
	sf::Clock clock_click;

	sf::Text text_style;
	sf::Sprite sprite_panel_style;
	sf::Vector2f position_text_style;
	sf::Vector2f position_panel_style;

	void UpdateStyleInterface();
public:
	UserInterface();
	~UserInterface();

	bool IsPlaying();
	void DrawToScreenMainInterface(sf::RenderWindow &window);
	void MainInterfaceInteraction(sf::RenderWindow &window);
	bool IsToClose();
	void WhilePlayingInterfaceGestion(std::shared_ptr<Player> player);
	void DrawToScreenOpenedInterfacesWhilePlaying(sf::RenderWindow &window, sf::Vector2f position_view_player, int opened_interface);
	void InitAllInterfaces(std::shared_ptr<Player> player);
	void WhilePlayingAllInteractionInterface(sf::Vector2f mouse_position, sf::Vector2f position_view_player, std::shared_ptr<Player> player);
};

