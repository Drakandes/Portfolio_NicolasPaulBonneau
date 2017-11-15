#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Text.h"
#include <iostream>
#include <list>
#include <string>
#include <cstring>
#include "TextBoxGenerator.h"
#include "Player.h"

class ControlsInterface
{
private:
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	std::shared_ptr<Player> player_ptr;
	enum {Beginner,Intermediate,Expert};
	enum {A,S,D,W};
	const static int number_shortcuts = 10;
	sf::RectangleShape rect_black;
	sf::Font font;
	sf::Text controls_text;
	sf::Text control_movement;
	sf::Text control_W;
	sf::Text control_S;
	sf::Text control_A;
	sf::Text control_D;
	sf::Text text_exit_button;
	sf::Text text_shortcuts[number_shortcuts];
	sf::Text text_save;
	sf::Text text_exit;
	sf::Text text_resolution;
	sf::Text text_language;
	sf::String string_shortcuts[number_shortcuts];
	sf::Text text_key_shortcuts[number_shortcuts];
	sf::String string_key_shortcuts[number_shortcuts];
	sf::Text text_tips[3];
	sf::String string_text_tips[3];
	sf::RectangleShape rect_control_A;
	sf::RectangleShape rect_control_S;
	sf::RectangleShape rect_control_W;
	sf::RectangleShape rect_control_D;
	sf::Sprite player_image_up;
	sf::Sprite player_image_down;
	sf::Sprite player_image_right;
	sf::Sprite player_image_left;
	float distance_between_shortcurts = 45;
	sf::Texture player_texture;
	sf::Texture texture_interface;
	sf::Vector2f position_title{ 800,75 };
	sf::Vector2f position_first_text_shortcuts{ 275,295 };
	sf::Vector2f position_text_moving_around{ 275,position_first_text_shortcuts.y - distance_between_shortcurts };
	sf::Vector2f position_first_text_key_shortcuts{ 550,295 };
	sf::Vector2f position_key_movement[4];
	sf::Vector2f position_sprite_movement[4];
	sf::Vector2f position_first_text_tips{ 850,300 };
	sf::Vector2f position_text_save{ 1475,700 };
	sf::Vector2f position_text_exit{ 125,700 };
	sf::Vector2f position_text_resolution{ 800,700 };
	sf::Vector2f position_text_language{ 800,700 };
	int character_size_24 = 24;
	int player_image_size_x = 24;
	int player_image_size_y = 32;
	int source_x = 0;
	sf::Clock player_animation_clock;
	sf::Clock clock_click;
	bool in_game_interface = false;
	bool do_once = false;
	bool language_switched = false;
public:
	ControlsInterface();
	~ControlsInterface();

	void InitAll(bool init_in_game);
	void Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void Draw(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void AnimationGestion();
	void InitMovementControls();
	void InitExitButton();
	void CreateRectInformation(sf::Vector2f mouse_position);
	sf::String Interaction( sf::Vector2f mouse_position);
};

