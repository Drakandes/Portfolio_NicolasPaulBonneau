#include "stdafx.h"
#include "BeerOnTheFloor.h"

BeerOnTheFloor::BeerOnTheFloor()
{
	if (!texture.loadFromFile("Beer_on_the_floor.png"))
	{
		std::cout << "Error while loading beer on the floor texture" << std::endl;
	}
}

BeerOnTheFloor::~BeerOnTheFloor()
{
}

void BeerOnTheFloor::Init(sf::Vector2f bottle_beer_position, int id_caster)
{
	id_parent = id_caster;
	sprite = GlobalFunction::CreateSprite(bottle_beer_position, size, texture);
	circle = GlobalFunction::CreateCircleForCollision(bottle_beer_position, rayon, sf::Color::Color(105, 105, 105, 125));
}

void BeerOnTheFloor::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (clock_for_animation.getElapsedTime().asSeconds() >= time_between_animation)
	{
		sprite.setTextureRect(sf::IntRect(size.x*holder_x, 0, size.x, size.y));
		holder_x++;
		if (holder_x == 2)
		{
			time_between_animation = 0.3;
		}
		if(holder_x == 3)
		{
			time_between_animation = time_alive / number_of_animation;
		}
		if (holder_x >= 5)
		{
			holder_x = 4;
		}
		clock_for_animation.restart();
	}
	if (clock_time_between_created.getElapsedTime().asSeconds() >= time_between_opacity && !can_change_opcatity)
	{
		clock_time_between_created.restart();
		can_change_opcatity = true;
	}
	if (can_change_opcatity)
	{
		float number = (1 - (clock_time_between_created.getElapsedTime().asSeconds() / time_alive)) * 255;
		if (number <= 0)
		{
			is_to_delete = true;
		}
		sprite.setColor(sf::Color(255, 255, 255, number));
	}
}

bool BeerOnTheFloor::IsNeedToDelete()
{
	return is_to_delete;
}

void BeerOnTheFloor::Draw(sf::RenderWindow &window)
{
	window.draw(circle);
	window.draw(sprite);
}

bool BeerOnTheFloor::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (sprite.getGlobalBounds().intersects(rect_collision))
	{
		return true;
	}
	return false;
}

int BeerOnTheFloor::GetRayon()
{
	return rayon;
}

sf::Vector2f BeerOnTheFloor::GetCurrentPosition()
{
	return sprite.getPosition();
}

bool BeerOnTheFloor::CanChangeObjectStat() { return true; }

int BeerOnTheFloor::GetNumberObjectStatChange() { return 1; }

int BeerOnTheFloor::GetObjectStatChanging(int number) { return MovementSpeedPercent; }

float BeerOnTheFloor::GetObjectStatChangeDuration(int number) { return -1; }

float BeerOnTheFloor::GetObjectStatChangValue(int number) { return slow_from_puddle; }

bool BeerOnTheFloor::CanAffectMonster() { return false; }

bool BeerOnTheFloor::CanAffectPlayer() { return true; }

void BeerOnTheFloor::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Player_E)
	{
		if (CanAffectPlayer())
		{
			float damage_dealt = object_collided->GotDamaged(GetDamage(),id_parent,0);

	
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
}

void BeerOnTheFloor::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool BeerOnTheFloor::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}