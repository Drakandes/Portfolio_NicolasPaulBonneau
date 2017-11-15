#pragma once
#include "SkillBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>
#include "ReplenishingWaterPack.h"
#include "SkillBase.h"

class ReplenishingWaterPack;

class SkillReplenishingWater : public SkillBase
{
private:
	int language;
	std::list<ReplenishingWaterPack*> listAllProjectiles;
	sf::Texture texture_icone_skill;
	const static int number_string_skill_information = 2;
	sf::String string_skill_information[number_string_skill_information];
	float range_projectile;
	float cooldown_skill = 15;
	float duration_projectile;
	float duration_recovery_bonus;
	float duration_movement_speed_bonus;
	float recovery_value;
	float movement_speed_bonus_value;

	int skill_level = 0;
	sf::Vector2f size_projectile{ 29,29 };
	int class_attribution = ClassWater;
public:
	SkillReplenishingWater(int current_language);
	~SkillReplenishingWater();

	virtual sf::String GetStringRuneBonus(int rune_number);
	virtual int GetSkillClassAttribution() { return class_attribution; }
	virtual void DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune);
	virtual void GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune);
	virtual sf::Texture ReturnSkillIconeTexture();
	virtual float GetSkillCooldown(int skill_level, int class_player);
	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual void ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune);
	virtual int GetTypeSkill() { return ProjectileSkill_E; }
};

