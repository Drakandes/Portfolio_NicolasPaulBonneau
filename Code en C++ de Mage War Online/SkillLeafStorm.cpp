#include "stdafx.h"
#include "SkillLeafStorm.h"

SkillLeafStorm::SkillLeafStorm(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("Skill_leaf_storm_icone.png"))
	{
		std::cout << "Error while loading SkillLeafStorm icone texture" << std::endl;
	}
}

SkillLeafStorm::~SkillLeafStorm()
{
}

void SkillLeafStorm::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	float rotation_initial = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_player);
	for (int number = 0; number < number_of_projectile; number++)
	{
		std::shared_ptr<Leaf>  projectile = std::shared_ptr<Leaf>(new Leaf());
		projectile->Initialized(player_id, rotation_initial - 360 / number_of_projectile * (number + 1));
		projectile->Init(position_player, damage_projectile*damage_modifier, speed_projectile*speed_modifier, range_projectile, duration_projectile, player);
		ProjectileGestion::instance()->AddObjectToList(projectile);
		projectile.reset();
	}
}

sf::Texture SkillLeafStorm::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillLeafStorm::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0,class_player,NoRune_E);
	return cooldown_skill;
}

int SkillLeafStorm::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillLeafStorm::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillLeafStorm::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 12 - 0.45 * (skill_level - 1);
	speed_projectile = 2 + 0.5 * (skill_level - 1);
	damage_percent_projectile = 125 + 15* (skill_level - 1);
	duration_projectile = 6 + 1 * (skill_level - 1);
	number_of_projectile = 3 + 1 * (skill_level - 1);
	range_projectile = 100 - 10 * (skill_level - 1);
	if (range_projectile < 50)
	{
		range_projectile = 50;
	}

	if (current_rune == FirstRune_E)
	{
		number_of_projectile += 2;
	}
	else if (current_rune == SecondRune_E)
	{
		speed_projectile += speed_projectile*0.25;
	}
	else if (current_rune == ThirdRune_E)
	{
		damage_percent_projectile += 10;
	}

	damage_projectile = player_damage*damage_percent_projectile / 100;

	if (language == English_E)
	{
		string_skill_information[0] = "Leaf storm";
		string_skill_information[1] = "Generate 3 (+1 per level) leaves that circle around the player and deal 125% (+15% per level) damage on hit. They can also destroy any projectile that collides with them.";
	}
	else
	{
		string_skill_information[0] = "Tempête de feuilles";
		string_skill_information[1] = "Génère 3 (+1 par niveau) feuilles qui tournent autour du joueur et font 125% (+15% per level) de dégâts à l'impact. Les feuilles peuvent aussi détruire les projectiles qui entrent en collision avec eux.";
	}
}

void SkillLeafStorm::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0, class_player, current_rune);
	float rotation_initial = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster);

	for (int number = 0; number < number_of_projectile; number++)
	{
		sf::RectangleShape rectangle;

		float rotation_projectile = rotation_initial- 360 / number_of_projectile * (number + 1);
		sf::Vector2f position_rectangle = position_caster + sf::Vector2f((cos(rotation_projectile * PI / 180))*range_projectile*range_modifier, (sin(rotation_projectile * PI / 180))*range_projectile*range_modifier);
		rectangle.setPosition(position_rectangle);
		rectangle.setSize(sf::Vector2f(size_projectile.x, size_projectile.y));
		rectangle.setFillColor(sf::Color::Color(173, 216, 230, 50));
		rectangle.setOrigin(sf::Vector2f(size_projectile.x / 2, size_projectile.y / 2));
		DrawGestion::instance()->AddRectangleToList(rectangle);
	}
}

sf::String SkillLeafStorm::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("The storm is bigger than ever, adding +2 leaves.");

		case SecondRune_E:
			return sf::String("The storm is more powerful than ever, increasing the speed of the leaves by 25%.");

		case ThirdRune_E:
			return sf::String("Add +15% to the percent damage of the skill.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("La tempête est plus grosse que jamais, ajoutant +2 feuilles.");

		case SecondRune_E:
			return sf::String("La tempête est plus forte que jamais, augmentant la vitesse des feuilles de 25%.");

		case ThirdRune_E:
			return sf::String("Ajoute +15% au pourcentage de dégâts du sort.");
		}
	}
}

