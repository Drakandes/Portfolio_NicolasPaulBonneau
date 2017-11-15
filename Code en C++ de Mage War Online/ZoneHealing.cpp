#include "stdafx.h"
#include "ZoneHealing.h"

ZoneHealing::ZoneHealing()
{
	texture_projectile.loadFromFile("ZoneHealing.png");
}

ZoneHealing::~ZoneHealing()
{
}

void ZoneHealing::Init(sf::Vector2f &position_initial, float healing_done, float duration_projectile_received, int id_caster, bool can_affect_player, bool can_affect_monster)
{
	id_parent = id_caster;
	damage_initial = healing_done;
	direction_projectile = 0;
	damage = damage_initial;
	position_origin = position_initial;
	duration_projectile = duration_projectile_received;
	this->can_affect_player = can_affect_player;
	this->can_affect_monster = can_affect_monster;

	size_projectile = sf::Vector2f(192, 192);
	this->range_projectile = 0;
	speed_projectile = 0;

	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
}

void  ZoneHealing::MovementGestion(float DELTATIME)
{
	if (clock_duration.getElapsedTime().asSeconds() >= duration_projectile + 0.25)
	{
		is_to_delete = true;
	}
	else
	{
		is_to_delete = false;
	}
}

void ZoneHealing::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Player_E)
	{
		if (CanAffectPlayer())
		{
			if (clock_heal.getElapsedTime().asSeconds() >= 1)
			{
				object_collided->HealObject(damage);
				clock_heal.restart();
			}

			if (CanPush())
			{
				object_collided->GetPushedAway(GetDistancePushing(), StrongPush, position_objet, position_self);
			}
			if (CanStun())
			{
				object_collided->ChangeStunTime(GetStunTime());
			}
			if (CanChangeObjectStat())
			{
				for (int i = 0; i < GetNumberObjectStatChange(); i++)
				{
					object_collided->GivePlayerChangeStat(GetObjectStatChanging(i), GetObjectStatChangeDuration(i), GetObjectStatChangValue(i));
				}
			}
			if (CanChangeSkillCooldown())
			{
				object_collided->ChangeASkillCooldown(GetSkillCooldownChanging(), GetNewSkillCooldown());
			}
		}
	}
}

void ZoneHealing::Update(float DELTATIME, sf::Vector2f player_position)
{
	MovementGestion(DELTATIME);
}