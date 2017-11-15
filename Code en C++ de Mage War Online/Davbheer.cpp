#include "stdafx.h"
#include "Davbheer.h"

Davbheer::Davbheer()
{
	if (!texture.loadFromFile("Davbheer.1.png"))
	{
		std::cout << "Error while loading Davbheer texture" << std::endl;
	}

	if (!texture_ignition.loadFromFile("Burning_animation.png"))
	{
		std::cout << "Error: Couldn't load Burning_animation in davbheer" << std::endl;
	}

	if (!shadow_texture.loadFromFile("DavbheerShadow.png"))
	{
		std::cout << "Error while loading davbheer projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
	shadow.setOrigin(sf::Vector2f(size_monster.x / 2, 0));

	for (int i = 0; i < number_monster_elite_bonus; i++)
	{
		sf::Clock clock;
		listEliteBonusClock.push_back(clock);
		listEliteBonus.push_back(false);
		listEliteBonusCooldown.push_back(2);
	}
}

Davbheer::~Davbheer()
{
	if (can_drop && GlobalFunction::getRandomRange(1, 1000) <= chance_to_drop_on_thousand)
	{
		std::shared_ptr<LootBag> loot_bag = std::shared_ptr<LootBag>(new LootBag());
		loot_bag->Init(GetCurrentPosition(), ListObjectsSingleton::instance()->GetNewID());
		loot_bag->AddRingToBag(CreateRing(level_monster));
		ProjectileGestion::instance()->AddObjectToList(loot_bag);
		MainQuadtree::instance()->insert(GetCurrentPosition(), loot_bag->GetSize(), loot_bag);
		loot_bag.reset();
	}


}

void Davbheer::Init(int Davbheer_id_received, sf::Vector2f position_spawn_r, int id_spawn_r, float size_spawn_r, int level_monster_r, sf::Vector2f position_monster, bool is_elite, bool is_monster_guardian)
{
	level_monster = level_monster_r;
	position_of_spawn = position_spawn_r;
	id_spawn = id_spawn_r;
	size_spawn = size_spawn_r;

	float level_monster_float = level_monster;
	damage = DamageIncreaseGestion(damage, level_monster_float);
	monster_maximum_health = HealthIncreaseGestion(monster_maximum_health, level_monster_float);
	armor = ArmorIncreaseGestion(armor, level_monster_float);
	speed_initial = SpeedIncreaseGestion(speed_initial, level_monster_float);
	attack_speed = AttackSpeedIncreaseGestion(attack_speed, level_monster_float);

	exp_given = GetExpGiven(level_monster_float);
	money_given = GetMoneyGiven(level_monster_float);

#pragma region Fragment

	if (GlobalFunction::getRandomRange(1, 1000) <= 200 + level_monster*7.5)
	{
		if (GlobalFunction::getRandomRange(1, 1000) <= 150 + level_monster * 8)
		{
			if (GlobalFunction::getRandomRange(1, 1000) <= 100 + level_monster * 8.5)
			{
				monster_type_fragment_given = AncientFragment;
			}
			else
			{
				monster_type_fragment_given = RunicFragment;
			}
		}
		else
		{
			monster_type_fragment_given = EnchantedFragment;
		}
	}
	else
	{
		monster_type_fragment_given = StrongFragment;
	}

	if (GlobalFunction::getRandomRange(1, 1000) <= 499)
	{
		monster_fragments_given = 20 + GlobalFunction::getRandomRange(2, 10);
	}
	else
	{
		monster_fragments_given = 20 - GlobalFunction::getRandomRange(1, 4);
	}

#pragma endregion Fragment

	monster_maximum_health = GlobalFunction::getRandomRangeIfFloat(monster_maximum_health*0.95, monster_maximum_health*1.05);
	damage = GlobalFunction::getRandomRangeIfFloat(damage*0.95, damage*1.05);
	armor = GlobalFunction::getRandomRangeIfFloat(armor*0.95, armor*1.05);
	attack_speed = GlobalFunction::getRandomRangeIfFloat(attack_speed*0.95, attack_speed*1.05);
	speed_initial = GlobalFunction::getRandomRangeIfFloat(speed_initial*0.95, speed_initial*1.05);
	range_of_view = GlobalFunction::getRandomRangeIfFloat(range_of_view*0.95, range_of_view*1.05);

	is_guardian = is_monster_guardian;
	monster_is_elite = is_elite;
	if (is_elite)
	{
		if (is_guardian)
		{
			texture.loadFromFile("DavbheerGuardian.png");
		}
		else
		{
			texture.loadFromFile("DavbheerElite.png");
		}
		MonsterEliteInit();
		exp_given = exp_given * elite_percent_exp / 100;
		money_given = money_given*elite_percent_money / 100;
		monster_fragments_given = monster_fragments_given*elite_percent_fragments / 100;
	}

	int gamemode = ListObjectsSingleton::instance()->GetGameMode();
	//monster_maximum_health = monster_maximum_health*(0.5 + 0.25*gamemode);
	damage = damage*(0.5 + 0.25*gamemode);
	//armor = armor*(0.5 + 0.25*gamemode);

	sprite_monster.setPosition(position_monster);
	sprite_monster.setOrigin(sf::Vector2f(size_monster.x / 2, size_monster.y / 2));
	monster_health = monster_maximum_health;
	monster_alive = true;
	sprite_monster.setTexture(texture);
	bar_total_health.setFillColor(sf::Color::Black);
	bar_total_health.setOrigin(sf::Vector2f(size_monster.x / 2, 2));
	bar_current_health.setFillColor(sf::Color::Red);
	bar_current_health.setOrigin(sf::Vector2f(size_monster.x / 2, 2));
	id_monster = Davbheer_id_received;
	direction_davbheer_going = GlobalFunction::getRandomRangeWithException(0, 4, 2);
	holder_cutting_position.y = direction_davbheer_going;
	speed = speed_initial;
	sprite_ignition = GlobalFunction::CreateSprite(sprite_monster.getPosition(), size_sprite_ignition, texture_ignition);
	stun_bar.setOrigin(0, 2);
	stun_bar.setFillColor(sf::Color::Blue);

	font.loadFromFile("Constantine.ttf");
	string_monster_name = "";
	string_monster_name = GlobalFunction::InsertNumberToString(string_monster_name, level_monster, string_monster_name.getSize());
	string_monster_name.insert(string_monster_name.getSize(), sf::String("   Davbheer"));
	if (monster_is_elite)
	{
		if (is_guardian)
		{
			string_monster_name.insert(string_monster_name.getSize(), sf::String(" Guardian"));
		}
		else
		{
			string_monster_name.insert(string_monster_name.getSize(), sf::String(" (E)"));
		}
	}
	text_monster_name = GlobalFunction::CreateText(sf::Vector2f(0, 0), string_monster_name, font, 13);
	text_monster_name.setStyle(sf::Text::Bold);
}

void Davbheer::MonsterEliteInit()
{
	int number_bonus = GetNumberMonsterEliteBonus(level_monster);

	for (int i = 0; i < number_bonus; i++)
	{
		listEliteBonus[GetRandomMonsterEliteBonus(listEliteBonus)] = true;
	}

	/*for (int i = 0; i < listEliteBonus.size(); i++)
	{
	listEliteBonus[i] = false;
	}
	listEliteBonus[Invisibility_E] = true;*/

	damage = damage*elite_percent_damage / 100;
	monster_maximum_health = monster_maximum_health*elite_percent_health / 100;

	if (listEliteBonus[HastyMonster_E])
	{
		speed_initial = speed_initial*elite_percent_speed / 100;
		attack_speed = attack_speed*elite_percent_attack_speed / 100;
	}

	if (listEliteBonus[DividedHealth_E])
	{
		monster_maximum_health = 20 + std::ceil(25 * level_monster / 100);
	}
}

void Davbheer::MonsterEliteGestion(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, sf::Vector2f velocity_player)
{
	sf::Vector2f monster_position = GetCurrentPosition();

	if (listEliteBonus[Energized_E])
	{
		if (GlobalFunction::GetDistanceBetweenTwoPositions(monster_position, player_position) <= range_of_view)
		{
			if (listEliteBonusClock[Energized_E].getElapsedTime().asSeconds() >= listEliteBonusCooldown[Energized_E])
			{
				float angle_to_player = GlobalFunction::GetRotationBetweenTwoPositions(GetCurrentPosition(), player_position);

				for (int i = 0; i < number_energized_ball; i++)
				{
					std::shared_ptr<EnergizedBall> projectile = std::shared_ptr<EnergizedBall>(new EnergizedBall());
					projectile->Init(monster_position, damage, angle_to_player + (360 / number_energized_ball)*i, id_monster);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();
				}

				listEliteBonusClock[Energized_E].restart();
			}
		}
	}

	if (listEliteBonus[Trap_E])
	{
		if (GlobalFunction::GetDistanceBetweenTwoPositions(monster_position, player_position) <= range_of_view)
		{
			if (listEliteBonusClock[Trap_E].getElapsedTime().asSeconds() >= listEliteBonusCooldown[Trap_E])
			{
				float angle_to_player = GlobalFunction::GetRotationBetweenTwoPositions(GetCurrentPosition(), player_position);

				for (int i = 0; i < number_traps; i++)
				{
					std::shared_ptr<NetProjectile> projectile = std::shared_ptr<NetProjectile>(new NetProjectile());
					projectile->Init(monster_position, damage, angle_to_player - 5 + 10 * i, id_monster);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();
				}

				listEliteBonusCooldown[Trap_E] = GlobalFunction::getRandomRange(90, 140) / 10;
				listEliteBonusClock[Trap_E].restart();
			}
		}
	}

	if (listEliteBonus[HealingOrbs_E])
	{
		if (GlobalFunction::GetDistanceBetweenTwoPositions(monster_position, player_position) <= range_of_view)
		{
			if (listEliteBonusClock[HealingOrbs_E].getElapsedTime().asSeconds() >= listEliteBonusCooldown[HealingOrbs_E])
			{
				sf::Vector2f position_to_add{ static_cast<float>(GlobalFunction::getRandomRange(range_healing_ball.x,range_healing_ball.y)),static_cast<float>(GlobalFunction::getRandomRange(range_healing_ball.x,range_healing_ball.y)) };
				position_to_add.x = GlobalFunction::getRandomRange(1, 1000) > 500 ? position_to_add.x*-1 : position_to_add.x;
				position_to_add.y = GlobalFunction::getRandomRange(1, 1000) > 500 ? position_to_add.y*-1 : position_to_add.y;

				std::shared_ptr<HealingBall> projectile = std::shared_ptr<HealingBall>(new HealingBall());
				projectile->Init(monster_position + position_to_add, damage, id_monster, shared_from_this());
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();

				listEliteBonusCooldown[HealingOrbs_E] = GlobalFunction::getRandomRange(20, 35) / 10;
				listEliteBonusClock[HealingOrbs_E].restart();
			}
		}
	}

	if (listEliteBonus[Scary_E])
	{
		if (GlobalFunction::GetDistanceBetweenTwoPositions(monster_position, player_position) <= rayon_scary_face)
		{
			if (listEliteBonusClock[Scary_E].getElapsedTime().asSeconds() >= listEliteBonusCooldown[Scary_E])
			{
				float angle_to_player = GlobalFunction::GetRotationBetweenTwoPositions(GetCurrentPosition(), player_position);

				std::shared_ptr<ScaryFace> projectile = std::shared_ptr<ScaryFace>(new ScaryFace());
				projectile->Init(monster_position + sf::Vector2f(0, -size_monster.y / 2), id_monster);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();

				listEliteBonusCooldown[Scary_E] = GlobalFunction::getRandomRange(80, 130) / 10;
				listEliteBonusClock[Scary_E].restart();
			}
		}
	}

	if (listEliteBonus[Invisibility_E])
	{
		if (listEliteBonusClock[Invisibility_E].getElapsedTime().asSeconds() >= listEliteBonusCooldown[Invisibility_E])
		{
			if (is_invisible)
			{
				is_invisible = false;
				listEliteBonusCooldown[Invisibility_E] = 1;
				sprite_monster.setColor(sf::Color::Color(255, 255, 255, 45));
				shadow.setColor(sf::Color::Color(255, 255, 255, 45));
				listEliteBonusClock[Invisibility_E].restart();
			}
			else
			{
				is_invisible = true;
				listEliteBonusCooldown[Invisibility_E] = duration_invisibility;
				sprite_monster.setColor(sf::Color::Color(255, 255, 255, 30));
				shadow.setColor(sf::Color::Color(255, 255, 255, 30));
				listEliteBonusClock[Invisibility_E].restart();

			}
		}
	}

	if (listEliteBonus[Teleportation_E])
	{
		if (GlobalFunction::GetDistanceBetweenTwoPositions(monster_position, player_position) <= rayon_scary_face)
		{
			if (listEliteBonusClock[Teleportation_E].getElapsedTime().asSeconds() >= listEliteBonusCooldown[Teleportation_E])
			{
				float angle_to_player = GlobalFunction::GetRotationBetweenTwoPositions(GetCurrentPosition(), player_position);
				sf::Vector2f new_position = player_position;
				if (GlobalFunction::GetDistanceBetweenTwoPositions(player_position, monster_position) > range_teleportation)
				{
					float rotation = GlobalFunction::GetRotationBetweenTwoPositions(player_position, monster_position);
					sf::Vector2f position_to_add = sf::Vector2f(sf::Vector2f((cos(rotation * PI / 180))*range_teleportation, (sin(rotation * PI / 180))*range_teleportation));
					new_position = monster_position + position_to_add;
				}

				sprite_monster.setPosition(new_position);

				listEliteBonusCooldown[Teleportation_E] = GlobalFunction::getRandomRange(90, 160) / 10;
				listEliteBonusClock[Teleportation_E].restart();
			}
		}
	}

	if (listEliteBonus[ElectricShot_E])
	{
		if (GlobalFunction::GetDistanceBetweenTwoPositions(monster_position, player_position) <= range_of_view)
		{
			if (listEliteBonusClock[ElectricShot_E].getElapsedTime().asSeconds() >= listEliteBonusCooldown[ElectricShot_E])
			{
				float distance_to_player = GlobalFunction::GetDistanceBetweenTwoPositions(player_position, monster_position);
				sf::Vector2f position_target = player_position;
				float angle = GlobalFunction::GetRotationBetweenTwoPositions(monster_position, player_position);
				sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(monster_position, position_target, velocity_player, 1000);
				float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_aiming, monster_position);

				std::shared_ptr<Electricity> projectile = std::shared_ptr<Electricity>(new Electricity());
				projectile->Init(monster_position, damage*1.25, angle_aiming, id_monster, shared_from_this());
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();

				listEliteBonusCooldown[ElectricShot_E] = GlobalFunction::getRandomRange(100, 150) / 10;
				listEliteBonusClock[ElectricShot_E].restart();
			}
		}
	}

	if (listEliteBonus[PushImpact_E])
	{
		if (GlobalFunction::GetDistanceBetweenTwoPositions(monster_position, player_position) <= range_of_view)
		{
			if (listEliteBonusClock[PushImpact_E].getElapsedTime().asSeconds() >= listEliteBonusCooldown[PushImpact_E])
			{
				float distance_to_player = GlobalFunction::GetDistanceBetweenTwoPositions(player_position, monster_position);
				sf::Vector2f position_target = player_position;
				float angle = GlobalFunction::GetRotationBetweenTwoPositions(monster_position, player_position);
				sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(monster_position, position_target, velocity_player, 1000);
				float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(monster_position, position_aiming);

				float range_projectile_throwing = GlobalFunction::GetDistanceBetweenTwoPositions(monster_position, position_aiming) + 10;
				float distance_two_entites = GlobalFunction::GetDistanceBetweenTwoPositions(monster_position, position_target);

				if (range_projectile_throwing < distance_two_entites)
				{
					range_projectile_throwing = distance_two_entites;
				}

				sf::Vector2f position_impact = GlobalFunction::AddDistanceWithAngleToVector(monster_position, range_projectile_throwing, angle_aiming);

				std::shared_ptr<PushImpact> projectile = std::shared_ptr<PushImpact>(new PushImpact());
				projectile->Init(position_impact, damage*1.25, id_monster);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();

				listEliteBonusCooldown[PushImpact_E] = GlobalFunction::getRandomRange(50, 90) / 10;
				listEliteBonusClock[PushImpact_E].restart();
			}
		}
	}

	if (listEliteBonus[Regeneration_E])
	{
		if (listEliteBonusClock[Regeneration_E].getElapsedTime().asSeconds() >= 0.5)
		{
			if (monster_health < monster_maximum_health)
			{
				monster_health += monster_maximum_health*elite_percent_regeneration;
			}
			if (monster_health > monster_maximum_health)
			{
				monster_health = monster_maximum_health;
			}
			listEliteBonusClock[Regeneration_E].restart();
		}
	}
}

