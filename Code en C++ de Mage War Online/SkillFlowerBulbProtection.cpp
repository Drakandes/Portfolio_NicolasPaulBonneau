#include "stdafx.h"
#include "SkillFlowerBulbProtection.h"

SkillFlowerBulbProtection::SkillFlowerBulbProtection(int current_language)
{
	language = current_language;
	if (!texture_icone_skill.loadFromFile("Skill_bulb_icone.png"))
	{
		std::cout << "Couldn't load flower bulb icone" << std::endl;
	}

	string_skill_information[0] = "Bulb of protection";
	string_skill_information[1] = "Make grow a bulb around the player that prevents any damage done to the player for ";
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], duration_boost, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), " seconds and heal the player for ");
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], healing_percent_bonus, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), "% of his maximum health for the duration.");
}

SkillFlowerBulbProtection::~SkillFlowerBulbProtection()
{
}

void SkillFlowerBulbProtection::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received,player_damage, player->GetCurrentClassPlayer(), current_rune);

	std::shared_ptr<FlowerBulb>  projectile = std::shared_ptr<FlowerBulb>(new FlowerBulb());
	projectile->Initialized(player_id);
	projectile->Init(position_player, duration_boost, player, healing_percent_bonus);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();

	SoundGestion::instance()->AddSound("SoundFlowerBulb.wav", 85, false);

	if (current_rune == SecondRune_E)
	{
		player->GivePlayerChangeStat(DamagePercent, duration_boost + 2, 5);
	}
	else if (current_rune == ThirdRune_E)
	{
		player->GivePlayerChangeStat(DefensePercent, duration_boost + 2, 10);
	}
}

sf::Texture SkillFlowerBulbProtection::ReturnSkillIconeTexture()
{
	return texture_icone_skill;
}

float SkillFlowerBulbProtection::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0, class_player,NoRune_E);
	return cooldown_skill;
}

int SkillFlowerBulbProtection::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillFlowerBulbProtection::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillFlowerBulbProtection::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 13 - 0.85 * (skill_level - 1);
	duration_boost = 2 + 0.25 * (skill_level - 1);
	healing_percent_bonus = 3 + 1.25 * (skill_level - 1);

	if (current_rune == FirstRune_E)
	{
		healing_percent_bonus += 1.5;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Bulb of protection";
		string_skill_information[1] = "Grow a bulb around the player that prevents any damage done to the player for 2 (+0.25 per level) seconds and heal the player for 3% (+1.25% per level) of the player maximum health each second.";
	}
	else
	{
		string_skill_information[0] = "Protection Florale";
		string_skill_information[1] = "Fait pousser une plante autour du joueur qui prévient toute attaque envers le joueur pendant 2 (+0.25 par niveau) secondes et soigne le joueur de 3% (+1.25% par niveau) de sa vie totale à chaque seconde pendant toute la durée.";
	}
}

sf::String SkillFlowerBulbProtection::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +1.5% to the recovery bonus.");

		case SecondRune_E:
			return sf::String("Refresh the player, giving him +5% damage for 2 seconds after the bulb went off.");

		case ThirdRune_E:
			return sf::String("At the end, the bulb merges with the player, granting him +10% armor for 2 seconds.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +1.5% au bonus de regénération.");

		case SecondRune_E:
			return sf::String("Rafraîchis le joueur, lui octroyant +5% de dégâts pendantr 2 secondes après la disparition de la fleur. ");

		case ThirdRune_E:
			return sf::String("À la fin, la fleur fusionne avec le joueur, lui octroyant +10% d'armure pendant 2 secondes.");
		}
	}
}
