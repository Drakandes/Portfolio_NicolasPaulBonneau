#pragma once
#include "BaseSimpleProjectileWithoutPlayer.h"
#include "Player.h"
class RockArmor : public BaseSimpleProjectileWithoutPlayer
{
private:
	std::shared_ptr<Player> parent;
	sf::Clock clock_duration;

	float duration = 0;
	float bonus_overtime;
	float player_image_size_x = 48;
	float player_image_size_y = 64;
	int level_skill = 0;
	int rune = NoRune_E;
public:
	RockArmor();
	~RockArmor();

	void Init(sf::Vector2f &position_initial, float bonus_overtime, int id_caster , bool can_affect_player, bool can_affect_monster , std::shared_ptr<Player> player, int level_skill, int rune, float duration);
	virtual float GetDamage();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided); 
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual sf::Vector2f GetCurrentPosition() { return projectile.getPosition() - sf::Vector2f(0, -5); }
};


