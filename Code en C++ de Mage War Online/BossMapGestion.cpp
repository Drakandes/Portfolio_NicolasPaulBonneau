#include "stdafx.h"
#include "BossMapGestion.h"

BossMapGestion::BossMapGestion()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font boss map gestion interface" << std::endl;
	}

	text_countdown = GlobalFunction::CreateText(sf::Vector2f(0, 0), "Countdown", font, 40);

	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<Viking> monster = std::shared_ptr<Viking>(new Viking());
		monster->Init(ListObjectsSingleton::instance()->GetNewID(), sf::Vector2f(2335, 1550));
		boss.push_back(monster);
		monster.reset();
		boss[i].reset();
	}
}

BossMapGestion::~BossMapGestion()
{
}

std::vector<std::vector<sf::Vector2i>> BossMapGestion::GetBossMap(int type_boss, std::shared_ptr<Player> player)
{
	type_boss_fighting = type_boss;

	std::ifstream openfile;

	if (type_boss == BossViking)
	{
		openfile.open("BossMapViking.txt");
	}
	else if (type_boss == BossMolly)
	{
		openfile.open("BossMapMolly.txt");
	}

	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<std::vector<sf::Vector2i>> map_reverted;
	std::vector<sf::Vector2i> tempmap;
	sf::Vector2i counter(0,0);

	if (openfile.is_open())
	{
		while (!openfile.eof())
		{
			std::string str;
			std::string value;
			std::getline(openfile, str);
			std::stringstream stream(str);
			counter.x = 0;
			while (std::getline(stream, value, ' '))
			{
				if (value.length() > 0)
				{
					std::string xx = value.substr(0, value.find(","));
					std::string yy = value.substr(value.find(",") + 1);

					int x, y, i, j;

					for (i = 0; i < xx.length(); i++)
					{
						if (!isdigit(xx[i]))
						{
							break;
						}
					}

					for (j = 0; j < yy.length(); j++)
					{
						if (!isdigit(yy[j]))
						{
							break;
						}
					}

					x = (i == xx.length()) ? atoi(xx.c_str()) : -1;
y = (i == yy.length()) ? atoi(yy.c_str()) : -1;

tempmap.push_back(sf::Vector2i(x, y));
counter.x++;
				}
			}

			for (int i = 0; i < 20; i++)
			{
				tempmap.push_back(sf::Vector2i(-1, -1));
				counter.x++;
			}

			map.push_back(tempmap);
			tempmap.clear();
			counter.y++;
		}
	}

	map_tile_size = counter;

	for (int x = 0; x < counter.x; ++x)
	{
		std::vector<sf::Vector2i> tempmap_reverted;
		std::vector<bool> tile_boolean;
		for (int y = 0; y < counter.y; ++y)
		{
			sf::Vector2i tile = map[y][x];
			tempmap_reverted.push_back(tile);
			tile_boolean.push_back(false);
		}
		map_reverted.push_back(tempmap_reverted);
		ListIfDeathTile.push_back(tile_boolean);
	}

	CreateInvisibleWall(map_reverted);
	CreatePillars(player);

	return map_reverted;
}

void BossMapGestion::CreatePillars(std::shared_ptr<Player> player)
{
	if (type_boss_fighting == BossViking)
	{
		if (true)
		{
			std::shared_ptr<VikingPillar> pillar = std::shared_ptr<VikingPillar>(new VikingPillar());
			pillar->Init(sf::Vector2f(2797, 2086), true, false, player);
			MainQuadtree::instance()->insert(pillar->GetCurrentPosition(), pillar->GetSize(), pillar);
			ProjectileGestion::instance()->AddObjectToList(pillar);
			listPillars.push_back(pillar);
			pillar.reset();
		}

		if (true)
		{
			std::shared_ptr<VikingPillar> pillar = std::shared_ptr<VikingPillar>(new VikingPillar());
			pillar->Init(sf::Vector2f(1880, 2086), true, false, player);
			MainQuadtree::instance()->insert(pillar->GetCurrentPosition(), pillar->GetSize(), pillar);
			ProjectileGestion::instance()->AddObjectToList(pillar);
			listPillars.push_back(pillar);
			pillar.reset();
		}

		if (true)
		{
			std::shared_ptr<VikingPillar> pillar = std::shared_ptr<VikingPillar>(new VikingPillar());
			pillar->Init(sf::Vector2f(3169, 1892), true, false, player);
			MainQuadtree::instance()->insert(pillar->GetCurrentPosition(), pillar->GetSize(), pillar);
			ProjectileGestion::instance()->AddObjectToList(pillar);
			listPillars.push_back(pillar);
			pillar.reset();
		}

		if (true)
		{
			std::shared_ptr<VikingPillar> pillar = std::shared_ptr<VikingPillar>(new VikingPillar());
			pillar->Init(sf::Vector2f(1500, 1892), true, false, player);
			MainQuadtree::instance()->insert(pillar->GetCurrentPosition(), pillar->GetSize(), pillar);
			ProjectileGestion::instance()->AddObjectToList(pillar);
			listPillars.push_back(pillar);
			pillar.reset();
		}
	}
	else if (type_boss_fighting == BossMolly)
	{
		sf::Vector2i counter;
		for (int i = 0; i < 15; i++)
		{
			std::shared_ptr<MollyPillar> pillar = std::shared_ptr<MollyPillar>(new MollyPillar());
			pillar->Init(sf::Vector2f(1700 + 350 * counter.x, 1800 + counter.y * 350) + GlobalFunction::GetRandomVectorBetweenRange(150), true, false, player);
			MainQuadtree::instance()->insert(pillar->GetCurrentPosition(), pillar->GetSize(), pillar);
			ProjectileGestion::instance()->AddObjectToList(pillar);
			listPillars.push_back(pillar);
			pillar.reset();

			counter.x++;

			if (counter.x == 5)
			{
				counter.x = 0;
				counter.y++;
			}
		}
	}
}

