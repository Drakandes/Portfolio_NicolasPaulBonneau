#include "stdafx.h"
#include "SkillLeafZoneBoost.h"

SkillLeafZoneBoost::SkillLeafZoneBoost(int current_language)
{
	language = current_language;
	if (!texture_icone_skill.loadFromFile("Skill_leaf_zone_icone.png"))
	{
		std::cout << "Couldn't load leafzoneboost icone" << std::endl;
	}

	string_skill_information[0] = "LeafGuard zone";
	string_skill_information[1] = "Transform an aera into a leaf zone that gives player ";
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], health_percent_boost, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), "% of bonus health and ");
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], defense_boost, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), "% of bonus armor while he stands on it.");
}

SkillLeafZoneBoost::~SkillLeafZoneBoost()
{
}

void SkillLeafZoneBoost::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(), current_rune);

	std::shared_ptr<LeafZone>  leaf_zone = std::shared_ptr<LeafZone>(new LeafZone());
	leaf_zone->Initialized(player_id);
	leaf_zone->Init(position_player, duration_area, defense_boost, health_percent_boost, duration_boost, current_rune);
	ProjectileGestion::instance()->AddObjectToList(leaf_zone);
	leaf_zone.reset();

	SoundGestion::instance()->AddSound("SoundZoneLeaf.wav", 75, false);
}

sf::Texture SkillLeafZoneBoost::ReturnSkillIconeTexture()
{
	return texture_icone_skill;
}

float SkillLeafZoneBoost::GetSkillCooldown(int skill_level, int class_player)
{
	return cooldown_skill;
}

int SkillLeafZoneBoost::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillLeafZoneBoost::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillLeafZoneBoost::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 14 - 0.2 * (skill_level - 1);
	duration_area = 8 + 1 * (skill_level - 1);
	defense_boost = 25 + 3.5 * (skill_level - 1);
	health_percent_boost = 30 + 5 * (skill_level - 1);

	if (current_rune == FirstRune_E)
	{
		defense_boost += 6;
		health_percent_boost += 12;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Natural zone";
		string_skill_information[1] = "Transform the ground in a certain aera into leaves. Any ally standing in that zone will have his maximum health increase by 30% (+5% per level) and his armor increase by 25% (+3.5% per level). The zone last for 8 (+1 per level) seconds.";
	}
	else
	{
		string_skill_information[0] = "Zone Naturelle";
		string_skill_information[1] = "Transforme le sol à un certain endroit en feuilles. Tous les joueurs dans la zone ont un bonus de 30% (+5% par niveau) à leur vie totale et un bonus de 25% (+3.5% par niveau) à leur armure. La zone dure 8 (+1 par niveau) secondes.";
	}
}

void SkillLeafZoneBoost::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0,class_player,NoRune_E);
	sf::CircleShape circle;
	circle.setPosition(position_caster);
	circle.setRadius(radius);
	circle.setFillColor(sf::Color::Color(173, 216, 230, 50));
	circle.setOrigin(sf::Vector2f(radius, radius));
	DrawGestion::instance()->AddCircleToList(circle);
}

sf::String SkillLeafZoneBoost::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +6% to the armor bonus and +12% to the maximum health bonus.");

		case SecondRune_E:
			return sf::String("It is easier for the player to move on this ground, granting the player +10% movement speed while he walks on it.");

		case ThirdRune_E:
			return sf::String("The sanctuary also fully fill the shield of the player. ");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +6% au bonus d'armure et +12% au bonus à la vie totale.");

		case SecondRune_E:
			return sf::String("Il est plus facile pour le joueur de se déplacer sur ce sol, octroyant au joueur +10 de vitesse de déplacement tant qu'il est dessus.");

		case ThirdRune_E:
			return sf::String("Le sanctuaire remplit aussi complètement le bouclier du joueur.");
		}
	}
}