sf::Vector2f Davbheer::GetCurrentPosition()
{
	return sprite_monster.getPosition();
}

void Davbheer::MovementGestion(float DELTATIME)
{
	if (!being_pushed)
	{
		if (!drinking_a_potion)
		{
			sf::Vector2f davbheer_position = sprite_monster.getPosition();
			if (ready_to_change_direction && !chasing_player)
			{
				int random_number = GlobalFunction::getRandomRange(1, 100);
				if (random_number <= 50 && !(direction_davbheer_going == Standing))
				{
					ready_to_change_direction = false;
				}
				else if (random_number <= 50)
				{
					direction_davbheer_going = GlobalFunction::getRandomRangeWithException(0, 4, 2);
					holder_cutting_position.y = direction_davbheer_going;
					ready_to_change_direction = false;
				}
				else if (random_number > 50 && random_number <= 80)
				{
					direction_davbheer_going = GlobalFunction::getRandomRangeWithException(0, 4, 2);
					holder_cutting_position.y = direction_davbheer_going;
					ready_to_change_direction = false;
				}
				else
				{
					direction_davbheer_going = Standing;
					holder_cutting_position.y = direction_davbheer_going;
					ready_to_change_direction = false;
				}
			}

			sf::Vector2f map_limit_maximum = ListObjectsSingleton::instance()->GetMapLimitSizeMaximum();
			sf::Vector2f map_limit_minimum = ListObjectsSingleton::instance()->GetMapLimitSizeMinimum();

			sf::Vector2f position_entity = GetCurrentPosition();

			if (position_entity.x < map_limit_minimum.x)
			{
				direction_davbheer_going = Standing;
				holder_cutting_position.y = direction_davbheer_going;
				sprite_monster.move(1, 0);
			}
			else if (position_entity.x > map_limit_maximum.x)
			{
				direction_davbheer_going = Standing;
				holder_cutting_position.y = direction_davbheer_going;
				sprite_monster.move(-1, 0);
			}

			else if (position_entity.y < map_limit_minimum.y)
			{
				direction_davbheer_going = Standing;
				holder_cutting_position.y = direction_davbheer_going;
				sprite_monster.move(0, 1);
			}
			else if (position_entity.y > map_limit_maximum.y)
			{
				direction_davbheer_going = Standing;
				holder_cutting_position.y = direction_davbheer_going;
				sprite_monster.move(0, -1);
			}
			else
			{
				if (distance_from_player >= range_davbheer)
				{
					CalculateMovementSpeedWithSlows();
					if (direction_davbheer_going == Up)
					{
						sprite_monster.move(0, -speed*DELTATIME);
					}
					if (direction_davbheer_going == Right)
					{
						sprite_monster.move(speed*DELTATIME, 0);
					}
					if (direction_davbheer_going == Down)
					{
						sprite_monster.move(0, speed*DELTATIME);
					}
					if (direction_davbheer_going == Left)
					{
						sprite_monster.move(-speed*DELTATIME, 0);
					}
				}
			}
		}
	}
	else
	{
		sprite_monster.move(-(cos(push_rotation * PI / 180))*push_speed*DELTATIME*push_force, -(sin(push_rotation * PI / 180))*push_speed*DELTATIME*push_force);
		if (GlobalFunction::GetDistanceBetweenTwoPositions(push_origin, GetCurrentPosition()) >= distance_being_pushed)
		{
			push_force = NoPush;
			distance_being_pushed = 0;
			being_pushed = false;
			push_rotation = 0;
		}
	}
}

