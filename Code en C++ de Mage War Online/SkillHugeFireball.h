#pragma once
#include "SkillBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "HugeFireball.h"
#include <iostream>
#include <list>
#include "Player.h"

class HugeFireball;

class SkillHugeFireball : public SkillBase
{
private:
	int language;
	float cooldown_skill_huge_fireball = 5;
	sf::Texture texture_icone_skill_huge_fireball;
	const static int number_string_skill_information = 2;
	sf::String string_skill_information[number_string_skill_information];
	int skill_level = 0;
	int rune = NoRune_E;

	float speed_huge_fireball = 7;
	float damage_projectile;
	float damage_multiplier = 2.5;
	float range_projectile;

	sf::Vector2f size_projectile{64,36};
	int class_attribution = ClassFire;

public:
	SkillHugeFireball(int current_language);
	~SkillHugeFireball();

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

