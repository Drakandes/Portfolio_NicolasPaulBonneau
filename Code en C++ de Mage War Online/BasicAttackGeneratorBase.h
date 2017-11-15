#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <iostream>

class Player;

class BasicAttackGeneratorBase
{
public:
	BasicAttackGeneratorBase();
	~BasicAttackGeneratorBase();

	virtual void GenerateOneFireball(sf::RenderWindow &window, sf::Vector2f &position_view_player, sf::Vector2f &position_player, float player_damage, float player_attack_speed, bool is_player_stunned, std::shared_ptr<Player> player) { std::cout << "Error" << std::endl; }
};