float Davbheer::GetDurationOfStun()
{
	return 0;
}

void Davbheer::CuttingSprite()
{
	if (clock_between_animation.getElapsedTime().asSeconds() >= time_between_animation && !drinking_a_potion)
	{
		sprite_monster.setTextureRect(sf::IntRect(holder_cutting_position.x*size_monster.x, holder_cutting_position.y*size_monster.y, size_monster.x, size_monster.y));
		shadow.setTextureRect(sf::IntRect(holder_cutting_position.x*size_monster.x, holder_cutting_position.y*size_monster.y, size_monster.x, size_monster.y));
		holder_cutting_position.x++;
		if (holder_cutting_position.x >= 6 && !(holder_cutting_position.y == Standing))
		{
			ready_to_change_direction = true;
			holder_cutting_position.x = 0;
		}
		else if (holder_cutting_position.x >= 17)
		{
			ready_to_change_direction = true;
			holder_cutting_position.x = 0;
			std::shared_ptr<BottleBeer> bottle_beer = std::shared_ptr<BottleBeer>(new BottleBeer());
			bottle_beer->Init(sprite_monster.getPosition(), angle_going, damage, speed_bottle, 0, id_monster);
			ProjectileGestion::instance()->AddObjectToList(bottle_beer);
			bottle_beer.reset();
			drinking_a_potion = false;
		}
		clock_between_animation.restart();

		if (!been_drawn)
		{
			been_drawn = true;
		}
	}
	else if (clock_between_animation.getElapsedTime().asSeconds() >= time_between_animation)
	{
		sprite_monster.setTextureRect(sf::IntRect(holder_cutting_position.x*size_monster.x, holder_cutting_position.y*size_monster.y, size_monster.x, size_monster.y));
		shadow.setTextureRect(sf::IntRect(holder_cutting_position.x*size_monster.x, holder_cutting_position.y*size_monster.y, size_monster.x, size_monster.y));
		holder_cutting_position.x++;
		if (holder_cutting_position.x >= 17)
		{
			if (!listEliteBonus[Invisibility_E])
			{
				if (is_guardian)
				{
					sprite_monster.setColor(sf::Color::Color(255, 255, 255));
				}
				else if (monster_is_elite)
				{
					sprite_monster.setColor(sf::Color::Color(255, 255, 255));
				}
				else
				{
					sprite_monster.setColor(sf::Color(255, 255, 255, 255));
				}
			}
			ready_to_change_direction = true;
			holder_cutting_position.x = 0;
			drinking_a_potion = false;
			std::shared_ptr<BottleBeer> bottle_beer = std::shared_ptr<BottleBeer>(new BottleBeer());
			bottle_beer->Init(sprite_monster.getPosition(), angle_going, damage, speed_bottle, 0, id_monster);
			ProjectileGestion::instance()->AddObjectToList(bottle_beer);
			bottle_beer.reset();
		}
		clock_between_animation.restart();

		if (!been_drawn)
		{ 
			been_drawn = true;
		}
	}
}

