#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SpriteBase.h"
#include "CollisionalObject.h"
#include "GlobalFunction.h"
#include <vector>
#include "Pillar.h"
#include "Player.h"

class Player;

class PillarGestion
{
private:
	enum TypePillar { Self_Damage, Self_Speed, Self_Exp, Self_Health };
	std::vector<std::shared_ptr<Pillar>> ListPillar;
	const static int number_pillar = 4;

	sf::Clock clock_activation;
public:
	PillarGestion();
	~PillarGestion();

	void Init(sf::Vector2f size_map);
	void ResetPillar();
	sf::Vector2i Update(std::shared_ptr<Player> &player, float DELTATIME);
	void AddPillarDraw();
};

