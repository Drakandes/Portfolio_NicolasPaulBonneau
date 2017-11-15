#include "stdafx.h"
#include "ScaryFace.h"

ScaryFace::ScaryFace()
{
	if (!texture_projectile.loadFromFile("ScaryFace.png"))
	{
		std::cout << "Error while loading energy projectile texture" << std::endl;
	}
}

ScaryFace::~ScaryFace()
{
}

void  ScaryFace::Init(sf::Vector2f &position_initial, int id_caster)
{
	id_parent = id_caster;
	position_origin = position_initial + sf::Vector2f(0,-size_projectile.y/2 - 20);
	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	circle_collision = GlobalFunction::CreateCircleWithOrigin(position_initial,rayon);
	circle_collision.setFillColor(sf::Color::Transparent);
	circle_collision.setOutlineColor(sf::Color::Color(105, 105, 105, 125));
	circle_collision.setOutlineThickness(3);
}

void ScaryFace::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (clock_duration.getElapsedTime().asSeconds() >= duration)
	{
		is_to_delete = true;
	}
}

sf::Vector2f  ScaryFace::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f  ScaryFace::GetSize()
{
	return size_projectile;
}

int  ScaryFace::GetRayon()
{
	return rayon;
}

bool  ScaryFace::IsNeedToDelete()
{
	return is_to_delete;
}

void ScaryFace::Draw(sf::RenderWindow &window)
{
	window.draw(circle_collision);
	window.draw(projectile);
}

bool ScaryFace::CanAffectMonster() { return false; }

bool ScaryFace::CanAffectPlayer() { return true; }

void ScaryFace::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Player_E)
	{
		if (CanAffectPlayer())
		{
			if (CanChangeObjectStat())
			{
				for (int i = 0; i < GetNumberObjectStatChange(); i++)
				{
					object_collided->GivePlayerChangeStat(GetObjectStatChanging(i), GetObjectStatChangeDuration(i), GetObjectStatChangValue(i));
				}
			}
		}
	}
}

void ScaryFace::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool ScaryFace::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

bool ScaryFace::CanChangeObjectStat() { return true; }

int ScaryFace::GetNumberObjectStatChange() { return 1; }

int ScaryFace::GetObjectStatChanging(int number)
{
	return Scared;
}

float ScaryFace::GetObjectStatChangeDuration(int number)
{
	return time_scared;
}

float ScaryFace::GetObjectStatChangValue(int number)
{
	return 0;
}