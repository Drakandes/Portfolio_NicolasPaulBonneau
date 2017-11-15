#include "stdafx.h"
#include "SkillRestrainingLeafBlade.h"

SkillRestrainingLeafBlade::SkillRestrainingLeafBlade(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("Skill_leafblade_icone.png"))
	{
		std::cout << "Error while loading SkillRestrainingLeafBlade icone texture" << std::endl;
	}
	string_skill_information[0] = "Restraining Leaf blade";
	string_skill_information[1].clear();
	string_skill_information[1] = "Throw a leaf blade that does ";
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], damage_percent, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), "% damage and reduce the target movement speed by ");
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], slow_applied, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), "% for ");
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], duration_reduction, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), " seconds.");
}

SkillRestrainingLeafBlade::~SkillRestrainingLeafBlade()
{
}

void SkillRestrainingLeafBlade::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;

	std::shared_ptr<LeafBlade>  projectile = std::shared_ptr<LeafBlade>(new LeafBlade());
	projectile->Initialized(player_id);
	projectile->Init(position_player, mouse_position, damage_projectile*damage_modifier, speed_projectile*speed_modifier,range_projectile*range_modifier,duration_reduction,slow_applied, player);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();
}

sf::Texture SkillRestrainingLeafBlade::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillRestrainingLeafBlade::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0,class_player,NoRune_E);
	return cooldown_skill;
}

int SkillRestrainingLeafBlade::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillRestrainingLeafBlade::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillRestrainingLeafBlade::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 15 - 0.5 * (skill_level - 1);
	damage_percent = 125 + 12.5 * (skill_level - 1);
	range_projectile = 250 + 25 * (skill_level - 1);
	slow_applied = 14 + 3.5 * (skill_level - 1);

	if (current_rune == FirstRune_E)
	{
		slow_applied += 7;
	}
	else if (current_rune == SecondRune_E)
	{
		damage_percent += 3 * (skill_level - 1);
	}
	else if (current_rune == ThirdRune_E)
	{
		range_projectile += range_projectile*0.3;
	}

	damage_projectile = player_damage*damage_percent / 100;

	if (language == English_E)
	{
		string_skill_information[0] = "Restraining Leaf blade";
		string_skill_information[1] = "Throw a leaf blade that does 125% (+12.5% per level) damage on hit and reduce the target's movement speed by 14% (+3.5% per level) for 2 (+0.5 per level) seconds. If it hits a target, the cooldown is greatly reduce.";
	}
	else
	{
		string_skill_information[0] = "Lame de feuilles entravente";
		string_skill_information[1] = "Lance une lame de feuilles qui fait 125% (+12.5% par niveau) de dégâts à l'impact et réduit la vitesse de déplacement de la cible touchée de 14% (+3.5% par niveau) pendant 2 (+0.5 par niveau) secondes. Si le sort touche une cible, la temps de latence est grandement réduit.";
	}
}

void SkillRestrainingLeafBlade::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
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

sf::String SkillRestrainingLeafBlade::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +7% to the slow effect.");

		case SecondRune_E:
			return sf::String("Add +3% per skill level to the damage percent of the skill.");

		case ThirdRune_E:
			return sf::String("The blade is aerodynamic, increasing his range by 30%.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +12% à l'effet de ralentissement.");

		case SecondRune_E:
			return sf::String("Ajoute +3% par niveau de sort au pourcentage de dégâts du sort.");

		case ThirdRune_E:
			return sf::String("La lame est aérodynamique, augmentant sa porté de 30%.");
		}
	}
}

