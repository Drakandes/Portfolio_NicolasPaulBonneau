#include "stdafx.h"
#include "LeafZone.h"

LeafZone::LeafZone()
{
	if (!texture_projectile.loadFromFile("Leaf_zone.png"))
	{
		std::cout << "Error while loading bulb texture" << std::endl;
	}
}

LeafZone::~LeafZone()
{
}

void LeafZone::Init(sf::Vector2f position_initial, float duration_received, float defense_boost, float health_percent_boost, float time_between_boost_received, int current_rune)
{
	position_projectile = position_initial;
	projectile = GlobalFunction::CreateSprite(position_projectile, size_projectile, texture_projectile);
	duration_projectile = duration_received;
	boost_of_defense = defense_boost;
	boost_of_health_percent = health_percent_boost;
	time_between_boost = time_between_boost_received;
	been_init = true;
	current_rune_using = current_rune;
}

void LeafZone::Update(float DELTATIME, sf::Vector2f player_position)
{
}

sf::Vector2f LeafZone::GetCurrentPosition()
{
	return projectile.getPosition();
}

void LeafZone::CuttingSprite()
{

}

sf::Vector2f LeafZone::GetSize()
{
	return size_projectile;
}

int LeafZone::GetRayon()
{
	return rayon;
}

float LeafZone::GetDamage()
{
	return 0;
}

bool LeafZone::IsNeedToDelete()
{
	CheckIfToDelete();
	return is_to_delete;
}

bool LeafZone::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (projectile.getGlobalBounds().intersects(rect_collision))
	{
		return true;
	}
	return false;
	return false;
}

void LeafZone::CheckIfToDelete()
{
	if (clock_time_creation.getElapsedTime().asSeconds() >= duration_projectile)
	{
		is_to_delete = true;
	}
}

void LeafZone::Initialized(int player_id)
{
	id_parent = player_id;
}

bool LeafZone::GetInitStatus()
{
	return been_init;
}

void LeafZone::Draw(sf::RenderWindow &window)
{
	window.draw(projectile);
}

bool LeafZone::CanChangeObjectStat() { return true; }

int LeafZone::GetNumberObjectStatChange() { return 2; }

int LeafZone::GetObjectStatChanging(int number)
{ 
	if (number == 0)
	{
		return DefensePercent;
	}
	else
	{
		return HealthPercent;

	}
}

float LeafZone::GetObjectStatChangeDuration(int number)
{ 
	return duration_projectile - clock_time_creation.getElapsedTime().asSeconds();
}

float LeafZone::GetObjectStatChangValue(int number)
{ 
	if (number == 0)
	{
		return boost_of_defense;
	}
	else
	{
		return boost_of_health_percent;

	}
}

bool LeafZone::CanAffectMonster() { return false; }

bool LeafZone::CanAffectPlayer() { return true; }

void LeafZone::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
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

				if (current_rune_using == SecondRune_E)
				{
					object_collided->GivePlayerChangeStat(MovementSpeedPercent, -1, 10);
				}
				else if (current_rune_using == ThirdRune_E)
				{
					if (!shield_refilled)
					{
						shield_refilled = true;
						object_collided->ShieldObject(10000000);
					}
				}
			}
		}
	}
}

void LeafZone::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool LeafZone::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

bool LeafZone::CheckIdObject(int id_object)
{
	bool new_object = true;
	std::vector<int>::iterator iterator = ListIdObject.begin();
	while (iterator != ListIdObject.end())
	{
		if ((*iterator) == id_object)
		{
			return false;
		}
		iterator++;
	}
	if (new_object)
	{
		ListIdObject.push_back(id_object);
	}
	return true;
}
