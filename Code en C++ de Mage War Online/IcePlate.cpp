#include "stdafx.h"
#include "IcePlate.h"

IcePlate::IcePlate()
{
	if (!texture.loadFromFile("Ice_plate.png"))
	{
		std::cout << "Error while loading beer on the floor texture" << std::endl;
	}
}

IcePlate::~IcePlate()
{
}

void IcePlate::Init(sf::Vector2f puddle_position, float damage_puddle_received, int id_caster)
{
	id_parent = id_caster;
	damage_puddle = damage_puddle_received;
	sprite = GlobalFunction::CreateSprite(puddle_position, size, texture);
	circle = GlobalFunction::CreateCircleForCollision(puddle_position, rayon, sf::Color::Color(105, 105, 105, 125));
}

void IcePlate::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (clock_time_between_created.getElapsedTime().asSeconds() >= time_alive)
	{
		is_to_delete = true;
	}
}

bool IcePlate::IsNeedToDelete()
{
	return is_to_delete;
}

void IcePlate::Draw(sf::RenderWindow &window)
{
	window.draw(circle);
	window.draw(sprite);
}

float IcePlate::GetDamage()
{
	clock_between_damage.restart();
	return damage_puddle;
}

int IcePlate::GetRayon()
{
	return rayon;
}

sf::Vector2f IcePlate::GetCurrentPosition()
{
	return sprite.getPosition();
}

bool IcePlate::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (CheckIdObject(id_object))
	{
		/*if (GlobalFunction::Check_collision(rayon, rayon_1, sprite.getPosition(), position_1, size, size_1))
		{
			return true;
		}*/

		if (sprite.getGlobalBounds().intersects(rect_collision))
		{
			return true;
		}
	}
	return false;
}

bool IcePlate::CanAffectMonster() { return false; }

bool IcePlate::CanAffectPlayer() { return true; }

bool IcePlate::CheckIdObject(int id_object)
{
	bool new_object = true;
	int counter = 0;
	std::vector<int>::iterator iterator = ListIdObject.begin();
	while (iterator != ListIdObject.end())
	{
		if ((*iterator) == id_object)
		{
			if (ListClockObject[counter].getElapsedTime().asSeconds() >= reset_timer)
			{
				ListClockObject[counter].restart();
				return true;
			}
			else
			{
				return false;
			}
			new_object = false;
		}
		counter++;
		iterator++;
	}
	if (new_object)
	{
		sf::Clock clock;
		ListClockObject.push_back(clock);
		ListIdObject.push_back(id_object);
	}
	return true;
}

void IcePlate::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Player_E)
	{
		if (CanAffectPlayer())
		{
			if (CheckIdObject(object_collided->GetId()))
			{
				object_collided->GivePlayerChangeStat(MovementSpeedPercent, 1, slow);
			}
		}
	}
}

void IcePlate::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool IcePlate::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

