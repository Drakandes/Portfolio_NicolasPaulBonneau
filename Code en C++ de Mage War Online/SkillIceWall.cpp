#include "stdafx.h"
#include "SkillIceWall.h"

SkillIceWall::SkillIceWall(int current_language)
{
	language = current_language;
	if (!texture_icone_skill.loadFromFile("SkillIceBlock.png"))
	{
		std::cout << "Couldn't load ice wall icone" << std::endl;
	}

	string_skill_information[0] = "Ice Wall";
	string_skill_information[1] = "Create an ice wall that blocks a certain area and last for ";
	string_skill_information[1] = "that steps on it ";
	string_skill_information[1] = GlobalFunction::InsertNumberToString(string_skill_information[1], duration_projectile, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), "seconds.");
}

SkillIceWall::~SkillIceWall()
{
}

void SkillIceWall::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received,player_damage, player->GetCurrentClassPlayer(), current_rune);
	float range_modifier = player->GetProjectileRangeBonus() / 100 + 1;

	sf::Vector2f position_projectile = mouse_position;
	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_player, mouse_position) > range_projectile*range_modifier)
	{
		float rotation = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_player);
		sf::Vector2f position_to_add =sf::Vector2f((cos(rotation * PI / 180))*range_projectile*range_modifier, (sin(rotation * PI / 180))*range_projectile*range_modifier);
		position_projectile = position_player + position_to_add;
	}

	std::shared_ptr<IceBlock>  projectile = std::shared_ptr<IceBlock>(new IceBlock());
	projectile->Initialized(player_id);
	projectile->Init(position_projectile, duration_projectile,distance_propulsion_when_colliding);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	projectile.reset();

	SoundGestion::instance()->AddSound("SoundIceWall.wav", 100, false);

	if (current_rune == ThirdRune_E)
	{
		player->GivePlayerChangeStat(MovementSpeedPercent, duration_projectile, 5);
	}
	else if (current_rune == SecondRune_E)
	{
		sf::RectangleShape rectangle1;

		float angle = GlobalFunction::GetRotationBetweenTwoPositions(position_player, mouse_position) ;
		float distance = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_projectile);

		sf::Vector2f position_second_projectile = sf::Vector2f((cos(angle * PI / 180))*distance, (sin(angle * PI / 180))*distance) + position_player;

		std::shared_ptr<IceBlock>  projectile1 = std::shared_ptr<IceBlock>(new IceBlock());
		projectile1->Initialized(player_id);
		projectile1->Init(position_second_projectile, duration_projectile, distance_propulsion_when_colliding);
		ProjectileGestion::instance()->AddObjectToList(projectile1);
		projectile1.reset();

		SoundGestion::instance()->AddSound("SoundIceWall.wav", 100, false);
	}
}

sf::Texture SkillIceWall::ReturnSkillIconeTexture()
{
	return texture_icone_skill;
}

float SkillIceWall::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0,class_player,NoRune_E);
	return cooldown_skill;
}

int SkillIceWall::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillIceWall::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillIceWall::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_skill = 16 - 0.45 * (skill_level - 1);
	duration_projectile = 6 + 1 * (skill_level - 1);
	range_projectile = 250 + 25 * (skill_level - 1);

	if (current_rune == FirstRune_E)
	{
		range_projectile += range_projectile*0.3;
	}
	
	if (language == English_E)
	{
		string_skill_information[0] = "Ice Wall";
		string_skill_information[1] = "Create an ice wall that blocks a certain area and last for 6 (+1 per level) seconds. Nobody can go through the wall.";
	}
	else
	{
		string_skill_information[0] = "Mur de Glace";
		string_skill_information[1] = "Crée un mur de glace qui bloque une certaine zone et dure 6 (+1 par niveau) secondes. Aucune entité peut passer au travers.";
	}
}

void SkillIceWall::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0,class_player, current_rune);
	sf::RectangleShape rectangle;

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
	rectangle.setOrigin(sf::Vector2f(size_projectile.x/2, size_projectile.y / 2));
	DrawGestion::instance()->AddRectangleToList(rectangle);

	if (current_rune == SecondRune_E)
	{
		sf::RectangleShape rectangle1;

		float angle = GlobalFunction::GetRotationBetweenTwoPositions(position_caster, mouse_position);
		float distance = GlobalFunction::GetDistanceBetweenTwoPositions(position_caster, position_projectile);

		sf::Vector2f position_second_projectile = sf::Vector2f(sf::Vector2f((cos(angle * PI / 180))*distance, (sin(angle * PI / 180))*distance)) + position_caster;

		rectangle1.setPosition(position_second_projectile);
		rectangle1.setSize(sf::Vector2f(size_projectile.x, size_projectile.y));
		rectangle1.setFillColor(sf::Color::Color(173, 216, 230, 50));
		rectangle1.setOrigin(sf::Vector2f(size_projectile.x / 2, size_projectile.y / 2));
		DrawGestion::instance()->AddRectangleToList(rectangle1);
	}
}

sf::String SkillIceWall::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Increase the range by 30%.");

		case SecondRune_E:
			return sf::String("Spawn a second wall in the opposite direction.");

		case ThirdRune_E:
			return sf::String("Increase the movement speed by 5% for the duration.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Augmente la porté de 30%.");

		case SecondRune_E:
			return sf::String("Fait apparaître un second mur de glace dans la direction opposée.");

		case ThirdRune_E:
			return sf::String("Augmente la vitesse de déplacement de 5% pendant toute la durée.");
		}
	}
}



