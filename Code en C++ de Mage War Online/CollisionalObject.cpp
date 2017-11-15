#include "stdafx.h"
#include "CollisionalObject.h"

CollisionalObject::CollisionalObject()
{
}

CollisionalObject::~CollisionalObject()
{
}

sf::Vector2f CollisionalObject::GetCurrentPosition()
{
	return sf::Vector2f(0, 0);
}

void CollisionalObject::Draw(sf::RenderWindow &window)
{

}

void CollisionalObject::GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking)
{

}

void CollisionalObject::ChangeStunTime(float stun_time_received)
{
	std::cout << "Error collisional object got stunned" << std::endl;
}

void CollisionalObject::GivePlayerChangeStat(int type_change, float duration_change, float value_change)
{

}

void CollisionalObject::GetSlowed(int type_slow, float duration_slow, float percent_slow)
{

}

void CollisionalObject::GetIgnited(int type_ignition, float duration_ignition, float damage_ignition)
{

}

float CollisionalObject::GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent)
{
	return 0;
}

void CollisionalObject::ChangeASkillCooldown(int skill_cooldown_changing, float new_cooldown)
{

}

int CollisionalObject::GetRayon()
{
	return 1000;
}

sf::Vector2f CollisionalObject::GetSize()
{
	return sf::Vector2f(0, 0);
}

float CollisionalObject::GetDamage()
{
	return 0;
}

bool CollisionalObject::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	return false;
}

bool CollisionalObject::CanStun()
{
	return false;
}

float CollisionalObject::GetDurationOfStun()
{
	return 0;
}

bool CollisionalObject::CheckIdObject(int id_object)
{
	return true;
}

void CollisionalObject::DrawShadow(sf::RenderWindow &window)
{

}