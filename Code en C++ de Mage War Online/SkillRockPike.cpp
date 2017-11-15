#include "stdafx.h"
#include "SkillRockPike.h"

SkillRockPike::SkillRockPike(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("SkillRockPike.png"))
	{
		std::cout << "Error while loading SkillRockPike icone texture" << std::endl;
	}
}

SkillRockPike::~SkillRockPike()
{
}

void SkillRockPike::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	float angle_going = GlobalFunction::GetRotationBetweenTwoPositions(position_player, mouse_position);

	std::shared_ptr<RockPike>  projectile = std::shared_ptr<RockPike>(new RockPike());
	projectile->Init(position_player, damage_projectile*damage_modifier, angle_going,player_id, speed_projectile*speed_modifier,false,true,range_projectile*range_modifier, player);
	projectile->GiveStunEffect(stun_duration);
	if (current_rune == FirstRune_E)
	{
		projectile->CanPierce();
	}
	else if (current_rune == SecondRune_E)
	{
		projectile->GiveSlowEffect(stun_duration + 3, 20);
	}

	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();
}

sf::Texture SkillRockPike::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillRockPike::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0, class_player, NoRune_E);
	return cooldown_skill;
}

int SkillRockPike::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillRockPike::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillRockPike::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 8 - 0.35 * (skill_level - 1);
	speed_projectile = 350 + 30 * (skill_level - 1);
	range_projectile = 350 + 30 * (skill_level - 1);
	damage_percent = 0;
	stun_duration = 3 + 0.25*(skill_level - 1);

	if (current_rune == ThirdRune_E)
	{
		damage_percent = 250;
		stun_duration = stun_duration / 2;
	}

	damage_projectile = player_damage*damage_percent / 100;

	if (language == English_E)
	{
		string_skill_information[0] = "Rock Pike";
		string_skill_information[1] = "Throw a rock pike that stuns the first target hit for 3 (+0.25 per level) seconds.";
	}
	else
	{
		string_skill_information[0] = "Pique de Roche";
		string_skill_information[1] = "Lance un pique de roche qui étourdit la première cible touchée pendant 3 (+0.25 par niveau) secondes.";
	}
}

void SkillRockPike::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0, class_player, current_rune);
	sf::RectangleShape rectangle;
	rectangle.setPosition(position_caster);
	rectangle.setSize(sf::Vector2f(range_projectile*range_modifier + size_projectile.x / 2, size_projectile.y));
	rectangle.setFillColor(sf::Color::Color(173, 216, 230, 50));
	rectangle.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
	rectangle.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster));
	DrawGestion::instance()->AddRectangleToList(rectangle);
}

sf::String SkillRockPike::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("The pike can pierce one more target.");

		case SecondRune_E:
			return sf::String("The pike also slows the target by 20% for 3 seconds after the stun.");

		case ThirdRune_E:
			return sf::String("The pike now deals 250% damage, but reduce the stun effect by 50%.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Le pique peut transpercer une cible supplémentaire.");

		case SecondRune_E:
			return sf::String("Le pique ralentit aussi la cible de 20% pendant 3 secondes après l'effet d'étourdissement.");

		case ThirdRune_E:
			return sf::String("Le pique fait maintenant 250% de dégâts, mais l'effet d'étourdissement est réduit de 50%.");
		}
	}
}