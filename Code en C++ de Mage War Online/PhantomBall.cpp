#include "stdafx.h"
#include "PhantomBall.h"

PhantomBall::PhantomBall()
{
	if (!texture_projectile.loadFromFile("PhantomBall.png"))
	{
		std::cout << "Error while loading PhantomBall texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("PhantomBallShadow.png"))
	{
		std::cout << "Error while loading PhantomBall projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

PhantomBall::~PhantomBall()
{
}

void PhantomBall::Init(sf::Vector2f &position_caster, float damage_received, float speed_received,float angle, int id_caster)
{
	rotation_projectile = angle;
	damage = damage_received;
	position_origin = position_caster;
	projectile = GlobalFunction::CreateSprite(position_caster, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(angle);
	speed_initial = speed_received;
	speed_projectile = speed_received;
	id_projectile = id_caster;
}

void PhantomBall::Update(float DELTATIME, sf::Vector2f player_position)
{
	Movement_of_fireball(player_position, DELTATIME);
}

void PhantomBall::Movement_of_fireball(sf::Vector2f position_player, float DELTATIME)
{
	sf::Vector2f position_projectile = GetCurrentPosition();
	if (coming_back)
	{
		float distance = GlobalFunction::GetDistanceBetweenTwoPositions(position_origin, position_projectile);
		if (distance < 10)
		{
			is_to_delete = true;
		}
		rotation_projectile = GlobalFunction::GetRotationBetweenTwoPositions(position_origin, GetCurrentPosition());
		/*speed_projectile = speed_initial;
		float speed_modification = ((1 - (distance / range_projectile)) - 0.1) * speed_projectile;
		if (speed_modification > 0)
		{
			speed_projectile -= speed_modification;
		}*/
	}
	else
	{
		/*float distance = GlobalFunction::GetDistanceBetweenTwoPositions(position_origin, position_projectile);
		speed_projectile = speed_initial;
		float speed_modification = ((distance / range_projectile) - 0.1) * speed_projectile;
		if (speed_modification > 0)
		{
			speed_projectile -= speed_modification;
		}*/
	}

	projectile.move((cos(rotation_projectile * PI / 180))*speed_projectile*DELTATIME, (sin(rotation_projectile * PI / 180))*speed_projectile*DELTATIME);

	if (!coming_back)
	{
		sf::Vector2f position_2 = GetCurrentPosition();
		if (GlobalFunction::GetDistanceBetweenTwoPositions(position_2, position_origin) >= range_projectile)
		{
			coming_back = true;
		}
	}
}

sf::Vector2f PhantomBall::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f PhantomBall::GetSize()
{
	return size_projectile;
}

int PhantomBall::GetRayon()
{
	return rayon;
}

float PhantomBall::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool PhantomBall::IsNeedToDelete()
{
	return is_to_delete;
}

void PhantomBall::Draw(sf::RenderWindow &window)
{
	window.draw(projectile);
}

void PhantomBall::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, shadow_size.y));
	window.draw(shadow);
}

sf::Vector2f PhantomBall::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, -size_projectile.y/2);
}

bool PhantomBall::CanAffectPlayer() { return true; }

void PhantomBall::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Player_E)
	{
		if (CanAffectPlayer())
		{
			is_to_delete = true;
			float damage_dealt = object_collided->GotDamaged(GetDamage(), id_projectile, 0);
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

void PhantomBall::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool PhantomBall::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

void PhantomBall::GiveParentPosition(sf::Vector2f position)
{
	if (coming_back)
	{
		position_origin = position;
	}
}