#include "stdafx.h"
#include "MonsterGenerator.h"
#include "GlobalEnum.h"

MonsterGenerator::MonsterGenerator()
{
}

MonsterGenerator::~MonsterGenerator()
{
}

void MonsterGenerator::CreateSpawns(sf::Vector2f size_map, int map_level,sf::Vector2f spawn_point)
{
	rect_spawn_point = GlobalFunction::CreateRectangleWithOrigin(sf::Vector2f(range_spawn_no_monster, range_spawn_no_monster), spawn_point, sf::Color::Color(255,0,0,75));

	level_map = map_level;
	size_current_map = size_map;
	center_map = sf::Vector2f(size_map.x / 2, size_map.y / 2);
	map_width = GlobalFunction::GetDistanceBetweenTwoPositions(sf::Vector2f(0, size_map.y / 2), center_map);
	for (int y = 0; y < std::ceil(size_map.y/size_spawn); y++) 
	{
		for (int x = 0; x < std::ceil(size_map.x / size_spawn); x++)
		{
			sf::Vector2f spawn_location(size_spawn * x, size_spawn*y);
			listSpawnLocation.push_back(spawn_location);
			int number_monster = 0;
			listSpawnMonsterQuantity.push_back(number_monster);
			sf::Clock clock_holder;
			listSpawnClock.push_back(clock_holder);
			float holder = 5;
			listSpawnClockTimer.push_back(holder);
			int number_monster_elite = 0;
			listSpawnMonsterEliteQuantity.push_back(number_monster_elite);

			bool smaller = false;
			sf::Vector2f area_spawn{ static_cast<float>(size_spawn),static_cast<float>(size_spawn) };
			if (size_spawn * (x+ 1) > size_map.x)
			{
				smaller = true;
				area_spawn.x = size_spawn * (x + 1) - size_map.x;
			}
			if (size_spawn * (y+1) > size_map.y)
			{
				smaller = true;
				area_spawn.y = size_spawn *(y + 1) - size_map.y;
			}

			sf::RectangleShape rect_size = GlobalFunction::CreateRectangle(area_spawn, spawn_location);
			rect_size.setFillColor(sf::Color::Color(0, 0, 255, 50));
			listRectSpawn.push_back(rect_size);
			if (rect_size.getGlobalBounds().intersects(rect_spawn_point.getGlobalBounds()))
			{
				listSpawnActivated.push_back(false);
			}
			else
			{
				listSpawnActivated.push_back(true);
			}

			int limit_monster = std::ceil((area_spawn.x*area_spawn.y) / (size_spawn*size_spawn) * number_maximum_monster) + level_map;
			int limit_monster_elite = GlobalFunction::getRandomRange(1, 1000) < 700 ? 1 : 0;
			if (smaller)
			{
				limit_monster_elite = 0;
				limit_monster--;
				if (limit_monster < 0)
				{
					limit_monster = 0;
				}
			}
			listLimitMonsterEliteQuantity.push_back(limit_monster_elite);
			listLimitMonsterQuantity.push_back(limit_monster);
		}
	}

	for (int i = 0; i < listSpawnLocation.size(); i++)
	{
		while (listSpawnMonsterQuantity[i] < listLimitMonsterQuantity[i] && listSpawnActivated[i])
		{
			std::vector<int> listExceptions{ SquidChildEnum + 1,DummyEnum + 1 };
			int type_monster_created = GlobalFunction::getRandomRangeWithUnknownException(1, number_type_monsters, listExceptions) - 1;
			sf::Vector2f location_spawn = listSpawnLocation[i];
			sf::Vector2f position_monster = GetNewPositionMonster(i);
			
			int monster_level = (1-(std::ceil(GlobalFunction::GetDistanceBetweenTwoPositions(position_monster, center_map)) / map_width)) *11 + 10*(level_map-1);
			if (monster_level <= 0)
			{
				monster_level = 1;
			}

			if (listSpawnMonsterEliteQuantity[i]  < listLimitMonsterEliteQuantity[i])
			{
				SpawnSpecificMonster(type_monster_created, position_monster, location_spawn, i, size_spawn, monster_level, true,false);
				//SpawnSpecificMonster(BlobEnum, position_monster, location_spawn, counter_spawn_checking, size_spawn, monster_level, true,false);
				listSpawnMonsterEliteQuantity[i]++;
			}
			else
			{
				SpawnSpecificMonster(type_monster_created, position_monster, location_spawn, i, size_spawn, monster_level, false, false);
				//SpawnSpecificMonster(BlobEnum, position_monster, location_spawn, counter_spawn_checking, size_spawn, monster_level, false, false);
			}

			listSpawnMonsterQuantity[i]++;
		}
		listSpawnClock[i].restart();
		listSpawnClockTimer[i] = timer_spawn_normal;
	}
}

