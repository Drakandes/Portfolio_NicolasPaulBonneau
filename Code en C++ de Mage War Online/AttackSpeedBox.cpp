#include "stdafx.h"
#include "AttackSpeedBox.h"

AttackSpeedBox::AttackSpeedBox()
{
	if (!texture_ablaze_the_fire_box.loadFromFile("AttackSpeedBox.png"))
	{
		std::cout << "Couldn't load balze the fire box correctly" << std::endl;
	}
}

AttackSpeedBox::~AttackSpeedBox()
{
}

bool AttackSpeedBox::GetInitStatus()
{
	return been_init;
}

void AttackSpeedBox::Init(sf::Vector2f position_player, std::shared_ptr<Player> player, float duration_boost_ablaze_the_fire, float attack_speed_bonus_received)
{
	position_ablaze_the_fire_box = sf::Vector2f(35, - 20);
	sf::Vector2f position_holder = sf::Vector2f(position_ablaze_the_fire_box.x + position_player.x, position_ablaze_the_fire_box.y + position_player.y);
	sprite_ablaze_the_fire_box = GlobalFunction::CreateSprite(position_holder, size_ablaze_the_fire_box, texture_ablaze_the_fire_box);
	been_init = true;
	duration_boost = duration_boost_ablaze_the_fire;
	player->GivePlayerChangeStat(type_of_the_box, duration_boost_ablaze_the_fire, attack_speed_bonus_received);
}

void AttackSpeedBox::DrawToScreen(sf::RenderWindow &window)
{
	window.draw(sprite_ablaze_the_fire_box);
}

bool AttackSpeedBox::IsNeedToDelete()
{
	CheckToDelete();
	return to_delete;
}

void AttackSpeedBox::Initialized(int player_id_received, int type_box)
{
	player_id = player_id_received;
	type_of_the_box = type_box;
}

void AttackSpeedBox::Update(float DELTATIME, sf::Vector2f player_position)
{
	sprite_ablaze_the_fire_box.setPosition(sf::Vector2f (player_position.x + position_ablaze_the_fire_box.x, player_position.y + position_ablaze_the_fire_box.y));
}

void AttackSpeedBox::CheckToDelete()
{
	if (clock_timer_box_created.getElapsedTime().asSeconds() >= duration_boost)
	{
		to_delete = true;
	}
}

int AttackSpeedBox::GetTypeBox()
{
	return type_of_the_box;
}

sf::Vector2f AttackSpeedBox::GetCurrentPosition()
{
	return sprite_ablaze_the_fire_box.getPosition();
}

void AttackSpeedBox::Draw(sf::RenderWindow &window)
{
	window.draw(sprite_ablaze_the_fire_box);
}