void Davbheer::Update(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player)
{
	distance_from_player = GlobalFunction::GetDistanceBetweenTwoPositions(GetCurrentPosition(), playerPosition);
	StunGestion();
	if (!monster_is_stunned)
	{
		DrinkPotions(playerPosition);
		MovementGestion( DELTATIME);
		ThrowBottle(playerPosition, player_speed, DELTATIME, velocity_player);
		ChasingPlayer(playerPosition, player_speed);
	}
	CuttingSprite();
	Regeneration();
	Health_maintenance();
	if (monster_is_elite)
	{
		MonsterEliteGestion(player_position, player_speed, player_position, velocity_player);
	}
}

void Davbheer::ChasingPlayer(sf::Vector2f playerPosition, float player_speed)
{
	if (!drinking_a_potion)
	{
		if (distance_from_player <= range_of_view)
		{
			chasing_player = true;
			direction_davbheer_going = GlobalFunction::GetDirectionFromAngle(angle_going);
			holder_cutting_position.y = direction_davbheer_going;
		}
		else
		{
			chasing_player = false;
			clock_time_chasing_player.restart();
		}
	}
}

std::vector<float> Davbheer::quad(float a, float b, float c) 
{
	float sol_x = 0;
	float sol_y = 0;

	if (abs(a) < pow(1, -6))
	{
		if (abs(b) < pow(1, -6))
		{
		}
		else
		{
			sol_x = -c / b;
			sol_y = -c / b;
		}
	}
	else
	{
		float disc = b*b - 4 * a * c;
		if (disc >= 0)
		{
			disc = sqrt(disc);
			a = 2 * a;
			sol_x = (-b - disc) / a;
			sol_y = (-b + disc) / a;
		}
	}
	std::vector<float> answer;
	answer.push_back(sol_x);
	answer.push_back(sol_y);
	return answer;
}

