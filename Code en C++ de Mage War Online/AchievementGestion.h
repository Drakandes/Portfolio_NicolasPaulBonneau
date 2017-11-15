#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "NotificationSystem.h"
#include <vector>

class AchievementGestion
{
private:
	std::vector<float> listValueNeeded{ 10000,300,20,35,100,5,500,10,5,300000,5,75 };
	std::vector<sf::String> string_achievement;
	float last_time = 0;
	sf::Clock clock_outside_battle;
public:
	AchievementGestion();
	~AchievementGestion();

	std::vector<bool> listPossible{ true, true, true, true, true, true, true, true, true, true, true, true };
	std::vector<bool> listSucceeded{ false, false, false, false, false, false, false, false, false, false, false, false };
	std::vector<float> listValueReached{ 0,0,0,0,0,0,0,0,0,0,0,0 };

	void ActionInAchievement(int type_action, float value);
	void PlayerDied();
	void PlayerTookDamage();
	void Update();
	void Init(std::vector<sf::String> string_achievement_received);

	void SaveInformation(int current_save);
	void LoadInformation(int current_save);
};

