#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <string>
#include <cstring>
#include <list>
#include <vector>
#include "Player.h"
#include "MainQuadtree.h"

class PlayerGestion
{
private:

public:
	std::list<std::shared_ptr<Player>> listPlayers;

	PlayerGestion();
	~PlayerGestion();

	void AddPlayer(sf::Vector2f window_dimension);
	void UpdateAllPlayer(float DELTATIME, SkillManagement &skill_manager, sf::Vector2f mouse_position);
	std::list<std::shared_ptr<Player>> GetListPlayers() {return listPlayers;};
	void AddPlayerToDrawList();
};

