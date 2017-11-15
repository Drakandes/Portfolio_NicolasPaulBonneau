#include "stdafx.h"
#include "HugeFireball.h"
#include <iostream>
#include "GlobalFunction.h"
#include "GlobalEnum.h"

HugeFireball::HugeFireball()
{
	if (!shadow_texture.loadFromFile("HugeFireballShadow.png"))
	{
		std::cout << "Error while loading huge fireball projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

HugeFireball::~HugeFireball()
{

	parent.reset();
}

void HugeFireball::Texture_loading()
{
	if (!texture_huge_fireball.loadFromFile("Huge_fireball.png"))
	{
		std::cout << "Error: Couldn't load Huge_fireball texture" << std::endl;
	}
}

void HugeFireball::Init(sf::Vector2f &position_player, float player_damage,float angle, float speed_huge_fireball_received, float range_received, std::shared_ptr<Player> player, float lifesteal_bonus)
{
	parent = player;
	player.reset();
	rotation_huge_fireball = angle;
	fireball_image_position_origin = position_player;
	huge_fireball.setPosition(sf::Vector2f(position_player.x, position_player.y));
	huge_fireball.setTexture(texture_huge_fireball);
	huge_fireball.setTextureRect(sf::IntRect(0, 0, size_huge_fireball.x, size_huge_fireball.y));
	fireball_reapparition = false;
	huge_fireball.setOrigin(sf::Vector2f(size_huge_fireball.x / 2, size_huge_fireball.y / 2));
	huge_fireball.setRotation(rotation_huge_fireball);
	shadow.setRotation(rotation_huge_fireball);
	damage_huge_fireball = player_damage;
	range_huge_fireball = range_received;
	touching_fireball = false;
	been_init = true;
	speed_huge_fireball = speed_huge_fireball_received;
	lifesteal_rune_bonus = lifesteal_bonus;
}

void HugeFireball::Movement_of_fireball( float DELTATIME)
{
	huge_fireball.move((cos(rotation_huge_fireball * PI / 180))*speed_huge_fireball*DELTATIME, (sin(rotation_huge_fireball * PI / 180))*speed_huge_fireball*DELTATIME);

	sf::Vector2f position_2 = GetCurrentPosition();

	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_2, fireball_image_position_origin) >= range_huge_fireball)
	{
		is_to_delete = true;
	}
}

sf::Vector2f HugeFireball::GetCurrentPosition()
{
	return huge_fireball.getPosition();
}

void HugeFireball::Update(float DELTATIME, sf::Vector2f player_position)
{
	Movement_of_fireball(DELTATIME);
}

sf::Vector2f HugeFireball::GetSize()
{
	return size_huge_fireball;
}

int HugeFireball::GetRayon()
{
	return rayon;
}

float HugeFireball::GetDamage()
{
	return damage_huge_fireball;
}

bool HugeFireball::IsNeedToDelete()
{
	return is_to_delete;
}

void HugeFireball::Initialized(int player_id)
{
	id_parent = player_id;
}

bool HugeFireball::GetInitStatus()
{
	return been_init;
}

void HugeFireball::Draw(sf::RenderWindow &window)
{
	window.draw(huge_fireball);
}

void HugeFireball::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(huge_fireball.getPosition() + sf::Vector2f(0, 30));
	window.draw(shadow);
}

sf::Vector2f HugeFireball::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool HugeFireball::CanAffectMonster() { return true; }

bool HugeFireball::CanAffectPlayer() { return false; }

void HugeFireball::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();
	float armor_penetration = parent->GetArmorPenetrationPercent();

	if (CheckIdObject(object_collided->GetId()))
	{
		if (type_object == Player_E)
		{
			if (CanAffectPlayer())
			{
				float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, armor_penetration);

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
			if (CanAffectMonster())
			{
				float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, armor_penetration);
				parent->OnHitGestion(id_object, damage_dealt, type_object,SkillProjectile_E);
				parent->HealPlayer(lifesteal_rune_bonus*damage_dealt / 100);
				
				TextGenerator::instance()->GenerateOneTextForBlob(position_objet, damage_dealt, size_object, object_collided);

				if (CanIgnite())
				{
					object_collided->GetIgnited(GetTypeIgnition(), GetIgnitionDuration(), GetIgnitionDamage());
				}
				if (CanPush())
				{
					object_collided->GetPushedAway(GetDistancePushing(), StrongPush, position_objet, position_self);
				}
				if (CanSlow())
				{
					object_collided->GetSlowed(1, GetDurationSlow(), GetPercentSlow());
				}
				if (CanStun())
				{
					ChangeStunTime(GetStunTime());
				}
			}
		}
	}
	if (type_object == NatureObject_E)
	{
		if (!object_collided->CheckIfProjectileDisable())
		{
			rotation_huge_fireball;
		}
	}
}

void HugeFireball::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool HugeFireball::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

bool HugeFireball::CheckIdObject(int id_object)
{
	std::vector<int>::iterator iterator = ListIdObject.begin();
	while (iterator != ListIdObject.end())
	{
		if ((*iterator) == id_object)
		{
			return false;
		}
		iterator++;
	}
	ListIdObject.push_back(id_object);
	return true;
}