void MonsterGenerator::ModifiySpawnWithSpawnPoint(sf::Vector2f spawn_point)
{
	rect_spawn_point = GlobalFunction::CreateRectangleWithOrigin(sf::Vector2f(2000, 2000), spawn_point, sf::Color::Color(255, 0, 0, 75));

	for (int i = 0; i < listSpawnLocation.size(); i++)
	{
		if (listRectSpawn[i].getGlobalBounds().intersects(rect_spawn_point.getGlobalBounds()))
		{
			listSpawnActivated[i] = false;
		}
		else
		{
			listSpawnActivated[i] = true; 

			while (listSpawnMonsterQuantity[i] < listLimitMonsterQuantity[i] && listSpawnActivated[i])
			{
				std::vector<int> listExceptions{ SquidChildEnum + 1,DummyEnum + 1 };
				int type_monster_created = GlobalFunction::getRandomRangeWithUnknownException(1, number_type_monsters, listExceptions) - 1;
				sf::Vector2f location_spawn = listSpawnLocation[i];
				sf::Vector2f position_monster = GetNewPositionMonster(i);

				int monster_level = (1 - (std::ceil(GlobalFunction::GetDistanceBetweenTwoPositions(position_monster, center_map)) / map_width)) * 11 + 10 * (level_map - 1);
				if (monster_level <= 0)
				{
					monster_level = 1;
				}

				if (listSpawnMonsterEliteQuantity[i]  < listLimitMonsterEliteQuantity[i])
				{
					SpawnSpecificMonster(type_monster_created, position_monster, location_spawn, counter_spawn_checking, size_spawn, monster_level, true, false);
					//SpawnSpecificMonster(BlobEnum, position_monster, location_spawn, counter_spawn_checking, size_spawn, monster_level, true,false);
					listSpawnMonsterEliteQuantity[i]++;
				}
				else
				{
					SpawnSpecificMonster(type_monster_created, position_monster, location_spawn, counter_spawn_checking, size_spawn, monster_level, false, false);
					//SpawnSpecificMonster(BlobEnum, position_monster, location_spawn, counter_spawn_checking, size_spawn, monster_level, false, false);
				}

				listSpawnMonsterQuantity[i]++;
			}
			listSpawnClock[i].restart();
			listSpawnClockTimer[i] = timer_spawn_normal;
		}
	}

	std::list<std::shared_ptr<MonsterBase>>::iterator i = listMonster.begin();
	while(i != listMonster.end())
	{
		bool erased = false;

		int id_spawn = (*i)->GetIdSpawn();
 		if (id_spawn != -1)
		{
			if (!listSpawnActivated[id_spawn])
			{
				(*i)->SetToDelete();
				erased = true;
				listMonster.erase(i++);
			}
		}

		if (!erased)
		{
			i++;
		}
	}
}

