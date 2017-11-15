#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Font.hpp>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include "Fireball.h"
#include "Blob.h"
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "FireballGenerator.h"
#include "TextGenerator.h"
#include "UserInterface.h"
#include "MainInterface.h"
#include "Davbhear.h"
#include "MonsterGenerator.h"
#include "ExplosionGenerator.h"
#include "SkillManagement.h"
#include "SkillHugeFireball.h"
#include "SkillBase.h"
#include "PlayerStaticInterface.h"

class MainLoop
{
private : 

#pragma region variables
	bool collision_blob_fireball = false;
	float window_height_f = 800;
	float window_width_f = 1600;
	bool isPlaying = false;
	sf::Vector2i map[100][100];
	sf::Vector2i loadcounter = sf::Vector2i(0, 0);
	sf::Texture tiletexture;
	float tile_map_size = 64;
	sf::Sprite tile;
	sf::Texture screen_layer_texture;
	sf::Clock game_timer_before_start;
	sf::View view_player;
	sf::Vector2f position_view_player = sf::Vector2f(0, 0);
#pragma endregion variables
	/*
#pragma region Calls
	void entity_creation();
	void textures_loading();
	void set_view();
	void map_loading();
	void test_interface_creation();
#pragma endregion Calls*/

	sf::Font font;
	sf::Text text;
	sf::String string_of_text;
	sf::RectangleShape rect_test;
	Player player;
	Fireball fireball;
	FireballGenerator fireballgenerator;
	MonsterGenerator monster_generator;
	TextGenerator text_generator;
	UserInterface user_interface;
	ExplosionGenerator explosion_generator;
	SkillManagement skill_manager;
	//sf::RenderWindow &window;
	
	void textures_loading();
	void map_loading();
	void set_view();
	void entity_creation();
	void test_interface_creation();

public:
	int Starter(sf::RenderWindow &aWindow);

};
