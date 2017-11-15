#include "stdafx.h"
#include "IceBall.h"

 IceBall:: IceBall()
{
	if (!texture_projectile.loadFromFile("IceBall_penguin.png"))
	{
		std::cout << "Error while loading vine projectile texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("IceBallShadow.png"))
	{
		std::cout << "Error while loading fireball projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

 IceBall::~ IceBall()
{
	 std::shared_ptr<IcePlate> puddle = std::shared_ptr<IcePlate>(new IcePlate());
	 puddle->Init(GetCurrentPosition(), damage / 3, id_parent);
	 ProjectileGestion::instance()->AddObjectToList(puddle);
	 puddle.reset();
}

 void  IceBall::Init(sf::Vector2f &position_player, float range_projectile_received, float damage_received, float direction_projectile_received, float speed_received, int id_caster)
 {
	 id_parent = id_caster;
	 range_projectile = range_projectile_received;
	 speed_projectile = speed_received;
	 direction_projectile = direction_projectile_received;
	 damage_initial = damage_received;
	 damage = damage_received;
	 position_origin = position_player;
	 projectile = GlobalFunction::CreateSprite(position_player, size_projectile, texture_projectile);
	 projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	 projectile.setRotation(rotation_spinning_projectile);
 }

 void IceBall::Update(float DELTATIME, sf::Vector2f player_position)
 {
	 if (clock_movement.getElapsedTime().asSeconds() >= FPS_LIMIT * 2)
	 {
		 projectile.move((cos(direction_projectile * PI / 180))*-speed_projectile*DELTATIME, (sin(direction_projectile * PI / 180))*-speed_projectile*DELTATIME);
		 sf::Vector2f projectile_position = projectile.getPosition();
		 if (GlobalFunction::GetDistanceBetweenTwoPositions(position_origin, projectile_position) > range_projectile)
		 {
			 is_to_delete = true;

			 std::shared_ptr<IcePlate> puddle = std::shared_ptr<IcePlate>(new IcePlate());
			 puddle->Init(GetCurrentPosition(), damage, id_parent);
			 ProjectileGestion::instance()->AddObjectToList(puddle);
			 puddle.reset();
		 }
		 clock_movement.restart();
	 }
 }

sf::Vector2f  IceBall::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f  IceBall::GetSize()
{
	return size_projectile;
}

int  IceBall::GetRayon()
{
	return rayon;
}

float  IceBall::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool  IceBall::IsNeedToDelete()
{
	return is_to_delete;
}

void IceBall::Draw(sf::RenderWindow &window)
{
	
	window.draw(projectile);
}

void IceBall::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 25));
	window.draw(shadow);
}

sf::Vector2f IceBall::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool IceBall::CanStun() { return true; }

float IceBall::GetStunTime() { return stun_duration; }

bool IceBall::CanAffectMonster() { return false; }

bool IceBall::CanAffectPlayer() { return true; }

void IceBall::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

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

	if (type_object == NatureObject_E)
	{
		if (!object_collided->CheckIfProjectileDisable())
		{
			is_to_delete = true;
		}
	}
}

void IceBall::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool IceBall::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