void MonsterGenerator::GenerateEntities()
{
	if (clock_generating_monster.getElapsedTime().asSeconds() >= 0.5)
	{
		if (listSpawnMonsterQuantity[counter_spawn_checking] < listLimitMonsterQuantity[counter_spawn_checking] && listSpawnActivated[counter_spawn_checking])
		{
			if (listSpawnClock[counter_spawn_checking].getElapsedTime().asSeconds() >= listSpawnClockTimer[counter_spawn_checking])
			{
				std::vector<int> listExceptions{ SquidChildEnum + 1,DummyEnum + 1 };
				int type_monster_created = GlobalFunction::getRandomRangeWithUnknownException(1, number_type_monsters, listExceptions) - 1;
				sf::Vector2f location_spawn = listSpawnLocation[counter_spawn_checking];
				sf::Vector2f position_monster = GetNewPositionMonster(counter_spawn_checking);
				
				int monster_level = (1 - (std::ceil(GlobalFunction::GetDistanceBetweenTwoPositions(position_monster, center_map)) / map_width)) * 11 + 10 * (level_map - 1);
				if (monster_level == 0)
				{
					monster_level = 1;
				}

				if (listSpawnMonsterEliteQuantity[counter_spawn_checking] < listLimitMonsterEliteQuantity[counter_spawn_checking])
				{
					SpawnSpecificMonster(type_monster_created, position_monster, location_spawn, counter_spawn_checking, size_spawn, monster_level, true, false);
					listSpawnMonsterEliteQuantity[counter_spawn_checking]++;
				}
				else
				{
					SpawnSpecificMonster(type_monster_created, position_monster, location_spawn, counter_spawn_checking, size_spawn, monster_level, false, false);
				}

				listSpawnClock[counter_spawn_checking].restart();
				listSpawnClockTimer[counter_spawn_checking] = timer_spawn_normal;
				listSpawnMonsterQuantity[counter_spawn_checking]++;
			}
		}
		counter_spawn_checking++;
		if (counter_spawn_checking == listSpawnLocation.size())
		{
			counter_spawn_checking = 0;
		}
		clock_generating_monster.restart();
	}
}

void MonsterGenerator::SpawnSpecificMonster(int type_monster_to_spawn,sf::Vector2f position, sf::Vector2f position_spawn, int id_spawn, float size_spawn,int level_monster, bool is_elite,bool is_guardian)
{
	switch (type_monster_to_spawn)
	{
	case BlobEnum:
	{
		std::shared_ptr<Blob> monster = std::shared_ptr<Blob>(new Blob());
		monster->Texture_loading();
		monster->Init(ListObjectsSingleton::instance()->GetNewID(),position_spawn,id_spawn,size_spawn,level_monster,position, is_elite,is_guardian);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	case DavbheerEnum:
	{
		std::shared_ptr<Davbheer> monster = std::shared_ptr<Davbheer>(new Davbheer());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), position_spawn, id_spawn, size_spawn, level_monster, position, is_elite, is_guardian);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	case MiniGoatEnum:
	{
		float id_group = ListObjectsSingleton::instance()->GetNewID();
		std::shared_ptr<MiniGoat> monster = std::shared_ptr<MiniGoat>(new MiniGoat());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), position_spawn, id_spawn, size_spawn, level_monster,position, is_elite, is_guardian);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	case PenguinEnum:
	{
		std::shared_ptr<Penguin> monster = std::shared_ptr<Penguin>(new Penguin());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), position_spawn, id_spawn, size_spawn, level_monster, position, is_elite, is_guardian);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	case DemonEnum:
	{
		std::shared_ptr<Demon> monster = std::shared_ptr<Demon>(new Demon());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), position_spawn, id_spawn, size_spawn, level_monster, position, is_elite, is_guardian);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	case SentryEnum:
	{
		std::shared_ptr<Sentry> monster = std::shared_ptr<Sentry>(new Sentry());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), position_spawn, id_spawn, size_spawn, level_monster, position, is_elite, is_guardian);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	case SquidEnum:
	{
		std::shared_ptr<Squid> monster = std::shared_ptr<Squid>(new Squid());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), position_spawn, id_spawn, size_spawn, level_monster, position, is_elite, is_guardian);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	case DummyEnum:
	{
		std::shared_ptr<Dummy> monster = std::shared_ptr<Dummy>(new Dummy());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), position_spawn, id_spawn, size_spawn, level_monster, position);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	case FliesEnum:
	{
		std::shared_ptr<Flies> monster = std::shared_ptr<Flies>(new Flies());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), position_spawn, id_spawn, size_spawn, level_monster, position, is_elite, is_guardian);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	case BombyEnum:
	{
		std::shared_ptr<Bomby> monster = std::shared_ptr<Bomby>(new Bomby());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), position_spawn, id_spawn, size_spawn, level_monster, position, is_elite, is_guardian);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	case WaelfonEnum:
	{
		std::shared_ptr<Waelfon> monster = std::shared_ptr<Waelfon>(new Waelfon());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), position_spawn, id_spawn, size_spawn, level_monster, position, is_elite, is_guardian);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	case DarkMageEnum:
	{
		std::shared_ptr<DarkMage> monster = std::shared_ptr<DarkMage>(new DarkMage());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), position_spawn, id_spawn, size_spawn, level_monster, position, is_elite, is_guardian);
		listMonster.push_back(monster);
		MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
		monster.reset();
		break;
	}
	}
}

