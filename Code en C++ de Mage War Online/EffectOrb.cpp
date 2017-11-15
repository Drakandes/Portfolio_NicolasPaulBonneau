#include "stdafx.h"
#include "EffectOrb.h"

EffectOrb::EffectOrb()
{
	texture_projectile.loadFromFile("EffectOrb.png");
	shadow_texture.loadFromFile("EffectOrbShadow.png");
}

EffectOrb::~EffectOrb()
{
}

void EffectOrb::Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, int id_caster, float speed, bool can_affect_player, bool can_affect_monster, float range_projectile, int type_pet)
{
	id_parent = id_caster;
	direction_projectile = direction_projectile_received;
	damage_initial = damage_received;
	damage = damage_received;
	position_origin = position_initial;
	this->can_affect_player = can_affect_player;
	this->can_affect_monster = can_affect_monster;

	size_projectile = sf::Vector2f(21, 21);
	shadow_size = size_projectile;
	this->range_projectile = range_projectile;
	speed_projectile = speed;

	projectile = GlobalFunction::CreateSprite(position_initial, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(size_projectile.x*type_pet, 0, size_projectile.x, size_projectile.y));

	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}