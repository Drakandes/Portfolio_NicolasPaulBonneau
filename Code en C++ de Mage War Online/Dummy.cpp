#include "stdafx.h"
#include "Dummy.h"

Dummy::Dummy()
{
	if (!texture.loadFromFile("Dummy.png"))
	{
		std::cout << "Error while loading dummy texture" << std::endl;
	}
	if (!texture_ignition.loadFromFile("Burning_animation.png"))
	{
		std::cout << "Error: Couldn't load Burning_animation in sentry" << std::endl;
	}

	if (!shadow_texture.loadFromFile("DummyShadow.png"))
	{
		std::cout << "Error while loading dummy projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), size_monster, shadow_texture);
	shadow.setOrigin(sf::Vector2f(size_monster.x / 2, 0));
}

Dummy::~Dummy()
{
}

void Dummy::Init(int id_received, sf::Vector2f position_spawn_r, int id_spawn_r, float size_spawn_r, int level_monster_r, sf::Vector2f position_monster)
{
	position_of_spawn = position_spawn_r;
	id_spawn = id_spawn_r;
	size_spawn = size_spawn_r;

	sprite_monster = GlobalFunction::CreateSprite(position_monster, size_monster, texture);
	rect_collision = GlobalFunction::CreateRectangleWithOrigin(size_monster, sf::Vector2f(1000, 200), sf::Color::Blue);
	id_monster = id_received;
	sprite_ignition = GlobalFunction::CreateSprite(sprite_monster.getPosition(), size_sprite_ignition, texture_ignition);

	font.loadFromFile("Constantine.ttf");
	string_monster_name = "";
	string_monster_name = GlobalFunction::InsertNumberToString(string_monster_name, 1, string_monster_name.getSize());
	string_monster_name.insert(string_monster_name.getSize(), sf::String("   Dummy"));
	text_monster_name = GlobalFunction::CreateText(sf::Vector2f(0, 0), string_monster_name, font, 13);
	text_monster_name.setStyle(sf::Text::Bold);
}

sf::Vector2f Dummy::GetCurrentPosition()
{
	return sprite_monster.getPosition();
}

void Dummy::Update(sf::Vector2f player_postion, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player)
{
	Health_maintenance();
	MoveTexts();
	damage_received += DamageFromAllIgnition();
	CheckIfIgnited();

	sf::Vector2f monster_position = GetCurrentPosition();
	text_monster_name.setPosition(sf::Vector2f(monster_position.x, monster_position.y - size_monster.y / 2 - 20));
}

void Dummy::Health_maintenance()
{
	if (clock_dps.getElapsedTime().asSeconds() >= 3)
	{
		if (damage_received > 0)
		{
			clock_dps.restart();
			std::shared_ptr<Text> text = std::shared_ptr<Text>(new Text());
			sf::String str = "DPS : ";
			str = GlobalFunction::InsertNumberToString(str, damage_received / 3, str.getSize());
			text->Init(GetCurrentPosition(), str, size_monster, shared_from_this());
			text->ChangeTextColor(sf::Color::Yellow);
			listText.push_back(text);
			text.reset();
			damage_received = 0;
		}
	}
}

float Dummy::GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent)
{
	if (damage_dealt > 0)
	{
		damage_received += damage_dealt;
	}
	return damage_dealt;
}

int Dummy::GetRayon()
{
	return rayon_of_collision;
}

sf::Vector2f Dummy::GetSize()
{
	return size_monster;
}

bool Dummy::IsNeedToDelete()
{
	return !monster_alive;
}

sf::String Dummy::GetMonsterType()
{
	return "Dummy";
}

int Dummy::GetId()
{
	return id_monster;
}

void Dummy::FirstDraw(sf::RenderWindow &window)
{

}

