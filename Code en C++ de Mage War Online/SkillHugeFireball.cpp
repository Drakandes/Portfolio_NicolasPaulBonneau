#include "stdafx.h"
#include "SkillHugeFireball.h"

SkillHugeFireball::SkillHugeFireball(int current_language)
{
	language = current_language;
	if (!texture_icone_skill_huge_fireball.loadFromFile("Huge_fireball_icone.png"))
	{
		std::cout << "Texture of hugre fireball icone didn't load correctly" << std::endl;
	}
}

SkillHugeFireball::~SkillHugeFireball()
{
}

void SkillHugeFireball::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	if (current_rune == FirstRune_E)
	{
		float angle = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_player);
		std::shared_ptr<HugeFireball>  huge_fireball = std::shared_ptr<HugeFireball>(new HugeFireball());
		huge_fireball->Texture_loading();
		huge_fireball->Initialized(player_id);
		huge_fireball->Init(position_player, damage_projectile*damage_modifier, angle+5, speed_huge_fireball*speed_modifier, range_projectile*range_modifier, player, current_rune == ThirdRune_E ? 7 : 0);
		ProjectileGestion::instance()->AddObjectToList(huge_fireball);
		huge_fireball.reset();

		std::shared_ptr<HugeFireball>  huge_fireball1 = std::shared_ptr<HugeFireball>(new HugeFireball());
		huge_fireball1->Texture_loading();
		huge_fireball1->Initialized(player_id);
		huge_fireball1->Init(position_player, damage_projectile*damage_modifier, angle-5, speed_huge_fireball*speed_modifier, range_projectile*range_modifier, player, current_rune == ThirdRune_E ? 7 : 0);
		ProjectileGestion::instance()->AddObjectToList(huge_fireball1);
		huge_fireball1.reset();
	}
	else
	{
		float angle = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_player);
		std::shared_ptr<HugeFireball>  huge_fireball = std::shared_ptr<HugeFireball>(new HugeFireball());
		huge_fireball->Texture_loading();
		huge_fireball->Initialized(player_id);
		huge_fireball->Init(position_player, damage_projectile*damage_modifier, angle, speed_huge_fireball*speed_modifier, range_projectile*range_modifier, player, current_rune == ThirdRune_E ? 7 : 0);
		ProjectileGestion::instance()->AddObjectToList(huge_fireball);
		huge_fireball.reset();
	}

}

sf::Texture SkillHugeFireball::ReturnSkillIconeTexture()
{
	return texture_icone_skill_huge_fireball;
}

float SkillHugeFireball::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0,class_player, NoRune_E);
	return cooldown_skill_huge_fireball;
}

int SkillHugeFireball::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillHugeFireball::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillHugeFireball::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill_huge_fireball = 5 - 0.5 * (skill_level - 1);
	damage_multiplier = 2.05 + 0.175 * (skill_level - 1);
	speed_huge_fireball = 595 + 85 * (skill_level - 1);
	range_projectile = 700 + 50 * (skill_level - 1);
	damage_projectile = damage_multiplier*player_damage;

	if (current_rune == SecondRune_E)
	{
		damage_projectile += damage_projectile*1.35;
	}


	if (language == English_E)
	{
		string_skill_information[0] = "Huge Fireball";
		string_skill_information[1] = "Throw a fireball that deals 205% (+17.5% per level) damage any ennemy it goes through. The fireball is not deleted after hitting an ennemy.";
	}
	else
	{
		string_skill_information[0] = "Boule de feu géante";
		string_skill_information[1] = "Lance une énorme boule de feu qui fait 205% (+17.5% per level) de dégats à tous les ennemies qu'elle entre en collision avec. La boule de feu ne disparaît pas à l'impact et continue sa route.";
	}
}

void SkillHugeFireball::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0,class_player, current_rune);
	if (current_rune == FirstRune_E)
	{
		sf::RectangleShape rectangle;
		rectangle.setPosition(position_caster);
		rectangle.setSize(sf::Vector2f(range_projectile*range_modifier, size_projectile.y));
		rectangle.setFillColor(sf::Color::Color(173, 216, 230, 50));
		rectangle.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
		rectangle.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster)-5);
		DrawGestion::instance()->AddRectangleToList(rectangle);

		sf::RectangleShape rectangle1;
		rectangle1.setPosition(position_caster);
		rectangle1.setSize(sf::Vector2f(range_projectile*range_modifier, size_projectile.y));
		rectangle1.setFillColor(sf::Color::Color(173, 216, 230, 50));
		rectangle1.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
		rectangle1.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster) + 5);
		DrawGestion::instance()->AddRectangleToList(rectangle1);
	}
	else
	{
		sf::RectangleShape rectangle;
		rectangle.setPosition(position_caster);
		rectangle.setSize(sf::Vector2f(range_projectile*range_modifier, size_projectile.y));
		rectangle.setFillColor(sf::Color::Color(173, 216, 230, 50));
		rectangle.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
		rectangle.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster));
		DrawGestion::instance()->AddRectangleToList(rectangle);
	}
}

sf::String SkillHugeFireball::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Instead, cast 2 fireballs with 10 degree between them.");

		case SecondRune_E:
			return sf::String("Increase the damage by 135%.");

		case ThirdRune_E:
			return sf::String("Heal the player for 7% of the damage done with this skill.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("À la place, lance 2 boules de feu avec un angle de 10 degré entre elles.");

		case SecondRune_E:
			return sf::String("Augmente les dégâts de 135%.");

		case ThirdRune_E:
			return sf::String("Soigne le joueur de 7% des dégâts causés par ce sort.");
		}
	}
}

