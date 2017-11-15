#include "stdafx.h"
#include "VikingPillar.h"

VikingPillar::VikingPillar()
{
	texture_projectile.loadFromFile("VikingPillar.png");
	//shadow_texture.loadFromFile("VikingPillarShadow.png");
}

VikingPillar::~VikingPillar()
{
}

void VikingPillar::Init(sf::Vector2f &position_initial, bool can_affect_player, bool can_affect_monster, std::shared_ptr<Player> player)
{
	this->player = player;
	position_origin = position_initial;

	this->can_affect_player = can_affect_player;
	this->can_affect_monster = can_affect_monster;

	size_projectile = sf::Vector2f(90, 118);
	//shadow_size = size_projectile;

	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));

	//shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

void VikingPillar::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Projectile_E)
	{
		if (CanAffectPlayer())
		{
			if (object_collided->CanStun())
			{
				destroyed = true;
				player->GivePlayerChangeStat(DamageAddition, 10, 1000);
			}
		}
	}
}

void VikingPillar::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (!destroyed)
	{
		if (clock_animation.getElapsedTime().asSeconds() >= 0.01)
		{
			projectile.setTextureRect(sf::IntRect(size_projectile.x*source_x, 0, size_projectile.x, size_projectile.y));
			shadow.setTextureRect(sf::IntRect(size_projectile.x*source_x, 0, size_projectile.x, size_projectile.y));
			source_x++;
			if (source_x == 24)
			{
				source_x = 0;
			}
			clock_animation.restart();
		}
	}
	else
	{
		if (clock_animation.getElapsedTime().asSeconds() >= 0.02)
		{
			projectile.setTextureRect(sf::IntRect(size_projectile.x*source_x, size_projectile.y, size_projectile.x, size_projectile.y));
			shadow.setTextureRect(sf::IntRect(size_projectile.x*source_x, size_projectile.y, size_projectile.x, size_projectile.y));
			source_x++;
			if (source_x == 10)
			{
				source_x = 9;
			}
			clock_animation.restart();
		}
	}
}

sf::Vector2f VikingPillar::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

void VikingPillar::DrawShadow(sf::RenderWindow &window)
{
	//shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, ));
	//window.draw(shadow);
}