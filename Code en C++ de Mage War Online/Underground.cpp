#include "stdafx.h"
#include "Underground.h"

Underground::Underground()
{
	texture_projectile.loadFromFile("Underground.png");
}

Underground::~Underground()
{
}

void Underground::Init(sf::Vector2f &position_initial, float duration, int id_caster, bool can_affect_player, bool can_affect_monster, std::shared_ptr<Player> player, int rune, float duration_immune)
{
	this->duration = duration;
	this->rune = rune;
	parent = player;
	id_parent = id_caster;
	this->duration_immune = duration_immune;
	position_origin = position_initial;

	this->can_affect_player = can_affect_player;
	this->can_affect_monster = can_affect_monster;

	size_projectile = sf::Vector2f(52, 45);

	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
}

float Underground::GetDamage()
{
	return damage;
}

void Underground::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{

}

void Underground::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (clock_duration.getElapsedTime().asSeconds() >= duration)
	{
		is_to_delete = true;

		parent->TeleportEntity(position_origin, 0);
		parent->GivePlayerChangeStat(Immunity, duration_immune, 0);

		if (rune == SecondRune_E)
		{
			parent->GivePlayerChangeStat(MovementSpeedPercent, duration_immune-1, -200);
		}
		else
		{
			parent->GivePlayerChangeStat(MovementSpeedPercent, duration_immune, -200);
		}

		if (rune == ThirdRune_E)
		{
			parent->GivePlayerChangeStat(DamagePercentOverall, duration_immune, 20);
		}
	}
}