void Davbheer::ThrowBottle(sf::Vector2f playerPosition, float player_speed, float DELTATIME, sf::Vector2f velocity_player)
{
	/*sf::Vector2f holder;
	float angle_aiming;
	sf::Vector2f position_aiming_at;
	sf::Vector2f davbheer_position = sprite_monster.getPosition();
	float distance_traveled_by_player = GlobalFunction::GetDistanceBetweenTwoPositions(last_position_player, playerPosition)*60;
	if (last_position_player.x < playerPosition.x)
	{
		holder.x = 1;
	}
	else
	{
		holder.x = -1;
	}
	if(last_position_player.y < playerPosition.y)
	{ 
		holder.y = -1;
	}
	else
	{
		holder.y = 1;
	}*/

	/*position_aiming_at = playerPosition + sf::Vector2f((cos(push_rotation * PI / 180))*(distance_traveled_by_player*holder.x), (sin(push_rotation * PI / 180))*(distance_traveled_by_player*holder.y));
	angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(davbheer_position, position_aiming_at);*/

	sf::Vector2f position_shooter = sprite_monster.getPosition();
	sf::Vector2f position_target = playerPosition;
	angle_going = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, playerPosition);

	if (clock_between_attack.getElapsedTime().asSeconds() >= 1/ attack_speed && !drinking_a_potion)
	{
		if (distance_from_player <= range_davbheer)
		{
			sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, position_target, velocity_player, speed_bottle);
			range_bottle = GlobalFunction::GetDistanceBetweenTwoPositions(position_shooter, position_aiming) + 10;
			float distance_two_entites = GlobalFunction::GetDistanceBetweenTwoPositions(position_shooter, position_target);

			if (range_bottle < distance_two_entites)
			{
				range_bottle = distance_two_entites;
			}

			float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

			std::shared_ptr<BottleBeer> bottle_beer = std::shared_ptr<BottleBeer>(new BottleBeer());
			bottle_beer->Init(position_shooter, angle_aiming, damage, speed_bottle, range_bottle, id_monster);
			ProjectileGestion::instance()->AddObjectToList(bottle_beer);
			clock_between_attack.restart();
			number_of_thrown_beers++;
			bottle_beer.reset();

			SoundGestion::instance()->AddSound("SoundMonsterAttack.wav", 85, false);
		}
	}
	last_position_player = playerPosition;
}

