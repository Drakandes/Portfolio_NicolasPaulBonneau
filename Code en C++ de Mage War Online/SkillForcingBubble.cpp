#include "stdafx.h"
#include "SkillForcingBubble.h"

SkillForcingBubble::SkillForcingBubble(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("Skill_forcing_bubble_icone.png"))
	{
		std::cout << "Error while loading SkillForcingBubble icone texture" << std::endl;
	}
}

SkillForcingBubble::~SkillForcingBubble()
{
}

void SkillForcingBubble::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	std::shared_ptr<BigBubble>  projectile = std::shared_ptr<BigBubble>(new BigBubble());
	projectile->Init(position_player, mouse_position, damage_projectile*damage_modifier, speed_projectile*speed_modifier, range_projectile*range_modifier, distance_explosion, maximum_bounce_projecile, player);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();
}

sf::Texture SkillForcingBubble::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillForcingBubble::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0,class_player,NoRune_E);
	return cooldown_skill;
}

int SkillForcingBubble::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillForcingBubble::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillForcingBubble::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 7 - 0.35 * (skill_level - 1);
	speed_projectile = 400 + 30 * (skill_level - 1);
	range_projectile = 650 + 50 * (skill_level - 1);
	distance_explosion = 75 + 15 * (skill_level - 1);
	damage_percent = 90 + 5 * (skill_level - 1);
	maximum_bounce_projecile = 3 + 1 * (skill_level - 1);

	damage_projectile = player_damage*damage_percent / 100;

	if (current_rune == FirstRune_E)
	{
		distance_explosion += distance_explosion*0.4;
	}
	else if (current_rune == SecondRune_E)
	{
		maximum_bounce_projecile += 2; 
	}
	else if (current_rune == ThirdRune_E)
	{
		damage_projectile += damage_projectile*0.2;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Forcing Bubble";
		string_skill_information[1] = "Throw a bubble that deals 90% (+5% per level) damage to ennemy hit. Heal for the same amount if it hits an ally. The bubble will bounce on any ennemy it his, propulsing them away.";
	}
	else
	{
		string_skill_information[0] = "Bubble contraignante";
		string_skill_information[1] = "Lance une bulle d'eau qui fait 90% (+5% par niveau) de dégâts à l'impact et soigne du même montant le joueur lorsqu'elle entre en collision avec lui. La bulle rebondit à l'impact, repoussant la cible ennemi touchée.";
	}
}

void SkillForcingBubble::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0,class_player, current_rune);
	sf::RectangleShape rectangle;
	rectangle.setPosition(position_caster);
	rectangle.setSize(sf::Vector2f(range_projectile*range_modifier + size_projectile.x/2,size_projectile.y));
	rectangle.setFillColor(sf::Color::Color(173, 216, 230, 50));
	rectangle.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
	rectangle.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster));
	DrawGestion::instance()->AddRectangleToList(rectangle);
}

sf::String SkillForcingBubble::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Increase the propulsion's distance by 40%.");

		case SecondRune_E:
			return sf::String("The bubble is more resistant, adding +2 bounces.");

		case ThirdRune_E:
			return sf::String("Increase the damage by 20%.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Augmente la distance de la propulsion de 40%.");

		case SecondRune_E:
			return sf::String("La bulle est plus résistante, ajoutant +2 rebonds.");

		case ThirdRune_E:
			return sf::String("Augmente les dégâts de 20%.");
		}
	}
}

