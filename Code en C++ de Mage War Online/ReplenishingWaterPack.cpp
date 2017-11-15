#include "stdafx.h"
#include "ReplenishingWaterPack.h"

ReplenishingWaterPack::ReplenishingWaterPack()
{
	if (!texture_projectile.loadFromFile("WaterHealthPack.png"))
	{
		std::cout << "Error while loading water pack texture" << std::endl;
	}
}

ReplenishingWaterPack::~ReplenishingWaterPack()
{
}

void ReplenishingWaterPack::Init(sf::Vector2f position_initial, float duration_received, float hp_recovery_received, float duration_recovery_received, float movement_speed_bonus_received, float duration_movement_speed_bonus_received)
{
	position_projectile = position_initial;
	projectile = GlobalFunction::CreateSprite(position_projectile, size_projectile, texture_projectile);
	duration_projectile = duration_received;
	hp_recovery = hp_recovery_received;
	duration_recovery = duration_recovery_received;
	been_init = true;
	duration_bonus_movement_speed = duration_movement_speed_bonus_received;
	boost_movement_speed = movement_speed_bonus_received;
}

void ReplenishingWaterPack::Update(float DELTATIME, sf::Vector2f player_position)
{

}

sf::Vector2f ReplenishingWaterPack::GetCurrentPosition()
{
	return projectile.getPosition();
}

void ReplenishingWaterPack::CuttingSprite()
{

}

sf::Vector2f ReplenishingWaterPack::GetSize()
{
	return size_projectile;
}

int ReplenishingWaterPack::GetRayon()
{
	return rayon;
}

float ReplenishingWaterPack::GetDamage()
{
	return 0;
}

bool ReplenishingWaterPack::IsNeedToDelete()
{
	return is_to_delete;
}

bool ReplenishingWaterPack::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	/*if (clock_time_creation.getElapsedTime().asSeconds() >= 1)
	{
		if (GlobalFunction::CheckCollisionWithCircleIfBothWithOrigin(rayon, GetCurrentPosition(), position_1, size_1, rayon_1))
		{
			is_to_delete = true;
			return true;
		}
	}
	return false;*/

	if (projectile.getGlobalBounds().intersects(rect_collision))
	{
		is_to_delete = true;
		return true;
	}
	return false;
}

void ReplenishingWaterPack::CheckIfToDelete()
{
	if (clock_time_creation.getElapsedTime().asSeconds() >= duration_projectile)
	{
		is_to_delete = true;
	}
}

void ReplenishingWaterPack::Initialized(int player_id)
{
	id_parent = player_id;
}

bool ReplenishingWaterPack::GetInitStatus()
{
	return been_init;
}

void ReplenishingWaterPack::Draw(sf::RenderWindow &window)
{
	/*CheckIfToDelete();
	CheckCollision(player);*/
	window.draw(projectile);
}

bool ReplenishingWaterPack::CanChangeObjectStat() { return true; }

int ReplenishingWaterPack::GetNumberObjectStatChange() { return 2; }

int ReplenishingWaterPack::GetObjectStatChanging(int number)
{
	if (number == 0)
	{
		return HpPercentRecovery;
	}
	else
	{
		return MovementSpeedPercent;
	}
}

float ReplenishingWaterPack::GetObjectStatChangeDuration(int number)
{
	if (number == 0)
	{
		return duration_recovery;
	}
	else
	{
		return duration_bonus_movement_speed;
	}
}

float ReplenishingWaterPack::GetObjectStatChangValue(int number)
{
	if (number == 0)
	{
		return hp_recovery;
	}
	else
	{
		return boost_movement_speed;
	}
}

bool ReplenishingWaterPack::CanAffectMonster() { return false; }

bool ReplenishingWaterPack::CanAffectPlayer() { return true; }

void ReplenishingWaterPack::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Player_E)
	{
		if (CanAffectPlayer())
		{
			is_to_delete = true;

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

	if (type_object == Monster_E)
	{
		/*if (CanAffectMonster())
		{
			is_to_delete = true;
		}*/
		is_to_delete = true;
	}
	if (type_object == NatureObject_E)
	{
		if (!object_collided->CheckIfProjectileDisable())
		{
			is_to_delete = true;
		}
	}
}

void ReplenishingWaterPack::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool ReplenishingWaterPack::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}
