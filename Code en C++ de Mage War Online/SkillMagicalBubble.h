#pragma once
#include "SkillBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Bubble.h"
#include <iostream>
#include <list>

class Bubble;

class SkillMagicalBubble : public SkillBase
{
private:
	int language;
	std::list<Bubble*> listFireball;
	float cooldown_skill_triple_fireball = 5;
	sf::Clock clock_triple_fireball_cooldown;
	sf::Texture texture_icone_skill_triple_fireball;
	float damage_percent;
	float damage_projectile = 1.05;
	float stun_duration;
	const static int number_string_skill_information = 2;
	sf::String string_skill_information[number_string_skill_information];
	int skill_level = 0;

	float range_projectile = 800;
	sf::Vector2f size_projectile{ 26,26 };
	int class_attribution = ClassWater;
public:
	SkillMagicalBubble(int current_language);
	~SkillMagicalBubble();

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

