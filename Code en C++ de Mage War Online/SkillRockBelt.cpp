#include "stdafx.h"
#include "SkillRockBelt.h"

SkillRockBelt::SkillRockBelt(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("SkillRockBelt.png"))
	{
		std::cout << "Error while loading SkillRockBelt icone texture" << std::endl;
	}
}

SkillRockBelt::~SkillRockBelt()
{
}

void SkillRockBelt::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	float angle_going = GlobalFunction::GetRotationBetweenTwoPositions(position_player, mouse_position);

	std::shared_ptr<RockBelt>  projectile = std::shared_ptr<RockBelt>(new RockBelt());
	projectile->Init(position_player, damage, player_id, false, true, player, duration, skill_shield_leech);

	if (current_rune == FirstRune_E)
	{
		projectile->GiveSlowEffect(1, 15);
	}
	else if (current_rune == FirstRune_E)
	{
		player->GivePlayerChangeStat(DamageReduction, duration, 10);
	}

	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();
}

sf::Texture SkillRockBelt::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillRockBelt::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0, class_player, NoRune_E);
	return cooldown_skill;
}

int SkillRockBelt::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillRockBelt::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillRockBelt::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 8 - 0.15 * (skill_level - 1);
	duration = 5;
	float damage_percent = 45 + 5 * (skill_level - 1);
	skill_shield_leech = 25;

	damage = player_damage*damage_percent / 100;

	if (current_rune == ThirdRune_E)
	{
		skill_shield_leech += 12;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Rock Belt";
		string_skill_information[1] = "Cast rocks that gravitate around the player, dealing 45% (+5% per level) damage each second to nearby ennemies for 5 seconds. Whenever a ennemy is hit, the player recovers 25% of the damage dealt in shield.";
	}
	else
	{
		string_skill_information[0] = "Ceinture de Roche";
		string_skill_information[1] = "Fait appaître des roches qui gravitent autour du joueur, infligeant 45% (+5% par niveau) de dégâts aux ennemis proches pendant 5 secondes. À chaque ennemi touché, le joueur récupère 25% des dégâts infligés en bouclier.";
	}
}

void SkillRockBelt::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
}

sf::String SkillRockBelt::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("The belt slows nearby ennemies by 15% for 1 second each hit.");

		case SecondRune_E:
			return sf::String("Reduce the damage received by 10% while the rock belt is active.");

		case ThirdRune_E:
			return sf::String("The shield recovery is increased by +12%.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("La ceinture ralentit les ennemis proches de 15% pendant 1 seconde à chaque coup.");

		case SecondRune_E:
			return sf::String("Réduit les dégâts reçus de 10% pendant que la ceinture de roche est active.");

		case ThirdRune_E:
			return sf::String("La récupération de bouclier est augmentée de +12%.");
		}
	}
}