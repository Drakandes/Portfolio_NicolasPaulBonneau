#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ProjectileGestion.h"

class Player;
class ExplosionGenerator;

class SkillBase
{
private:

public:
	SkillBase();
	~SkillBase();

	virtual sf::String GetStringRuneBonus(int rune_number) { return sf::String("Error Wrong Rune"); }
	virtual int GetSkillClassAttribution() { return NoClass; }
	virtual void DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune){}
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
