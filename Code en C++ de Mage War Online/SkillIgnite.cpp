#include "stdafx.h"
#include "SkillIgnite.h"

SkillIgnite::SkillIgnite(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("Skill_ignite_icone.png"))
	{
		std::cout << "Error while loading SkillIgnite icone texture" << std::endl;
	}
}

SkillIgnite::~SkillIgnite()
{
}

void SkillIgnite::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(),current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	std::shared_ptr<IgniteProjectile>  projectile = std::shared_ptr<IgniteProjectile>(new IgniteProjectile());
	projectile->Initialized(player_id);
	projectile->Init(position_player, mouse_position, damage_projectile*damage_modifier, speed_projectile*speed_modifier, damage_ignition*damage_modifier, duration_ignition, range_projectile*range_modifier, player);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();
}

sf::Texture SkillIgnite::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillIgnite::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0,class_player, NoRune_E);
	return cooldown_skill;
}

int SkillIgnite::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillIgnite::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillIgnite::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 5 - 0.2 * (skill_level - 1);
	damage_percent = 50 + 5 * (skill_level - 1);
	speed_projectile = 425 + 42.5 * (skill_level - 1);
	duration_ignition = 3 + 0.5 * (skill_level - 1);
	damage_ignition_percent = 18 + 4 * (skill_level - 1);
	range_projectile = 400 + 100 * (skill_level - 1);

	damage_projectile = player_damage*damage_percent / 100;
	damage_ignition = player_damage*damage_ignition_percent / 100;

	if (current_rune == FirstRune_E)
	{
		damage_projectile += damage_projectile*0.5;
	}
	else if (current_rune == SecondRune_E)
	{
		duration_ignition += 1.5;
	}
	else if( current_rune == ThirdRune_E)
	{
		range_projectile += range_projectile*0.2;
		speed_projectile += speed_projectile*0.2;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Ignite";
		string_skill_information[1] = "Throw a fireball that deals 50% (+5% per level) damage on hit and ignite the target. The target hit will burn and take 18% (+4% per level) damage each second for 3 (+0.5 per level) seconds.";
	}
	else
	{
		string_skill_information[0] = "Embrasement";
		string_skill_information[1] = "Lance une boule de feu qui fait 50% (+5% par niveau) de dégâts à l'impact et enflamme la cible touchée. La cible touchée va brûler et prendre 10% (+5% par niveau) de dégâts à chaque seconde pendant 3 (+0.5 par niveau) secondes.";
	}
}

void SkillIgnite::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0,class_player, current_rune);
	sf::RectangleShape rectangle;
	rectangle.setPosition(position_caster);
	rectangle.setSize(sf::Vector2f(range_projectile*range_modifier + size_projectile.x / 2, size_projectile.y));
	rectangle.setFillColor(sf::Color::Color(173, 216, 230, 50));
	rectangle.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
	rectangle.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster));
	DrawGestion::instance()->AddRectangleToList(rectangle);
}

sf::String SkillIgnite::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Increase the skill's damage on impact by 50%.");

		case SecondRune_E:
			return sf::String("Add +1.5 second to the duration of the burning effect.");

		case ThirdRune_E:
			return sf::String("Increase the range and the speed of the projectile by 20%.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Augmente les dégâts du sort à l'impact de 50%.");

		case SecondRune_E:
			return sf::String("Ajoute +1.5 seconde à la durée de l'effet d'embrasement");

		case ThirdRune_E:
			return sf::String("Augmente la portée et la vitesse du sort de 20%.");
		}
	}
}

