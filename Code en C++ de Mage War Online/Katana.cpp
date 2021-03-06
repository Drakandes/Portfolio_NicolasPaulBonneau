#include "stdafx.h"
#include "Katana.h"


Katana::Katana()
{
	texture_projectile.loadFromFile("Katana.png");
	shadow_texture.loadFromFile("KatanaShadow.png");
}

Katana::~Katana()
{
}

void Katana::Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, int id_caster, float speed, bool can_affect_player, bool can_affect_monster, float range_projectile)
{
	id_parent = id_caster;
	direction_projectile = direction_projectile_received;
	damage_initial = damage_received;
	damage = damage_received;
	position_origin = position_initial;

	this->can_affect_player = can_affect_player;
	this->can_affect_monster = can_affect_monster;

	size_projectile = sf::Vector2f(14, 15);
	shadow_size = size_projectile;
	this->range_projectile = range_projectile;
	speed_projectile = speed;

	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(direction_projectile + 45);

	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
	shadow.setRotation(direction_projectile + 45);
}
