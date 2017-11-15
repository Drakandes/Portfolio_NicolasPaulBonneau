#include "stdafx.h"
#include "SkillRockArmor.h"

SkillRockArmor::SkillRockArmor(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("SkillRockArmor.png"))
	{
		std::cout << "Error while loading SkillRockArmor icone texture" << std::endl;
	}
}

SkillRockArmor::~SkillRockArmor()
{
}

void SkillRockArmor::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	float angle_going = GlobalFunction::GetRotationBetweenTwoPositions(position_player, mouse_position);

	std::shared_ptr<RockArmor>  projectile = std::shared_ptr<RockArmor>(new RockArmor());
	projectile->Init(position_player,bonus_overtime,player_id,false,false,player,skill_level_received,current_rune,duration);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();

	SoundGestion::instance()->AddSound("SoundRockArmor.wav", 85, false);
}

sf::Texture SkillRockArmor::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillRockArmor::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0, class_player, NoRune_E);
	return cooldown_skill;
}

int SkillRockArmor::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillRockArmor::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillRockArmor::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 16 - 0.4 * (skill_level - 1);
	duration = 5.5 + 0.25*(skill_level - 1);
	bonus_overtime = 55 + 7 * (skill_level - 1);

	if (language == English_E)
	{
		string_skill_information[0] = "Rock Armor";
		string_skill_information[1] = "Cast a rock armor that increase the player's armor by up to 55% (+7% per level) over 5.5 (+0.25 per level) seconds.";
	}
	else
	{
		string_skill_information[0] = "Armure de Roche";
		string_skill_information[1] = "Fait appaître une armure de roche qui augmente l'armure du joueur jusqu'à 55% (+7% par niveau) sur 5.5 (+0.25 par niveau) secondes.";
	}
}

void SkillRockArmor::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
}

sf::String SkillRockArmor::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Also give the player 10 (+2 per skill level) bonus armor.");

		case SecondRune_E:
			return sf::String("Also increase the player's damage by 20%, but reduce movement speed by 10%.");

		case ThirdRune_E:
			return sf::String("It takes 2 seconds less time to get the full bonus and the duration remains the same.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Donne aussi au joueur 10 (+2 par niveau du sort) armure bonus.");

		case SecondRune_E:
			return sf::String("Augmente aussi les dégâts du joueur de 20%, mais réduit la vitesse de déplacement de 10%.");

		case ThirdRune_E:
			return sf::String("Il faut 2 secondes de moins afin d'avoir le bonus entier et la duration reste la même.");
		}
	}
}