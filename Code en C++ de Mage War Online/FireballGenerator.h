#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Fireball.h"
#include <iostream>
#include <list>
#include <string>
#include <cstring>
#include <vector>
#include "IncludeAllSkills.h"
#include "BasicAttackGeneratorBase.h"

class FireballGenerator : public BasicAttackGeneratorBase
{
private:
	sf::Clock clock_rate_of_fireball;
public:
	FireballGenerator();
	~FireballGenerator();

	virtual void GenerateOneFireball(sf::RenderWindow &window, sf::Vector2f &position_view_player, sf::Vector2f &position_player, float player_damage, float player_attack_speed, bool is_player_stunned, std::shared_ptr<Player> player);
};

