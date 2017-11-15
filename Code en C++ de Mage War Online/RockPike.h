#pragma once
#include "BaseSimpleProjectileWithoutPlayer.h"
#include "Player.h"
class RockPike : public BaseSimpleProjectileWithoutPlayer
{
private:
	bool can_pierce = false;
	std::shared_ptr<Player> parent;
public:
	RockPike();
	~RockPike();

	void Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, int id_caster, float speed, bool can_affect_player, bool can_affect_monster, float range_projectile, std::shared_ptr<Player> player);
	void CanPierce() { can_pierce = true; }
	virtual float GetDamage();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
};


