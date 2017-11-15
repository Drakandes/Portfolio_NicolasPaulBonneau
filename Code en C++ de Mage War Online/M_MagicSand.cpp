#include "stdafx.h"
#include "M_MagicSand.h"

M_MagicSand::M_MagicSand()
{
	if (!texture.loadFromFile("MagicSand.png"))
	{
		std::cout << "Error while laoding MagicSand texture" << std::endl;
	}
}

M_MagicSand::~M_MagicSand()
{
}

void M_MagicSand::Init(sf::Vector2f position, int new_id)
{
	sprite = GlobalFunction::CreateSprite(position, size_material, texture);
	sprite.setRotation(GlobalFunction::getRandomRange(1, 360));
	id = new_id;
}

void M_MagicSand::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (current_animation % 2 == 0)
	{
		if (clock_animation.getElapsedTime().asSeconds() >= rate_animation_flashing)
		{
			sprite.setTextureRect(sf::IntRect(size_material.x * current_animation, 0, size_material.x, size_material.y));
			current_animation++;
			sprite.setColor(sf::Color::Color(GlobalFunction::getRandomRange(1, 255), GlobalFunction::getRandomRange(1, 255), GlobalFunction::getRandomRange(1, 255)));
			if (current_animation == number_animation)
			{
				current_animation = 0;
			}
			clock_animation.restart();

		}
	}
	else
	{
		if (clock_animation.getElapsedTime().asSeconds() >= rate_animation)
		{
			sprite.setTextureRect(sf::IntRect(size_material.x * current_animation, 0, size_material.x, size_material.y));
			current_animation++;
			sprite.setColor(sf::Color::Color(GlobalFunction::getRandomRange(1, 255), GlobalFunction::getRandomRange(1, 255), GlobalFunction::getRandomRange(1, 255)));
			if (current_animation == number_animation)
			{
				current_animation = 0;
			}
			clock_animation.restart();

		}
	}

	if (clock_duration.getElapsedTime().asSeconds() >= 30)
	{
		is_to_delete = true;
	}
}

void M_MagicSand::Draw(sf::RenderWindow &window)
{
	if (clock_duration.getElapsedTime().asSeconds() >= 45)
	{
		is_to_delete = true;
	}
	window.draw(sprite);
}

void M_MagicSand::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{

	if (object_collided->GetTypeCollisionalObject() == Player_E)
	{
		object_collided->AddMaterialToList(shared_from_this());
	}
}