void MonsterGenerator::Update(sf::FloatRect map_part_activated, std::shared_ptr<Player> player, TextGenerator &text_generator,  float DELTATIME)
{
	listPositionGuardian.clear();
	listActivatedMonster.clear();
	std::list<std::shared_ptr<MonsterBase>>::iterator iterator = listMonster.begin();
	sf::Vector2f player_position = player->GetCurrentPosition();
	sf::Vector2f player_size = player->GetSize();
	sf::Vector2f player_velocity = player->GetVelocityPlayer();
	float speed_player = player->GetMovementSpeed();
	int player_id = player->GetId();

	while (iterator != listMonster.end())
	{
		sf::FloatRect monster_box = (*iterator)->GetCollisionRect();
		if (map_part_activated.contains((*iterator)->GetCurrentPosition()))
		{
			listActivatedMonster.push_back(*iterator);
			sf::String monster_type = (*iterator)->GetMonsterType();
			sf::Vector2f monster_position = (*iterator)->GetCurrentPosition();

			Minimap::instance()->AddPosition(monster_position, Monster_E);

			if ((*iterator)->GetIfMonsterIsGuardian())
			{
				listPositionGuardian.push_back(monster_position);
			}

			if ((*iterator)->CheckIfNeedGoBackQuadtree())
			{
				MainQuadtree::instance()->insert((*iterator)->GetCurrentPosition(), (*iterator)->GetSize(), (*iterator));
			}

			(*iterator)->Update(player->GetCurrentPosition(), speed_player, player_position, DELTATIME, player_velocity);
			(*iterator)->UpdateWithPlayer(player);

			float damage_ignition = (*iterator)->DamageFromAllIgnition();
			if (damage_ignition > 0)
			{
				sf::String str = "-";
				str = GlobalFunction::InsertNumberToString(str, (*iterator)->GotDamaged(damage_ignition, -1, 0), str.getSize());
				TextGenerator::instance()->GenerateOneTextStringAndColor(monster_position, str, (*iterator)->GetSize(), sf::Color::White, (*iterator));
			}

			if ((*iterator)->CanSpawnChild())
			{
				std::shared_ptr<MonsterBase> monster = std::shared_ptr<MonsterBase>((*iterator)->SpawnChild());
				monster->Init(ListObjectsSingleton::instance()->GetNewID(), (*iterator)->IsMonsterElite());
				monster->GivePosition((*iterator)->GetCurrentPosition());
				listMonster.push_back(monster);
				MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
				monster.reset();
			}

			bool isNeedToDelete = (*iterator)->IsNeedToDelete();
			if (isNeedToDelete)
			{
				if (monster_type != "SquidChild")
				{
					int id_spawn = (*iterator)->GetIdSpawn();
					if (id_spawn != -1)
					{
						listSpawnMonsterQuantity[id_spawn]--;
						listSpawnClockTimer[id_spawn] = timer_spawn_monster_die;
						listSpawnClock[id_spawn].restart();
						if ((*iterator)->IsMonsterElite())
						{
							listSpawnMonsterEliteQuantity[id_spawn]--;
						}
					}
				}

				if (monster_type == "Blob")
				{
				}
				else if (monster_type == "Davbheer")
				{
				}
				else if (monster_type == "MiniGoat")
				{

				}
				else if (monster_type == "Penguin")
				{
				}
				else if (monster_type == "Demon")
				{
				}
				else if (monster_type == "Sentry")
				{
				}
				else if (monster_type == "Squid")
				{
				}
				else if (monster_type == "Dummy")
				{
				}

#pragma region ExperienceGiven
				float exp_received = (*iterator)->GetExp();
				float exp_bonus = player->GetBonusExperiencePercent();
				exp_received += exp_received*exp_bonus / 100;

				float level_player = player->GetPlayerLevel() * 5;
				float level_monster = (*iterator)->GetLevelMonster();
				float level_difference = level_player - level_monster;

				if (level_difference > 25)
				{
					exp_received = 0;
				}
				else if (level_difference > 20)
				{
					exp_received -= exp_received*(0.75 + 0.05*(level_difference - 20));
				}
				else if (level_difference > 15)
				{
					exp_received -= exp_received*(0.50 + 0.05*(level_difference - 15));
				}
				else if (level_difference > 10)
				{
					exp_received -= exp_received*(0.25 + 0.05*(level_difference - 10));
				}
				else if (level_difference > 5)
				{
					exp_received -= exp_received*(0.05*(level_difference - 5));
				}

				player->GetExp(exp_received);
#pragma endregion ExperienceGiven

#pragma region MoneyGiven

				float money_given = (*iterator)->GetMoney();
				float money_bonus = player->GetBonusMoneyPercent();

				if (level_difference > 25)
				{
					money_given = 0;
				}
				else if (level_difference > 20)
				{
					money_given -= money_given*(0.75 + 0.05*(level_difference - 20));
				}
				else if (level_difference > 15)
				{
					money_given -= money_given*(0.50 + 0.05*(level_difference - 15));
				}
				else if (level_difference > 10)
				{
					money_given -= money_given*(0.25 + 0.05*(level_difference - 10));
				}
				else if (level_difference > 5)
				{
					money_given -= money_given*(0.05*(level_difference - 5));
				}

				money_given += money_given*money_bonus / 100;
				player->GivePlayerMoney(money_given);

#pragma endregion MoneyGiven

#pragma region FragmentsGiven

				sf::Vector2f monster_fragments_loot = (*iterator)->GetTypeAndNumberFragments();
				if (player->GetPlayerListEquippedScroll()[GetFiveSkillLevelTwo])
				{
					monster_fragments_loot.y += GlobalFunction::getRandomRange(5, 10);
				}

				monster_fragments_loot.y += player->GetBonusFragmentsPercent()*monster_fragments_loot.y / 100;

				if (level_difference > 25)
				{
					monster_fragments_loot.y = 0;
				}
				else if (level_difference > 20)
				{
					monster_fragments_loot.y -= monster_fragments_loot.y*(0.75 + 0.05*(level_difference - 20));
				}
				else if (level_difference > 15)
				{
					monster_fragments_loot.y -= monster_fragments_loot.y*(0.50 + 0.05*(level_difference - 15));
				}
				else if (level_difference > 10)
				{
					monster_fragments_loot.y -= monster_fragments_loot.y*(0.25 + 0.05*(level_difference - 10));
				}
				else if (level_difference > 5)
				{
					monster_fragments_loot.y -= monster_fragments_loot.y*(0.05*(level_difference - 5));
				}

				player->GivePlayerFragments(monster_fragments_loot.x, monster_fragments_loot.y);
#pragma endregion FragmentsGiven

				text_generator.GenerateOneTextPlayerColorSpecified(player_position, exp_received, player_size, sf::Color::Blue, player);
				CreateNotice(exp_received, money_given, monster_fragments_loot);
				if (monster_type != "SquidChild")
				{
					player->MonsterKilledGestion((*iterator)->IsMonsterElite());
				}
				if ((*iterator)->GetIfMonsterIsGuardian())
				{
					number_guardian_alive--;
					if (number_guardian_alive == 0)
					{
						if (language == English_E)
						{
							NotificationSystem::instance()->AddNoticeToList("You completed the ritual! You can proceed to the next map!");
						}
						else
						{
							NotificationSystem::instance()->AddNoticeToList("Vous avez compléter le rituel! Vous pouvez procéder au prochain monde!");
						}
						player->ChangePlayerDoneRitual(true);
						ritual_started = false;
					}
				}
				listMonster.erase(iterator++);
			}
			else
			{
				++iterator;
			}
		}
		else
		{
			sf::Vector2f monster_position = (*iterator)->GetCurrentPosition();
			Minimap::instance()->AddPosition(monster_position, Monster_E);

			if ((*iterator)->GetIfMonsterIsGuardian())
			{
				listPositionGuardian.push_back(monster_position);
			}

			++iterator;
		}
	}

	Minimap::instance()->GiveGuardiansPosition(listPositionGuardian);
}

