#include "stdafx.h"
#include "RockBelt.h"

RockBelt::RockBelt()
{
	texture_projectile.loadFromFile("RockShield.png");
	shadow_texture.loadFromFile("RockShieldShadow.png");
}

RockBelt::~RockBelt()
{
}

void RockBelt::Init(sf::Vector2f &position_initial, float damage, int id_caster, bool can_affect_player, bool can_affect_monster, std::shared_ptr<Player> player, float duration, float skill_shield_leech)
{
	this->duration = duration;
	parent = player;
	id_parent = id_caster;
	this->damage = damage;
	this->skill_shield_leech = skill_shield_leech;
	position_origin = position_initial;

	this->can_affect_player = can_affect_player;
	this->can_affect_monster = can_affect_monster;

	size_projectile = sf::Vector2f(116, 116);
	shadow_size = size_projectile;

	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(direction_projectile);

	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
	shadow.setRotation(direction_projectile);
}

float RockBelt::GetDamage()
{
	return damage;
}

void RockBelt::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();
	float armor_penetration = 0;

	if (type_object == Player_E)
	{
		if (CanAffectPlayer() && CheckIdObject(id_object))
		{
			float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, 0);

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

	if (type_object == Monster_E)
	{
		if (CanAffectMonster() && CheckIdObject(id_object))
		{
			float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, armor_penetration);
			parent->ShieldObject(damage_dealt*skill_shield_leech / 100);

			TextGenerator::instance()->GenerateOneTextForBlob(position_objet, damage_dealt, size_object, object_collided);

			if (CanIgnite())
			{
				object_collided->GetIgnited(GetTypeIgnition(), GetIgnitionDuration(), GetIgnitionDamage());
			}
			if (CanPush())
			{
				object_collided->GetPushedAway(GetDistancePushing(), StrongPush, position_objet, position_self);
			}
			if (CanSlow())
			{
				object_collided->GetSlowed(1, GetDurationSlow(), GetPercentSlow());
			}
			if (CanStun())
			{
				ChangeStunTime(GetStunTime());
			}
		}
	}

	if (type_object == NatureObject_E)
	{
		if (CheckIdObject(id_object))
		{
			if (!object_collided->CheckIfProjectileDisable())
			{
			}
		}
	}
}

void RockBelt::Update(float DELTATIME, sf::Vector2f player_position)
{
	projectile.setPosition(player_position);
	direction_projectile++;
	if (direction_projectile > 360)
	{
		direction_projectile = 2;
	}
	projectile.setRotation(direction_projectile);
	shadow.setRotation(direction_projectile);

	if (clock_duration.getElapsedTime().asSeconds() >= duration)
	{
		is_to_delete = true;
	}
}

bool RockBelt::CheckIdObject(int id_object)
{
	bool new_object = true;
	int counter = 0;
	std::vector<int>::iterator iterator = ListIdObject.begin();
	while (iterator != ListIdObject.end())
	{
		if ((*iterator) == id_object)
		{
			if (ListClockObject[counter].getElapsedTime().asSeconds() >= time_between_damage)
			{
				ListClockObject[counter].restart();
				return true;
			}
			else
			{
				return false;
			}
			new_object = false;
		}
		counter++;
		iterator++;
	}
	if (new_object)
	{
		sf::Clock clock;
		ListClockObject.push_back(clock);
		ListIdObject.push_back(id_object);
	}
	return true;
}