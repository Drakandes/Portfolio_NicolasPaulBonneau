#include "stdafx.h"
#include "M_Ore.h"

M_Ore::M_Ore()
{
	if (!texture_iron.loadFromFile("Iron.png"))
	{
		std::cout << "Error while laoding iron ore texture" << std::endl;
	}
	if (!texture_ruby.loadFromFile("Ruby.png"))
	{
		std::cout << "Error while laoding ruby ore texture" << std::endl;
	}
	if (!texture_emerald.loadFromFile("Emerald.png"))
	{
		std::cout << "Error while laoding emrald ore texture" << std::endl;
	}
	if (!texture_topaz.loadFromFile("Topaz.png"))
	{
		std::cout << "Error while laoding toipaz ore texture" << std::endl;
	}
}

M_Ore::~M_Ore()
{
}

void M_Ore::Init(sf::Vector2f position, int new_id, int type_ore_received)
{
	if (type_ore_received == IM_Iron)
	{
		sprite = GlobalFunction::CreateSprite(position, size_material, texture_iron);
	}
	else if (type_ore_received == IM_Ruby)
	{
		sprite = GlobalFunction::CreateSprite(position, size_material, texture_ruby);
	}
	else if (type_ore_received == IM_Emerald)
	{
		sprite = GlobalFunction::CreateSprite(position, size_material, texture_emerald);
	}
	else if (type_ore_received == IM_Topaz)
	{
		sprite = GlobalFunction::CreateSprite(position, size_material, texture_topaz);
	}

	id = new_id;
	type_ore = type_ore_received;
}

void M_Ore::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (clock_duration.getElapsedTime().asSeconds() >= 30)
	{
		is_to_delete = true;
	}
}

void M_Ore::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

void M_Ore::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (object_collided->GetTypeCollisionalObject() == Player_E)
	{
		object_collided->AddMaterialToList(shared_from_this());
	}
}