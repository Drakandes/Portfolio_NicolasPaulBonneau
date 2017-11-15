#include "stdafx.h"
#include "SkillLavaFloor.h"

SkillLavaFloor::SkillLavaFloor(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("SkillLavaFloor_icone.png"))
	{
		std::cout << "Error while loading SkillLavaFloor icone texture" << std::endl;
	}
	string_skill_information[0] = "Lava floor";
	string_skill_information[1] = "Transform the floor into lava that does ";
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], projectile_damage, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), " damage each ");
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], projectile_thick_per_second, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), "second for ");
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], projectile_duration, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), " seconds.");

}

SkillLavaFloor::~SkillLavaFloor()
{
}

void SkillLavaFloor::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received,player_damage, player->GetCurrentClassPlayer(), current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;

	sf::Vector2f position_projectile = mouse_position;
	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_player, mouse_position) > range_projectile*range_modifier)
	{
		float rotation = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_player);
		sf::Vector2f position_to_add = sf::Vector2f(sf::Vector2f((cos(rotation * PI / 180))*range_projectile*range_modifier, (sin(rotation * PI / 180))*range_projectile*range_modifier));
		position_projectile = position_player + position_to_add;
	}

	std::shared_ptr<LavaFloor>  projectile = std::shared_ptr<LavaFloor>(new LavaFloor());
	projectile->Initialized(player_id);
	projectile->Init(position_projectile, projectile_damage, projectile_duration, projectile_thick_per_second,damage_ignition,duration_ignition, player);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();

	SoundGestion::instance()->AddSound("SoundLavaFloor.wav", 65, false);
}

sf::Texture SkillLavaFloor::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillLavaFloor::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0, class_player,NoRune_E);
	return cooldown_skill;
}

int SkillLavaFloor::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillLavaFloor::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillLavaFloor::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 12 - 0.25 * (skill_level - 1);
	projectile_damage = player_damage * (30 + 4 * (skill_level - 1)) / 100;
	projectile_duration = 4;
	projectile_thick_per_second = 0.8 - 0.1 * (skill_level - 1);
	damage_ignition_percent = 18 + 3 * (skill_level - 1);
	duration_ignition = 1.501 + 0.25 * (skill_level - 1);

	damage_ignition = player_damage*damage_ignition_percent / 100;

	if (current_rune == FirstRune_E)
	{
		projectile_damage += player_damage*0.15;
	}
	else if (current_rune == SecondRune_E)
	{
		damage_ignition += player_damage*0.08;
	}
	else if(current_rune == ThirdRune_E)
	{
		duration_ignition += 0.15 * (skill_level - 1);
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Lava floor";
		string_skill_information[1] = "Transform the floor into lava. Any ennemy that steps on it will take 30% (+4% per level) damage and ignite. Any target burning from lava floor will take 18% (+3% per level) damage each second for 1.5 (+0.25 per level) seconds.";
	}
	else
	{
		string_skill_information[0] = "Sol de lave";
		string_skill_information[1] = "Transforme le sol à un certain endroit en lave. Tous les ennemies qui sont sur ce sol prennent 30% (+4% par niveau) de dégâts et sont embrasés. Tous les cibles embrasées par ce sort sont emflammées et prennent 18% (+3% par niveau) de dégâts par seconde pendant 1.5 (+0.25 par niveau) secondes.";
	}
}

void SkillLavaFloor::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0, class_player, current_rune);
	sf::RectangleShape rectangle;

	sf::Vector2f position_projectile = mouse_position;
	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_caster, mouse_position) > range_projectile*range_modifier)
	{
		float rotation = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster);
		sf::Vector2f position_to_add = sf::Vector2f(sf::Vector2f((cos(rotation * PI / 180))*range_projectile*range_modifier, (sin(rotation * PI / 180))*range_projectile*range_modifier));
		position_projectile = position_caster + position_to_add;
	}
	rectangle.setPosition(position_projectile);
	rectangle.setSize(sf::Vector2f(size_projectile.x, size_projectile.y));
	rectangle.setFillColor(sf::Color::Color(173, 216, 230, 50));
	rectangle.setOrigin(sf::Vector2f(size_projectile.x / 2, size_projectile.y / 2));
	DrawGestion::instance()->AddRectangleToList(rectangle);
}

sf::String SkillLavaFloor::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +15% to the percent damage of the skill.");

		case SecondRune_E:
			return sf::String("Add +8% to the percent damage of the burning effect.");

		case ThirdRune_E:
			return sf::String("Add +0.15 second per skill level to the duration of the burning effect.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +15% au pourcentage de dégâts du sort.");

		case SecondRune_E:
			return sf::String("Ajoute +8% au pourcentage de dégâts de l'effet d'embrasement.");

		case ThirdRune_E:
			return sf::String("Ajoute +0.15 seconde par niveau du sort à la durée de l'effet d'embrasement.");
		}
	}
}

