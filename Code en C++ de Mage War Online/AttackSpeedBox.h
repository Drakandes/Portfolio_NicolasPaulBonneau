#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "Player.h"
#include "BonusBoxBase.h"

class Player;

class AttackSpeedBox : public BonusBoxBase
{
private:
	bool been_init = false;
	sf::Texture texture_ablaze_the_fire_box;
	sf::Vector2f size_ablaze_the_fire_box{ 26,10 };
	sf::Vector2f position_ablaze_the_fire_box;
	sf::Sprite sprite_ablaze_the_fire_box;
	bool to_delete = false;
	int player_id;
	int type_of_the_box;
	float duration_boost;
	sf::Clock clock_timer_box_created;
public:
	AttackSpeedBox();
	~AttackSpeedBox();

	virtual bool GetInitStatus();
	virtual void Init(sf::Vector2f position_player, std::shared_ptr<Player> player, float duration_boost_ablaze_the_fire, float attack_speed_bonus_received);
	virtual void DrawToScreen(sf::RenderWindow &window);
	virtual bool IsNeedToDelete();
	virtual void Initialized(int player_id_received, int type_box);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void CheckToDelete();
	virtual int GetTypeBox();
	virtual sf::Vector2f GetCurrentPosition();
	virtual void Draw(sf::RenderWindow &window);
};

