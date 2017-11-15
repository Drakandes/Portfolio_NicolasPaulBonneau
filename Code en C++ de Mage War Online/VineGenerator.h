#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>
#include <string>
#include <cstring>
#include <vector>
#include "IncludeAllSkills.h"
#include "Vine.h"
#include "BasicAttackGeneratorBase.h"

class VineGenerator : public BasicAttackGeneratorBase
{

private:
	sf::Clock clock_rate_of_projectile;
public:
	VineGenerator();
	~VineGenerator();

	virtual void GenerateOneFireball(sf::RenderWindow &window, sf::Vector2f &position_view_player, sf::Vector2f &position_player, float player_damage, float player_attack_speed, bool is_player_stunned, std::shared_ptr<Player> player);
};

