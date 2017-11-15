#include "stdafx.h"
#include "BottleBeer.h"


BottleBeer::BottleBeer()
{
	if (!texture.loadFromFile("Bottle_of_beer.png"))
	{
		std::cout << "Error while loading bottle of beer texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("BottleBeerShadow.png"))
	{
		std::cout << "Error while loading forcing bubble projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

BottleBeer::~BottleBeer()
{
	std::shared_ptr<BeerOnTheFloor> beer_on_the_floor = std::shared_ptr<BeerOnTheFloor>(new BeerOnTheFloor());
	beer_on_the_floor->Init(GetCurrentPosition(), id_parent);
	ProjectileGestion::instance()->AddObjectToList(beer_on_the_floor);
	beer_on_the_floor.reset();
}

void BottleBeer::Init(sf::Vector2f position_davbheer, float angle_rotation_received, float davbheer_damage, float speed_bottle_received, float range_bottle, int id_caster)
{
	id_parent = id_caster;
	bottle_beer = GlobalFunction::CreateSprite(position_davbheer, size, texture);
	angle_rotation = angle_rotation_received;
	damage = davbheer_damage;
	position_initial = position_davbheer;
	speed_bottle = speed_bottle_received;
	range = range_bottle;
}

void BottleBeer::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (!on_the_floor)
	{
		bottle_beer.move((cos(angle_rotation * PI / 180))*-speed_bottle*DELTATIME, (sin(angle_rotation * PI / 180))*-speed_bottle*DELTATIME);
	}
	if (GlobalFunction::GetDistanceBetweenTwoPositions(bottle_beer.getPosition(), position_initial) >= range && !on_the_floor)
	{
		on_the_floor = true;
		max_animation = 8;
		time_between_animation = 0.3;
		holder_x = 8;
	}
	CuttingSprite();
}

void BottleBeer::CuttingSprite()
{
	if (clock_between_animation.getElapsedTime().asSeconds() >= time_between_animation)
	{
		bottle_beer.setTextureRect(sf::IntRect(size.x*holder_x, 0, size.x, size.y));
		shadow.setTextureRect(sf::IntRect(size.x*holder_x, 0, size.x, size.y));
		holder_x++;
		if (holder_x >= max_animation)
		{
			if (on_the_floor)
			{
				is_to_delete = true;
			}
			holder_x = 0;
		}
		clock_between_animation.restart();
	}
}

void BottleBeer::Draw(sf::RenderWindow &window)
{
	

	window.draw(bottle_beer);
}

void BottleBeer::DrawShadow(sf::RenderWindow &window)
{
	if (!on_the_floor)
	{
		shadow.setPosition(bottle_beer.getPosition() + sf::Vector2f(0, 12));
		window.draw(shadow);
	}
}

sf::Vector2f BottleBeer::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool BottleBeer::IsNeedToDelete()
{
	return is_to_delete;
}

float BottleBeer::GetDamage()
{
	return damage;
}

int BottleBeer::GetRayon()
{
	return rayon;
}

sf::Vector2f BottleBeer::GetSize()
{
	return size_for_collision;
}

sf::Vector2f BottleBeer::GetCurrentPosition()
{
	return bottle_beer.getPosition();
}

bool BottleBeer::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	/*if (GlobalFunction::Check_collision(rayon_1, GetRayon(), position_1, GetCurrentPosition(), size_1, GetSize()) && !on_the_floor)
	{
		on_the_floor = true;
		max_animation = 8;
		time_between_animation = 0.3;
		holder_x = 8;
		return true;
	}
	else
	{
		return false;
	}*/

	if (bottle_beer.getGlobalBounds().intersects(rect_collision))
	{
		on_the_floor = true;
		max_animation = 8;
		time_between_animation = 0.3;
		holder_x = 8;
		return true;
	}
	return false;
}

bool BottleBeer::CanAffectMonster() { return false; }

bool BottleBeer::CanAffectPlayer() { return true; }

void BottleBeer::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (!on_the_floor)
	{
		int type_object = object_collided->GetTypeCollisionalObject();
		sf::Vector2f position_self = GetCurrentPosition();
		sf::Vector2f position_objet = object_collided->GetCurrentPosition();
		sf::Vector2f size_object = object_collided->GetSize();

		if (type_object == Player_E)
		{
			if (CanAffectPlayer())
			{
				on_the_floor = true;
				max_animation = 8;
				time_between_animation = 0.3;
				holder_x = 8;

				float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, 0);

				if (CanPush())
				{
					object_collided->GetPushedAway(GetDistancePushing(), StrongPush, position_objet, position_self);
				}
				if (CanStun())
				{
					object_collided->ChangeStunTime(GetStunTime());
				}
				if (CanChangeObjectStat())
				{
					for (int i = 0; i < GetNumberObjectStatChange(); i++)
					{
						object_collided->GivePlayerChangeStat(GetObjectStatChanging(i), GetObjectStatChangeDuration(i), GetObjectStatChangValue(i));
					}
				}
				if (CanChangeSkillCooldown())
				{
					object_collided->ChangeASkillCooldown(GetSkillCooldownChanging(), GetNewSkillCooldown());
				}
			}
		}

		if (type_object == NatureObject_E)
		{
			if (!object_collided->CheckIfProjectileDisable())
			{
				is_to_delete = true;
			}
		}
	}
}

void BottleBeer::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool BottleBeer::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}