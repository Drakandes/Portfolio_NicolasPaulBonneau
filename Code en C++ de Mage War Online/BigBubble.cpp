#include "stdafx.h"
#include "BigBubble.h"

BigBubble::BigBubble()
{
	if (!texture_projectile.loadFromFile("BigBubble.png"))
	{
		std::cout << "Error while loading forcing bubble projectile texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("BigBubbleShadow.png"))
	{
		std::cout << "Error while loading forcing bubble projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

BigBubble::~BigBubble()
{
	parent.reset();
}

void BigBubble::Init(sf::Vector2f &position_player, sf::Vector2f mouse_position, float damage_received, float speed_received, float range_projectile_received, float propulsion_distance_received, int bouncing_time, std::shared_ptr<Player> player)
{
	parent = player;
	player.reset();
	damage = damage_received;
	SetAngles(mouse_position, position_player);
	propulsion_distance = propulsion_distance_received;
	position_origin = position_player;
	projectile = GlobalFunction::CreateSprite(position_player, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(rotation_projectile);
	been_init = true;
	maximum_bounces = bouncing_time;
	speed_projectile = speed_received;
	range_projectile = range_projectile_received;
}

void BigBubble::SetAngles(sf::Vector2f &mouse_position, sf::Vector2f &position)
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

void BigBubble::Movement_of_fireball(float DELTATIME)
{
	projectile.move((cos(rotation_projectile * PI / 180))*speed_projectile*DELTATIME, (sin(rotation_projectile * PI / 180))*speed_projectile*DELTATIME);

	sf::Vector2f position_2 = GetCurrentPosition();

	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_2, position_origin) >= range_projectile)
	{
		is_to_delete = true;
	}
}

sf::Vector2f BigBubble::GetCurrentPosition()
{
	return projectile.getPosition();
}

void BigBubble::Update(float DELTATIME, sf::Vector2f player_position)
{
	Movement_of_fireball(DELTATIME);
}

sf::Vector2f BigBubble::GetSize()
{
	return size_projectile;
}

int BigBubble::GetRayon()
{
	return rayon;
}

float BigBubble::GetDamage()
{
	return damage;
}

bool BigBubble::IsNeedToDelete()
{
	if (number_of_bounces >= maximum_bounces)
	{
		is_to_delete = true;
	}
	return is_to_delete;
}

bool BigBubble::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	/*sf::Vector2f position_projectile = GetCurrentPosition();
	bool is_colliding = GlobalFunction::CheckCollisionWithCircleIfBothWithOrigin(rayon, position_projectile, position_1, size_1, rayon_1);
	if (is_colliding)
	{
		rotation_projectile = GlobalFunction::GetRotationBetweenTwoPositions(position_projectile, position_1);
		number_of_bounces++;
		can_affect_player = true;
	}
	return is_colliding;*/

	if (projectile.getGlobalBounds().intersects(rect_collision))
	{
		rotation_projectile = GlobalFunction::GetRotationBetweenTwoPositions(GetCurrentPosition(), position_object);
		number_of_bounces++;
		can_affect_player = true;
		return true;
	}
	return false;
}

void BigBubble::Initialized(int player_id)
{
	id_parent = player_id;
}

bool BigBubble::GetInitStatus()
{
	return been_init;
}

float BigBubble::CheckCollisionWithCaster(int rayon_player, sf::Vector2f position_player, sf::Vector2f size_player)
{
	if (number_of_bounces > 0)
	{
		sf::Vector2f position_projectile = GetCurrentPosition();
		if (GlobalFunction::Check_collision(rayon, rayon_player, position_projectile, position_player, size_projectile, size_player))
		{
			rotation_projectile = GlobalFunction::GetRotationBetweenTwoPositions(position_projectile, position_player);
			number_of_bounces++;
		}
		return GetDamage();
	}
	return 0;
}

void BigBubble::Draw(sf::RenderWindow &window)
{
	window.draw(projectile);

	
}

void BigBubble::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 30));
	window.draw(shadow);

}

sf::Vector2f BigBubble::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool BigBubble::CanPush() { return true; }

float BigBubble::GetDistancePushing() { return propulsion_distance; }

bool BigBubble::CanAffectMonster() { return true; }

bool BigBubble::CanAffectPlayer() { return can_affect_player; }

void BigBubble::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int type_object = object_collided->GetTypeCollisionalObject();
	int id_object = object_collided->GetId();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Player_E)
	{
		if (CanAffectPlayer())
		{
			if (parent->GetId() == object_collided->GetId())
			{
				parent->HealPlayer(GetDamage());
				sf::Vector2f position_objet = object_collided->GetCurrentPosition();
				rotation_projectile = GlobalFunction::GetRotationBetweenTwoPositions(GetCurrentPosition(), position_objet);
				number_of_bounces++;
				can_affect_player = true;

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
			float armor_penetration = parent->GetArmorPenetrationPercent();
			sf::Vector2f position_objet = object_collided->GetCurrentPosition();
			rotation_projectile = GlobalFunction::GetRotationBetweenTwoPositions(GetCurrentPosition(), position_objet);
			number_of_bounces++;
			can_affect_player = true;
			float damage_dealt = object_collided->GotDamaged(GetDamage(),id_parent,armor_penetration);
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

void BigBubble::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool BigBubble::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

