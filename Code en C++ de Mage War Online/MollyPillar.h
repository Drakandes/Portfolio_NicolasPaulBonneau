#pragma once
#include "BaseSimpleProjectileWithoutPlayer.h"
#include "Player.h"
#include "MollySpike.h"

class MollyPillar :
	public BaseSimpleProjectileWithoutPlayer
{
private:
	std::shared_ptr<Player> player;
	int source_x = 0;
	float size_spike = 40;
	float range_spike = 6;
	float damage_spike = 350;
	bool boosted = false;
	sf::Clock clock_boosted;
	sf::Clock clock_attack;
public:
	MollyPillar();
	~MollyPillar();

	void Init(sf::Vector2f &position_initial, bool can_affect_player, bool can_affect_monster, std::shared_ptr<Player> player);
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual int GetTypeCollisionalObject() { return NatureObject_E; }
	virtual sf::Vector2f GetCurrentPositionShadow();
	virtual void DrawShadow(sf::RenderWindow &window);
	void Attack();
};

