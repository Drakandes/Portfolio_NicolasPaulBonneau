#pragma once
#include "BaseSimpleProjectileWithoutPlayer.h"

class MollySpike :
	public BaseSimpleProjectileWithoutPlayer
{
private:
	int source_x = 0;
	bool can_attack = false;
	bool can_update = true;
public:
	MollySpike();
	~MollySpike();

	void Init(sf::Vector2f &position_initial, bool can_affect_player, bool can_affect_monster, float damage);
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::Vector2f GetCurrentPositionShadow();
	virtual void DrawShadow(sf::RenderWindow &window);
};

