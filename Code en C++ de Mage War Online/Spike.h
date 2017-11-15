#pragma once
#include "BaseSimpleProjectile.h"
#include "Player.h"

class Spike :
	public BaseSimpleProjectile
{
private:
public:
	Spike();
	~Spike();

	void Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, int id_caster, float speed, bool can_affect_player, bool can_affect_monster, float range_projectile, std::shared_ptr<Player> player);
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
};