void BossMapGestion::CreateInvisibleWall(std::vector<std::vector<sf::Vector2i>> map)
{
	for (int i = 1; i < map_tile_size.x - 1; i++)
	{
		for (int j = 1; j < map_tile_size.y - 1; j++)
		{
			if (map[i][j] == sf::Vector2i(-1 ,- 1) || map[i][j] == sf::Vector2i(0, 1) || map[i][j] == sf::Vector2i(5, 1) || map[i][j] == sf::Vector2i(3, 2) || map[i][j] == sf::Vector2i(2, 2) || map[i][j] == sf::Vector2i(1, 1) || map[i][j] == sf::Vector2i(4, 1) || map[i][j] == sf::Vector2i(0, 0) || map[i][j] == sf::Vector2i(5, 0))
			{
				if (map[i - 1][j] != sf::Vector2i(-1, -1))
				{
					ListPositionInvisibleWall.push_back(sf::Vector2f(i*TILESIZE, j*TILESIZE));
				}
				else if (map[i + 1][j] != sf::Vector2i(-1, -1))
				{
					ListPositionInvisibleWall.push_back(sf::Vector2f(i*TILESIZE, j*TILESIZE));
				}
				else if (map[i + 1][j - 1] != sf::Vector2i(-1, -1))
				{
					ListPositionInvisibleWall.push_back(sf::Vector2f(i*TILESIZE, j*TILESIZE));
				}
				else if (map[i][j - 1] != sf::Vector2i(-1, -1))
				{
					ListPositionInvisibleWall.push_back(sf::Vector2f(i*TILESIZE, j*TILESIZE));
				}
				else if (map[i - 1][j - 1] != sf::Vector2i(-1, -1))
				{
					ListPositionInvisibleWall.push_back(sf::Vector2f(i*TILESIZE, j*TILESIZE));
				}
				else if (map[i + 1][j + 1] != sf::Vector2i(-1, -1))
				{
					ListPositionInvisibleWall.push_back(sf::Vector2f(i*TILESIZE, j*TILESIZE));
				}
				else if (map[i][j + 1] != sf::Vector2i(-1, -1))
				{
					ListPositionInvisibleWall.push_back(sf::Vector2f(i*TILESIZE, j*TILESIZE));
				}
				else if (map[i - 1][j + 1] != sf::Vector2i(-1, -1))
				{
					ListPositionInvisibleWall.push_back(sf::Vector2f(i*TILESIZE, j*TILESIZE));
				}
				else if(map[i][j] == sf::Vector2i(-1,-1))
				{
					ListIfDeathTile[i][j] = true;
				}
			}
			else if (map[i][j] == sf::Vector2i(-1, -1))
			{
				ListIfDeathTile[i][j] = true;
			}
		}
	}

	for (int i = 0; i < ListPositionInvisibleWall.size(); i++)
	{
		sf::RectangleShape wall = GlobalFunction::CreateRectangle(sf::Vector2f(TILESIZE, TILESIZE), ListPositionInvisibleWall[i]);
		wall.setFillColor(sf::Color::Red);
		ListInvisibleWall.push_back(wall);
	}
}

