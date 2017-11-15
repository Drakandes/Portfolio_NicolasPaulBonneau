#pragma once
#include "SkillBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>
#include <vector>

class SkillSwiftness : public SkillBase
{
private:
	int language;
	sf::Texture texture_icone;
	const static int number_string_skill_information = 2;
	sf::String string_skill_information[number_string_skill_information];
	int skill_level;

	int passive_type = DefensePercent;
	float passive_value = 22;
	int class_attribution = NoClass;
public:
	SkillSwiftness(int current_language);
	~SkillSwiftness();

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
};

