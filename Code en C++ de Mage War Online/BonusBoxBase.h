#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "ProjectileBase.h" 


class Player;
class BonusBoxBase : public ProjectileBase
{
public:
	BonusBoxBase();
	~BonusBoxBase();

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

