#include "stdafx.h"
#include "PlayerIconeBonus.h"

PlayerIconeBonus::PlayerIconeBonus()
{
	texture_icone.loadFromFile("BonusStaticIcone.png");

	int counter_x = 0;
	int counter_y = 0;
	for (int i = 0; i < number_bonus; i++)
	{
		sprite_icone[i] = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), size_icone, texture_icone);
		sprite_icone[i].setTextureRect(sf::IntRect(size_icone.x*i, 0, size_icone.x, size_icone.y));
		position_icone[i] = position_first_icone + sf::Vector2f(counter_x * size_icone.x + counter_x, counter_y * size_icone.y + counter_y);
		counter_x++;
		if (counter_x == 2)
		{
			counter_x = 0;
			counter_y++;
		}
	}
}

PlayerIconeBonus::~PlayerIconeBonus()
{
}

void PlayerIconeBonus::Update(bool out_battle, float attack_bonus, float  health_bonus, float armor_bonus, float speed_bonus, float regen_bonus, bool immune_bonus, float ats_bonus)
{
	can_draw[PeaceIcone_Self] = out_battle;

	can_draw[ImmunityIcone_Self] = immune_bonus;

	if (attack_bonus > 0)
	{
		sprite_icone[AttackIcone_Self].setTextureRect(sf::IntRect(size_icone.x*AttackIcone_Self, 0, size_icone.x, size_icone.y));
		can_draw[AttackIcone_Self] = true;
	}
	else if (attack_bonus < 0)
	{
		sprite_icone[AttackIcone_Self].setTextureRect(sf::IntRect(size_icone.x*AttackIcone_Self, size_icone.y, size_icone.x, size_icone.y));
		can_draw[AttackIcone_Self] = true;
	}
	else
	{
		can_draw[AttackIcone_Self] = false;
	}

	if (health_bonus > 0)
	{
		sprite_icone[HealthIcone_Self].setTextureRect(sf::IntRect(size_icone.x*HealthIcone_Self, 0, size_icone.x, size_icone.y));
		can_draw[HealthIcone_Self] = true;
	}
	else if (health_bonus < 0)
	{
		sprite_icone[HealthIcone_Self].setTextureRect(sf::IntRect(size_icone.x*HealthIcone_Self, size_icone.y, size_icone.x, size_icone.y));
		can_draw[HealthIcone_Self] = true;
	}
	else
	{
		can_draw[HealthIcone_Self] = false;
	}

	if (armor_bonus > 0)
	{
		sprite_icone[ArmorIcone_Self].setTextureRect(sf::IntRect(size_icone.x*ArmorIcone_Self, 0, size_icone.x, size_icone.y));
		can_draw[ArmorIcone_Self] = true;
	}
	else if (armor_bonus < 0)
	{
		sprite_icone[ArmorIcone_Self].setTextureRect(sf::IntRect(size_icone.x*ArmorIcone_Self, size_icone.y, size_icone.x, size_icone.y));
		can_draw[ArmorIcone_Self] = true;
	}
	else
	{
		can_draw[ArmorIcone_Self] = false;
	}

	if (speed_bonus > 0)
	{
		sprite_icone[SpeedIcone_Self].setTextureRect(sf::IntRect(size_icone.x*SpeedIcone_Self, 0, size_icone.x, size_icone.y));
		can_draw[SpeedIcone_Self] = true;
	}
	else if (speed_bonus < 0)
	{
		sprite_icone[SpeedIcone_Self].setTextureRect(sf::IntRect(size_icone.x*SpeedIcone_Self, size_icone.y, size_icone.x, size_icone.y));
		can_draw[SpeedIcone_Self] = true;
	}
	else
	{
		can_draw[SpeedIcone_Self] = false;
	}

	if (regen_bonus > 0)
	{
		sprite_icone[RegenerationIcone_Self].setTextureRect(sf::IntRect(size_icone.x*RegenerationIcone_Self, 0, size_icone.x, size_icone.y));
		can_draw[RegenerationIcone_Self] = true;
	}
	else if (regen_bonus < 0)
	{
		sprite_icone[RegenerationIcone_Self].setTextureRect(sf::IntRect(size_icone.x*RegenerationIcone_Self, size_icone.y, size_icone.x, size_icone.y));
		can_draw[RegenerationIcone_Self] = true;
	}
	else
	{
		can_draw[RegenerationIcone_Self] = false;
	}

	if (ats_bonus > 0)
	{
		sprite_icone[AttackSpeedIcone_Self].setTextureRect(sf::IntRect(size_icone.x*AttackSpeedIcone_Self, 0, size_icone.x, size_icone.y));
		can_draw[AttackSpeedIcone_Self] = true;
	}
	else if (ats_bonus < 0)
	{
		sprite_icone[AttackSpeedIcone_Self].setTextureRect(sf::IntRect(size_icone.x*AttackSpeedIcone_Self, size_icone.y, size_icone.x, size_icone.y));
		can_draw[AttackSpeedIcone_Self] = true;
	}
	else
	{
		can_draw[AttackSpeedIcone_Self] = false;
	}
}

void PlayerIconeBonus::Draw(sf::RenderWindow &window,sf::Vector2f position_player)
{
	for (int i = 0; i < number_bonus; i++)
	{
		if (can_draw[i])
		{
			sprite_icone[i].setPosition(position_player + position_icone[i]);
			window.draw(sprite_icone[i]);
		}
	}
}
