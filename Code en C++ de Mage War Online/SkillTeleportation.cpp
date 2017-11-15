#include "stdafx.h"
#include "SkillTeleportation.h"

SkillTeleportation::SkillTeleportation(int current_language)
{
	language = current_language;
	if (!texture_icone_skill.loadFromFile("SkillTeleportation.png"))
	{
		std::cout << "Error while loading skill teleportation icone texture" << std::endl;
	}
	string_skill_information[0] = "Teleportation";
	string_skill_information[1] = "Teleport the player on a short distance toward his cursor.";
}

SkillTeleportation::~SkillTeleportation()
{
}

void SkillTeleportation::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level, 0, player->GetCurrentClassPlayer(), current_rune);

	sf::Vector2f position_projectile = mouse_position;
	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_player, mouse_position) > range_teleportation)
	{
		float rotation = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_player);
		sf::Vector2f position_to_add = sf::Vector2f(sf::Vector2f((cos(rotation * PI / 180))*range_teleportation, (sin(rotation * PI / 180))*range_teleportation));
		position_projectile = position_player + position_to_add;
	}

	player->TeleportEntity(position_projectile, Projectile_E);
	SoundGestion::instance()->AddSound("SoundTeleportation.wav", 100, false);

	if (current_rune == FirstRune_E)
	{
		player->GivePlayerChangeStat(DamagePercent, 2, 10);
	}
	else if (current_rune == SecondRune_E)
	{
		player->GivePlayerChangeStat(DefensePercent, 2, 15);
	}
	else if (current_rune == ThirdRune_E)
	{
		player->GivePlayerChangeStat(MovementSpeedPercent, 2, 7);
	}
}

sf::Texture SkillTeleportation::ReturnSkillIconeTexture()
{
	return texture_icone_skill;
}

float SkillTeleportation::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0,class_player, NoRune_E);
	return cooldown_skill;
}

int SkillTeleportation::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillTeleportation::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillTeleportation::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 0.75;// -1.5 * (skill_level - 1);
	if (cooldown_skill < 0)
	{
		cooldown_skill = 0;
	}
	range_teleportation = 175 + 25 * (skill_level - 1);

	if (language == English_E)
	{
		string_skill_information[0] = "Teleportation";
		string_skill_information[1] = "Teleport the player on a short distance toward his cursor.";
	}
	else
	{
		string_skill_information[0] = "Téléportation";
		string_skill_information[1] = "Téléporte le joueur sur une courte distance vers le curseur.";
	}
}

void SkillTeleportation::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0,class_player, current_rune);
	sf::CircleShape circle;
	sf::Vector2f position_projectile = mouse_position;
	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_caster, mouse_position) > range_teleportation)
	{
		float rotation = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster);
		sf::Vector2f position_to_add = sf::Vector2f(sf::Vector2f((cos(rotation * PI / 180))*range_teleportation, (sin(rotation * PI / 180))*range_teleportation));
		position_projectile = position_caster + position_to_add;
	}
	circle.setPosition(position_projectile);
	circle.setRadius(radius);
	circle.setFillColor(sf::Color::Color(173, 216, 230, 50));
	circle.setOrigin(sf::Vector2f(radius, radius));
	DrawGestion::instance()->AddCircleToList(circle);
}

sf::String SkillTeleportation::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Empower the player, granting him +10% damage for 2 seconds after the teleportation.");

		case SecondRune_E:
			return sf::String("Empower the player, granting him +10% armor for 2 seconds after the teleportation.");

		case ThirdRune_E:
			return sf::String("Empower the player, granting him +10% movement speed for 2 seconds after the teleportation.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Enchante le joueur, lui octroyant +10% de dégâts pendant 2 secondes après la téléportation.");

		case SecondRune_E:
			return sf::String("Enchante le joueur, lui octroyant +10% d'armure pendant 2 secondes après la téléportation.");

		case ThirdRune_E:
			return sf::String("Enchante le joueur, lui octroyant +10% de vitesse de déplacement pendant 2 secondes après la téléportation.");
		}
	}
}

