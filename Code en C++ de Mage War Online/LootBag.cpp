#include "stdafx.h"
#include "LootBag.h"


LootBag::LootBag()
{
	if (!texture_sprite.loadFromFile("LootBag.png"))
	{
		std::cout << "Error while loading loot bag texture" << std::endl;
	}
}

LootBag::~LootBag()
{
}

void LootBag::Init(sf::Vector2f position, int new_id)
{
	sprite = GlobalFunction::CreateSprite(position, size_sprite, texture_sprite);
	id = new_id;
}

void LootBag::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (clock_duration.getElapsedTime().asSeconds() >= 45)
	{
		is_to_delete = true;
	}
}

void LootBag::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

void LootBag::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (object_collided->GetTypeCollisionalObject() == Player_E)
	{
		object_collided->AddMaterialToList(shared_from_this());
	}
}
