#include "stdafx.h"
#include "HealingBall.h"

HealingBall::HealingBall()
{
	if (!texture_projectile.loadFromFile("HealingBall.png"))
	{
		std::cout << "Error while loading healing bal projectile texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("HealingBallShadow.png"))
	{
		std::cout << "Error while loading healing ball projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

HealingBall::~HealingBall()
{
}

void  HealingBall::Init(sf::Vector2f position_initial, float damage_received, int id_caster, std::shared_ptr<MonsterBase> parent_received)
{
	parent = parent_received;
	id_parent = id_caster;
	damage_initial = damage_received;
	damage = damage_received;
	position_origin = position_initial;
	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
}

void HealingBall::Update(float DELTATIME, sf::Vector2f player_position)
{
	MovementGestion(DELTATIME);
}

void  HealingBall::MovementGestion(float DELTATIME)
{
	if (parent != NULL)
	{
		sf::Vector2f parent_position = parent->GetCurrentPosition();
		float angle = GlobalFunction::GetRotationBetweenTwoPositions(GetCurrentPosition(), parent_position);

		projectile.move((cos(angle * PI / 180))*-speed_projectile*DELTATIME, (sin(angle * PI / 180))*-speed_projectile*DELTATIME);
		speed_projectile += 100 * DELTATIME;

		if (parent->IsNeedToDelete())
		{
			parent.reset();
			is_to_delete;
		}
	}
}

sf::Vector2f  HealingBall::GetCurrentPosition()
{
	return projectile.getPosition();
}

sf::Vector2f  HealingBall::GetSize()
{
	return size_projectile;
}

int  HealingBall::GetRayon()
{
	return rayon;
}

float  HealingBall::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool  HealingBall::IsNeedToDelete()
{
	return is_to_delete;
}

void HealingBall::Draw(sf::RenderWindow &window)
{


	window.draw(projectile);
}

void HealingBall::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 18));
	window.draw(shadow);
}

sf::Vector2f HealingBall::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool HealingBall::CanAffectMonster() { return true; }

bool HealingBall::CanAffectPlayer() { return true; }

void HealingBall::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Player_E)
	{
		is_to_delete = true;

		if (CanChangeObjectStat())
		{
			for (int i = 0; i < GetNumberObjectStatChange(); i++)
			{
				object_collided->GivePlayerChangeStat(GetObjectStatChanging(i), GetObjectStatChangeDuration(i), GetObjectStatChangValue(i));
			}
		}
	}

	if (type_object == Monster_E)
	{
		is_to_delete = true;

		object_collided->HealObject(damage);
	}
}

void HealingBall::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool HealingBall::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

bool HealingBall::CanChangeObjectStat() { return true; }

int HealingBall::GetNumberObjectStatChange() { return 1; }

int HealingBall::GetObjectStatChanging(int number) { return MovementSpeedPercent; }

float HealingBall::GetObjectStatChangeDuration(int number) { return slow_duration; }

float HealingBall::GetObjectStatChangValue(int number) { return slow_percent; }

