#include "stdafx.h"
#include "SkillTripleFireball.h"

SkillTripleFireball::SkillTripleFireball(int current_language)
{
	language = current_language;
	if (!texture_icone_skill_triple_fireball.loadFromFile("Triple_fireball_icone.png"))
	{
		std::cout << "Texture of hugre fireball icone didn't load correctly" << std::endl;
	}

	string_skill_information[0] = "Triple shot";
	string_skill_information[1] = "Fire three fireballs in a cone. Each fireball deals 115% (+7% per level) damage on hit.";
}

SkillTripleFireball::~SkillTripleFireball()
{
}

void SkillTripleFireball::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	ChangeSkillLevel(skill_level_received, player_damage, player->GetCurrentClassPlayer(),current_rune);
	float range_modifier = player->GetProjectileRangeBonus()/100 + 1;
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float damage_modifier = player->GetSkillDamageBonus() / 100 + 1;
	float damage_fireball = player_damage*damage_multiplier*damage_modifier;

	if (current_rune == FirstRune_E)
	{
		damage_fireball -= damage_fireball*0.25;
		for (int i = 0; i < 5; i++)
		{
			std::shared_ptr<Fireball>  fireball1 = std::shared_ptr<Fireball>(new Fireball());
			fireball1->Texture_loading();
			fireball1->Initialized(player_id);
			fireball1->ChangeFireballRotation(-30 + i * 10);
			fireball1->InitFromSkill(position_player, damage_fireball, fireball_range*range_modifier, fireball_speed, mouse_position, player, speed_modifier);
			ProjectileGestion::instance()->AddObjectToList(fireball1);
			fireball1.reset();

			SoundGestion::instance()->AddSound("SoundIgnite.wav", 25, false);
		}
	}
	else if (current_rune == SecondRune_E)
	{
		damage_fireball -= damage_fireball*0.4;
		for (int i = 0; i < 6; i++)
		{
			std::shared_ptr<Fireball>  fireball1 = std::shared_ptr<Fireball>(new Fireball());
			fireball1->Texture_loading();
			fireball1->Initialized(player_id);
			fireball1->ChangeFireballRotation(-50 + i * 20);
			fireball1->InitFromSkill(position_player, damage_fireball, fireball_range*range_modifier, fireball_speed, mouse_position, player, speed_modifier);
			ProjectileGestion::instance()->AddObjectToList(fireball1);
			fireball1.reset();

			SoundGestion::instance()->AddSound("SoundIgnite.wav", 25, false);
		}
	}
	else if(current_rune == ThirdRune_E)
	{
		for (int i = 0; i < 3; i++)
		{
			std::shared_ptr<Fireball>  fireball1 = std::shared_ptr<Fireball>(new Fireball());
			fireball1->Texture_loading();
			fireball1->Initialized(player_id);
			fireball1->ChangeFireballRotation(-5 + i * 5);
			fireball1->InitFromSkill(position_player, damage_fireball, fireball_range*range_modifier, fireball_speed, mouse_position, player, speed_modifier);
			ProjectileGestion::instance()->AddObjectToList(fireball1);
			fireball1.reset();

			SoundGestion::instance()->AddSound("SoundIgnite.wav", 25, false);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			std::shared_ptr<Fireball>  fireball1 = std::shared_ptr<Fireball>(new Fireball());
			fireball1->Texture_loading();
			fireball1->Initialized(player_id);
			fireball1->ChangeFireballRotation(-20 + i * 20);
			fireball1->InitFromSkill(position_player, damage_fireball, fireball_range*range_modifier, fireball_speed, mouse_position, player, speed_modifier);
			ProjectileGestion::instance()->AddObjectToList(fireball1);
			fireball1.reset();

			SoundGestion::instance()->AddSound("SoundIgnite.wav", 25, false);
		}
	}

}

sf::Texture SkillTripleFireball::ReturnSkillIconeTexture()
{
	return texture_icone_skill_triple_fireball;
}

float SkillTripleFireball::GetSkillCooldown(int skill_level, int class_player)
{
	ChangeSkillLevel(skill_level, 0,class_player,NoRune_E);
	return cooldown_skill_triple_fireball;
}

