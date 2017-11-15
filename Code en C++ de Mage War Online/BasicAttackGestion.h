#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "FireballGenerator.h"
#include "BubbleGenerator.h"
#include "VineGenerator.h"
#include "Boulder.h"
#include "BasicAttackGeneratorBase.h"
#include "SoundGestion.h"

class Player;

class BasicAttackGestion
{
private:
	sf::Clock clock_rate_of_basic_attack;
	std::vector<std::shared_ptr<BasicAttackGeneratorBase>> listGenerators;
public:
	BasicAttackGestion();
	~BasicAttackGestion();

	void GenerateOneFireball(sf::RenderWindow &window, sf::Vector2f &position_view_player, sf::Vector2f &position_player, float player_damage, float player_attack_speed, std::shared_ptr<Player> player);
};

