#include "stdafx.h"
#include "IceBlock.h"

IceBlock::IceBlock()
{
	if (!texture_projectile.loadFromFile("IceBlock.png"))
	{
		std::cout << "Error while loading ice block texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("IceBlockShadow.png"))
	{
		std::cout << "Error while loading fireball projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

IceBlock::~IceBlock()
{
}

void IceBlock::Init(sf::Vector2f position_initial, float duration_received, float distance_pushing_received)
{
	distance_pushing = distance_pushing_received;
	position_projectile = position_initial;
	projectile = GlobalFunction::CreateSprite(position_projectile, size_projectile, texture_projectile);
	duration_projectile = duration_received;
	been_init = true;
}

void IceBlock::Update(float DELTATIME, sf::Vector2f player_position)
{
}

sf::Vector2f IceBlock::GetCurrentPosition()
{
	return projectile.getPosition();
}

void IceBlock::CuttingSprite()
{

}

sf::Vector2f IceBlock::GetSize()
{
	return size_projectile;
}

int IceBlock::GetRayon()
{
	return rayon;
}

float IceBlock::GetDamage()
{
	return 0;
}

bool IceBlock::IsNeedToDelete()
{
	return is_to_delete;
}

bool IceBlock::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (projectile.getGlobalBounds().intersects(rect_collision))
	{
		return true;
	}
	return false;
}

void IceBlock::CheckIfToDelete()
{
	if (clock_time_creation.getElapsedTime().asSeconds() >= duration_projectile)
	{
		is_to_delete = true;
	}
}

void IceBlock::Initialized(int player_id)
{
	id_parent = player_id;
}

bool IceBlock::GetInitStatus()
{
	return been_init;
}

void IceBlock::Draw(sf::RenderWindow &window)
{
	CheckIfToDelete();
	
	window.draw(projectile);
}

void IceBlock::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 10));
	window.draw(shadow);
}

sf::Vector2f IceBlock::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool IceBlock::CanPush() { return true; }

float IceBlock::GetDistancePushing() { return distance_pushing; }

bool IceBlock::CanAffectMonster() { return true; }

bool IceBlock::CanAffectPlayer() { return true; }

void IceBlock::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Player_E)
	{
		if (CanPush())
		{
			object_collided->GetPushedAway(GetDistancePushing(), StrongPush, position_objet, position_self);
		}
		if (CanStun())
		{
			object_collided->ChangeStunTime(GetStunTime());
		}
	}

	if (type_object == Monster_E)
	{
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

void IceBlock::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool IceBlock::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}
