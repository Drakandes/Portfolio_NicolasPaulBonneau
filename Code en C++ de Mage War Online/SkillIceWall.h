#pragma once
#include "SkillBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>
#include "IceBlock.h"
#include "Player.h"

class IceBlock;

class SkillIceWall : public SkillBase
{
private:
	int language;
	std::list<IceBlock*> listAllProjectiles;
	sf::Texture texture_icone_skill;
	const static int number_string_skill_information = 2;
	sf::String string_skill_information[number_string_skill_information];
	sf::Vector2f last_position_forcing_bubble_explosed{ 0,0 };
	float distance_propulsion_when_colliding = 5;
	float range_projectile;
	float cooldown_skill = 15;
	float duration_projectile;

	int skill_level = 0;
	sf::Vector2f size_projectile{ 124,76 };
	int class_attribution = ClassWater;
public:
	SkillIceWall(int current_language);
	~SkillIceWall();

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

