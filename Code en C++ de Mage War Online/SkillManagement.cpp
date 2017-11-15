#include "stdafx.h"
#include "SkillManagement.h"

SkillManagement::SkillManagement()
{
	listAllSkill = ListObjectsSingleton::instance()->GetListSkill();
}

SkillManagement::~SkillManagement()
{
	listAllSkill.clear();
}

void SkillManagement::InitSkill(int player_id, int skill_used, sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int skill_used_level, int current_rune)
{
	listAllSkill[skill_used]->GenerateSkillProjectile(position_player, player_damage, mouse_position, player, player_id, skill_used_level, current_rune);
}

void SkillManagement::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int skill_used, int class_player,float range_modifier, int current_rune)
{
	listAllSkill[skill_used]->DrawSkillHitBox(mouse_position, skill_level, position_caster, class_player,range_modifier, current_rune);
}
