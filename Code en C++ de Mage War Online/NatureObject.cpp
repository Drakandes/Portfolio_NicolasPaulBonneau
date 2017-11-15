#include "stdafx.h"
#include "NatureObject.h"

NatureObject::NatureObject()
{
}

NatureObject::~NatureObject()
{
}

void NatureObject::Init(sf::Vector2f position)
{
}

bool NatureObject::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	return false;
}

sf::Vector2f NatureObject::GetCurrentPosition()
{
	return sf::Vector2f(0, 0);
}

void NatureObject::Draw(sf::RenderWindow &window)
{

}

bool NatureObject::CanPush() { return true; }

float NatureObject::GetDistancePushing() { return 1; }