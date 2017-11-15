#pragma once
#include "BaseSimpleProjectileWithoutPlayer.h"
class VikingHammer : public BaseSimpleProjectileWithoutPlayer
{
private:
	int source_x = 0;

	void CuttingSprite();
public:
	VikingHammer();
	~VikingHammer();

	void Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, int id_caster, float speed, bool can_affect_player, bool can_affect_monster);
	virtual float GetDamage();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
};


