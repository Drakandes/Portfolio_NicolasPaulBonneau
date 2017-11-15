#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "IncludeAllMonsters.h"
#include <iostream>
#include <list>
#include <vector>
#include "FireballGenerator.h"
#include "Player.h"
#include "TextGenerator.h"
#include "GlobalEnum.h"
#include "VineGenerator.h"
#include "BubbleGenerator.h"
#include "MainQuadtree.h"
#include "Minimap.h"
#include "NotificationSystem.h"

class MonsterGenerator
{
private:
	const static int number_type_monsters = 13;
	float time_between_entities = 0.5;
	sf::Clock clock_monster_generation;
	sf::Clock clock_monster_chasing_player_cooldown;
	sf::Clock clock_restraining_fps;

	float map_width = 0;
	sf::Vector2f center_map{ 0,0 };
	sf::Vector2f size_current_map;
	float timer_spawn_monster_die = 30;
	float timer_spawn_normal = 10;
	float guardian_distance_from_player = 600;
	float range_spawn_no_monster = 2500;
	int number_maximum_monster = 6;
	int number_maximum_monster_elite =  1;
	int size_spawn = 2000;
	int counter_spawn_checking = 0;
	int level_map = 1;
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	int number_guardian_alive = 0;
	sf::Clock clock_generating_monster;
	std::vector<sf::Vector2f> listSpawnLocation;
	std::vector<sf::Clock> listSpawnClock;
	std::vector<int> listSpawnMonsterQuantity;
	std::vector<float> listSpawnClockTimer;
	std::vector<int> listSpawnMonsterEliteQuantity;
	std::vector<int> listLimitMonsterQuantity;
	std::vector<int> listLimitMonsterEliteQuantity;
	std::vector<bool> listSpawnActivated;
	std::vector<sf::RectangleShape> listRectSpawn;
	sf::Font font;
	bool ritual_started = false;

	std::vector<sf::Vector2f> listPositionGuardian;

	void CreateNotice(float experience_given, float money_given, sf::Vector2f fragments_given);
	sf::Vector2f GetNewPositionMonster(int id_spawn);

	sf::RectangleShape rect_spawn_point;
public:
	std::list<std::shared_ptr<MonsterBase>> listMonster;
	std::list<std::shared_ptr<MonsterBase>> listActivatedMonster;

	MonsterGenerator();
	~MonsterGenerator();

	void SpawnSpecificMonster(int type_monster_to_spawn, sf::Vector2f position, sf::Vector2f position_spawn, int id_spawn, float size_spawn, int level_monster, bool is_elite, bool is_guardian);
	void GenerateEntities();
	void Update(sf::FloatRect map_part_activated, std::shared_ptr<Player> player, TextGenerator &text_generator , float DELTATIME);
	void DrawToScreen(sf::RenderWindow &window, sf::View &view_player);
	void FirstDrawToScreen(TextGenerator &text_generator, sf::RenderWindow &window, sf::View &view_player);
	void CreateSpawns(sf::Vector2f size_map, int map_level, sf::Vector2f spawn_point);
	void ClearSpawns();
	void StartRitual(sf::Vector2f position_player);
	void SpawnRandomMonsterAroundArea(sf::Vector2f position, int number_monsters);
	void SpawnMonsterInEachSpawn(int number_monsters);
	std::shared_ptr<MonsterBase> GetMonsterCloserToPosition(sf::Vector2f position);
	void ModifiySpawnWithSpawnPoint(sf::Vector2f spawn_point);
};

