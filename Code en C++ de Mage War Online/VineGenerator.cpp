#include "stdafx.h"
#include "VineGenerator.h"


VineGenerator::VineGenerator()
{
}

VineGenerator::~VineGenerator()
{

}

void VineGenerator::GenerateOneFireball(sf::RenderWindow &window, sf::Vector2f &position_view_player, sf::Vector2f &position_player, float player_damage, float player_attack_speed, bool is_player_stunned, std::shared_ptr<Player> player)
{
	std::shared_ptr<Vine>  projectile = std::shared_ptr<Vine>(new Vine());
	float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
	float angle = GlobalFunction::GetRotationBetweenTwoPositions(GlobalFunction::GetMousePosition(window, position_view_player), position_player);
	if (player->GetPlayerListDrawback()[0])
	{
		if (GlobalFunction::getRandomRange(1, 1000) <= 500)
		{
			angle += GlobalFunction::getRandomRange(30, 70) / 10;
		}
		else
		{
			angle -= GlobalFunction::getRandomRange(30, 70) / 10;
		}
	}
	projectile->Initialized(player->GetId());
	projectile->Init(position_player, angle, player_damage, player, speed_modifier);
	ProjectileGestion::instance()->AddObjectToList(projectile);
	clock_rate_of_projectile.restart();
	projectile.reset();
}


