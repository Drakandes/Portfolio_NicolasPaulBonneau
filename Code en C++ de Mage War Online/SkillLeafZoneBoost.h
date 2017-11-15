#pragma once
#include "SkillBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>
#include "LeafZone.h"

class LeafZone;

class SkillLeafZoneBoost : public SkillBase
{
private:
	int language;
	sf::Texture texture_icone_skill;
	const static int number_string_skill_information = 2;
	sf::String string_skill_information[number_string_skill_information];
	float cooldown_skill = 25;
	float duration_area = 8;
	float duration_boost = 0.1;
	float defense_boost = 10;
	float health_percent_boost = 20;
	
	int skill_level = 0;
	float radius = 150;
	int class_attribution = ClassGrass;
public:
	SkillLeafZoneBoost(int current_language);
	~SkillLeafZoneBoost();

	virtual sf::String GetStringRuneBonus(int rune_number);
	virtual int GetSkillClassAttribution() { return class_attribution; }
	virtual void DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune);
	virtual void GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune);
	virtual sf::Texture ReturnSkillIconeTexture();
	virtual float GetSkillCooldown(int skill_level, int class_player);
	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual void ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune);
	virtual int GetTypeSkill() { return ZoneSkill_E; }
};

