#include "stdafx.h"
#include "NetProjectile.h"

NetProjectile::NetProjectile()
{
	if (!texture_projectile.loadFromFile("Net.png"))
	{
		std::cout << "Error while loading energy projectile texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("NetShadow.png"))
	{
		std::cout << "Error while loading energy projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

NetProjectile::~NetProjectile()
{
}

void  NetProjectile::Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, int id_caster)
{
	id_parent = id_caster;
	direction_projectile = direction_projectile_received;
	damage_initial = damage_received;
	damage = damage_received;
	position_origin = position_initial;
	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(direction_projectile - 90);
	shadow.setRotation(direction_projectile - 90);
}

void NetProjectile::Update(float DELTATIME, sf::Vector2f player_position)
{
	MovementGestion(DELTATIME);
}

void  NetProjectile::MovementGestion(float DELTATIME)
{
	projectile.move((cos(direction_projectile * PI / 180))*-speed_projectile*DELTATIME, (sin(direction_projectile * PI / 180))*-speed_projectile*DELTATIME);
	sf::Vector2f projectile_position = projectile.getPosition();

	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_origin, projectile_position) > range_projectile)
	{
		is_to_delete = true;
	}
}

sf::Vector2f  NetProjectile::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f  NetProjectile::GetSize()
{
	return size_projectile;
}

int  NetProjectile::GetRayon()
{
	return rayon;
}

float  NetProjectile::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool  NetProjectile::IsNeedToDelete()
{
	return is_to_delete;
}

void NetProjectile::Draw(sf::RenderWindow &window)
{


	window.draw(projectile);
}

void NetProjectile::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 18));
	window.draw(shadow);
}

sf::Vector2f NetProjectile::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool NetProjectile::CanAffectMonster() { return false; }

bool NetProjectile::CanAffectPlayer() { return true; }

void NetProjectile::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
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

			if (CanChangeObjectStat())
			{
				for (int i = 0; i < GetNumberObjectStatChange(); i++)
				{
					object_collided->GivePlayerChangeStat(GetObjectStatChanging(i), GetObjectStatChangeDuration(i), GetObjectStatChangValue(i));
				}
			}
		}
	}
}

void NetProjectile::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool NetProjectile::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

bool NetProjectile::CanChangeObjectStat() { return true; }

int NetProjectile::GetNumberObjectStatChange() { return 1; }

int NetProjectile::GetObjectStatChanging(int number) { return MovementSpeedPercent; }

float NetProjectile::GetObjectStatChangeDuration(int number) { return slow_duration; }

float NetProjectile::GetObjectStatChangValue(int number) { return slow_percent; }
