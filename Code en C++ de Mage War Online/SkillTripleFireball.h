#pragma once
#include "SkillBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Fireball.h"
#include <iostream>
#include <list>

class Fireball;

class SkillTripleFireball : public SkillBase
{
private:
	int language;
	int number_fireball = 3;
	float cooldown_skill_triple_fireball = 5;
	sf::Clock clock_triple_fireball_cooldown;
	sf::Texture texture_icone_skill_triple_fireball;
	float damage_multiplier = 1.051;
	float fireball_range = 800;
	float fireball_speed = 1.5;
	const static int number_string_skill_information = 2;
	sf::String string_skill_information[number_string_skill_information];
	int skill_level = 0;

	sf::Vector2f size_projectile{ 32,18 };
	int class_attribution = ClassFire;
public:
	SkillTripleFireball(int current_language);
	~SkillTripleFireball();

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

