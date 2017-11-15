#include "stdafx.h"
#include "Electricity.h"

Electricity::Electricity()
{
	if (!texture_projectile.loadFromFile("Lightning.png"))
	{
		std::cout << "Error while loading vine projectile texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("LightningShadow.png"))
	{
		std::cout << "Error while loading forcing bubble projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

Electricity::~Electricity()
{

}

void Electricity::Init(sf::Vector2f &position_player,float damage_received, float angle,float id_parent_received, std::shared_ptr<MonsterBase> parent_received)
{
	parent = parent_received;
	damage_initial = damage_received;
	damage = damage_received;
	rotation_projectile = angle;
	position_origin = position_player;
	projectile = GlobalFunction::CreateSpriteWithoutOrigin(position_player, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(rotation_projectile);
	shadow.setRotation(rotation_projectile);
	shadow.setOrigin(0, size_projectile.y / 2);
	projectile.setOrigin(0, size_projectile.y / 2);
	rect_collision.setPosition(position_player);
	rect_collision.setSize(size_rect_collision);
	rect_collision.setRotation(rotation_projectile - 90);
	rect_collision.setOrigin(sf::Vector2f(size_rect_collision.x / 2 + size_projectile.y / 4, size_rect_collision.y));
	rect_collision.setFillColor(sf::Color::Red);
	id_parent = id_parent_received;
}

void Electricity::Update(float DELTATIME, sf::Vector2f player_position)
{
	Movement_of_fireball();
	CuttingSprite();
}

void Electricity::Movement_of_fireball()
{
	projectile.setPosition(parent->GetCurrentPosition());
}

sf::Vector2f Electricity::GetCurrentPosition()
{
	return rect_collision.getPosition();
}

sf::Vector2f Electricity::GetSize()
{
	return size_rect_collision;
}

float Electricity::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool Electricity::IsNeedToDelete()
{
	return is_to_delete;
}

void Electricity::CuttingSprite()
{
	length_projectile = range_projectile * clock_time_creation.getElapsedTime().asSeconds() / timer_to_reach_end;
	projectile.setTextureRect(sf::IntRect(0, 0, length_projectile, size_projectile.y));
	shadow.setTextureRect(sf::IntRect(0, 0, length_projectile, size_projectile.y));
	if (length_projectile > range_projectile)
	{
		is_to_delete  = true;
	}
	float current_size_vine = length_projectile;
	rect_collision.setPosition(projectile.getPosition() + sf::Vector2f((cos(rotation_projectile * PI / 180))*current_size_vine, (sin(rotation_projectile * PI / 180))*current_size_vine));
}

void Electricity::Draw(sf::RenderWindow &window)
{
	window.draw(projectile);
}

void Electricity::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 12));
	window.draw(shadow);
}

sf::Vector2f Electricity::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool Electricity::CanAffectMonster() { return false; }

bool Electricity::CanAffectPlayer() { return true; }

bool Electricity::CanStun()
{
	return true;
}

float Electricity::GetStunTime()
{
	return stun_duration;
}

void Electricity::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (true)
	{
		int type_object = object_collided->GetTypeCollisionalObject();
		sf::Vector2f position_self = GetCurrentPosition();
		sf::Vector2f position_objet = object_collided->GetCurrentPosition();
		sf::Vector2f size_object = object_collided->GetSize();

		if (type_object == Player_E)
		{
			if (CanAffectPlayer())
			{
				int id_object = object_collided->GetId();
				is_to_delete = true;
				float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, 0);

				if (CanStun())
				{
					object_collided->ChangeStunTime(GetStunTime());
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
}

void Electricity::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Electricity::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}
