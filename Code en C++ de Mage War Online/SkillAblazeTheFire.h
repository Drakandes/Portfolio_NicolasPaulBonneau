#pragma once
#include "SkillBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>
#include "AttackSpeedBox.h"

class AttackSpeedBox;

class SkillAblazeTheFire : public SkillBase
{
private:
	int language;
	std::list<AttackSpeedBox*> listAblazeTheFirebox;
	sf::Texture texture_icone_skill_ablaze_the_fire;
	float cooldown_skill_ablaze_the_fire = 30;
	float duration_boost_ablaze_the_fire = 5;
	const static int number_string_skill_information = 2;
	sf::String string_skill_information[number_string_skill_information];
	float attack_speed_bonus = 50;
	int skill_level = 0;
	int class_attribution = ClassFire;
public:
	SkillAblazeTheFire(int current_language);
	~SkillAblazeTheFire();

	virtual sf::String GetStringRuneBonus(int rune_number);
	virtual int GetSkillClassAttribution() { return class_attribution; }
	virtual void GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune);
	virtual sf::Texture ReturnSkillIconeTexture();
	virtual float GetSkillCooldown(int skill_level, int class_player);
	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual void ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune);
	virtual int GetTypeSkill() { return BuffSkill_E; }
};