void BossMapGestion::StartBossFight(int type_boss)
{
	can_check_defeated = true;
	defeated = false;
	boss_fight_started = true;
	showing_countdown = true;
	counter_countdown = 0;
	clock_duration_fight.restart();

	type_boss_fighting = type_boss;

	switch (type_boss)
	{
	case BossViking:
	{		
	boss[0].reset();
	std::shared_ptr<Viking> monster = std::shared_ptr<Viking>(new Viking());
	monster->Init(ListObjectsSingleton::instance()->GetNewID(), sf::Vector2f(2335, 1550));
	MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
	boss[0] = monster;
	monster.reset();
	break;
	}
	
	case BossMolly:
	{
		if (true)
		{
			boss[0].reset();
			std::shared_ptr<Molly> monster = std::shared_ptr<Molly>(new Molly());
			monster->Init(ListObjectsSingleton::instance()->GetNewID(), sf::Vector2f(2335, 1550));
			MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
			boss[0] = monster;
			monster.reset();
		}

		if (true)
		{
			boss[1].reset();
			std::shared_ptr<Molly> monster = std::shared_ptr<Molly>(new Molly());
			monster->Init(ListObjectsSingleton::instance()->GetNewID(), sf::Vector2f(2500, 1800));
			MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
			boss[1] = monster;
			monster.reset();
		}

		if (true)
		{
			boss[2].reset();
			std::shared_ptr<Molly> monster = std::shared_ptr<Molly>(new Molly());
			monster->Init(ListObjectsSingleton::instance()->GetNewID(), sf::Vector2f(1600, 2200));
			MainQuadtree::instance()->insert(monster->GetCurrentPosition(), monster->GetSize(), monster);
			boss[2] = monster;
			monster.reset();
		}
		break;
	}
	}
}

void BossMapGestion::UpdateBossFight(std::shared_ptr<Player> player, float DELTATIME, sf::Vector2f position_view_player, TextGenerator &text_generator)
{
	if (showing_countdown)
	{
		if (counter_countdown == timer_countdown)
		{
			text_countdown.setString("FIGHT!");
			showing_countdown = false;
			fighting = true;
		}
		else if (clock_duration_fight.getElapsedTime().asSeconds() >= counter_countdown)
		{
			sf::String str = "Starting the fight in ... ";
			str = GlobalFunction::InsertNumberToString(str, timer_countdown - counter_countdown, str.getSize());
			text_countdown.setString(str);

			counter_countdown++;
		}

		sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();
		text_countdown.setPosition(position_view_player + sf::Vector2f(window_size.x / 2, window_size.y / 2 - 200));
		sf::FloatRect rect_text = text_countdown.getGlobalBounds();
		text_countdown.setOrigin(rect_text.width / 2, rect_text.height / 2);
	}

	if (fighting)
	{
		for (int i = 0; i < boss.size(); i++)
		{
			if (boss[i] != NULL)
			{
				sf::Vector2f monster_position = boss[i]->GetCurrentPosition();
				Minimap::instance()->AddPosition(boss[i]->GetCurrentPosition(), Monster_E);

				MainQuadtree::instance()->insert(monster_position, boss[i]->GetSize(), boss[i]);

				boss[i]->Update(player->GetCurrentPosition(), player->GetMovementSpeed(), player->GetCurrentPosition(), DELTATIME, player->GetVelocityPlayer());

				float damage_ignition = boss[i]->DamageFromAllIgnition();
				if (damage_ignition > 0)
				{
					sf::String str = "-";
					str = GlobalFunction::InsertNumberToString(str, boss[i]->GotDamaged(damage_ignition, -1, 0), str.getSize());
					TextGenerator::instance()->GenerateOneTextStringAndColor(monster_position, str, boss[i]->GetSize(), sf::Color::White, boss[i]);
				}

				bool isNeedToDelete = boss[i]->IsNeedToDelete();
				if (isNeedToDelete)
				{

#pragma region ExperienceGiven
					float exp_received = boss[i]->GetExp();
					float exp_bonus = player->GetBonusExperiencePercent();
					exp_received += exp_received*exp_bonus / 100;

					float level_player = player->GetPlayerLevel() * 5;
					float level_monster = boss[i]->GetLevelMonster();
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

					float money_given = boss[i]->GetMoney();
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

					sf::Vector2f monster_fragments_loot = boss[i]->GetTypeAndNumberFragments();
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

					text_generator.GenerateOneTextPlayerColorSpecified(player->GetCurrentPosition(), exp_received, player->GetSize(), sf::Color::Blue, player);
					CreateNotice(exp_received, money_given, monster_fragments_loot);

					player->MonsterKilledGestion(true);

					boss[i].reset();
				}
			}
		}
	}

	if (boss_fight_started)
	{
		CheckCollisionWithInvisibleWall(player);
	}

	if (can_check_defeated)
	{
		int counter = 0;
		for (int i = 0; i < boss.size(); i++)
		{
			if (boss[i] == NULL)
			{
				counter++;
			}
		}
		if (counter == boss.size())
		{
			FightOver(true, player);
			defeated = true;
			can_check_defeated = false;
		}
	}
}

