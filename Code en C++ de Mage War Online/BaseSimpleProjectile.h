#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "Player.h"
#include "GlobalFunction.h"
#include "ProjectileBase.h"

class BaseSimpleProjectile : public ProjectileBase
{
protected:
	std::shared_ptr<Player> parent;
	bool need_to_be_put_in_quadtree = false;
	int rayon = 6;
	int id_projectile;
	int id_parent;
	int ignite_type = 0;
	float damage_initial;
	float damage;
	float direction_projectile;
	float range_projectile = 300;
	float speed_projectile = 850;
	float slow_duration = 0;
	float slow_percent = 0;
	float stun_duration = 0;
	float ignite_duration = 0;
	float ignite_damage = 0;
	float duration_projectile = 0;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile{ 11,10 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	bool is_to_delete = false;
	bool been_drawed = false;
	bool can_affect_monster = false;
	bool can_affect_player = false;
	bool can_slow = false;
	bool can_stun = false;
	bool can_ignite = false;
	bool can_change_stat = false;
	sf::Clock clock_animation;
	sf::Clock clock_duration;
	std::vector<int> ListChangeType;
	std::vector<float> ListChangeDuration;
	std::vector<float> ListChangeValue;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 11,10 };
public:
	BaseSimpleProjectile();
	~BaseSimpleProjectile();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void GiveParent(std::shared_ptr<Player> parent_received) { parent = parent_received; }
	void MovementGestion(float DELTATIME);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();

	virtual void GiveSlowEffect(float duration, float percent) { can_slow = true; slow_duration = duration; slow_percent = percent; }
	virtual void GiveStunEffect(float duration) { can_stun = true; stun_duration = duration; }
	virtual void GiveStunEffect(float duration, float percent, int type) {can_ignite = true; ignite_duration = duration; ignite_damage = percent; ignite_type = type;}
	virtual void GiveChangeEffect(std::vector<int> ListType, std::vector<float> ListDuration, std::vector<float> ListValue) { ListChangeDuration = ListDuration; ListChangeType = ListType; ListChangeValue = ListValue; can_change_stat = true; }

	virtual bool CanSlow() { return can_slow; }
	virtual float GetDurationSlow() { return slow_duration; }
	virtual float GetPercentSlow(){return slow_percent;}

	virtual bool CanChangeObjectStat() { return can_change_stat; }
	virtual int GetNumberObjectStatChange() { return ListChangeType.size(); }
	virtual int GetObjectStatChanging(int number) { return ListChangeType[number]; }
	virtual float GetObjectStatChangeDuration(int number) { return ListChangeDuration[number]; }
	virtual float GetObjectStatChangValue(int number) { return ListChangeValue[number]; }

	virtual bool CanIgnite() { return can_ignite; }
	virtual int GetTypeIgnition() { return ignite_type; }
	virtual float GetIgnitionDuration() { return ignite_duration; }
	virtual float GetIgnitionDamage() { return ignite_damage; }

	virtual bool CanStun() { return can_stun; }
	virtual float GetStunTime() { return stun_duration; }
};