void Davbheer::DrinkPotions(sf::Vector2f player_position)
{
#pragma region AttackSpeedPotion
	if (potions[AttackSpeedPotion] > 0 && potion_can_be_use[AttackSpeedPotion] && number_of_thrown_beers >= 10 && !drinking_a_potion)
	{
		 attack_speed =  attack_speed * 1.5;
		speed_bottle += speed_bottle_modifier;
		potion_can_be_use[AttackSpeedPotion] = false;
		clock_between_potions[AttackSpeedPotion].restart();
		potions[AttackSpeedPotion]--;
		using_a_potion = true;
		drinking_a_potion = true;
		direction_davbheer_going = Standing;
		holder_cutting_position.y = Standing;
		holder_cutting_position.x = 0;
		number_of_thrown_beers = 0;
		sprite_monster.setColor(sf::Color(255, 215, 0, 255));
	}
	if (clock_between_potions[AttackSpeedPotion].getElapsedTime().asSeconds() >= cooldown_potions[AttackSpeedPotion] && !potion_can_be_use[AttackSpeedPotion])
	{
		 attack_speed =  attack_speed / 2;
		speed_bottle -= speed_bottle_modifier;
		potion_can_be_use[AttackSpeedPotion] = true;
		using_a_potion = false;
	}
#pragma endregion AttackSpeedPotion
#pragma region DamagePotion
	if (potions[DamagePotion] > 0 && potion_can_be_use[DamagePotion] && monster_health <= monster_maximum_health / 2 && !drinking_a_potion)
	{
		damage = damage * 2;
		potion_can_be_use[DamagePotion] = false;
		clock_between_potions[DamagePotion].restart();
		potions[DamagePotion]--;
		using_a_potion = true;
		drinking_a_potion = true;
		direction_davbheer_going = Standing;
		holder_cutting_position.y = Standing;
		holder_cutting_position.x = 0;
		sprite_monster.setColor(sf::Color(255, 0, 0, 255));
	}
	if (clock_between_potions[DamagePotion].getElapsedTime().asSeconds() >= cooldown_potions[DamagePotion] && !potion_can_be_use[DamagePotion])
	{
		damage = damage / 2;
		potion_can_be_use[DamagePotion] = true;
		using_a_potion = false;
	}
#pragma endregion DamagePotion
#pragma region MovementPotion
	if (potions[MovementPotion] > 0 && potion_can_be_use[MovementPotion] && clock_time_chasing_player.getElapsedTime().asSeconds() >= 7 && !drinking_a_potion)
	{
		speed += movement_potion_modifier;
		potion_can_be_use[MovementPotion] = false;
		clock_between_potions[MovementPotion].restart();
		potions[MovementPotion]--;
		using_a_potion = true;
		drinking_a_potion = true;
		direction_davbheer_going = Standing;
		holder_cutting_position.y = Standing;
		holder_cutting_position.x = 0;
		sprite_monster.setColor(sf::Color(0, 0, 255, 255));
	}

	if (clock_between_potions[MovementPotion].getElapsedTime().asSeconds() >= cooldown_potions[MovementPotion] && !potion_can_be_use[MovementPotion])
	{
		speed -= movement_potion_modifier;
		potion_can_be_use[MovementPotion] = true;
		using_a_potion = false;
	}
#pragma endregion MovementPotion
#pragma region RegenerationPotion
	if (potions[RegenerationPotion] > 0 && potion_can_be_use[RegenerationPotion] && monster_health <= monster_maximum_health /2 && !drinking_a_potion)
	{
		health_per_second += monster_maximum_health*5/100;
		potion_can_be_use[RegenerationPotion] = false;
		clock_between_potions[RegenerationPotion].restart();
		potions[RegenerationPotion]--;
		using_a_potion = true;
		drinking_a_potion = true;
		direction_davbheer_going = Standing;
		holder_cutting_position.y = Standing;
		holder_cutting_position.x = 0;
		sprite_monster.setColor(sf::Color(0, 255, 0, 255));
	}

	if (clock_between_potions[RegenerationPotion].getElapsedTime().asSeconds() >= cooldown_potions[RegenerationPotion] && !potion_can_be_use[RegenerationPotion])
	{
		health_per_second -= monster_maximum_health * 10 / 100;
		potion_can_be_use[RegenerationPotion] = true;
		using_a_potion = false;
	}
#pragma endregion RegenerationPotion

	if (clock_bottle_regeneration.getElapsedTime().asSeconds() >= regeneration_bottle)
	{
		for (int i = 0; i < potions.size(); i++)
		{
			if (potions[i] == 0)
			{
				potions[i]++;
			}
		}
		clock_bottle_regeneration.restart();
	}
}

