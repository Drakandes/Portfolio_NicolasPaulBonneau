#include "stdafx.h"
#include "SkillBlackVine.h"

SkillBlackVine::SkillBlackVine(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("Skill_black_vine_icone.png"))
	{
		std::cout << "Error while loading SkillBlackVine icone texture" << std::endl;
	}
	string_skill_information[0] = "Cursed Vine";
	string_skill_information[1] = "Create a black vine that stuns for ";
	string_skill_information[1] = GlobalFunction::InsertNumberToStringIfFloat(string_skill_information[1], stun_duration, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), " seconds on impact and deals ");
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], damage_percent, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), "% damage.");
}

SkillBlackVine::~SkillBlackVine()
{
}

void SkillBlackVine::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	std::shared_ptr<Vine>  projectile = std::shared_ptr<Vine>(new Vine());
	projectile->Initialized(player_id);
	projectile->InitFromSkill(position_player, mouse_position, damage_projectile*damage_modifier, stun_duration, player, speed_modifier);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();
}

sf::Texture SkillBlackVine::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillBlackVine::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0, class_player,NoRune_E);
	return cooldown_skill;
}

int SkillBlackVine::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillBlackVine::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillBlackVine::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	if (current_rune == ThirdRune_E)
	{
		skill_level += 2;
	}

	cooldown_skill = 6 - 0.35 * (skill_level - 1);
	damage_percent = 125 + 5 * (skill_level - 1);
	stun_duration = 1 + 0.2 * (skill_level - 1);

	damage_projectile = player_damage*damage_percent / 100;

	if (current_rune == FirstRune_E)
	{
		stun_duration += 0.6;
	}
	else if (current_rune == SecondRune_E)
	{
		damage_projectile += player_damage*0.3;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Cursed Vine";
		string_skill_information[1] = "Create a black vine that stuns for 1 second (+0.2 per level) seconds on impact and deals 125% (+5 per level) damage on hit.";
	}
	else
	{
		string_skill_information[0] = "Vigne maudite";
		string_skill_information[1] = "Crée une vigne noire qui étourdit pendant 1 (+0.2 par niveau) secondes à l'impact et fait 125% (+5 par niveau) de dégâts.";
	}
}

void SkillBlackVine::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0, class_player, current_rune);
	sf::RectangleShape rectangle;
	rectangle.setPosition(position_caster);
	rectangle.setSize(size_projectile);
	rectangle.setFillColor(sf::Color::Color(173, 216, 230, 50));
	rectangle.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
	rectangle.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster));
	DrawGestion::instance()->AddRectangleToList(rectangle);
}

sf::String SkillBlackVine::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +0.6 second to the srun duration.");

		case SecondRune_E:
			return sf::String("Add +30% to the percent damage of the skill.");

		case ThirdRune_E:
			return sf::String("Add +2 to the skill level.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +0.6 second à la durée de l'étourdissement.");

		case SecondRune_E:
			return sf::String("Ajoute +30% au pourcentage des dégâts du sort.");

		case ThirdRune_E:
			return sf::String("Ajoute +2 au niveau du sort.");
		}
	}
}


