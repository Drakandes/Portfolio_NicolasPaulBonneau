#include "stdafx.h"
#include "LeafBlade.h"

LeafBlade::LeafBlade()
{
	if (!texture_projectile.loadFromFile("LeafBlade.png"))
	{
		std::cout << "Error while loading leaf blade texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("LeafBladeShadow.png"))
	{
		std::cout << "Error while loading fireball projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

LeafBlade::~LeafBlade()
{
	parent.reset();
}

void LeafBlade::Init(sf::Vector2f &position_player, sf::Vector2f mouse_position, float damage_received, float speed_received, float range_projectile_received, float duration_reduction_recevied, float slow_applied_recevied, std::shared_ptr<Player> player)
{
	parent = player;
	player.reset();
	duration_reduction = duration_reduction_recevied;
	slow_applied = slow_applied_recevied;
	damage = damage_received;
	SetAngles(mouse_position, position_player);
	position_origin = position_player;
	projectile = GlobalFunction::CreateSprite(position_player, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	rotation_on_itself = GlobalFunction::getRandomRange(1, 360);
	projectile.setRotation(rotation_on_itself);
	been_init = true;
	speed_initial = speed_received;
	speed_projectile = speed_received;
	range_projectile = range_projectile_received;
}

void LeafBlade::Update(float DELTATIME, sf::Vector2f player_position)
{
	Movement_of_fireball(player_position, DELTATIME);
}

void LeafBlade::SetAngles(sf::Vector2f &mouse_position, sf::Vector2f &position)
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

void LeafBlade::Movement_of_fireball(sf::Vector2f position_player, float DELTATIME)
{
	sf::Vector2f position_projectile = GetCurrentPosition();
	if (coming_back_to_player)
	{ 
		SetAngles(position_player, position_projectile);
		float distance = GlobalFunction::GetDistanceBetweenTwoPositions(position_origin, position_projectile);
		if (distance < 10)
		{
			damage = 0;
		}
		speed_projectile = speed_initial;
		float speed_modification = ((1-(distance / range_projectile)) - 0.1) * speed_projectile;
		if (speed_modification > 0)
		{
			speed_projectile -= speed_modification;
		}
	}
	else
	{
		float distance = GlobalFunction::GetDistanceBetweenTwoPositions(position_origin, position_projectile);
		speed_projectile = speed_initial;
		float speed_modification = ((distance / range_projectile) - 0.1) * speed_projectile;
		if (speed_modification > 0)
		{
			speed_projectile -= speed_modification;
		}
	}

	projectile.move((cos(rotation_projectile * PI / 180))*speed_projectile*DELTATIME, (sin(rotation_projectile * PI / 180))*speed_projectile*DELTATIME);

	if (!coming_back_to_player)
	{
		sf::Vector2f position_2 = GetCurrentPosition();
		if (GlobalFunction::GetDistanceBetweenTwoPositions(position_2, position_origin) >= range_projectile)
		{
			can_affect_player = true;
			coming_back_to_player = true;
			position_origin = position_2;
		}
	}
	projectile.setRotation(rotation_on_itself);
	shadow.setRotation(rotation_on_itself);
	rotation_on_itself += 10;
	if (rotation_on_itself > 360)
	{
		rotation_on_itself = 1;
	}
}

sf::Vector2f LeafBlade::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f LeafBlade::GetSize()
{
	return size_projectile;
}

int LeafBlade::GetRayon()
{
	return rayon;
}

float LeafBlade::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool LeafBlade::IsNeedToDelete()
{
	if (is_to_delete)
	{
		//parent->ChangeASkillCooldown(RestrainingLeafBladeEnum, 0.5);
	}
	return is_to_delete;
}

bool LeafBlade::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (projectile.getGlobalBounds().intersects(rect_collision))
	{
		is_to_delete = true;
		return true;
	}
	return false;
}

void LeafBlade::Initialized(int player_id)
{
	id_parent = player_id;
}

bool LeafBlade::GetInitStatus()
{
	return been_init;
}

float LeafBlade::CheckCollisionWithCaster(int rayon_player, sf::Vector2f position_player, sf::Vector2f size_player)
{
	if (coming_back_to_player)
	{
		if (GlobalFunction::Check_collision(rayon, rayon_player, GetCurrentPosition(), position_player, size_projectile, size_player))
		{
			is_to_delete = true;
		}
	}
	return 0;
}

void LeafBlade::Draw(sf::RenderWindow &window)
{
	
	window.draw(projectile);
}

void LeafBlade::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 18));
	window.draw(shadow);
}

sf::Vector2f LeafBlade::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool LeafBlade::CanSlow() { return true; }

float LeafBlade::GetDurationSlow() { return duration_reduction; }

float LeafBlade::GetPercentSlow() { return slow_applied; }

bool LeafBlade::CanAffectMonster() { return true; }

bool LeafBlade::CanAffectPlayer() { return can_affect_player; }

void LeafBlade::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
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
			if (CanChangeSkillCooldown())
			{
				parent->ChangeASkillCooldown(GetSkillCooldownChanging(), GetNewSkillCooldown());
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

void LeafBlade::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool LeafBlade::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}


