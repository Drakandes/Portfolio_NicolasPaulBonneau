#include "stdafx.h"
#include "BaseSimpleProjectile.h"


BaseSimpleProjectile::BaseSimpleProjectile()
{

}

BaseSimpleProjectile::~BaseSimpleProjectile()
{
}

void BaseSimpleProjectile::Update(float DELTATIME, sf::Vector2f player_position)
{
	MovementGestion(DELTATIME);
}

void  BaseSimpleProjectile::MovementGestion(float DELTATIME)
{
	projectile.move((cos(direction_projectile * PI / 180))*-speed_projectile*DELTATIME, (sin(direction_projectile * PI / 180))*-speed_projectile*DELTATIME);
	sf::Vector2f projectile_position = projectile.getPosition();

	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_origin, projectile_position) > range_projectile)
	{
		is_to_delete = true;
	}
}

sf::Vector2f  BaseSimpleProjectile::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f  BaseSimpleProjectile::GetSize()
{
	return size_projectile;
}

int  BaseSimpleProjectile::GetRayon()
{
	return rayon;
}

float  BaseSimpleProjectile::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool  BaseSimpleProjectile::IsNeedToDelete()
{
	return is_to_delete;
}

void BaseSimpleProjectile::Draw(sf::RenderWindow &window)
{


	window.draw(projectile);
}

void BaseSimpleProjectile::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 18));
	window.draw(shadow);
}

sf::Vector2f BaseSimpleProjectile::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, -20);
}

bool BaseSimpleProjectile::CanAffectMonster() { return can_affect_monster; }

bool BaseSimpleProjectile::CanAffectPlayer() { return can_affect_player; }

void BaseSimpleProjectile::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
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
			is_to_delete = true;
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
			is_to_delete = true;
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

void BaseSimpleProjectile::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool BaseSimpleProjectile::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}
