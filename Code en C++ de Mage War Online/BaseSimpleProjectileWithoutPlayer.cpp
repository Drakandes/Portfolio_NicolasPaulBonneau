#include "stdafx.h"
#include "BaseSimpleProjectileWithoutPlayer.h"

BaseSimpleProjectileWithoutPlayer::BaseSimpleProjectileWithoutPlayer()
{

}

BaseSimpleProjectileWithoutPlayer::~BaseSimpleProjectileWithoutPlayer()
{
}

void BaseSimpleProjectileWithoutPlayer::Update(float DELTATIME, sf::Vector2f player_position)
{
	MovementGestion(DELTATIME);
}

void  BaseSimpleProjectileWithoutPlayer::MovementGestion(float DELTATIME)
{
	projectile.move((cos(direction_projectile * PI / 180))*-speed_projectile*DELTATIME, (sin(direction_projectile * PI / 180))*-speed_projectile*DELTATIME);
	sf::Vector2f projectile_position = projectile.getPosition();

	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_origin, projectile_position) > range_projectile)
	{
		is_to_delete = true;
	}
}

sf::Vector2f  BaseSimpleProjectileWithoutPlayer::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f  BaseSimpleProjectileWithoutPlayer::GetSize()
{
	return size_projectile;
}

int  BaseSimpleProjectileWithoutPlayer::GetRayon()
{
	return rayon;
}

float  BaseSimpleProjectileWithoutPlayer::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool  BaseSimpleProjectileWithoutPlayer::IsNeedToDelete()
{
	return is_to_delete;
}

void BaseSimpleProjectileWithoutPlayer::Draw(sf::RenderWindow &window)
{


	window.draw(projectile);
}

void BaseSimpleProjectileWithoutPlayer::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 18));
	window.draw(shadow);
}

sf::Vector2f BaseSimpleProjectileWithoutPlayer::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, -20);
}

bool BaseSimpleProjectileWithoutPlayer::CanAffectMonster() { return can_affect_monster; }

bool BaseSimpleProjectileWithoutPlayer::CanAffectPlayer() { return can_affect_player; }

void BaseSimpleProjectileWithoutPlayer::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();
	float armor_penetration = 0;

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

void BaseSimpleProjectileWithoutPlayer::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool BaseSimpleProjectileWithoutPlayer::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}
