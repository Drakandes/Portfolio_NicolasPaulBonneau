#include "stdafx.h"
#include "DarkOrb.h"

DarkOrb::DarkOrb()
{
	if (!texture_projectile.loadFromFile("Demon_Orb.png"))
	{
		std::cout << "Error while loading vine projectile texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("DarkOrbShadow.png"))
	{
		std::cout << "Error while loading darkorb projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

DarkOrb::~DarkOrb()
{
	parent.reset();
}

void DarkOrb::Init(int id_caster, sf::Vector2f &position_player, float distance_to_go, float damage_received, float direction_projectile_received, std::shared_ptr<MonsterBase> parent_received)
{
	id_parent = id_caster;
	parent = parent_received;
	position_to_go = position_player+sf::Vector2f((cos(projectile_rotation_around_caster * PI / 180))*distance_to_go, (sin(projectile_rotation_around_caster * PI / 180))*distance_to_go);
	projectile_rotation_around_caster = direction_projectile_received;
	damage_initial = damage_received;
	damage = damage_received;
	position_origin = position_player;
	projectile = GlobalFunction::CreateSprite(position_player, size_projectile_for_drawing, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile_for_drawing.x, size_projectile_for_drawing.y));
	last_caster_position = position_player;
}

void DarkOrb::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (!is_to_delete)
	{
		float distance_to_go = parent->GetChildPositionGoing().x;
		sf::Vector2f position_caster = parent->GetCurrentPosition();
		position_to_go = position_caster + sf::Vector2f((cos(projectile_rotation_around_caster * PI / 180))*distance_to_go, (sin(projectile_rotation_around_caster * PI / 180))*distance_to_go);
		current_position = projectile.getPosition();
		MovementGestion(DELTATIME);
	}
}

void  DarkOrb::MovementGestion(float DELTATIME)
{
	float distance_to_go = GlobalFunction::GetDistanceBetweenTwoPositions(position_to_go, position_origin) - distance_from_caster;
	if (distance_to_go > 0)
	{
		sf::Vector2f position_to_add = sf::Vector2f(((cos(projectile_rotation_around_caster * PI / 180))*speed_projectile*DELTATIME), ((sin(projectile_rotation_around_caster * PI / 180))*speed_projectile*DELTATIME));
		sf::Vector2f distance_from_caster_vector = sf::Vector2f((cos(projectile_rotation_around_caster * PI / 180))*distance_from_caster, (sin(projectile_rotation_around_caster * PI / 180))*distance_from_caster);
		projectile.setPosition(distance_from_caster_vector + position_to_add + position_origin);
		distance_from_caster += sqrt((position_to_add.x*position_to_add.x) + (position_to_add.y*position_to_add.y));
	}
	else
	{
		sf::Vector2f position_to_add = sf::Vector2f(((cos(projectile_rotation_around_caster * PI / 180))*-speed_projectile*DELTATIME), ((sin(projectile_rotation_around_caster * PI / 180))*-speed_projectile*DELTATIME));
		sf::Vector2f distance_from_caster_vector = sf::Vector2f((cos(projectile_rotation_around_caster * PI / 180))*distance_from_caster, (sin(projectile_rotation_around_caster * PI / 180))*distance_from_caster);
		projectile.setPosition(-position_to_add + position_origin + distance_from_caster_vector);
		distance_from_caster -= sqrt((position_to_add.x*position_to_add.x) + (position_to_add.y*position_to_add.y));
	}

	if (distance_from_caster > range_of_orbs)
	{
		sf::Vector2f distance_from_caster_vector = sf::Vector2f((cos(projectile_rotation_around_caster * PI / 180))*range_of_orbs, (sin(projectile_rotation_around_caster * PI / 180))*range_of_orbs);
		projectile.setPosition(position_origin + distance_from_caster_vector);
		distance_from_caster = range_of_orbs;
	}

	if (clock_for_rotation.getElapsedTime().asSeconds() >= 0.01)
	{
		projectile.setRotation(rotation_on_itself);
		shadow.setRotation(rotation_on_itself);
		rotation_on_itself+=15;
		if (rotation_on_itself > 360)
		{
			rotation_on_itself = 1;
		}
		projectile_rotation_around_caster += speed_projectile_rotation;
		if (projectile_rotation_around_caster > 360)
		{
			projectile_rotation_around_caster = 1;
		}
		clock_for_rotation.restart();
	}
}

sf::Vector2f  DarkOrb::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f  DarkOrb::GetSize()
{
	return size_projectile;
}

int  DarkOrb::GetRayon()
{
	return rayon;
}

float  DarkOrb::GetDamage()
{
	return damage;
}

bool  DarkOrb::IsNeedToDelete()
{
	if (parent != NULL)
	{
		if (parent->IsNeedToDelete())
		{
			is_to_delete = true;
			parent.reset();
		}
	}
	return is_to_delete;
}

void DarkOrb::SetToDelete()
{ 
	is_to_delete = true; 
	parent.reset();
}

void DarkOrb::UpdateAfterTeleportation(sf::Vector2f position_caster)
{
	position_origin -= last_caster_position;
	position_origin += position_caster;
	last_caster_position = position_caster;
}

float DarkOrb::GetRotation()
{
	return projectile_rotation_around_caster;
}

void DarkOrb::Draw(sf::RenderWindow &window)
{
	if (is_activated)
	{
		window.draw(projectile);
		shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 25));
		window.draw(shadow);
	}
	is_activated = false;
}

void DarkOrb::DrawShadow(sf::RenderWindow &window)
{
}

sf::Vector2f DarkOrb::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool DarkOrb::CanAffectMonster() { return false; }

bool DarkOrb::CanAffectPlayer() { return true; }

void DarkOrb::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
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
}

void DarkOrb::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool DarkOrb::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}


