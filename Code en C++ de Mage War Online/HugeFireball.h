#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Player.h"
#include "ProjectileBase.h"

class HugeFireball : public ProjectileBase
{
private:
	std::vector<int> ListIdObject;

	std::shared_ptr<Player> parent;
	sf::Texture texture_huge_fireball;
	sf::Sprite huge_fireball;
	sf::Vector2f size_huge_fireball{ 64,36 };
	sf::Vector2f fireball_image_position_origin;
	sf::Clock clock_animation_of_fireball;
	float speed_huge_fireball;
	float damage_huge_fireball;
	float rotation_huge_fireball;
	float lifesteal_rune_bonus;
	int rayon = 16;
	int fireballDirectionToPlayer;
	int id_projectile;
	int id_parent;
	int fireball_image_animation;
	int range_huge_fireball = 500;
	bool been_init = false;
	bool is_to_delete = false;
	bool fireball_reapparition;
	bool touching_fireball = false;
	bool can_init = true;
	bool need_to_be_put_in_quadtree = false;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 64,36 };

	bool CheckIdObject(int id_object);
public:
	HugeFireball();
	~HugeFireball();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return huge_fireball.getGlobalBounds(); }
	void Init(sf::Vector2f &position_player, float player_damage, float angle, float speed_huge_fireball_received, float range_received, std::shared_ptr<Player> player,float lifesteal_bonus);
	virtual void Texture_loading();
	virtual void Movement_of_fireball( float DELTATIME);
	virtual sf::Vector2f GetCurrentPosition();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual void Initialized(int player_id);
	virtual bool GetInitStatus();
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

