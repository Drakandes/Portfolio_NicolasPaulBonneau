#include "stdafx.h"
#include "AttackDamageBox.h"

AttackDamageBox::AttackDamageBox()
{
	if (!texture_ablaze_the_fire_box.loadFromFile("AttackDamageBox.png"))
	{
		std::cout << "Couldn't load balze the fire box correctly" << std::endl;
	}
}

AttackDamageBox::~AttackDamageBox()
{
}

bool AttackDamageBox::GetInitStatus()
{
	return been_init;
}

void AttackDamageBox::Init(sf::Vector2f position_player, std::shared_ptr<Player> player, float duration_boost_received, float value_received)
{
	position_ablaze_the_fire_box = sf::Vector2f(35, -30);
	sf::Vector2f position_holder = sf::Vector2f(position_ablaze_the_fire_box.x + position_player.x, position_ablaze_the_fire_box.y + position_player.y);
	sprite = GlobalFunction::CreateSprite(position_holder, size_ablaze_the_fire_box, texture_ablaze_the_fire_box);
	been_init = true;
	duration_boost = duration_boost_received;
	player->GivePlayerChangeStat(type_of_the_box, duration_boost_received, value_received);
}

bool AttackDamageBox::IsNeedToDelete()
{
	CheckToDelete();
	return to_delete;
}

void AttackDamageBox::Initialized(int player_id_received, int type_box)
{
	player_id = player_id_received;
	type_of_the_box = type_box;
}

void AttackDamageBox::Update(float DELTATIME, sf::Vector2f player_position)
{
	sprite.setPosition(sf::Vector2f(player_position.x + position_ablaze_the_fire_box.x, player_position.y + position_ablaze_the_fire_box.y));
}

void AttackDamageBox::CheckToDelete()
{
	if (clock_timer_box_created.getElapsedTime().asSeconds() >= duration_boost)
	{
		to_delete = true;
	}
}

int AttackDamageBox::GetTypeBox()
{
	return 	type_of_the_box;
}

sf::Vector2f AttackDamageBox::GetCurrentPosition()
{
	return sprite.getPosition();
}

void AttackDamageBox::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

