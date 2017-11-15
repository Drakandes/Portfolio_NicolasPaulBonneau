#include "stdafx.h"
#include "VikingHammer.h"

VikingHammer::VikingHammer()
{
	texture_projectile.loadFromFile("VikingHammer.png");
	shadow_texture.loadFromFile("VikingHammerShadow.png");
}

VikingHammer::~VikingHammer()
{
}

void VikingHammer::Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, int id_caster, float speed, bool can_affect_player, bool can_affect_monster)
{
	id_parent = id_caster;
	direction_projectile = direction_projectile_received;
	damage_initial = damage_received;
	damage = damage_received;
	position_origin = position_initial;
	range_projectile = 800;

	this->can_affect_player = can_affect_player;
	this->can_affect_monster = can_affect_monster;

	size_projectile = sf::Vector2f(100, 60);
	shadow_size = size_projectile;
	speed_projectile = speed;

	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(direction_projectile);

	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
	shadow.setRotation(direction_projectile);
}

void VikingHammer::CuttingSprite()
{
	if (clock_animation.getElapsedTime().asSeconds() >= 0.01)
	{
		projectile.setTextureRect(sf::IntRect(size_projectile.x*source_x, 0, size_projectile.x, size_projectile.y));
		shadow.setTextureRect(sf::IntRect(size_projectile.x*source_x, 0, size_projectile.x, size_projectile.y));
		source_x++;
		if (source_x == 20)
		{
			source_x = 0;
		}
		clock_animation.restart();
	}
}

void VikingHammer::Update(float DELTATIME, sf::Vector2f player_position)
{
	MovementGestion(DELTATIME);
	CuttingSprite();
}

float VikingHammer::GetDamage()
{
	return damage;
}

void VikingHammer::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();
	float armor_penetration = 0;

	if (type_object == Player_E)
	{
		if (CanAffectPlayer())
		{
			is_to_delete = true;
			
			float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, 0);

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

			TextGenerator::instance()->GenerateOneTextForBlob(position_objet, damage_dealt, size_object, object_collided);
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