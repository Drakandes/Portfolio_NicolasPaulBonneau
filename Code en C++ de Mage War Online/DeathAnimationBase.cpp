#include "stdafx.h"
#include "DeathAnimationBase.h"

DeathAnimationBase::DeathAnimationBase()
{
}

DeathAnimationBase::~DeathAnimationBase()
{
}

void DeathAnimationBase::Init(sf::Vector2f size_sprite, int number_animation, float frame_per_second, int position_y, sf::Vector2f position, sf::String string_texture)
{
	this->size_sprite = size_sprite;
	this->number_animation = number_animation;
	this->frame_per_second = frame_per_second;
	this->position_y = position_y;

	texture.loadFromFile(string_texture);
	sprite = GlobalFunction::CreateSprite(position, size_sprite, texture);
	sprite.setTextureRect(sf::IntRect(0, size_sprite.y*position_y, size_sprite.x, size_sprite.y));
}

void DeathAnimationBase::Update()
{
	if (clock.getElapsedTime().asSeconds() >= frame_per_second)
	{
		sprite.setTextureRect(sf::IntRect(size_sprite.x*counter, size_sprite.y*position_y, size_sprite.x, size_sprite.y));
		counter++;
		if (counter == number_animation)
		{
			to_delete = true;
		}
		clock.restart();
	}
}