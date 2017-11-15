#pragma once
#include "BaseSimpleProjectile.h"

class Shield :
	public BaseSimpleProjectile
{
private:
public:
	Shield();
	~Shield();

	void Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, int id_caster, float speed, bool can_affect_player, bool can_affect_monster, float range_projectile);
};

