#pragma once
#include "SkillBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>
#include <vector>
#include "BigBubble.h"

class SkillForcingBubble : public SkillBase
{
private:
	int language;
	sf::Texture texture_icone;
	const static int number_string_skill_information = 2;
	sf::String string_skill_information[number_string_skill_information];

	sf::Vector2f last_position_forcing_bubble_explosed{ 0,0 };

	float cooldown_skill;
	int skill_level;

	float damage_percent;
	float distance_explosion;
	float force_explosion = WeakPush;
	float range_projectile;
	float damage_projectile;
	float speed_projectile;
	int maximum_bounce_projecile;

	sf::Vector2f size_projectile{30,30};
	int class_attribution = ClassWater;
public:
	SkillForcingBubble(int current_language);
	~SkillForcingBubble();

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


