#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <string>
#include <cstring>
#include "IncludeAllSkills.h"

#include "Player.h"

class SkillBase;

class SkillManagement
{
private:
public:
	std::vector<std::shared_ptr<SkillBase>> listAllSkill;

	SkillManagement();
	~SkillManagement();

	void InitSkill(int player_id, int skill_used,sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int skill_used_level, int current_rune);
	void DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int skill_used, int class_player,float range_modifier, int current_rune);
};

