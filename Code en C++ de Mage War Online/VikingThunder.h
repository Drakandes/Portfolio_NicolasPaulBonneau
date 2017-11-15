#pragma once
#include "BaseSimpleProjectileWithoutPlayer.h"
class VikingThunder : public BaseSimpleProjectileWithoutPlayer
{
private:
	sf::CircleShape circle_impact;
	sf::CircleShape circle_channeling;
	sf::CircleShape rect_hitbox;;

	int rayon = 30;
	int bonus_size = -3;

	bool spawned = false;
	bool can_pierce = false;
	bool can_do_damage = false;

	float time_before_attack =1;
	float time_to_do_damage = 0.94;
	float time_lighting = 0.25;
public:
	VikingThunder();
	~VikingThunder();

	virtual sf::FloatRect GetCollisionRect() { return rect_hitbox.getGlobalBounds(); }
	void Init(sf::Vector2f &position_initial, float damage_received, int id_caster, bool can_affect_player, bool can_affect_monster);
	virtual float GetDamage();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void Draw(sf::RenderWindow &window);
};