void Davbheer::Regeneration()
{
	if (clock_regeneration.getElapsedTime().asSeconds() >= 0.5)
	{
		monster_health += health_per_second/2;
		clock_regeneration.restart();
	}
}

float Davbheer::GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent)
{
	damage_dealt = damage_dealt*GlobalFunction::GetArmorReductionModifier(armor*(1 - armor_penetration_percent / 100));
	if (!drinking_a_potion)
	{
		if (!listEliteBonus[DividedHealth_E])
		{
			if (damage_dealt > 0)
			{
				monster_health -= damage_dealt;
			}
		}
		else
		{
			if (damage_dealt > 0)
			{
				damage_dealt = 1;
				monster_health -= damage_dealt;
			}
		}
	}
	else
	{
		if (!listEliteBonus[DividedHealth_E])
		{
			if (damage_dealt > 0)
			{
				damage_dealt = damage_dealt / 4;
				monster_health -= damage_dealt;
			}
		}
		else
		{
			if (damage_dealt > 0)
			{
				damage_dealt = 1;
				monster_health -= damage_dealt;
			}
		}
	}
	return damage_dealt;
}

int Davbheer::GetRayon()
{
	return rayon_of_collision;
}

sf::Vector2f Davbheer::GetSize()
{
	return size_monster;
}

bool Davbheer::IsNeedToDelete()
{
	if (monster_alive)
	{
		return false;
	}
	if (!monster_alive)
	{
		return true;
	}
}

int Davbheer::GetExp()
{
	return exp_given;
}

sf::String Davbheer::GetMonsterType()
{
	return "Davbheer";
}

int Davbheer::GetId()
{
	return id_monster;
}

sf::Vector2f Davbheer::GetTypeAndNumberFragments()
{
	return sf::Vector2f(monster_type_fragment_given,monster_fragments_given);
}

void Davbheer::FirstDraw(sf::RenderWindow &window)
{

}

void Davbheer::Health_maintenance()
{
	if (monster_health <= 0)
	{
		if (listEliteBonus[SecondLife_E])
		{
			listEliteBonus[SecondLife_E] = false;
			monster_health = monster_maximum_health;
		}
		else
		{
			if (is_guardian)
			{
				DeathAnimationGestion::instance()->Init(sf::Vector2f(42, 60), 27, 0.08, 0, GetCurrentPosition(), "DavbheerDeath.png");
			}
			else if (monster_is_elite)
			{
				DeathAnimationGestion::instance()->Init(sf::Vector2f(42, 60), 27, 0.08, 1, GetCurrentPosition(), "DavbheerDeath.png");
			}
			else
			{
				DeathAnimationGestion::instance()->Init(sf::Vector2f(42, 60), 27, 0.08, 2, GetCurrentPosition(), "DavbheerDeath.png");
			}

			can_drop = true;
			monster_alive = false;
		}
	}

	if (monster_alive)
	{
		sf::Vector2f davbheer_position = sprite_monster.getPosition();
		bar_total_health.setSize(sf::Vector2f(size_monster.x, 4));
		bar_total_health.setPosition(sf::Vector2f(davbheer_position.x, davbheer_position.y - size_monster.y / 2 - 5));

		bar_current_health.setSize(sf::Vector2f(size_monster.x * (monster_health / monster_maximum_health), 4));
		bar_current_health.setPosition(sf::Vector2f(davbheer_position.x, davbheer_position.y - size_monster.y / 2 - 5));

		text_monster_name.setPosition(sf::Vector2f(davbheer_position.x, davbheer_position.y - size_monster.y / 2 - 20));
	}
}

void Davbheer::GetIgnited(int type_ignition, float duration_ignition, float damage_ignition)
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

float Davbheer::DamageFromAllIgnition()
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
	return damage_from_all_ignition;
}

void Davbheer::CheckIfIgnited()
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

void Davbheer::IgnitionAnimationGestion()
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

