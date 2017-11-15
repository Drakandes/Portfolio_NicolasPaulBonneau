#include "stdafx.h"
#include "TransparentRect.h"

TransparentRect::TransparentRect()
{

}

TransparentRect::~TransparentRect()
{
}

void TransparentRect::Init(sf::Vector2f &position_initial,std::shared_ptr<PetBase> parent_pet, sf::Vector2f size_received)
{
	id_parent = -1;
	direction_projectile = 0;
	damage_initial = 0;
	damage = 0;
	position_origin = position_initial;
	this->can_affect_player = false;
	this->can_affect_monster = false;

	size_projectile = size_received;
	this->range_projectile = range_projectile;
	speed_projectile = 0;

	rect = GlobalFunction::CreateRectangleWithOrigin(size_projectile,position_initial, sf::Color::Transparent);
}

void  TransparentRect::MovementGestion(float DELTATIME)
{
	rect.setPosition(parent->GetCurrentPosition());

	if (clock_duration.getElapsedTime().asSeconds() >= 4)
	{
		is_to_delete = true;
	}
}

void TransparentRect::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();

	if (type_object == Projectile_E)
	{
		if (id_parent != object_collided->GetId())
		{
			object_collided->SetToDelete();
		}
	}
}

void TransparentRect::Update(float DELTATIME, sf::Vector2f player_position)
{
	MovementGestion(DELTATIME);
}

void TransparentRect::Draw(sf::RenderWindow &window)
{

}