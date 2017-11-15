#include "stdafx.h"
#include "SkillWoodSkin.h"

SkillWoodSkin::SkillWoodSkin(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("SkillWoodSkin.png"))
	{
		std::cout << "Error while loading skill wood skin icone texture" << std::endl;
	}
	string_skill_information[0] = "Wood skin (Passive skill)";
	string_skill_information[1] = "Increase the player defense by ";
	string_skill_information[1] = GlobalFunction::InsertNumberToStringIfFloat(string_skill_information[1], passive_value, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), "%.");
}

SkillWoodSkin::~SkillWoodSkin()
{
}

void SkillWoodSkin::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{

}

sf::Texture SkillWoodSkin::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillWoodSkin::GetSkillCooldown(int skill_level, int class_player)
{
	return 0;
}

int SkillWoodSkin::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillWoodSkin::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillWoodSkin::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	passive_value = 10 + 2.5*(skill_level-1);

	if (current_rune == FirstRune_E)
	{
		passive_value += 4;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Wood skin (Passive skill)";
		string_skill_information[1] = "Increase the player armor by 10% (+2.5% per level).";
	}
	else
	{
		string_skill_information[0] = "Peau de bois (Sort passif)";
		string_skill_information[1] = "Augmente l'armure du joueur de 10% (+2.5% par niveau).";
	}
}

int SkillWoodSkin::GetPassiveBonusType()
{
	return passive_type;
}

float SkillWoodSkin::GetPassiveBonusValue(int player_level, int class_player, int current_rune)
{
	ChangeSkillLevel(player_level, 0,class_player, current_rune);
	return passive_value;
}

sf::String SkillWoodSkin::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +4% to the armor bonus.");

		case SecondRune_E:
			return sf::String("The wood strengthen the body of the player, also increasing the maximum health by 5%.");

		case ThirdRune_E:
			return sf::String("Turns the skin into hardwood, applying the armor bonus on every other armor bonuses.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +4% au bonus d'armure.");

		case SecondRune_E:
			return sf::String("Le bois renforce le corps du joueur, augmentant aussi la vie totale de 5%.");

		case ThirdRune_E:
			return sf::String("Transforme la peau en bois dur, appliquant le bonus d'armure à tous les autres bonus d'armure.");
		}
	}
}
