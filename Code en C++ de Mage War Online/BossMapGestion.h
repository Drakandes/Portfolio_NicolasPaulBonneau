#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalFunction.h"
#include "GlobalEnum.h"
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include "NotificationSystem.h"
#include "Viking.h"
#include "Molly.h"
#include "Minimap.h"
#include "MollyPillar.h"
#include "VikingPillar.h"

class BossMapGestion
{
	sf::Font font;

	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	int type_boss_fighting = NoBoss;
	int counter_countdown = 0;
	int timer_countdown = 10;

	float damage_death_tile = 1500;

	std::vector<std::shared_ptr<MonsterBase>> boss;

	bool showing_countdown = false;
	bool fighting = false;
	bool boss_fight_started = false;
	bool defeated = false;
	bool can_check_defeated = false;

	sf::Text text_countdown;
	sf::Clock clock_duration_fight;
	sf::Clock clock_death_tile;
	sf::Clock clock_collision_wall_boss;

	sf::Vector2i map_tile_size{ 1,1 };

	std::vector<sf::Vector2f> ListPositionInvisibleWall;
	std::vector<sf::RectangleShape> ListInvisibleWall;
	std::vector<std::vector<bool>> ListIfDeathTile;

	std::vector<std::shared_ptr<ProjectileBase>> listPillars;

	void CreateInvisibleWall(std::vector<std::vector<sf::Vector2i>> map);
	void CreatePillars(std::shared_ptr<Player> player);
	void CreateNotice(float experience_given, float money_given, sf::Vector2f fragments_given);
public:
	BossMapGestion();
	~BossMapGestion();

	std::vector<std::vector<sf::Vector2i>> GetBossMap(int type_boss, std::shared_ptr<Player> player);
	void StartBossFight(int type_boss);
	bool GetIfFighting() { return fighting; }
	bool GetIfBossFightStarted() { return boss_fight_started; }
	bool GetIfBossDefeated() { bool tmp = defeated; defeated = false; return tmp; }
	sf::Vector2i GetBossMapNumberTile() {return map_tile_size;}
	void UpdateBossFight(std::shared_ptr<Player> player, float DELTATIME, sf::Vector2f position_view_player, TextGenerator &text_generator);
	void DrawBoss();
	void DrawBossInterface(sf::RenderWindow &window);
	void CheckCollisionWithInvisibleWall(std::shared_ptr<Player> player);
	void FightOver(bool defeated, std::shared_ptr<Player> player);
};