void Dummy::GetIgnited(int type_ignition, float duration_ignition, float damage_ignition)
{
	bool can_add_ignition = true;
	if (type_ignition == OnFireFromPassive || type_ignition == OnFireFromLavaFloor)
	{
		std::list<int>::iterator iterator_type = TypeIgnition.begin();
		std::list<sf::Clock>::iterator iterator_clock = ClockIgnition.begin();
		while (iterator_type != TypeIgnition.end())
		{
			if ((*iterator_type) == OnFireFromPassive || (*iterator_type) == OnFireFromLavaFloor)
			{

				(*iterator_clock).restart();
				can_add_ignition = false;
				break;
			}
			iterator_type++;
			iterator_clock++;
		}
	}
	if (can_add_ignition)
	{
		TypeIgnition.push_back(type_ignition);
		DurationIgnition.push_back(duration_ignition);
		DamageIgnition.push_back(damage_ignition);
		sf::Clock clock_;
		ClockIgnition.push_back(clock_);
		number_ignition++;
	}
}

float Dummy::DamageFromAllIgnition()
{
	float damage_from_all_ignition = 0;

	if (clock_damage_from_all_inition.getElapsedTime().asSeconds() >= 0.5)
	{
		std::list<int>::iterator iterator_type = TypeIgnition.begin();
		std::list<float>::iterator iterator_duration = DurationIgnition.begin();
		std::list<float>::iterator iterator_damage = DamageIgnition.begin();
		std::list<sf::Clock>::iterator iterator_clock = ClockIgnition.begin();
		while (iterator_duration != DurationIgnition.end())
		{
			if ((*iterator_clock).getElapsedTime().asSeconds() <= (*iterator_duration))
			{
				damage_from_all_ignition += (*iterator_damage) / 2;
				iterator_duration++;
				iterator_type++;
				iterator_damage++;
				iterator_clock++;
			}
			else
			{
				DurationIgnition.erase(iterator_duration++);
				TypeIgnition.erase(iterator_type++);
				DamageIgnition.erase(iterator_damage++);
				ClockIgnition.erase(iterator_clock++);
				number_ignition--;
			}
		}
		clock_damage_from_all_inition.restart();
	}

	TextGenerator::instance()->GenerateOneTextForBlob(GetCurrentPosition(), damage_from_all_ignition, GetSize(), shared_from_this());

	return damage_from_all_ignition;
}

void Dummy::CheckIfIgnited()
{
	if (number_ignition > 0)
	{
		is_ignite = true;
		IgnitionAnimationGestion();
	}
	else
	{
		is_ignite = false;
	}
}

void Dummy::IgnitionAnimationGestion()
{
	if (clock_ignition_animation.getElapsedTime().asSeconds() >= 0.1)
	{
		sprite_ignition.setPosition(sprite_monster.getPosition());
		sprite_ignition.setTextureRect(sf::IntRect(size_sprite_ignition.x*holder_cutting_ignition_texture.x, size_sprite_ignition.y*holder_cutting_ignition_texture.y, size_sprite_ignition.x, size_sprite_ignition.y));
		holder_cutting_ignition_texture.x++;
		if (holder_cutting_ignition_texture.x >= dimension_texture_ignition.x)
		{
			holder_cutting_ignition_texture.x = 0;
			holder_cutting_ignition_texture.y++;
			if (holder_cutting_ignition_texture.y >= dimension_texture_ignition.y)
			{
				holder_cutting_ignition_texture.y = 0;
			}
		}
		clock_ignition_animation.restart();
	}
}

void Dummy::Draw(sf::RenderWindow &window)
{
	shadow.setPosition(sprite_monster.getPosition() + sf::Vector2f(0, size_monster.y / 2));
	window.draw(shadow);

	window.draw(sprite_monster);
	window.draw(text_monster_name);
	if (is_ignite)
	{
		window.draw(sprite_ignition);
	}
	std::list<std::shared_ptr<Text>>::iterator i = listText.begin();
	while (i != listText.end())
	{
		(*i)->Draw_text(window);
		i++;
	}
}

void Dummy::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(sprite_monster.getPosition() + sf::Vector2f(0, size_monster.y / 2));
	window.draw(shadow);
}

sf::Vector2f Dummy::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

void Dummy::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Dummy::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

void Dummy::MoveTexts()
{
	std::list<std::shared_ptr<Text>>::iterator i = listText.begin();
	while (i != listText.end())
	{
		(*i)->MoveText();
		if ((*i)->IsNeedToDelete())
		{
			listText.erase(i++);
		}
		else
		{
			i++;
		}
	}
}
