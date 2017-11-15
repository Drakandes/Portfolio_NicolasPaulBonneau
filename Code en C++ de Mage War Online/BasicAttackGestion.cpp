#include "stdafx.h"
#include "BasicAttackGestion.h"

BasicAttackGestion::BasicAttackGestion()
{
	std::shared_ptr<FireballGenerator> fireball_generator = std::shared_ptr<FireballGenerator>(new FireballGenerator());
	std::shared_ptr<BubbleGenerator> bubble_generator = std::shared_ptr<BubbleGenerator>(new BubbleGenerator());
	std::shared_ptr<VineGenerator> vine_generator = std::shared_ptr<VineGenerator>(new VineGenerator());
	listGenerators.push_back(fireball_generator);
	listGenerators.push_back(vine_generator);
	listGenerators.push_back(bubble_generator);
}

BasicAttackGestion::~BasicAttackGestion()
{
	listGenerators.clear();
}

void BasicAttackGestion::GenerateOneFireball(sf::RenderWindow &window, sf::Vector2f &position_view_player, sf::Vector2f &position_player, float player_damage, float player_attack_speed, std::shared_ptr<Player> player)
{
	bool player_stunned = player->IsPlayerStunned();
	if (!player_stunned && player->GetCurrentOpenedInterface() == NoInterface_E)
	{
		if (clock_rate_of_basic_attack.getElapsedTime().asSeconds() >= 1 / player_attack_speed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int current_player_class = player->GetCurrentClassPlayer();

				float angle_to_add = 0;
				if (player->GetPlayerListDrawback()[0])
				{
					if (GlobalFunction::getRandomRange(1, 1000) <= 500)
					{
						angle_to_add += GlobalFunction::getRandomRange(5, 10) / 10;
					}
					else
					{
						angle_to_add -= GlobalFunction::getRandomRange(5, 10) / 10;
					}
				}

				switch (current_player_class)
				{
				case ClassFire:
				{
					std::shared_ptr<Fireball>  projectile = std::shared_ptr<Fireball>(new Fireball());
					float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
					float angle = GlobalFunction::GetRotationBetweenTwoPositions(GlobalFunction::GetMousePosition(window, position_view_player), position_player) + angle_to_add;
		
					projectile->Initialized(player->GetId());
					projectile->Init(position_player, angle, player_damage, player, speed_modifier);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();

					SoundGestion::instance()->AddSound("SoundIgnite.wav", 15, false);

					break;
				}
				case ClassGrass:
				{
					std::shared_ptr<Vine>  projectile = std::shared_ptr<Vine>(new Vine());
					float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
					float angle = GlobalFunction::GetRotationBetweenTwoPositions(GlobalFunction::GetMousePosition(window, position_view_player), position_player) + angle_to_add;
					
					projectile->Initialized(player->GetId());
					projectile->Init(position_player, angle, player_damage, player, speed_modifier);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();

					SoundGestion::instance()->AddSound("VineCast.wav", 85, false);

					break;
				}
				case ClassWater:
				{
					std::shared_ptr<Bubble>  projectile = std::shared_ptr<Bubble>(new Bubble());
					float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
					float angle = GlobalFunction::GetRotationBetweenTwoPositions(GlobalFunction::GetMousePosition(window, position_view_player), position_player) + angle_to_add;
					
					projectile->Initialized(player->GetId());
					projectile->Init(position_player, angle, player_damage, player, speed_modifier);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();

					SoundGestion::instance()->AddSound("BubbleCast.wav", 90, false);

					break;
				}
				case ClassRock:
				{
					std::shared_ptr<Boulder>  projectile = std::shared_ptr<Boulder>(new Boulder());
					float speed_modifier = player->GetProjectileSpeedBonus() / 100 + 1;
					float angle = GlobalFunction::GetRotationBetweenTwoPositions(GlobalFunction::GetMousePosition(window, position_view_player), position_player) + angle_to_add;
					projectile->Initialized(player->GetId());
					projectile->Init(position_player, angle, player_damage, player, speed_modifier);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();

					SoundGestion::instance()->AddSound("SoundRock.wav", 100, false);

					break;
				}
				}

				clock_rate_of_basic_attack.restart();
			}
		}
	}
}
