#include "stdafx.h"
#include "SkillZoneHealing.h"

SkillZoneHealing::SkillZoneHealing(int current_language)
{
	language = current_language;
	if (!texture_icone_skill.loadFromFile("SkillZoneHealing.png"))
	{
		std::cout << "Couldn't load zone healing icone" << std::endl;
	}
}

SkillZoneHealing::~SkillZoneHealing()
{
}

void SkillZoneHealing::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);

	std::shared_ptr<ZoneHealing>  zone = std::shared_ptr<ZoneHealing>(new ZoneHealing());
	zone->Init(position_player, player_damage *healing_done_percent_dmg/100*healing_modifier ,duration_area,player_id, true , false);
	if (current_rune == ThirdRune_E)
	{
		std::vector<int> ListChangeType{ CantDie,MovementSpeedPercent };
		std::vector<float> ListChangeDuration{ -1,-1 };
		std::vector<float> ListChangeValue{ 0 ,-50};
		zone->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
	}
	ProjectileGestion::instance()->AddObjectToList(zone);
	zone.reset();
}

sf::Texture SkillZoneHealing::ReturnSkillIconeTexture()
{
	return texture_icone_skill;
}

float SkillZoneHealing::GetSkillCooldown(int skill_level, int class_player)
{
	return cooldown_skill;
}

int SkillZoneHealing::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillZoneHealing::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillZoneHealing::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 20 - 0.55 * (skill_level - 1);
	healing_done_percent_dmg = 25 + 5 * (skill_level - 1);
	slow_percent = 50;
	healing_modifier = 1;
	if (current_rune == FirstRune_E)
	{
		duration_area += 30;
	}
	else if (current_rune == SecondRune_E)
	{
		healing_modifier = 1.25;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Foutain of Youth";
		string_skill_information[1] = "Transform the ground in a small puddle. Any ally standing in it will be healed for 25% (+5% per level) of the caster's damage each second and will be slowed by 50%. The puddle lasts for 5 seconds.";
	}
	else
	{
		string_skill_information[0] = "Foutaine de Jouvence";
		string_skill_information[1] = "Transforme le sol à une petite marre. Tous les joueurs se tenant dans la zone seront soignés de 25% (+5% par niveau) du dégâts du lanceur à chaque seconde et seront ralentit de 50%. La marre dure 5 secondes.";
	}
}

void SkillZoneHealing::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0, class_player, NoRune_E);
	sf::CircleShape circle;
	circle.setPosition(position_caster);
	circle.setRadius(radius);
	circle.setFillColor(sf::Color::Color(173, 216, 230, 50));
	circle.setOrigin(sf::Vector2f(radius, radius));
	DrawGestion::instance()->AddCircleToList(circle);
}

sf::String SkillZoneHealing::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Reduce the slow to 30%.");

		case SecondRune_E:
			return sf::String("Increase the healing done by 20%.");

		case ThirdRune_E:
			return sf::String("Prevent the player's health to drop below 1.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Réduit l'effect de ralentissement à 30%.");

		case SecondRune_E:
			return sf::String("Augmente la guérison de 20%.");

		case ThirdRune_E:
			return sf::String("Empêche la vie du joueur de descendre sous 1.");
		}
	}
}
