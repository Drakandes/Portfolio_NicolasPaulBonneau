#pragma once
#include "BaseSimpleProjectileWithoutPlayer.h"
#include "Player.h"
class RockBelt : public BaseSimpleProjectileWithoutPlayer
{
private:
	std::shared_ptr<Player> parent;
	sf::Clock clock_duration;

	std::vector<int> ListIdObject;
	std::vector<sf::Clock> ListClockObject;

	float damage = 0;
	float duration = 0;
	float time_between_damage = 1;
	float skill_shield_leech;
public:
	RockBelt();
	~RockBelt();

	void Init(sf::Vector2f &position_initial, float damage, int id_caster, bool can_affect_player, bool can_affect_monster, std::shared_ptr<Player> player, float duration, float skill_shield_leech);
	virtual float GetDamage();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual sf::Vector2f GetCurrentPosition() { return projectile.getPosition() - sf::Vector2f(0, 1); }
	bool CheckIdObject(int id_object);
	virtual bool CanDamageNatureObject() { return false; }
};


