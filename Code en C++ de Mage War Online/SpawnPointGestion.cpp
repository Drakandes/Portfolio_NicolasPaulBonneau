#include "stdafx.h"
#include "SpawnPointGestion.h"

SpawnPointGestion::SpawnPointGestion()
{
	if (!texture_spawn_point.loadFromFile("SpawnPointX2.png"))
	{
		std::cout << "Error while loading the spawn point texture" << std::endl;
	}

	if (!texture_altar.loadFromFile("Altar.png"))
	{
		std::cout << "Error while loading the altar texture" << std::endl;
	}
}

SpawnPointGestion::~SpawnPointGestion()
{
}

void SpawnPointGestion::Init(std::shared_ptr<Player> player, int current_language, sf::Vector2f size_map)
{
	this->size_map = size_map;
	language = current_language;
	player_pointer = player;
	sprite_spawn_point = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), sf::Vector2f(128, 150), texture_spawn_point);
	sprite_altar = GlobalFunction::CreateSprite(sf::Vector2f(size_map.x / 2, size_map.y / 2), sf::Vector2f(85, 140), texture_altar);

	sf::Vector2f position = GetNewPositionPlayer();
	sprite_spawn_point.setPosition(position);
	player_pointer->TeleportEntity(position, Nothing_E);
}

void SpawnPointGestion::Update()
{
	if (player_pointer->GetCollisionRect().intersects(sprite_spawn_point.getGlobalBounds()))
	{
		player_pointer->ChangePlayerIsAtSpawn(true);
	}
	else
	{
		player_pointer->ChangePlayerIsAtSpawn(false);
	}

	sf::FloatRect hitbox_player = player_pointer->GetCollisionRect();

	if (clock_notice.getElapsedTime().asSeconds() >= TIMERNOTIFICATION + 2)
	{
		if (sprite_altar.getGlobalBounds().intersects(hitbox_player))
		{
			if (player_pointer->GetIfPlayerRitualDone())
			{
				if (language == English_E)
				{
					NotificationSystem::instance()->AddNoticeToList("Press 0 to go to the next map.");
					clock_notice.restart();
				}
				else
				{
					NotificationSystem::instance()->AddNoticeToList("Appuyez sur 0 pour passer à la carte suivante.");
					clock_notice.restart();
				}
			}
			else
			{
				if (language == English_E)
				{
					if (player_pointer->GetNumberMonsterHearts() >= 25)
					{
						NotificationSystem::instance()->AddNoticeToList("Press 0 to start the ritual.");
						clock_notice.restart();
					}
					else
					{
						NotificationSystem::instance()->AddNoticeToList("Appuyez sur 0 pour débuter le rituel.");
						clock_notice.restart();
					}
				}
				else
				{
					if (player_pointer->GetNumberMonsterHearts() >= 25)
					{
						NotificationSystem::instance()->AddNoticeToList("You don't have enough monsters' hearts to begin the ritual.");
						clock_notice.restart();
					}
					else
					{
						NotificationSystem::instance()->AddNoticeToList("Vous n'avez pas assez de coeur de monstres pour entamer le rituel.");
						clock_notice.restart();
					}
				}
			}
		}
		if (sprite_spawn_point.getGlobalBounds().intersects(hitbox_player))
		{
			if (language == English_E)
			{
				NotificationSystem::instance()->AddNoticeToList("You are at the spawn. Your regeneration is greatly increased when you are out of combat!");
				clock_notice.restart();
			}
			else
			{
				NotificationSystem::instance()->AddNoticeToList("Vous êtes au point de départ. Votre regénération est grandement augmentée lorsque vous êtes hors-combat!");
				clock_notice.restart();
			}
		}
	}

	if (sprite_spawn_point.getGlobalBounds().intersects(hitbox_player))
	{
		if (player_pointer->GetIfPlayerOutOfCombat())
		{
			player_pointer->GivePlayerChangeStat(HpPercentRecovery, -1, 6);
		}
	}
}

void SpawnPointGestion::Draw(sf::RenderWindow &window)
{
	window.draw(sprite_spawn_point);
	window.draw(sprite_altar);
}

sf::Vector2f SpawnPointGestion::GetNewPositionPlayer()
{
	sf::Vector2f new_position;

	bool horizontal = GlobalFunction::getRandomRange(1, 1000) < 500 ? true : false;

	if (horizontal)
	{
		if (GlobalFunction::getRandomRange(1, 1000) <= 500)
		{
			new_position.x = GlobalFunction::getRandomRange(range_from_border.x, range_from_border.y);
		}
		else
		{
			new_position.x = GlobalFunction::getRandomRange(size_map.x - range_from_border.y, size_map.x - range_from_border.x);
		}

		new_position.y = GlobalFunction::getRandomRange(range_from_border.x, size_map.y - range_from_border.x);
	}
	else
	{
		new_position.x = GlobalFunction::getRandomRange(range_from_border.x, size_map.x - range_from_border.x);

		if (GlobalFunction::getRandomRange(1, 1000) <= 500)
		{
			new_position.y = GlobalFunction::getRandomRange(range_from_border.x, range_from_border.y);
		}
		else
		{
			new_position.y = GlobalFunction::getRandomRange(size_map.y - range_from_border.y, size_map.y - range_from_border.x);
		}
	}

	return new_position;
}

void SpawnPointGestion::PlayerRespawnGestion()
{
	sf::Vector2f position = GetNewPositionPlayer();
	sprite_spawn_point.setPosition(position);
	player_pointer->TeleportEntity(position, Nothing_E);
	ListObjectsSingleton::instance()->ToggleNeedLoadSpawn();
}

void SpawnPointGestion::PlayerChangedMapGestion()
{
	sf::Vector2f position = GetNewPositionPlayer();
	sprite_spawn_point.setPosition(position);
	player_pointer->TeleportEntity(position, Nothing_E);
}

SpawnPointGestion* SpawnPointGestion::s_instance1 = 0;

