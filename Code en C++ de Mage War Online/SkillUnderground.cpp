#include "stdafx.h"
#include "SkillUnderground.h"

SkillUnderground::SkillUnderground(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("SkillUnderground.png"))
	{
		std::cout << "Error while loading SkillUnderground icone texture" << std::endl;
	}
}

SkillUnderground::~SkillUnderground()
{
}

void SkillUnderground::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	float angle_going = GlobalFunction::GetRotationBetweenTwoPositions(position_player, mouse_position);

	std::shared_ptr<Underground>  projectile = std::shared_ptr<Underground>(new Underground());
	projectile->Init(position_player, duration, player_id, false, false, player, current_rune, duration_immune);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();

	SoundGestion::instance()->AddSound("SoundZoneLeaf.wav", 100, false);
}

sf::Texture SkillUnderground::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillUnderground::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0, class_player, NoRune_E);
	return cooldown_skill;
}

int SkillUnderground::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillUnderground::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillUnderground::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 15 - 0.5 * (skill_level - 1);
	duration = 2.5;
	duration_immune = 3 + 0.25 * (skill_level - 1);

	if (current_rune == FirstRune_E)
	{
		duration = 1.5;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Undergrounds";
		string_skill_information[1] = "Dig a hole in the ground. After 2.5 seconds seconds, the player is teleported back to the hole. Following the teleportation, the player is immuned for 3 (+0.25 per level) seconds, but he can't move for the duration.";
	}
	else
	{
		string_skill_information[0] = "Souterrains";
		string_skill_information[1] = "Creuse une cavité dans le sol. Après 2.5 secondes, le joueur est téléporté devant la cavité. Suite à la téléportation, le joueur est immunisé pendant 3 (+0.25 par niveau) secondes, mais il ne peut pas bouger.";
	}
}

void SkillUnderground::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
}

sf::String SkillUnderground::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Instead, teleports back the player after 1.5 seconds.");

		case SecondRune_E:
			return sf::String("The player can now move 1 second before the immunity is over.");

		case ThirdRune_E:
			return sf::String("The player also gains +20% overall damage.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Téléporte maintenant le joueur devant la cavité après seulement 1.5 secondes.");

		case SecondRune_E:
			return sf::String("Le joueur peut maintenant bouger 1 seconde avant la fin de l'immunité.");

		case ThirdRune_E:
			return sf::String("Le joueur gagne aussi +20% de dégâts totaux.");
		}
	}
}