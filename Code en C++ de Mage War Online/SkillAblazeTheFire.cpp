
#include "stdafx.h"
#include "SkillAblazeTheFire.h"

SkillAblazeTheFire::SkillAblazeTheFire(int current_language)
{
	language = current_language;
	if (!texture_icone_skill_ablaze_the_fire.loadFromFile("Ablaze_the_fire_icone.png"))
	{
		std::cout << "Couldn't load ablaze the fire icone" << std::endl;
	}

	string_skill_information[0] = "Increase the player attak speed by ";
	string_skill_information[0] = GlobalFunction::InsertNumberToStringIfFloat(string_skill_information[0], attack_speed_bonus, string_skill_information[0].getSize());
	string_skill_information[0].insert(string_skill_information[0].getSize(), "% for ");
	string_skill_information[0] = GlobalFunction::InsertNumberToStringIfFloat(string_skill_information[0], duration_boost_ablaze_the_fire, string_skill_information[0].getSize());
	string_skill_information[0].insert(string_skill_information[0].getSize(), " seconds.");
}

SkillAblazeTheFire::~SkillAblazeTheFire()
{
}

void SkillAblazeTheFire::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(),current_rune);

	std::shared_ptr<AttackSpeedBox> projectile = std::shared_ptr<AttackSpeedBox>(new AttackSpeedBox());
	projectile->Initialized(player_id, AttackSpeedPercent);
	projectile->Init(position_player, player, duration_boost_ablaze_the_fire, attack_speed_bonus);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();

	if (current_rune == ThirdRune_E)
	{
		player->GivePlayerChangeStat(DamagePercent, duration_boost_ablaze_the_fire, 8);
	}
}

sf::Texture SkillAblazeTheFire::ReturnSkillIconeTexture()
{
	return texture_icone_skill_ablaze_the_fire;
}

float SkillAblazeTheFire::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0, class_player,NoRune_E);
	return cooldown_skill_ablaze_the_fire;
}

int SkillAblazeTheFire::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillAblazeTheFire::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillAblazeTheFire::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if(class_attribution == class_player)
	{ 
		skill_level++;
	}

	attack_speed_bonus = 40 + 12 * (skill_level - 1);
	cooldown_skill_ablaze_the_fire = 15 - 0.85 * (skill_level - 1);
	duration_boost_ablaze_the_fire = 5 + 1 * (skill_level - 1);

	if (current_rune == FirstRune_E)
	{
		duration_boost_ablaze_the_fire += 2;
	}
	else if (current_rune == SecondRune_E)
	{
		attack_speed_bonus += 15;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Ablaze the fire";
		string_skill_information[1] = "Increase the player attak speed by 40% (+12% per level) for 5 (+1 per level) seconds.";
	}
	else
	{
		string_skill_information[0] = "Augmenter la cadence";
		string_skill_information[1] = "Augemente la vitesse d'attaque du joueur de 40% (+12% par niveau) pendant 5 (+1 par niveau) secondes.";
	}
}

sf::String SkillAblazeTheFire::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Increase the duration by 2 seconds.");

		case SecondRune_E:
			return sf::String("Add +15% to the attack speed bonus.");

		case ThirdRune_E:
			return sf::String("The player now gets crazy, getting a +8% damage bonus over the duration.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Augmente la durée de 2 secondes.");

		case SecondRune_E:
			return sf::String("Ajoute +15% au bonus de vitesse d'attaque.");

		case ThirdRune_E:
			return sf::String("Le joueur devient fou, recevant un bonus de +8% aux dégâts pendant toute la durée.");
		}
	}
}

