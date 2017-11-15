#include "stdafx.h"
#include "LavaFloor.h"

LavaFloor::LavaFloor()
{
	if (!texture_projectile.loadFromFile("Lava.png"))
	{
		std::cout << "Error while loading lava texture" << std::endl;
	}
}

LavaFloor::~LavaFloor()
{
	parent.reset();
}

void  LavaFloor::Init(sf::Vector2f position_initial, float damage_received, float duration_received, float time_between_damage_received, float damage_ignition_received, float duration_ignition_received, std::shared_ptr<Player> player)
{
	parent = player;
	player.reset();
	damage_ignition = damage_ignition_received;
	duration_ignition = duration_ignition_received;
	damage = damage_received;
	position_projectile = position_initial;
	projectile = GlobalFunction::CreateSprite(position_projectile, size_projectile, texture_projectile);
	time_between_damage = time_between_damage_received;
	duration_projectile = duration_received;
	been_init = true;
}

void LavaFloor::Update(float DELTATIME, sf::Vector2f player_position)
{
	CuttingSprite();
	CheckIfToDelete();
}

sf::Vector2f  LavaFloor::GetCurrentPosition()
{
	return projectile.getPosition();
}

void LavaFloor::CuttingSprite()
{
	if (clock_between_animation.getElapsedTime().asSeconds() >= time_between_animation)
	{
		projectile.setTextureRect(sf::IntRect(size_projectile.x*holder_cuting_sprite.x, 0, size_projectile.x, size_projectile.y));
		holder_cuting_sprite.x++;
		if (holder_cuting_sprite.x == dimension_texture.x)
		{
			holder_cuting_sprite.x = 0;
		}
		clock_between_animation.restart();
	}
}

sf::Vector2f  LavaFloor::GetSize()
{
	return size_projectile;
}

int LavaFloor::GetRayon()
{
	return rayon;
}

float LavaFloor::GetDamage()
{
	return damage;
}

bool  LavaFloor::IsNeedToDelete()
{
	return is_to_delete;
}

bool  LavaFloor::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (CheckIdObject(id_object))
	{
		/*if (GlobalFunction::GetDistanceBetweenTwoPositions(position_1, position_projectile) <= rayon + rayon_1)
		{
			return true;
		}*/

		if (projectile.getGlobalBounds().intersects(rect_collision))
		{
			return true;
		}
	}
	return false;
}

void LavaFloor::CheckIfToDelete()
{
	if (clock_time_creation.getElapsedTime().asSeconds() >= duration_projectile)
	{
		is_to_delete = true;
	}
}

void LavaFloor::Initialized(int player_id)
{
	id_parent = player_id;
}

bool LavaFloor::GetInitStatus()
{
	return been_init;
}

void LavaFloor::Draw(sf::RenderWindow &window)
{
	window.draw(projectile);
}

bool LavaFloor::CanIgnite() { return true; }

int LavaFloor::GetTypeIgnition() { return type_ignition; }

float LavaFloor::GetIgnitionDuration() { return duration_ignition; }

float LavaFloor::GetIgnitionDamage() { return damage_ignition; }

bool LavaFloor::CanAffectMonster() { return true; }

bool LavaFloor::CanAffectPlayer() { return false; }

bool LavaFloor::CheckIdObject(int id_object)
{
	bool new_object = true;
	int counter = 0;
	std::vector<int>::iterator iterator = ListIdObject.begin();
	while (iterator != ListIdObject.end())
	{
		if ((*iterator) == id_object)
		{
			if (ListClockObject[counter].getElapsedTime().asSeconds() >= time_between_damage)
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

void LavaFloor::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();
	float armor_penetration = parent->GetArmorPenetrationPercent();

	if (type_object == Player_E)
	{
		if (CanAffectPlayer())
		{
			if (CheckIdObject(object_collided->GetId()))
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
	}

	if (type_object == Monster_E)
	{
		if (CanAffectMonster())
		{
			if (CheckIdObject(object_collided->GetId()))
			{
				float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, armor_penetration);
				 parent->OnHitGestion(id_object, damage_dealt, type_object,SkillProjectile_E);
				
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
}

void LavaFloor::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool LavaFloor::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

