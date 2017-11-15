#include "stdafx.h"
#include "IgniteProjectile.h"


IgniteProjectile::IgniteProjectile()
{
	if (!texture_projectile.loadFromFile("Skill_ignite_projectile.png"))
	{
		std::cout << "Error while loading ignite projectile texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("IgniteShadow.png"))
	{
		std::cout << "Error while loading ignite projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

IgniteProjectile::~IgniteProjectile()
{
	parent.reset();
}

void IgniteProjectile::Init( sf::Vector2f &position_player, sf::Vector2f mouse_position, float damage_received, float speed_received, float ignite_damage, float ignite_duration, float range_projectile_received, std::shared_ptr<Player> player)
{
	parent = player;
	player.reset();
	damage = damage_received;
	SetAngles(mouse_position, position_player);
	position_origin = position_player;
	projectile = GlobalFunction::CreateSprite(position_player, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(rotation_projectile);
	shadow.setRotation(rotation_projectile);
	been_init = true;
	speed_projectile = speed_received;
	range_projectile = range_projectile_received;
	this->ignite_duration = ignite_duration;
	this->ignite_damage = ignite_damage;
}

void IgniteProjectile::SetAngles(sf::Vector2f &mouse_position, sf::Vector2f &position)
{
	if (mouse_position.x > position.x && mouse_position.y < position.y)
	{
		rotation_projectile = 270 + ((((atan((mouse_position.x - position.x) / (position.y - mouse_position.y))) * 180 / PI)));
	}
	if (mouse_position.x < position.x && mouse_position.y < position.y)
	{
		rotation_projectile = 270 + ((atan((mouse_position.x - position.x) / (position.y - mouse_position.y))) * 180 / PI);
	}
	if (mouse_position.x > position.x && mouse_position.y > position.y)
	{
		rotation_projectile = (90 - ((atan((mouse_position.x - position.x) / (mouse_position.y - position.y)) * 180 / PI)));
	}
	if (mouse_position.x < position.x && mouse_position.y > position.y)
	{
		rotation_projectile = (180 - (((atan((position.y - mouse_position.y) / (mouse_position.x - position.x))) * 180 / PI)));
	}
	if (mouse_position.x == position.x && mouse_position.y <= position.y)
	{
		rotation_projectile = 270;
	}
	if (mouse_position.x == position.x && mouse_position.y >= position.y)
	{
		rotation_projectile = 90;
	}
	if (mouse_position.y == position.y && mouse_position.x >= position.x)
	{
		rotation_projectile = 0;
	}
	if (mouse_position.y == position.y && mouse_position.x <= position.x)
	{
		rotation_projectile = 180;
	}
}

void IgniteProjectile::Movement_of_fireball(float DELTATIME)
{
	projectile.move((cos(rotation_projectile * PI / 180))*speed_projectile*DELTATIME, (sin(rotation_projectile * PI / 180))*speed_projectile*DELTATIME);

	sf::Vector2f position_2 = GetCurrentPosition();

	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_2, position_origin) >= range_projectile)
	{
		is_to_delete = true;
	}
}

sf::Vector2f IgniteProjectile::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f IgniteProjectile::GetSize()
{
	return size_projectile;
}

void IgniteProjectile::Update(float DELTATIME, sf::Vector2f player_position)
{
	Movement_of_fireball(DELTATIME);
	CuttingSprite();
}

int IgniteProjectile::GetRayon()
{
	return rayon;
}

float IgniteProjectile::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool IgniteProjectile::IsNeedToDelete()
{
	return is_to_delete;
}

bool IgniteProjectile::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (projectile.getGlobalBounds().intersects(rect_collision))
	{
		is_to_delete = true;
		return true;
	}
	return false;
}

void IgniteProjectile::Initialized(int player_id)
{
	id_parent = player_id;
}

bool IgniteProjectile::GetInitStatus()
{
	return been_init;
}

void IgniteProjectile::CuttingSprite()
{
	if (clock_animation.getElapsedTime().asSeconds() >= timer_animation)
	{
		projectile.setTextureRect(sf::IntRect(size_projectile.x*holder_cuting_sprite.x, 0, size_projectile.x, size_projectile.y));
		shadow.setTextureRect(sf::IntRect(size_projectile.x*holder_cuting_sprite.x, 0, size_projectile.x, size_projectile.y));
		holder_cuting_sprite.x++;
		if(holder_cuting_sprite.x >= dimension_animation.x)
		{
			holder_cuting_sprite.x = 0;
		}
		clock_animation.restart();
	}
}

void IgniteProjectile::Draw(sf::RenderWindow &window)
{
	CuttingSprite();
	

	window.draw(projectile);
}

void IgniteProjectile::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 18));
	window.draw(shadow);
}

sf::Vector2f IgniteProjectile::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool IgniteProjectile::CanIgnite() { return true; }

int IgniteProjectile::GetTypeIgnition() { return type_ignition; }

float IgniteProjectile::GetIgnitionDuration() { return ignite_duration; }

float IgniteProjectile::GetIgnitionDamage() { return ignite_damage; }

bool IgniteProjectile::CanAffectMonster() { return true; }

bool IgniteProjectile::CanAffectPlayer() { return false; }

void IgniteProjectile::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
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
			is_to_delete = true;
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
			is_to_delete = true;
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
	if (type_object == NatureObject_E)
	{
		if (!object_collided->CheckIfProjectileDisable())
		{
			is_to_delete = true;
		}
	}
}

void IgniteProjectile::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool IgniteProjectile::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}