#pragma once
#include "BaseSimpleProjectileWithoutPlayer.h"
#include "Player.h"

class VikingPillar :
	public BaseSimpleProjectileWithoutPlayer
{
private:
	std::shared_ptr<Player> player;
	int source_x = 0;
	bool destroyed = false;
public:
	VikingPillar();
	~VikingPillar();

	void Init(sf::Vector2f &position_initial, bool can_affect_player, bool can_affect_monster, std::shared_ptr<Player> player);
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual int GetTypeCollisionalObject() { return NatureObject_E; }
	virtual sf::Vector2f GetCurrentPositionShadow();
	virtual void DrawShadow(sf::RenderWindow &window);
};

