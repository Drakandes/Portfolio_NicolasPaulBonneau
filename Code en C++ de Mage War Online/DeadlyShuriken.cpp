#include "stdafx.h"
#include "DeadlyShuriken.h"

DeadlyShuriken::DeadlyShuriken()
{
	texture_projectile.loadFromFile("DeadlyShuriken.png");
	shadow_texture.loadFromFile("DeadlyShurikenShadow.png");
}

DeadlyShuriken::~DeadlyShuriken()
{
}

void DeadlyShuriken::Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, int id_caster, float speed, bool can_affect_player, bool can_affect_monster, float range_projectile)
{
	id_parent = id_caster;
	direction_projectile = direction_projectile_received;
	damage_initial = damage_received;
	damage = damage_received;
	position_origin = position_initial;
	this->can_affect_player = can_affect_player;
	this->can_affect_monster = can_affect_monster;

	size_projectile = sf::Vector2f(32, 32);
	shadow_size = size_projectile;
	this->range_projectile = range_projectile;
	speed_projectile = speed;

	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));

	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

void DeadlyShuriken::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();
	float armor_penetration = 0;
	if (parent != NULL)
	{
		armor_penetration = parent->GetArmorPenetrationPercent();
	}

	if (type_object == Player_E)
	{
		if (CanAffectPlayer())
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
		if (CanAffectMonster())
		{
			float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, armor_penetration);
			if (parent != NULL)
			{
				parent->OnHitGestion(id_object, damage_dealt, type_object, SkillProjectile_E);
			}

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
		if (!object_collided->CheckIfProjectileDisable())
		{
			is_to_delete = true;
		}
	}
}