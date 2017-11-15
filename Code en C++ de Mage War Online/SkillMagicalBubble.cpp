#include "stdafx.h"
#include "SkillMagicalBubble.h"

SkillMagicalBubble::SkillMagicalBubble(int current_language)
{
	language = current_language;
	if (!texture_icone_skill_triple_fireball.loadFromFile("Skill_magical_bubble_icone.png"))
	{
		std::cout << "Texture of magical bubble icone didn't load correctly" << std::endl;
	}
}

SkillMagicalBubble::~SkillMagicalBubble()
{
}

void SkillMagicalBubble::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	std::shared_ptr<Bubble>  Bubble1 = std::shared_ptr<Bubble>(new Bubble());
	Bubble1->Texture_loading();
	Bubble1->InitFromSkill(position_player, damage_projectile*damage_modifier, mouse_position, stun_duration, player, range_modifier, speed_modifier);
	Bubble1->Initialized(player_id);

	std::shared_ptr<Bubble>  Bubble2 = std::shared_ptr<Bubble>(new Bubble());
	Bubble2->Texture_loading();
	Bubble2->Initialized(player_id);
	Bubble2->InitFromSkill(position_player, damage_projectile*damage_modifier, mouse_position, stun_duration, player, range_modifier, speed_modifier);
	Bubble2->ChangeProjectileRotation(90);

	std::shared_ptr<Bubble>  Bubble3 = std::shared_ptr<Bubble>(new Bubble());
	Bubble3->Texture_loading();
	Bubble3->Initialized(player_id);
	Bubble3->InitFromSkill(position_player, damage_projectile*damage_modifier, mouse_position, stun_duration, player, range_modifier, speed_modifier);
	Bubble3->ChangeProjectileRotation(-90);

	std::shared_ptr<Bubble>  Bubble4 = std::shared_ptr<Bubble>(new Bubble());
	Bubble4->Texture_loading();
	Bubble4->Initialized(player_id);
	Bubble4->InitFromSkill(position_player, damage_projectile*damage_modifier, mouse_position, stun_duration, player, range_modifier, speed_modifier);
	Bubble4->ChangeProjectileRotation(180); 

	ProjectileGestion::instance()->AddObjectToList(Bubble1);
	ProjectileGestion::instance()->AddObjectToList(Bubble2);
	ProjectileGestion::instance()->AddObjectToList(Bubble3);
	ProjectileGestion::instance()->AddObjectToList(Bubble4);
	Bubble1.reset();
	Bubble2.reset();
	Bubble3.reset();
	Bubble4.reset();
}

sf::Texture SkillMagicalBubble::ReturnSkillIconeTexture()
{
	return texture_icone_skill_triple_fireball;
}

float SkillMagicalBubble::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0,class_player,NoRune_E);
	return cooldown_skill_triple_fireball;
}

int SkillMagicalBubble::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillMagicalBubble::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillMagicalBubble::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill_triple_fireball = 6 - 0.35*(skill_level - 1);
	damage_percent = 85 + 7*(skill_level - 1);
	stun_duration = 1 + 0.25 * (skill_level - 1);

	if (current_rune == FirstRune_E)
	{
		stun_duration += 0.4;
	}
	else if (current_rune == SecondRune_E)
	{
		damage_percent += 15;
	}
	else if (current_rune == ThirdRune_E)
	{
		damage_percent += 75;
		stun_duration = 0;
	}

	damage_projectile = player_damage*damage_percent / 100;

	if (language == English_E)
	{
		string_skill_information[0] = "Magical bubbles";
		string_skill_information[1] = "Throw bubbles in each 4 direction that deal 85% (+7% per level) damage on hit and stun the target for 1 (+0.25 per level) seconds.";
	}
	else
	{
		string_skill_information[0] = "Bulles magiques";
		string_skill_information[1] = "Lance des bulles dans les quatres directions qui font 85% (+7% per level) de dégâts à l'impact et assomme la cible touchée pendant 1 (+0.25 par niveau) secondes.";
	}
}

void SkillMagicalBubble::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0,class_player, current_rune);
	sf::RectangleShape rectangle;
	rectangle.setPosition(position_caster);
	rectangle.setSize(sf::Vector2f(range_projectile*range_modifier + size_projectile.x / 2, size_projectile.y));
	rectangle.setFillColor(sf::Color::Color(173, 216, 230, 50));
	rectangle.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
	rectangle.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster));
	DrawGestion::instance()->AddRectangleToList(rectangle);

	sf::RectangleShape rectangle2;
	rectangle2.setPosition(position_caster);
	rectangle2.setSize(sf::Vector2f(range_projectile*range_modifier + size_projectile.x / 2, size_projectile.y));
	rectangle2.setFillColor(sf::Color::Color(173, 216, 230, 50));
	rectangle2.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
	rectangle2.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster) + 90);
	DrawGestion::instance()->AddRectangleToList(rectangle2);

	sf::RectangleShape rectangle3;
	rectangle3.setPosition(position_caster);
	rectangle3.setSize(sf::Vector2f(range_projectile*range_modifier + size_projectile.x / 2, size_projectile.y));
	rectangle3.setFillColor(sf::Color::Color(173, 216, 230, 50));
	rectangle3.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
	rectangle3.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster) - 90);
	DrawGestion::instance()->AddRectangleToList(rectangle3);

	sf::RectangleShape rectangle4;
	rectangle4.setPosition(position_caster);
	rectangle4.setSize(sf::Vector2f(range_projectile*range_modifier + size_projectile.x / 2, size_projectile.y));
	rectangle4.setFillColor(sf::Color::Color(173, 216, 230, 50));
	rectangle4.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
	rectangle4.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster) + 180);
	DrawGestion::instance()->AddRectangleToList(rectangle4);
}

sf::String SkillMagicalBubble::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +0.4 second to the stun duration.");

		case SecondRune_E:
			return sf::String("Add +15% to the damage percent of the skill.");

		case ThirdRune_E:
			return sf::String("Change the composition of the bubbles, adding +75% to the damage percent of the skill, but removing the stun effect.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +0.4 seconde à la durée de l'étourdissement.");

		case SecondRune_E:
			return sf::String("Ajoute +15% au pourcentage de dégâts du sort.");

		case ThirdRune_E:
			return sf::String("Change la composition des bulles, ajoutant +75% au pourcentage de dégâts du sort, mais enlève l'effet d'étourdissement");
		}
	}
}

