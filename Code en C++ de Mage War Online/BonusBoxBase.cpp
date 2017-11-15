#include "stdafx.h"
#include "BonusBoxBase.h"


BonusBoxBase::BonusBoxBase()
{
}

BonusBoxBase::~BonusBoxBase()
{
}

bool BonusBoxBase::GetInitStatus()
{
	return false;
}

void BonusBoxBase::Init(sf::Vector2f position_player, std::shared_ptr<Player> player, float duration_boost_ablaze_the_fire, float attack_speed_bonus_received)
{
}

void BonusBoxBase::DrawToScreen(sf::RenderWindow &window)
{
}

bool BonusBoxBase::IsNeedToDelete()
{
	return true;
}

void BonusBoxBase::Initialized(int player_id_received, int type_box)
{
}

void BonusBoxBase::Update(float DELTATIME, sf::Vector2f player_position)
{
}

void BonusBoxBase::CheckToDelete()
{

}

int BonusBoxBase::GetTypeBox()
{
	return 	0;
}

sf::Vector2f BonusBoxBase::GetCurrentPosition()
{
	return sf::Vector2f(0, 0);
}

void BonusBoxBase::Draw(sf::RenderWindow &window)
{

}
