#include "stdafx.h"
#include "EnergizedBall.h"

EnergizedBall::EnergizedBall()
{
	if (!texture_projectile.loadFromFile("EnergyBall.png"))
	{
		std::cout << "Error while loading energy projectile texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("EnergyBallShadow.png"))
	{
		std::cout << "Error while loading energy projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

EnergizedBall::~EnergizedBall()
{
}

void  EnergizedBall::Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, int id_caster)
{
	id_parent = id_caster;
	direction_projectile = direction_projectile_received;
	damage_initial = damage_received;
	damage = damage_received;
	position_origin = position_initial;
	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
}

void EnergizedBall::Update(float DELTATIME, sf::Vector2f player_position)
{
	MovementGestion(DELTATIME);
}

void  EnergizedBall::MovementGestion(float DELTATIME)
{
	projectile.move((cos(direction_projectile * PI / 180))*-speed_projectile*DELTATIME, (sin(direction_projectile * PI / 180))*-speed_projectile*DELTATIME);
	sf::Vector2f projectile_position = projectile.getPosition();

	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_origin, projectile_position) > range_projectile)
	{
		is_to_delete = true;
	}
}

sf::Vector2f  EnergizedBall::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f  EnergizedBall::GetSize()
{
	return size_projectile;
}

int  EnergizedBall::GetRayon()
{
	return rayon;
}

float  EnergizedBall::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool  EnergizedBall::IsNeedToDelete()
{
	return is_to_delete;
}

void EnergizedBall::Draw(sf::RenderWindow &window)
{


	window.draw(projectile);
}

void EnergizedBall::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 18));
	window.draw(shadow);
}

sf::Vector2f EnergizedBall::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool EnergizedBall::CanAffectMonster() { return false; }

bool EnergizedBall::CanAffectPlayer() { return true; }

void EnergizedBall::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

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

	if (type_object == NatureObject_E)
	{
		if (!object_collided->CheckIfProjectileDisable())
		{
			is_to_delete = true;
		}
	}
}

void EnergizedBall::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool EnergizedBall::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}
