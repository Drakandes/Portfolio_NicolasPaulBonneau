#include "stdafx.h"
#include "SkillReplenishingWater.h"

SkillReplenishingWater::SkillReplenishingWater(int current_language)
{
	language = current_language;
	if (!texture_icone_skill.loadFromFile("Skill_waterpack_icone.png"))
	{
		std::cout << "Couldn't load replenishing water pack icone" << std::endl;
	}
}

SkillReplenishingWater::~SkillReplenishingWater()
{
}

void SkillReplenishingWater::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	sf::Vector2f position_projectile = mouse_position;
	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_player, mouse_position) > range_projectile*range_modifier)
	{
		float rotation = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_player);
		sf::Vector2f position_to_add = sf::Vector2f(sf::Vector2f((cos(rotation * PI / 180))*range_projectile*range_modifier, (sin(rotation * PI / 180))*range_projectile*range_modifier));
		position_projectile = position_player + position_to_add;
	}


	std::shared_ptr<ReplenishingWaterPack>  projectile = std::shared_ptr<ReplenishingWaterPack>(new ReplenishingWaterPack());
	projectile->Initialized(player_id);
	projectile->Init(position_projectile, duration_projectile, recovery_value*damage_modifier, duration_recovery_bonus, movement_speed_bonus_value, duration_movement_speed_bonus);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();

	if (current_rune == ThirdRune_E)
	{
		std::shared_ptr<ReplenishingWaterPack>  projectile1 = std::shared_ptr<ReplenishingWaterPack>(new ReplenishingWaterPack());
		projectile1->Initialized(player_id);
		projectile1->Init(position_player, duration_projectile/4, recovery_value*damage_modifier / 4, duration_recovery_bonus / 4, movement_speed_bonus_value / 4, duration_movement_speed_bonus / 4);
		ProjectileGestion::instance()->AddObjectToList(projectile1);
		projectile1.reset();
	}
}

sf::Texture SkillReplenishingWater::ReturnSkillIconeTexture()
{
	return texture_icone_skill;
}

float SkillReplenishingWater::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0,class_player,NoRune_E);
	return cooldown_skill;
}

int SkillReplenishingWater::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillReplenishingWater::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillReplenishingWater::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 7 - 0.25 * (skill_level - 1);
	duration_projectile = 10 + 2 * (skill_level - 1);
	duration_recovery_bonus = 5;
	duration_movement_speed_bonus = 0.75 + 0.2 * (skill_level - 1);
	recovery_value = 1.5 + 0.25 * (skill_level - 1);
	movement_speed_bonus_value = 25 + 5 * (skill_level - 1);
	range_projectile = 300 + 50 * (skill_level - 1);

	if (current_rune == FirstRune_E)
	{
		duration_movement_speed_bonus += 0.6;
	}
	else if (current_rune == SecondRune_E)
	{
		recovery_value += 1;
		movement_speed_bonus_value += 13;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Replenishing Water pack";
		string_skill_information[1] = "Drop a pack containing a replenishing water. It gives to the first ally that steps on it 1.5% (+0.2% per level) of his maximum health per second for 5 seconds and 25% (+5% per level) movement speed for 0.75 (+0.25 per level) seconds. The pack lasts for 10 (+2 per level) seconds.";
	}
	else
	{
		string_skill_information[0] = "Pack d'eau de vie";
		string_skill_information[1] = "Laisse tomber un pack contenant de l'eau de vie. Il soigne le premier joueur qui le touche de 1.5% (+0.2% par niveau) de sa vie totale par seconde pendant 5 secondes et augmente sa vitesse de déplacement de 25% (+5% par niveau) pendant 0.75 (+0.25 par niveau) secondes. Le pack dure 10 (+2 par niveau) secondes.";
	}
}

void SkillReplenishingWater::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0,class_player, current_rune);
	sf::RectangleShape rectangle;
	sf::RectangleShape rectangle1;

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

	if (current_rune == ThirdRune_E)
	{
		rectangle1.setPosition(position_caster);
		rectangle1.setSize(sf::Vector2f(size_projectile.x, size_projectile.y));
		rectangle1.setFillColor(sf::Color::Color(173, 216, 230, 50));
		rectangle1.setOrigin(sf::Vector2f(size_projectile.x / 2, size_projectile.y / 2));
		DrawGestion::instance()->AddRectangleToList(rectangle1);
	}
}

sf::String SkillReplenishingWater::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +0.6 second to the duration of the movement speed bonus.");

		case SecondRune_E:
			return sf::String("Add +1% to the recovery bonus and +13% to the movement speed bonus.");

		case ThirdRune_E:
			return sf::String("Spawn an other pack at the player's position with 25% effectiveness.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +0.6 second à la durée du bonus de vitesse de déplacement.");

		case SecondRune_E:
			return sf::String("Ajoute +1% au bonus de regénération et +13% au bonus de vitesse de déplacement.");

		case ThirdRune_E:
			return sf::String("Fait apparaître un second pack où se situe le joueur avec 25% des effets.");
		}
	}
}

