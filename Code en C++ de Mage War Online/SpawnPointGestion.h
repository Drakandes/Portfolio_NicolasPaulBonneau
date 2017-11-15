#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <string>
#include <cstring>
#include "Player.h"

class SpawnPointGestion
{
private:
	static SpawnPointGestion *s_instance1;

	int language;
	std::shared_ptr<Player> player_pointer;
	sf::Clock clock_notice;

	sf::Texture texture_spawn_point;
	sf::Sprite sprite_spawn_point;

	sf::Sprite sprite_altar;
	sf::Texture texture_altar;

	sf::Vector2f range_from_border{ 200,1000 };
	sf::Vector2f size_map;

	sf::Vector2f GetNewPositionPlayer();
public:
	SpawnPointGestion();
	~SpawnPointGestion();

	static void Initialize()
	{
		s_instance1 = new SpawnPointGestion();
	}
	static SpawnPointGestion *instance()
	{
		if (!s_instance1)
			s_instance1 = new SpawnPointGestion;
		return s_instance1;
	}

	void Init(std::shared_ptr<Player> player,int current_language, sf::Vector2f size_map);
	void Update();
	void Draw(sf::RenderWindow &window);
	void PlayerRespawnGestion();
	void PlayerChangedMapGestion();
	sf::Vector2f GetCenterPosition() { return sprite_altar.getPosition(); }
	sf::FloatRect GetAltarCollisionRect() { return sprite_altar.getGlobalBounds(); }
	sf::Vector2f GetSpawnPointPosition() { return sprite_spawn_point.getPosition(); }
};