int SkillTripleFireball::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillTripleFireball::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillTripleFireball::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	number_fireball = 3;
	damage_multiplier = 1.15 + 0.03*(skill_level-1);
	cooldown_skill_triple_fireball = 4 - 0.25*(skill_level - 1);
	fireball_speed = 1.3 + 0.1*(skill_level - 1);
	fireball_range = 800 + 25 * (skill_level - 1);

	if (language == English_E)
	{
		string_skill_information[0] = "Triple Fireball";
		string_skill_information[1] = "Fire three fireballs in a cone. Each fireball deals 115% (+7% per level) damage on hit.";
	}
	else
	{
		string_skill_information[0] = "Triple boule de feu";
		string_skill_information[1] = "Projete trois boules de feu en cone. Chaque boule de feu fait 115% (+7% par niveau) de dégâts à l'impact.";
	}
}

void SkillTripleFireball::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
	ChangeSkillLevel(skill_level, 0,class_player, current_rune);

	if (current_rune == FirstRune_E)
	{
		for (int i = 0; i < 5; i++)
		{
			sf::RectangleShape rectangle2;
			rectangle2.setPosition(position_caster);
			rectangle2.setSize(sf::Vector2f(fireball_range*range_modifier + size_projectile.x / 2, size_projectile.y));
			rectangle2.setFillColor(sf::Color::Color(173, 216, 230, 50));
			rectangle2.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
			rectangle2.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster) - 30 + i * 10);
			DrawGestion::instance()->AddRectangleToList(rectangle2);
		}
	}
	else if (current_rune == SecondRune_E)
	{
		for (int i = 0; i < 6; i++)
		{
			sf::RectangleShape rectangle2;
			rectangle2.setPosition(position_caster);
			rectangle2.setSize(sf::Vector2f(fireball_range*range_modifier + size_projectile.x / 2, size_projectile.y));
			rectangle2.setFillColor(sf::Color::Color(173, 216, 230, 50));
			rectangle2.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
			rectangle2.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster) - 50 + 20*i);
			DrawGestion::instance()->AddRectangleToList(rectangle2);
		}
	}
	else if(current_rune == ThirdRune_E)
	{
		for (int i = 0; i < 3; i++)
		{
			sf::RectangleShape rectangle2;
			rectangle2.setPosition(position_caster);
			rectangle2.setSize(sf::Vector2f(fireball_range*range_modifier + size_projectile.x / 2, size_projectile.y));
			rectangle2.setFillColor(sf::Color::Color(173, 216, 230, 50));
			rectangle2.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
			rectangle2.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster) - 5 + i * 5);
			DrawGestion::instance()->AddRectangleToList(rectangle2);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			sf::RectangleShape rectangle2;
			rectangle2.setPosition(position_caster);
			rectangle2.setSize(sf::Vector2f(fireball_range*range_modifier + size_projectile.x / 2, size_projectile.y));
			rectangle2.setFillColor(sf::Color::Color(173, 216, 230, 50));
			rectangle2.setOrigin(sf::Vector2f(0, size_projectile.y / 2));
			rectangle2.setRotation(GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_caster) - 20 + i * 20);
			DrawGestion::instance()->AddRectangleToList(rectangle2);
		}
	}
}

sf::String SkillTripleFireball::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add 2 fireballs without changing the angle between the fireballs. Also reduce the damage dealt by each fireball by 25%.");

		case SecondRune_E:
			return sf::String("Add 4 fireballs, but increase the angle between the fireballs. Also reduce the damage dealt by each fireball by 40%.");

		case ThirdRune_E:
			return sf::String("Greatly reduce the angle between the fireballs.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute 2 boules de feu sans changer l'angle entre les boules de feu. Réduit aussi les dégâts de chaque boule de feu de 25%.");

		case SecondRune_E:
			return sf::String("Ajoute 4 boules de feu, mais change l'angle entre les boules de feu. Réduit aussi les dégâts de chaque boule de feu de 40%.");

		case ThirdRune_E:
			return sf::String("Réduis grandement l'angle entre les boules de feu.");
		}
	}
}