void MonsterGenerator::CreateNotice(float experience_given, float money_given, sf::Vector2f fragments_given)
{
	if (language == English_E)
	{
		if (experience_given > 0)
		{
			sf::String string_exp = "You received ";
			string_exp = GlobalFunction::InsertNumberToString(string_exp, experience_given, string_exp.getSize());
			string_exp.insert(string_exp.getSize(), " experience points.");
			NotificationSystem::instance()->AddNoticeToList(string_exp);
		}

		if (money_given > 0)
		{
			sf::String string_money = "You received ";
			string_money = GlobalFunction::InsertNumberToString(string_money, money_given, string_money.getSize());
			string_money.insert(string_money.getSize(), " gold.");
			NotificationSystem::instance()->AddNoticeToList(string_money);
		}

		if (fragments_given.y > 0)
		{
			sf::String string_type_fragment;
			int type = fragments_given.x;
			switch (type)
			{
			case StrongFragment:
				string_type_fragment = " strong fragments.";
				break;
			case EnchantedFragment:
				string_type_fragment = " enchanted fragments.";
				break;
			case RunicFragment:
				string_type_fragment = " runic fragments.";
				break;
			case AncientFragment:
				string_type_fragment = " ancient fragments.";
				break;
			case LostLegendaryFragment:
				string_type_fragment = " legendary fragments.";
				break;
			}
			sf::String string_fragments_given = "You received ";
			string_fragments_given = GlobalFunction::InsertNumberToString(string_fragments_given, fragments_given.y, string_fragments_given.getSize());
			string_fragments_given.insert(string_fragments_given.getSize(), string_type_fragment);

			NotificationSystem::instance()->AddNoticeToList(string_fragments_given);
		}
	}
	else
	{
		if (experience_given > 0)
		{
			sf::String string_exp = "Vous avez reçu ";
			string_exp = GlobalFunction::InsertNumberToString(string_exp, experience_given, string_exp.getSize());
			string_exp.insert(string_exp.getSize(), " points d'expérience.");
			NotificationSystem::instance()->AddNoticeToList(string_exp);
		}

		if (money_given > 0)
		{
			sf::String string_money = "Vous avez reçu ";
			string_money = GlobalFunction::InsertNumberToString(string_money, money_given, string_money.getSize());
			string_money.insert(string_money.getSize(), " pièces d'or.");
			NotificationSystem::instance()->AddNoticeToList(string_money);
		}

		if (fragments_given.y > 0)
		{
			sf::String string_type_fragment;
			int type = fragments_given.x;
			switch (type)
			{
			case StrongFragment:
				string_type_fragment = " fragments puissants.";
				break;
			case EnchantedFragment:
				string_type_fragment = " fragments enchantés.";
				break;
			case RunicFragment:
				string_type_fragment = " fragments runiques.";
				break;
			case AncientFragment:
				string_type_fragment = " fragments anciens.";
				break;
			case LostLegendaryFragment:
				string_type_fragment = " fragments légendaires.";
				break;
			}
			sf::String string_fragments_given = "Vous avez reçu ";
			string_fragments_given = GlobalFunction::InsertNumberToString(string_fragments_given, fragments_given.y, string_fragments_given.getSize());
			string_fragments_given.insert(string_fragments_given.getSize(), string_type_fragment);

			NotificationSystem::instance()->AddNoticeToList(string_fragments_given);
		}
	}
}

