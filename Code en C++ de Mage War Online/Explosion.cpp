#include "stdafx.h"
#include "Explosion.h"

Explosion::Explosion()
{
	if (!texture_explosion.loadFromFile("Explosion_50.png"))
	{
		std::cout << "Explosion texture was not load correctly" << std::endl;
	}
}

Explosion::~Explosion()
{
}

void Explosion::Init(sf::Vector2f position_explosion, float damage_explosion_received, int id_parent, float push_distance)
{
	sprite_explosion.setOrigin(sf::Vector2f(this->size_explosion.x/2, this->size_explosion.y/2));
	sprite_explosion.setPosition(position_explosion);
	sprite_explosion.setTexture(texture_explosion);
	sprite_explosion.setTextureRect(sf::IntRect(0, 0, this->size_explosion.x, this->size_explosion.y));
	damage_explosion = damage_explosion_received;
	explosion_push_distance = push_distance;
}

void Explosion::Draw(sf::RenderWindow &window)
{
	Update();
	window.draw(sprite_explosion);
}

bool Explosion::IsNeedToDelete()
{
	return is_to_delete;
}

void Explosion::Update()
{
	if (clock_explosion_timer.getElapsedTime().asSeconds() >= timer_explosion_to_update)
	{
		sprite_explosion.setTextureRect(sf::IntRect(source_x * size_explosion.x, 0, size_explosion.x, size_explosion.y));
		source_x++;
		if (source_x >= 10)
		{
			is_to_delete = true;
		}
		clock_explosion_timer.restart();
	}
}

void Explosion::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
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
				object_collided->GetPushedAway(GetDistancePushing(), ReallyStrongPush, position_objet, position_self);
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

bool Explosion::CanPush() { return true; }

float Explosion::GetDistancePushing() { return explosion_push_distance; }