#include "stdafx.h"
#include "Leaf.h"

Leaf::Leaf()
{
	if (!texture_projectile.loadFromFile("Leaf.png"))
	{
		std::cout << "Error while loading leaf projectile texture" << std::endl;
	}
}

Leaf::~Leaf()
{
	parent.reset();
}

void Leaf::Init(sf::Vector2f &position_player, float damage_received, float speed_received, float range_projectile_received, float duration_received, std::shared_ptr<Player> player)
{
	parent = player;
	player.reset();
	duration_projectile = duration_received;
	damage = damage_received;
	position_origin = position_player;
	projectile = GlobalFunction::CreateSprite(position_player, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	been_init = true;
	speed_projectile = speed_received;
	range_projectile = range_projectile_received;
}

void Leaf::Update(float DELTATIME, sf::Vector2f player_position)
{
	MovementOfProjectile( player_position, DELTATIME);
}

void Leaf::MovementOfProjectile(sf::Vector2f player_position, float DELTATIME)
{
	sf::Vector2f position_to_go = player_position + sf::Vector2f((cos(rotation_projectile * PI / 180))*range_projectile, (sin(rotation_projectile * PI / 180))*range_projectile);
	projectile.setPosition(position_to_go);
	if (clock_rotation.getElapsedTime().asSeconds() >= 0.01)
	{
		rotation_projectile += speed_projectile;
		if (rotation_projectile > 360)
		{
			rotation_projectile = 1;
		}
		clock_rotation.restart();
		projectile.setRotation(rotation_projectile);
	}
}

sf::Vector2f Leaf::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f Leaf::GetSize()
{
	return size_projectile;
}

int Leaf::GetRayon()
{
	return rayon;
}

float Leaf::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool Leaf::IsNeedToDelete()
{
	CheckIfToDelete();
	return is_to_delete;
}

bool Leaf::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	/*if (GlobalFunction::Check_collision(rayon_1, GetRayon(), position_1, GetCurrentPosition(), size_1, GetSize()))
	{
		is_to_delete = true;
		return true;
	}
	return false;*/

	if (projectile.getGlobalBounds().intersects(rect_collision))
	{
		is_to_delete = true;
		return true;
	}
	return false;
}

void Leaf::Initialized(int player_id, float angle_rotation_received)
{
	id_parent = player_id;
	rotation_projectile = angle_rotation_received;
}

bool Leaf::GetInitStatus()
{
	return been_init;
}

void Leaf::CheckIfToDelete()
{
	if (clock_time_of_creation.getElapsedTime().asSeconds() >= duration_projectile)
	{
		is_to_delete = true;
	}
}

void Leaf::ToDelete()
{
	is_to_delete = true;
}

void Leaf::Draw(sf::RenderWindow &window)
{
	window.draw(projectile);
}

void Leaf::DrawShadow(sf::RenderWindow &window)
{

}

bool Leaf::CanAffectMonster() { return true; }

bool Leaf::CanAffectPlayer() { return false; }

void Leaf::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
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

	else if (type_object == Monster_E)
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
	else if (type_object == NatureObject_E)
	{
		if (!object_collided->CheckIfProjectileDisable())
		{
			is_to_delete = true;
		}
	}
	else if (type_object == Projectile_E)
	{
		if (id_parent != object_collided->GetId())
		{
			object_collided->SetToDelete();
			health_leaf--;
			if (health_leaf == 0)
			{
				is_to_delete = true;
			}
		}
	}
}

void Leaf::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Leaf::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}