void BossMapGestion::DrawBoss()
{
	if (boss_fight_started)
	{
		for (int i = 0; i < boss.size(); i++)
		{
			if (boss[i] != NULL)
			{
				DrawGestion::instance()->AddObjectToList(boss[i]);
			}
		}
	}

	if (showing_countdown)
	{

	}
}

void BossMapGestion::CheckCollisionWithInvisibleWall(std::shared_ptr<Player> player)
{
	sf::FloatRect rect_collision_player = player->GetCollisionRect();

	for (int i = 0; i < ListInvisibleWall.size(); i++)
	{
		sf::FloatRect rect_collision_wall = ListInvisibleWall[i].getGlobalBounds();

		if (rect_collision_player.intersects(rect_collision_wall))
		{
			sf::Vector2f position_player = player->GetCurrentPosition();
			sf::Vector2f center_position_wall = ListInvisibleWall[i].getPosition() + sf::Vector2f(TILESIZE / 2, TILESIZE / 2);

			float angle = GlobalFunction::GetRotationBetweenTwoPositions(center_position_wall, position_player);
			float distance_from_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, center_position_wall);

			position_player = GlobalFunction::AddDistanceWithAngleToVector(position_player, TILESIZE  + 20, angle);
			player->TeleportEntity(position_player, 0);
		}
	}

	if (clock_death_tile.getElapsedTime().asSeconds() >= 0.25)
	{
		sf::Vector2f temp_position_player = player->GetCurrentPosition();
		sf::Vector2i counter(0, 0);
		while (temp_position_player.x > TILESIZE)
		{
			counter.x++;
			temp_position_player.x -= TILESIZE;
		}

		while (temp_position_player.y > TILESIZE)
		{
			counter.y++;
			temp_position_player.y -= TILESIZE;
		}

		if (counter.x >= 0 && counter.x < map_tile_size.x && counter.y >= 0 && counter.y < map_tile_size.y)
		{
			if (ListIfDeathTile[counter.x][counter.y])
			{
				player->GotDamaged(damage_death_tile, -1, 100);
			}
		}
		clock_death_tile.restart();
	}

	player.reset();

	if (type_boss_fighting == BossMolly)
	{
		if (clock_collision_wall_boss.getElapsedTime().asSeconds() >= 0.25)
		{
			std::vector<bool> listCheckBossCollision;
			for (int i = 0; i < boss.size(); i++)
			{
				listCheckBossCollision.push_back(true);
			}

			for (int i = 0; i < ListInvisibleWall.size(); i++)
			{
				sf::FloatRect rect_collision_wall = ListInvisibleWall[i].getGlobalBounds();

				for (int i = 0; i < boss.size(); i++)
				{
					if (boss[i] != NULL && listCheckBossCollision[i])
					{
						if (boss[i]->GetCollisionRect().intersects(rect_collision_wall))
						{
							boss[i]->ChangeStunTime(0.8);
							listCheckBossCollision[i] = false;
						}
					}
				}
			}

			clock_collision_wall_boss.restart();
		}

		for (int i = 0; i < listPillars.size(); i++)
		{
			for (int i = 0; i < boss.size(); i++)
			{
				if (boss[i] != NULL)
				{
					if (listPillars[i]->GetCollisionRect().intersects(boss[i]->GetCollisionRect()))
					{
						listPillars[i]->DealWithCollision(boss[i]);
					}
				}
			}
		}
	}
}

void BossMapGestion::DrawBossInterface(sf::RenderWindow &window)
{
	if (showing_countdown)
	{
		window.draw(text_countdown);
	}
}

void BossMapGestion::FightOver(bool defeated, std::shared_ptr<Player> player)
{
	counter_countdown = 0;
	ListIfDeathTile.clear();
	ListInvisibleWall.clear();
	ListPositionInvisibleWall.clear();

	map_tile_size = sf::Vector2i(1, 1);
	showing_countdown = false;
	fighting = false;
	boss_fight_started = false;
	type_boss_fighting = NoBoss;

	for (int i = 0; i < boss.size(); i++)
	{
		if (boss[i] != NULL)
		{
			boss[i]->SetToDelete();
			boss[i].reset();
		}
	}
}

void BossMapGestion::CreateNotice(float experience_given, float money_given, sf::Vector2f fragments_given)
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