void Davbheer::GetSlowed(int type_slow, float duration_slow, float percent_slow)
{
	bool can_be_slowed = true;

	if (type_slow == TranquilizerTalentSlow_E)
	{
		std::list<int>::iterator iterator_type = TypeSlow.begin();
		std::list<sf::Clock>::iterator iterator_clock = ClockSlow.begin();
		while (iterator_type != TypeSlow.end())
		{
			if ((*iterator_type) == TranquilizerTalentSlow_E)
			{

				(*iterator_clock).restart();
				can_be_slowed = false;
				break;
			}
			iterator_type++;
			iterator_clock++;
		}
	}
	if (can_be_slowed)
	{
		TypeSlow.push_back(type_slow);
		DurationSlow.push_back(duration_slow);
		PercentSlow.push_back(percent_slow);
		sf::Clock clock_;
		ClockSlow.push_back(clock_);
	}
}

void Davbheer::CalculateMovementSpeedWithSlows()
{
	float percent_all_slow = 1;

	std::list<int>::iterator iterator_type = TypeSlow.begin();
	std::list<float>::iterator iterator_duration = DurationSlow.begin();
	std::list<float>::iterator iterator_percent = PercentSlow.begin();
	std::list<sf::Clock>::iterator iterator_clock = ClockSlow.begin();
	while (iterator_duration != DurationSlow.end())
	{
		if ((*iterator_clock).getElapsedTime().asSeconds() <= (*iterator_duration))
		{
			percent_all_slow = percent_all_slow*(1 - ((*iterator_percent) / 100));
			iterator_duration++;
			iterator_type++;
			iterator_percent++;
			iterator_clock++;
		}
		else
		{
			DurationSlow.erase(iterator_duration++);
			TypeSlow.erase(iterator_type++);
			PercentSlow.erase(iterator_percent++);
			ClockSlow.erase(iterator_clock++);
		}
	}
	speed += last_slow_percent;
	float slow_applied = (1 - (percent_all_slow))*speed;
	if (slow_applied > speed)
	{
		slow_applied = speed;
	}
	speed -= slow_applied;
	last_slow_percent = slow_applied;
}

#pragma region StunGestion
void Davbheer::StunGestion()
{
	if (monster_is_stunned)
	{
		if (clock_check_if_still_stunned.getElapsedTime().asSeconds() >= time_being_stunned)
		{
			time_being_stunned = 0;
			monster_is_stunned = false;
			clock_check_if_still_stunned.restart();
		}
		else
		{
			holder_cutting_position.x = 0;
			holder_cutting_position.y = Standing;
		}
	}
	StunBarGestion();
}

float Davbheer::GetStunTime()
{
	return time_being_stunned;
}

void Davbheer::StunBarGestion()
{
	if (monster_is_stunned)
	{
		float size = (1 - (clock_check_if_still_stunned.getElapsedTime().asSeconds() / time_being_stunned)) * size_monster.x;
		stun_bar.setSize(sf::Vector2f(size, 4));
		stun_bar.setPosition(sf::Vector2f(sprite_monster.getPosition().x - bar_total_health.getSize().x / 2, bar_total_health.getPosition().y - bar_total_health.getSize().y / 2 - stun_bar.getSize().y / 2));
	}
}

void Davbheer::ChangeStunTime(float stun_time_received)
{
	monster_is_stunned = true;
	time_being_stunned = (time_being_stunned > stun_time_received ? time_being_stunned : stun_time_received);
	clock_check_if_still_stunned.restart();
}

bool Davbheer::IsPlayerStunned()
{
	return monster_is_stunned;
}

#pragma endregion StunGestion

void Davbheer::GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking)
{
	if (push_force < force_of_pushing)
	{
		sf::Vector2f position_monster = GetCurrentPosition();
		if (GlobalFunction::GetDistanceBetweenTwoPositions(origin_of_propulsion_receveid, position_monster) < distance_being_pushed_received)
		{
			distance_being_pushed = distance_being_pushed_received;
			being_pushed = true;
			push_force = force_of_pushing;
			push_origin = origin_of_propulsion_receveid;
			push_rotation = GlobalFunction::GetRotationBetweenTwoPositions(origin_object_blocking, position_monster);
		}
	}
}

void Davbheer::Draw(sf::RenderWindow &window)
{
	if (been_drawn)
	{
		window.draw(sprite_monster);
		if (!is_invisible)
		{
			window.draw(bar_total_health);
			window.draw(bar_current_health);
			window.draw(text_monster_name);

			CheckIfIgnited();
			if (is_ignite)
			{
				window.draw(sprite_ignition);
			}
			if (monster_is_stunned)
			{
				window.draw(stun_bar);
			}
		}
	}
}

void Davbheer::DrawShadow(sf::RenderWindow &window)
{
	if (been_drawn)
	{
		shadow.setPosition(sprite_monster.getPosition() + sf::Vector2f(0, size_monster.y / 2));
		window.draw(shadow);
	}
}

void Davbheer::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Davbheer::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

sf::Vector2f Davbheer::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

void Davbheer::HealObject(float heal_value)
{
	if (!listEliteBonus[DividedHealth_E])
	{
		monster_health += heal_value;
		if (monster_health > monster_maximum_health)
		{
			monster_health = monster_maximum_health;
		}
	}
	else
	{
		monster_health += 2;
		if (monster_health > monster_maximum_health)
		{
			monster_health = monster_maximum_health;
		}
	}
}

