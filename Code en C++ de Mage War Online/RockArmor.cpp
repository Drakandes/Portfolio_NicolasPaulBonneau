#include "stdafx.h"
#include "RockArmor.h"

RockArmor::RockArmor()
{
	texture_projectile.loadFromFile("RockArmor.png");
}

RockArmor::~RockArmor()
{
}

void RockArmor::Init(sf::Vector2f &position_initial, float bonus_overtime, int id_caster, bool can_affect_player, bool can_affect_monster, std::shared_ptr<Player> player, int level_skill, int rune, float duration)
{
	this->duration = duration;
	this->rune = rune;
	parent = player;
	id_parent = id_caster;
	this->bonus_overtime = bonus_overtime;
	this->level_skill = level_skill;
	position_origin = position_initial;

	this->can_affect_player = can_affect_player;
	this->can_affect_monster = can_affect_monster;

	size_projectile = sf::Vector2f(48, 64);

	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(direction_projectile);

	if (rune == FirstRune_E)
	{
		parent->GivePlayerChangeStat(DefenseAddition, duration, 10 + 2 * (level_skill - 1));
	}
	else if(rune == SecondRune_E)
	{
		parent->GivePlayerChangeStat(MovementSpeedPercent, duration, -10);
		parent->GivePlayerChangeStat(DamagePercent, duration, 20);
	}
}

float RockArmor::GetDamage()
{
	return damage;
}

void RockArmor::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	
}

void RockArmor::Update(float DELTATIME, sf::Vector2f player_position)
{
	projectile.setPosition(player_position);

	float percent_bonus = 0;

	if (rune == ThirdRune_E)
	{
		percent_bonus = clock_duration.getElapsedTime().asSeconds() / duration - 2;
	}
	else
	{
		percent_bonus = clock_duration.getElapsedTime().asSeconds() / duration;
	}

	parent->GivePlayerChangeStat(DefensePercent, -1, percent_bonus*bonus_overtime);

	sf::Vector2i source_cutting = parent->GetSourceCutting();
	projectile.setTextureRect(sf::IntRect(player_image_size_x * source_cutting.x, source_cutting.y * player_image_size_y, player_image_size_x, player_image_size_y));

	if (clock_duration.getElapsedTime().asSeconds() >= duration)
	{
		is_to_delete = true;
	}
}