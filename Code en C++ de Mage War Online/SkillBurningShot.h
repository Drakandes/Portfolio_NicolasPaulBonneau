#pragma once
#include "SkillBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>

class SkillBurningShot : public SkillBase
{
private:
	int language;
	sf::Texture texture_;
	const static int number_string_skill_information = 2;
	sf::String string_skill_information[number_string_skill_information];
	int skill_level = 0;
	float ignition_damage = 1;
	float ignition_duration = 3.001;
	int ignition_type = OnFireFromPassive;
	int class_attribution = ClassFire;
public:
	SkillBurningShot(int current_language);
	~SkillBurningShot();

	virtual sf::String GetStringRuneBonus(int rune_number);
	virtual int GetSkillClassAttribution() { return class_attribution; }
	virtual void GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune);
	virtual sf::Texture ReturnSkillIconeTexture();
	virtual float GetSkillCooldown(int skill_level, int class_player);
	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual void ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune);
	virtual int GetTypeSkill() { return PassiveSkill_E; }

	virtual int GetPassiveBonusType();
	virtual float GetPassiveBonusValue(int player_level, int class_player, int current_rune);
	virtual float GetPassiveBonusDuration(int player_level, int class_player, int current_rune);
};


