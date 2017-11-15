#include "stdafx.h"
#include "SkillWarCry.h"

SkillWarCry::SkillWarCry(int current_language)
{
	language = current_language;
	if (!texture_icone_skill.loadFromFile("WarCry_icone.png"))
	{
		std::cout << "Couldn't load ablaze the fire icone" << std::endl;
	}

	string_skill_information[0] = "Increase the player attak speed by ";
	string_skill_information[0] = GlobalFunction::InsertNumberToStringIfFloat(string_skill_information[0], attack_speed_bonus, string_skill_information[0].getSize());
	string_skill_information[0].insert(string_skill_information[0].getSize(), "% and the player damage by for ");
	string_skill_information[0] = GlobalFunction::InsertNumberToStringIfFloat(string_skill_information[0], damage_bonus, string_skill_information[0].getSize());
	string_skill_information[0].insert(string_skill_information[0].getSize(), "% for ");
	string_skill_information[0] = GlobalFunction::InsertNumberToStringIfFloat(string_skill_information[0], duration_boost, string_skill_information[0].getSize());
	string_skill_information[0].insert(string_skill_information[0].getSize(), " seconds.");
}

SkillWarCry::~SkillWarCry()
{
}

void SkillWarCry::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	std::shared_ptr<AttackSpeedBox>  box = std::shared_ptr<AttackSpeedBox>(new AttackSpeedBox());
	box->Initialized(player_id, AttackSpeedPercent);
	box->Init(position_player, player, duration_boost, attack_speed_bonus);
	ProjectileGestion::instance()->AddObjectToList(box);
	box.reset();

	std::shared_ptr<AttackDamageBox>  box2 = std::shared_ptr<AttackDamageBox>(new AttackDamageBox());
	box2->Initialized(player_id, DamagePercent);
	box2->Init(position_player, player, duration_boost, attack_speed_bonus);
	ProjectileGestion::instance()->AddObjectToList(box2);
	box2.reset();

	if (current_rune == FirstRune_E)
	{
		player->GivePlayerChangeStat(LifeSteal, duration_boost, 5);
	}
	else if (current_rune == ThirdRune_E)
	{
		player->GivePlayerChangeStat(MovementSpeedPercent, duration_boost, 10);
	}
}

sf::Texture SkillWarCry::ReturnSkillIconeTexture()
{
	return texture_icone_skill;
}

float SkillWarCry::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0, class_player,NoRune_E);
	return cooldown_skill;
}

int SkillWarCry::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillWarCry::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillWarCry::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	attack_speed_bonus = 30 + 6 * (skill_level - 1);
	cooldown_skill = 18 - 1 * (skill_level - 1);
	duration_boost = 5 + 1 * (skill_level - 1);
	damage_bonus = 15 + 2.5 * (skill_level - 1);

	if (current_rune == SecondRune_E)
	{
		attack_speed_bonus += 15;
		damage_bonus += 5;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Battle stance";
		string_skill_information[1] = "Increase the player attack speed by 30% (+6% per level) and his damage by 15% (+2.5% per level) for 5 (+1 per level) seconds.";
	}
	else
	{
		string_skill_information[0] = "Position d'attaque";
		string_skill_information[1] = "Augmente la vitesse d'attaque du joueur de 30% (+6% par niveau) et ses dégâts de 15% (+2.5% par niveau) pendant 5 (+1 par niveau) secondes.";
	}
}

sf::String SkillWarCry::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("The skill now turns the player into a beast, giving him +5% lifesteal over the duration.");

		case SecondRune_E:
			return sf::String("Add +15% to the attack speed bonus and +5% to the damage bonus.");

		case ThirdRune_E:
			return sf::String("While in battle stance, the player spends less energy moving, giving him +10% movement speed over the duration.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Le sort change le joueur en bête, lui octroyant +5% de vol de vie pendant toute la durée.");

		case SecondRune_E:
			return sf::String("Ajoute +15% au bonus de vitesse d'attaque et +5% au bonus de dégâts.");

		case ThirdRune_E:
			return sf::String("Dans cette position, le joueur dépense moins d'énergie en se déplacant, lui octroyant +10% de vitesse de déplacement pendant toute la durée.");
		}
	}
}

