#include "stdafx.h"
#include "SentryProjectile.h"
SentryProjectile::SentryProjectile()
{
	if (!texture_projectile.loadFromFile("Bat_projectile.png"))
	{
		std::cout << "Error while loading vine projectile texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("SentryProjectileShadow.png"))
	{
		std::cout << "Error while loading fireball projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

SentryProjectile::~SentryProjectile()
{
}

void  SentryProjectile::Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, float speed_received, int id_caster)
{
	id_parent = id_caster;
	speed_projectile = speed_received;
	direction_projectile = direction_projectile_received;
	damage_initial = damage_received;
	damage = damage_received;
	position_origin = position_initial;
	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(rotation_spinning_projectile);	
	shadow.setRotation(rotation_spinning_projectile);
}

void SentryProjectile::Update(float DELTATIME, sf::Vector2f player_position)
{
	MovementGestion(DELTATIME);
}

void  SentryProjectile::MovementGestion(float DELTATIME)
{
	if (clock_movement.getElapsedTime().asSeconds() >= FPS_LIMIT * 2)
	{
		projectile.move((cos(direction_projectile * PI / 180))*-speed_projectile*DELTATIME, (sin(direction_projectile * PI / 180))*-speed_projectile*DELTATIME);
		sf::Vector2f projectile_position = projectile.getPosition();
		if (GlobalFunction::GetDistanceBetweenTwoPositions(position_origin, projectile_position) > range_projectile)
		{
			is_to_delete = true;
		}
		clock_movement.restart();
	}

	projectile.setRotation(rotation_spinning_projectile);
	shadow.setRotation(rotation_spinning_projectile);
	rotation_spinning_projectile -= 27;
	if (rotation_spinning_projectile < 0)
	{
		rotation_spinning_projectile = 360;
	}
}

sf::Vector2f  SentryProjectile::GetCurrentPosition()
{
	return projectile.getPosition();
}

void  SentryProjectile::DrawToScreen(sf::RenderWindow &window)
{
	//window.draw(projectile);
}

sf::Vector2f  SentryProjectile::GetSize()
{
	return size_projectile;
}

int  SentryProjectile::GetRayon()
{
	return rayon;
}

float  SentryProjectile::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool  SentryProjectile::IsNeedToDelete()
{
	return is_to_delete;
}

bool  SentryProjectile::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (projectile.getGlobalBounds().intersects(rect_collision))
	{
		is_to_delete = true;
		return true;
	}
	return false;
}

void SentryProjectile::Draw(sf::RenderWindow &window)
{
	

	window.draw(projectile);
}

void SentryProjectile::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 18));
	window.draw(shadow);
}

sf::Vector2f SentryProjectile::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool SentryProjectile::CanAffectMonster() { return false; }

bool SentryProjectile::CanAffectPlayer() { return true; }

void SentryProjectile::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
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

void SentryProjectile::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool SentryProjectile::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}