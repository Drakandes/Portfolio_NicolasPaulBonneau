#pragma once
#include "SkillBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>
#include <vector>
#include "LavaFloor.h"

class SkillLavaFloor : public SkillBase
{
private:
	int language;
	sf::Texture texture_icone;
	const static int number_string_skill_information = 2;
	sf::String string_skill_information[number_string_skill_information];
	float cooldown_skill = 12;
	float current_player_damage = 0;
	int skill_level;

	float projectile_duration;
	float projectile_damage;
	float projectile_thick_per_second = 1;
	float range_projectile = 650;

	int type_ignition = OnFireFromSkill;
	float damage_ignition_percent = 20;
	float damage_ignition;
	float duration_ignition = 8;

	sf::Vector2f size_projectile{ 100,50 };
	int class_attribution = ClassFire;
public:
	SkillLavaFloor(int current_language);
	~SkillLavaFloor();

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

