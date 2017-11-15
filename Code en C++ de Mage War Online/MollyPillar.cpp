#include "stdafx.h"
#include "MollyPillar.h"

MollyPillar::MollyPillar()
{
	texture_projectile.loadFromFile("VikingPillar.png");
	//shadow_texture.loadFromFile("VikingPillarShadow.png");
}

MollyPillar::~MollyPillar()
{
}

void MollyPillar::Init(sf::Vector2f &position_initial, bool can_affect_player, bool can_affect_monster, std::shared_ptr<Player> player)
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

	projectile.setTextureRect(sf::IntRect(0 , size_projectile.y , size_projectile.x, size_projectile.y));
	shadow.setTextureRect(sf::IntRect(0, size_projectile.y , size_projectile.x, size_projectile.y));
}

void MollyPillar::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Monster_E)
	{
		if (CanAffectPlayer())
		{
			if (!boosted)
			{
				source_x = 0;
				boosted = true;
				clock_boosted.restart();
			}
		}
	}
}

void MollyPillar::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (boosted)
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

	Attack();
}

void MollyPillar::Attack()
{
	if (clock_boosted.getElapsedTime().asSeconds() >= 7)
	{
		boosted = false;

		projectile.setTextureRect(sf::IntRect(0, size_projectile.y * 2, size_projectile.x, size_projectile.y));
		shadow.setTextureRect(sf::IntRect(0, size_projectile.y * 2, size_projectile.x, size_projectile.y));
	}

	if(boosted)
	{
		if (clock_attack.getElapsedTime().asSeconds() >= 1)
		{
			sf::Vector2f position = GlobalFunction::GetRandomVectorBetweenRange(range_spike);
			position.x = position.x*size_spike;
			position.y = position.y*size_spike;
			position += position_origin;
			if (position.y > 1100)
			{
				std::shared_ptr<MollySpike> spike = std::shared_ptr<MollySpike>(new MollySpike());
				spike->Init(position, true, false, damage_spike);
				MainQuadtree::instance()->insert(spike->GetCurrentPosition(), spike->GetSize(), spike);
				ProjectileGestion::instance()->AddObjectToList(spike);
				spike.reset();
			}

			clock_attack.restart();
		}
	}
}

sf::Vector2f MollyPillar::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

void MollyPillar::DrawShadow(sf::RenderWindow &window)
{
	//shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, ));
	//window.draw(shadow);
}