#include "stdafx.h"
#include "M_Stick.h"

M_Stick::M_Stick()
{
	if (!texture.loadFromFile("Stick.png"))
	{
		std::cout << "Error while laoding Stick texture" << std::endl;
	}
}

M_Stick::~M_Stick()
{
}

void M_Stick::Init(sf::Vector2f position, int new_id)
{
	sprite = GlobalFunction::CreateSprite(position, size_material,texture);
	sprite.setRotation(GlobalFunction::getRandomRange(1, 360));
	id = new_id;
}

void M_Stick::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (clock_duration.getElapsedTime().asSeconds() >= 30)
	{
		is_to_delete = true;
	}
}

void M_Stick::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

void M_Stick::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (object_collided->GetTypeCollisionalObject() == Player_E)
	{
		object_collided->AddMaterialToList(shared_from_this());
	}
}