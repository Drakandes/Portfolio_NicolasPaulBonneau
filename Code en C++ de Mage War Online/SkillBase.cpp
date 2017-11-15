#include "stdafx.h"
#include "SkillBase.h"

SkillBase::SkillBase()
{
}

SkillBase::~SkillBase()
{
}

void SkillBase::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{

}

sf::Texture SkillBase::ReturnSkillIconeTexture()
{
	sf::Texture no_texture;
	return no_texture;
}

float SkillBase::GetSkillCooldown(int skill_level, int class_player)
{
	return 0;
}

int SkillBase::GetNumberStringSkillInformation()
{
	return 0;
}

sf::String SkillBase::GetStringSkillInformation(int number_string)
{
	sf::String string = "Unknown";
	return string;
}

void SkillBase::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
}

int SkillBase::GetPassiveBonusType()
{
	return 0;
}

float SkillBase::GetPassiveBonusValue(int player_level, int class_player, int current_rune)
{
	return 0;
}

float SkillBase::GetPassiveBonusDuration(int player_level, int class_player, int current_rune)
{
	return 0;
}