void MonsterGenerator::DrawToScreen(sf::RenderWindow &window, sf::View &view_player)
{
	std::list<std::shared_ptr<MonsterBase>>::iterator iterator = listMonster.begin();
	while (iterator != listMonster.end())
	{
		DrawGestion::instance()->AddObjectToList((*iterator));
		(*iterator)->DrawToScreen(window, view_player);
		iterator++;
	}

	/*window.draw(rect_spawn_point);
	for (int i = 0; i < listRectSpawn.size(); i++)
	{
		if (!listSpawnActivated[i])
		{
			window.draw(listRectSpawn[i]);
		}
	}*/
}

void MonsterGenerator::FirstDrawToScreen(TextGenerator &text_generator, sf::RenderWindow &window, sf::View &view_player)
{
}

void MonsterGenerator::ClearSpawns()
{
	std::list<std::shared_ptr<MonsterBase>>::iterator i = listMonster.begin();
	while (i != listMonster.end())
	{
		(*i)->SetToDelete();
		listMonster.erase(i++);
	}
	listSpawnLocation.clear();
	listSpawnClock.clear();
	listSpawnMonsterQuantity.clear();
	listSpawnClockTimer.clear();
	listSpawnMonsterEliteQuantity.clear();

	ritual_started = false;
	number_guardian_alive = 0;
}

