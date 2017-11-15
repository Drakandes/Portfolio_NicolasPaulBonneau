#include "stdafx.h"
#include "MollySpike.h"

MollySpike::MollySpike()
{
	texture_projectile.loadFromFile("MollySpike.png");
	//shadow_texture.loadFromFile("VikingPillarShadow.png");
}

MollySpike::~MollySpike()
{
}

void MollySpike::Init(sf::Vector2f &position_initial, bool can_affect_player, bool can_affect_monster,float damage)
{
	position_origin = position_initial;

	this->can_affect_player = can_affect_player;
	this->can_affect_monster = can_affect_monster;
	this->damage = damage;

	size_projectile = sf::Vector2f(40, 40);
	//shadow_size = size_projectile;

	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));

	//shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

void MollySpike::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (can_attack)
	{
		int id_object = object_collided->GetId();
		int type_object = object_collided->GetTypeCollisionalObject();
		sf::Vector2f position_self = GetCurrentPosition();
		sf::Vector2f position_objet = object_collided->GetCurrentPosition();
		sf::Vector2f size_object = object_collided->GetSize();

		if (type_object == Player_E)
		{
			object_collided->GotDamaged(damage,-1,0);
			can_attack = false;
			is_to_delete = true;
		}
	}
}

void MollySpike::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (can_update)
	{
		if (clock_animation.getElapsedTime().asSeconds() >= 0.1)
		{
			projectile.setTextureRect(sf::IntRect(size_projectile.x*source_x, 0, size_projectile.x, size_projectile.y));
			shadow.setTextureRect(sf::IntRect(size_projectile.x*source_x, 0, size_projectile.x, size_projectile.y));
			source_x++;
			if (source_x == 5)
			{
				source_x = 4;
				can_attack = true;
				can_update = false;
			}
			clock_animation.restart();
		}
	}


	if (clock_duration.getElapsedTime().asSeconds() >= 7)
	{
		is_to_delete = true;
	}
}

sf::Vector2f MollySpike::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

void MollySpike::DrawShadow(sf::RenderWindow &window)
{
	//shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, ));
	//window.draw(shadow);
}