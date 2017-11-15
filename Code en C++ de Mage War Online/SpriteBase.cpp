#include "stdafx.h"
#include "SpriteBase.h"

SpriteBase::SpriteBase()
{
}

SpriteBase::~SpriteBase()
{
}

sf::Vector2f SpriteBase::GetCurrentPosition()
{
	return sf::Vector2f(0, 0);
}

void SpriteBase::Draw(sf::RenderWindow &window)
{

}

void SpriteBase::DrawShadow(sf::RenderWindow &window)
{

}