sf::Vector2f MonsterGenerator::GetNewPositionMonster(int id_spawn)
{
	sf::Vector2f location_spawn = listSpawnLocation[id_spawn];
	sf::Vector2f position_monster;
	if (location_spawn.x + size_spawn - 50 < size_current_map.x)
	{
		if (location_spawn.y + size_spawn - 50 < size_current_map.y)
		{
			position_monster = location_spawn + sf::Vector2f(GlobalFunction::getRandomRange(50, size_spawn - 50), GlobalFunction::getRandomRange(50, size_spawn - 50));
		}
		else
		{
			position_monster = location_spawn + sf::Vector2f(GlobalFunction::getRandomRange(50, size_spawn - 50), GlobalFunction::getRandomRange(50, size_current_map.y - location_spawn.y - 50));
		}
	}
	else
	{
		if (location_spawn.y + size_spawn - 50 < size_current_map.y)
		{
position_monster = location_spawn + sf::Vector2f(GlobalFunction::getRandomRange(50, size_current_map.x - location_spawn.x - 50), GlobalFunction::getRandomRange(50, size_spawn - 50));
		}
		else
		{
			position_monster = location_spawn + sf::Vector2f(GlobalFunction::getRandomRange(50, size_current_map.x - location_spawn.x - 50), GlobalFunction::getRandomRange(50, size_current_map.y - location_spawn.y - 50));
		}
	}
	return position_monster;
}

void MonsterGenerator::StartRitual(sf::Vector2f position_player)
{
	if (!ritual_started)
	{
		for (int i = 0; i < 3; i++)
		{
			std::vector<int> listExceptions{ SquidChildEnum + 1,DummyEnum + 1 , BombyEnum+1, SquidEnum + 1};
			int type_monster_created = GlobalFunction::getRandomRangeWithUnknownException(1, number_type_monsters, listExceptions) - 1;

			sf::Vector2f position_monster;
			float angle = GlobalFunction::getRandomRange(1, 360);
			sf::Vector2f position_to_add{ static_cast<float>(-(cos((GlobalFunction::AddAngleToAngle( angle, 120 * i)) * PI / 180))*guardian_distance_from_player), static_cast<float>(-(sin((GlobalFunction::AddAngleToAngle(angle, 120 * i)) * PI / 180))*guardian_distance_from_player) };
			position_monster = position_to_add + position_player;

			int monster_level = (1 - (std::ceil(GlobalFunction::GetDistanceBetweenTwoPositions(position_monster, center_map)) / map_width)) * 11 + 10 * (level_map - 1);
			if (monster_level <= 0)
			{
				monster_level = 1;
			}

			SpawnSpecificMonster(type_monster_created, position_monster, sf::Vector2f(0, 0), -1, 0, monster_level, true, true);
			number_guardian_alive++;
		}
		ritual_started = true;
	}
}

