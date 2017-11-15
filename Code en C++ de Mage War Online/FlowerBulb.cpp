#include "stdafx.h"
#include "FlowerBulb.h"

FlowerBulb::FlowerBulb()
{
	if (!texture_projectile.loadFromFile("FlowerBulb.png"))
	{
		std::cout << "Error while loading bulb texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("FlowerBulbShadow.png"))
	{
		std::cout << "Error while loading flower bulb projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
	shadow.setOrigin(sf::Vector2f(size_projectile.x/2, 0));
}

FlowerBulb::~FlowerBulb()
{
}

void  FlowerBulb::Init(sf::Vector2f position_initial, float duration_received, std::shared_ptr<Player> player, float healing_percent)
{
	position_projectile = position_initial;
	projectile = GlobalFunction::CreateSprite(position_projectile + sf::Vector2f(0,1), size_projectile, texture_projectile);
	duration_projectile = duration_received;
	been_init = true;
	player->ChangeStunTime(duration_received);
	player->GivePlayerChangeStat(HpPercentRecovery, duration_received, healing_percent);
	player->GivePlayerChangeStat(Immunity, duration_received, 0);
}

void FlowerBulb::Update(float DELTATIME, sf::Vector2f player_position)
{
	CuttingSprite();
	CheckIfToDelete();
}

sf::Vector2f  FlowerBulb::GetCurrentPosition()
{
	return projectile.getPosition();
}

void FlowerBulb::CuttingSprite()
{
	if (clock_between_animation.getElapsedTime().asSeconds() >= 0.05)
	{
		projectile.setTextureRect(sf::IntRect(size_projectile.x*holder_cuting_sprite.x, 0, size_projectile.x, size_projectile.y));
		shadow.setTextureRect(sf::IntRect(size_projectile.x*holder_cuting_sprite.x, 0, size_projectile.x, size_projectile.y));
		if (holder_cuting_sprite.x < dimension_texture.x-1)
		{
			holder_cuting_sprite.x++;
		}
		else
		{
			holder_cuting_sprite.x = 6;
		}
		clock_between_animation.restart();
	}
}

sf::Vector2f  FlowerBulb::GetSize()
{
	return size_projectile;
}

int  FlowerBulb::GetRayon()
{
	return rayon;
}

float  FlowerBulb::GetDamage()
{
	return damage;
}

bool  FlowerBulb::IsNeedToDelete()
{
	return is_to_delete;
}

bool  FlowerBulb::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	return false;
}

void FlowerBulb::CheckIfToDelete()
{
	if (clock_time_creation.getElapsedTime().asSeconds() >= duration_projectile)
	{
		is_to_delete = true;
	}
}

void FlowerBulb::Initialized(int player_id)
{
	id_parent = player_id;
}

bool FlowerBulb::GetInitStatus()
{
	return been_init;
}

void FlowerBulb::Draw(sf::RenderWindow &window)
{
	

	window.draw(projectile);
}

void FlowerBulb::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, size_projectile.y / 2 - 20));
	window.draw(shadow);
}

sf::Vector2f FlowerBulb::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool FlowerBulb::CanAffectMonster() { return false; }

bool FlowerBulb::CanAffectPlayer() { return false; }

void FlowerBulb::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	
}

void FlowerBulb::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool FlowerBulb::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}
