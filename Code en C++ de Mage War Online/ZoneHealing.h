#pragma once
#include "BaseSimpleProjectileWithoutPlayer.h"

class ZoneHealing :
	public BaseSimpleProjectileWithoutPlayer
{
private:
	sf::Clock clock_heal;
public:
	ZoneHealing();
	~ZoneHealing();

	void Init(sf::Vector2f &position_initial, float healing_done, float duration_projectile_received, int id_caster, bool can_affect_player, bool can_affect_monster);
	virtual void MovementGestion(float DELTATIME);
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual bool DrawOnTheFloor() { return true; }
};

