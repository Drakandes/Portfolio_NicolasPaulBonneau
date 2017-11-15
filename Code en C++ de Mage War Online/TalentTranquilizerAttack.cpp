#include "stdafx.h"
#include "TalentTranquilizerAttack.h"


TalentTranquilizerAttack::TalentTranquilizerAttack(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Tranquilizer Attack";
		string_information[1] = "Add the chilled effect to your basic attacks. When your basic attacks hit ennemies, they slow them by up to 9% (3% per level) for 1.5 seconds. The chilled debuff doesn't stack.";
	}
	else
	{
		string_information[0] = "Attaque Tranquilisante";
		string_information[1] = "Ajoute un effet de glace à vos attaques de base. Lorsque celles-ci touchent un ennemi, elles le ralentissent jusqu'à 9% (3% par niveau) pendant 1.5 seconds. L'effet de glace ne se cumule pas.";
	}
}


TalentTranquilizerAttack::~TalentTranquilizerAttack()
{
}

float TalentTranquilizerAttack::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentTranquilizerAttack::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentTranquilizerAttack::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}