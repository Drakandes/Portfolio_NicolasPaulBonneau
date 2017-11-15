#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include <vector>
class PlayerIconeBonus
{
private:
	const static int number_bonus = 8;
	enum IconeBonusEnum{PeaceIcone_Self,AttackIcone_Self,HealthIcone_Self,ArmorIcone_Self,SpeedIcone_Self,RegenerationIcone_Self,ImmunityIcone_Self,AttackSpeedIcone_Self};

	sf::Texture texture_icone;
	sf::Sprite sprite_icone[number_bonus];
	sf::Vector2f size_icone{ 9,9 };
	sf::Vector2f position_icone[number_bonus];
	sf::Vector2f position_first_icone{-50,-21};

	bool can_draw[number_bonus]{ false,false,false,false,false,false,false,false };
public:
	PlayerIconeBonus();
	~PlayerIconeBonus();

	void Update(bool out_battle, float attack_bonus, float  health_bonus, float armor_bonus, float speed_bonus, float regen_bonus, bool immune_bonus, float ats_bonus);
	void Draw(sf::RenderWindow &window, sf::Vector2f position_player);
};