void MonsterGenerator::SpawnRandomMonsterAroundArea(sf::Vector2f position, int number_monsters)
{
	for (int i = 0; i < number_monsters; i++)
	{
		sf::Vector2f position_to_add;

		if (GlobalFunction::getRandomRange(1, 1000) < 500)
		{
			position.x = GlobalFunction::getRandomRange(150, 500);
		}
		else
		{
			position.x = -GlobalFunction::getRandomRange(150, 500);
		}


		if (GlobalFunction::getRandomRange(1, 1000) < 500)
		{
			position.y = GlobalFunction::getRandomRange(150, 500);
		}
		else
		{
			position.y = -GlobalFunction::getRandomRange(150, 500);
		}

		sf::Vector2f position_monster = position_to_add + position;
		std::vector<int> listExceptions{ SquidChildEnum + 1,DummyEnum + 1 };
		int type_monster_created = GlobalFunction::getRandomRangeWithUnknownException(1, number_type_monsters, listExceptions) - 1;
		int monster_level = (1 - (std::ceil(GlobalFunction::GetDistanceBetweenTwoPositions(position_monster, center_map)) / map_width)) * 11 + 10 * (level_map - 1);
		if (monster_level <= 0)
		{
			monster_level = 1;
		}

		SpawnSpecificMonster(type_monster_created, position_monster, sf::Vector2f(0, 0), -1, 0, monster_level, false, false);
	}
}

void MonsterGenerator::SpawnMonsterInEachSpawn(int number_monsters)
{
	for (int i = 0; i < number_monsters; i++)
	{
		for (int i_spawn = 0; i_spawn < listSpawnLocation.size(); i_spawn++)
		{
			std::vector<int> listExceptions{ SquidChildEnum + 1,DummyEnum + 1 };
			int type_monster_created = GlobalFunction::getRandomRangeWithUnknownException(1, number_type_monsters, listExceptions) - 1;
			sf::Vector2f location_spawn = listSpawnLocation[i_spawn];
			sf::Vector2f position_monster = GetNewPositionMonster(i_spawn);

			int monster_level = (1 - (std::ceil(GlobalFunction::GetDistanceBetweenTwoPositions(position_monster, center_map)) / map_width)) * 11 + 10 * (level_map - 1);
			if (monster_level == 0)
			{
				monster_level = 1;
			}

			SpawnSpecificMonster(type_monster_created, position_monster, location_spawn, i_spawn, size_spawn, monster_level, false, false);

			listSpawnClock[i_spawn].restart();
			listSpawnClockTimer[i_spawn] = timer_spawn_normal;
			listSpawnMonsterQuantity[i_spawn]++;
		}
	}
}

std::shared_ptr<MonsterBase> MonsterGenerator::GetMonsterCloserToPosition(sf::Vector2f position)
{
	std::shared_ptr<MonsterBase> closest_monster;
	float smallest_distance = 10000;
	std::list<std::shared_ptr<MonsterBase>>::iterator iterator = listActivatedMonster.begin();
	while (iterator != listActivatedMonster.end())
	{
		float distance = GlobalFunction::GetDistanceBetweenTwoPositions((*iterator)->GetCurrentPosition(), position);
		if (distance < smallest_distance)
		{
			smallest_distance = distance;
			closest_monster = (*iterator);
		}
		iterator++;
	} 

	return closest_monster;
}