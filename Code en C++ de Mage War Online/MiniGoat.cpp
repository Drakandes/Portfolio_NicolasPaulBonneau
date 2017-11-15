#include "stdafx.h"
#include "MiniGoat.h"

MiniGoat::MiniGoat()
{
	if(!texture.loadFromFile("MiniGoat.png"))
	{
		std::cout << "Error while loading mini goat texture" << std::endl;
	}
	if (!texture_ignition.loadFromFile("Burning_animation.png"))
	{
		std::cout << "Error: Couldn't load Burning_animation in blob" << std::endl;
	}

	if (!shadow_texture.loadFromFile("MiniGoatShadow.png"))
	{
		std::cout << "Error while loading squid child projectile shadow texture" << std::endl;
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

MiniGoat::~MiniGoat()
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

void MiniGoat::Init(int id_received, sf::Vector2f position_spawn_r, int id_spawn_r, float size_spawn_r, int level_monster_r,sf::Vector2f position_monster, bool is_elite, bool is_monster_guardian)
{
	monster_is_elite = is_elite;
	level_monster = level_monster_r;
	position_of_spawn = position_spawn_r;
	id_spawn = id_spawn_r;
	size_spawn = size_spawn_r;

	float level_monster_float = level_monster;
	damage = DamageIncreaseGestion(damage, level_monster_float);
	monster_maximum_health = HealthIncreaseGestion(monster_maximum_health, level_monster_float);
	armor = ArmorIncreaseGestion(armor, level_monster_float);
	speed_initial = SpeedIncreaseGestion(speed_initial, level_monster_float);

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
		monster_fragments_given = number_base_fragment_given + GlobalFunction::getRandomRange(2, 10);
	}
	else
	{
		monster_fragments_given = number_base_fragment_given - GlobalFunction::getRandomRange(1, 4);
	}

#pragma endregion Fragment

	monster_maximum_health = GlobalFunction::getRandomRangeIfFloat(monster_maximum_health*0.95, monster_maximum_health*1.05);
	damage = GlobalFunction::getRandomRangeIfFloat(damage*0.95, damage*1.05);
	armor = GlobalFunction::getRandomRangeIfFloat(armor*0.95, armor*1.05);
	speed_initial = GlobalFunction::getRandomRangeIfFloat(speed_initial*0.95, speed_initial*1.05); 
	stun_duration = GlobalFunction::getRandomRangeIfFloat(stun_duration*0.95*100, stun_duration*1.05*100)/100;

	is_guardian = is_monster_guardian;
	monster_is_elite = is_elite;
	if (is_elite)
	{
		if (is_guardian)
		{
			texture.loadFromFile("MiniGoatGuardian.png");
		}
		else
		{
			texture.loadFromFile("MiniGoatElite.png");
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

	sf::Vector2f position_origin(position_monster);
	sprite_monster = GlobalFunction::CreateSprite(position_origin, size_monster, texture);
	monster_health = monster_maximum_health;
	monster_alive = true;
	bar_total_health.setFillColor(sf::Color::Black);
	bar_total_health.setOrigin(sf::Vector2f(size_monster.x / 2, 2));
	bar_current_health.setFillColor(sf::Color::Red);
	bar_current_health.setOrigin(sf::Vector2f(size_monster.x / 2, 2));
	id_monster = id_received;
	speed = speed_initial;
	sprite_ignition = GlobalFunction::CreateSprite(sprite_monster.getPosition(), size_sprite_ignition, texture_ignition);
	GetNewPosition();
	timer_speed_modifier_with_sprint = 1;
	stun_bar.setOrigin(0, 2);
	stun_bar.setFillColor(sf::Color::Blue);

	font.loadFromFile("Constantine.ttf");
	string_monster_name = "";
	string_monster_name = GlobalFunction::InsertNumberToString(string_monster_name, level_monster, string_monster_name.getSize());
	string_monster_name.insert(string_monster_name.getSize(), sf::String("   Goat"));
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

void MiniGoat::MonsterEliteInit()
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
	}

	if (listEliteBonus[DividedHealth_E])
	{
		monster_maximum_health = 20 + std::ceil(25 * level_monster / 100);
	}
}

void MiniGoat::MonsterEliteGestion(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, sf::Vector2f velocity_player)
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

sf::Vector2f MiniGoat::GetCurrentPosition()
{
	return sprite_monster.getPosition();
}

void MiniGoat::Update(sf::Vector2f position_to_go, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player)
{

	StunGestion();
	Health_maintenance();
	CuttingSprite();
	if (!monster_is_stunned)
	{
		MovementGestion(player_position, DELTATIME);
	}
	if (monster_is_elite)
	{
		MonsterEliteGestion(player_position, player_speed, player_position, velocity_player);
	}
}

void MiniGoat::Health_maintenance()
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
				if (holder_cutting_position.y == 1)
				{
					DeathAnimationGestion::instance()->Init(sf::Vector2f(60, 40), 11, 0.08, 5, GetCurrentPosition(), "MiniGoatDeath.png");
				}
				else
				{
					DeathAnimationGestion::instance()->Init(sf::Vector2f(60, 40), 11, 0.08, 4, GetCurrentPosition(), "MiniGoatDeath.png");
				}
			}
			else if (monster_is_elite)
			{
				if (holder_cutting_position.y == 1)
				{
					DeathAnimationGestion::instance()->Init(sf::Vector2f(60, 40), 11, 0.08, 3, GetCurrentPosition(), "MiniGoatDeath.png");
				}
				else
				{
					DeathAnimationGestion::instance()->Init(sf::Vector2f(60, 40), 11, 0.08, 2, GetCurrentPosition(), "MiniGoatDeath.png");
				}
			}
			else
			{
				if (holder_cutting_position.y == 1)
				{
					DeathAnimationGestion::instance()->Init(sf::Vector2f(60, 40), 11, 0.08, 1, GetCurrentPosition(), "MiniGoatDeath.png");
				}
				else
				{
					DeathAnimationGestion::instance()->Init(sf::Vector2f(60, 40), 11, 0.08, 0, GetCurrentPosition(), "MiniGoatDeath.png");
				}
			}

			can_drop = true;
			monster_alive = false;
		}
	}

	if (monster_alive)
	{
		sf::Vector2f monster_position = sprite_monster.getPosition();
		bar_total_health.setSize(sf::Vector2f(size_monster.x, 4));
		bar_total_health.setPosition(sf::Vector2f(monster_position.x, monster_position.y - size_monster.y / 2 - 5));

		bar_current_health.setSize(sf::Vector2f(size_monster.x * (monster_health / monster_maximum_health), 4));
		bar_current_health.setPosition(sf::Vector2f(monster_position.x, monster_position.y - size_monster.y / 2 - 5));

		text_monster_name.setPosition(sf::Vector2f(monster_position.x, monster_position.y - size_monster.y / 2 - 20));
	}
}

void MiniGoat::CheckEntityStillInMap()
{
	sf::Vector2f map_limit_maximum = ListObjectsSingleton::instance()->GetMapLimitSizeMaximum();
	sf::Vector2f map_limit_minimum = ListObjectsSingleton::instance()->GetMapLimitSizeMinimum();

	sf::Vector2f position_entity = GetCurrentPosition();

	if (position_entity.x < map_limit_minimum.x)
	{
		position_entity.x = map_limit_minimum.x;
	}
	else if (position_entity.x > map_limit_maximum.x)
	{
		position_entity.x = map_limit_maximum.x;
	}

	if (position_entity.y < map_limit_minimum.y)
	{
		position_entity.y = map_limit_minimum.y;
	}
	else if (position_entity.y > map_limit_maximum.y)
	{
		position_entity.y = map_limit_maximum.y;
	}

	sprite_monster.setPosition(position_entity);
}

void MiniGoat::MovementGestion(sf::Vector2f player_position, float DELTATIME)
{
	if (!being_pushed)
	{
		sf::Vector2f monster_current_position = GetCurrentPosition();
		if (!chasing_player)
		{
			if (monster_is_moving)
			{
				sprite_monster.move(-1 * (cos(angle_going * PI / 180))*speed*DELTATIME, -1 * (sin(angle_going * PI / 180))*speed*DELTATIME);

				float distance_to_objectif = GlobalFunction::GetDistanceBetweenTwoPositions(monster_current_position, position_going_to);
				if (distance_to_objectif <= 5)
				{
					monster_is_moving = false;
					taking_a_breath_after_running = true;
					timer_taking_a_breath_after_running = GlobalFunction::getRandomRange(2, 8) / 4;
					clock_between_new_positition.restart();
				}
			}
			if (taking_a_breath_after_running)
			{
				if (clock_between_new_positition.getElapsedTime().asSeconds() >= timer_taking_a_breath_after_running)
				{
					GetNewPosition();
					taking_a_breath_after_running = false;
				}
			}

			if (GlobalFunction::GetDistanceBetweenTwoPositions(monster_current_position, player_position) <= range_of_view)
			{
				if (GlobalFunction::getRandomRange(1, 1000) <= 3)
				{
					monster_is_moving = true;
					taking_a_breath_after_running = false;
					chasing_player = true;
				}
			}
		}
		else
		{
			position_going_to = player_position;
			angle_going = GetAngle(monster_current_position, position_going_to);
			sprite_monster.move(-1 * (cos(angle_going * PI / 180))*speed*DELTATIME, -1 * (sin(angle_going * PI / 180))*DELTATIME*speed);
			if (monster_current_position.x >= position_going_to.x)
			{
				holder_cutting_position.y = 1;
			}
			else
			{
				holder_cutting_position.y = 0;
			}
			if (clock_while_sprinting.getElapsedTime().asSeconds() >= timer_speed_modifier_with_sprint)
			{
				speed += speed_initial*modifier_speed_while_sprinting / 100;
				clock_while_sprinting.restart();
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

	CheckEntityStillInMap();
}

float MiniGoat::GetDamage()
{
	return damage;
}

bool MiniGoat::CheckIdObject(int id_object)
{
	bool new_object = true;
	int counter = 0;
	std::vector<int>::iterator iterator = ListIdObject.begin();
	while (iterator != ListIdObject.end())
	{
		if ((*iterator) == id_object)
		{
			if (ListClockObject[counter].getElapsedTime().asSeconds() >= reset_timer)
			{
				ListClockObject[counter].restart();
				return true;
			}
			else
			{
				return false;
			}
			new_object = false;
		}
		counter++;
		iterator++;
	}
	if (new_object)
	{
		sf::Clock clock;
		ListClockObject.push_back(clock);
		ListIdObject.push_back(id_object);
	}
	return true;
}

bool MiniGoat::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (CheckIdObject(id_object) && chasing_player)
	{
		if (sprite_monster.getGlobalBounds().intersects(rect_collision))
		{
			clock_between_attack.restart();
			chasing_player = false;
			monster_is_moving = false;
			taking_a_breath_after_running = true;
			speed = speed_initial;
			return true;
		}
	}
	return false;
}

float MiniGoat::GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent)
{
	damage_dealt = damage_dealt*GlobalFunction::GetArmorReductionModifier(armor*(1 - armor_penetration_percent / 100));
	if (damage_dealt > 0)
	{
		if (!listEliteBonus[DividedHealth_E])
		{
			monster_health -= damage_dealt;
			monster_is_moving = true;
			taking_a_breath_after_running = false;
			chasing_player = true;
		}
		else
		{
			damage_dealt = 1;
			monster_health -= damage_dealt;
			monster_health -= damage_dealt;
			monster_is_moving = true;
			taking_a_breath_after_running = false;
			chasing_player = true;
		}
	}
	return damage_dealt;
}

int MiniGoat::GetRayon()
{
	return rayon_of_collision;
}

sf::Vector2f MiniGoat::GetSize()
{
	return size_monster;
}

void MiniGoat::CuttingSprite()
{
	been_drawn = true;
	if (!monster_is_stunned)
	{
		if (clock_between_animation.getElapsedTime().asSeconds() >= time_between_animation)
		{
			if (monster_is_moving)
			{
				sprite_monster.setTextureRect(sf::IntRect(size_monster.x*holder_cutting_position.x, size_monster.y*holder_cutting_position.y, size_monster.x, size_monster.y));
				shadow.setTextureRect(sf::IntRect(size_monster.x*holder_cutting_position.x, size_monster.y*holder_cutting_position.y, size_monster.x, size_monster.y));
				holder_cutting_position.x++;
				if (holder_cutting_position.x == dimension_monster_texture.x)
				{
					holder_cutting_position.x = 1;
				}
			}
			else
			{
				sprite_monster.setTextureRect(sf::IntRect(0, size_monster.y*holder_cutting_position.y, size_monster.x, size_monster.y));
				shadow.setTextureRect(sf::IntRect(0, size_monster.y*holder_cutting_position.y, size_monster.x, size_monster.y));
			}
			clock_between_animation.restart();
		}
	}
}

bool MiniGoat::IsNeedToDelete()
{
	return !monster_alive;
}

int MiniGoat::GetExp()
{
	return exp_given;
}

sf::String MiniGoat::GetMonsterType()
{
	return "MiniGoat";
}

int MiniGoat::GetId()
{
	return id_monster;
}

sf::Vector2f MiniGoat::GetTypeAndNumberFragments()
{
	sf::Vector2f holder{ monster_type_fragment_given,monster_fragments_given };
	return holder;
}

void MiniGoat::FirstDraw(sf::RenderWindow &window)
{

}

void MiniGoat::ModifyMovementSpeedFromPercent(float percent)
{

}

float MiniGoat::ReturnLastNumberPudleTouched()
{
	return 0;
}

void MiniGoat::GetIgnited(int type_ignition, float duration_ignition, float damage_ignition)
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

float MiniGoat::DamageFromAllIgnition()
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

void MiniGoat::CheckIfIgnited()
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

void MiniGoat::IgnitionAnimationGestion()
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

float MiniGoat::GetAngle(sf::Vector2f monster_current_position, sf::Vector2f position_to_go)
{
	float angle;
	if (monster_current_position.x > position_to_go.x && monster_current_position.y < position_to_go.y)
	{
		angle = 270 + ((((atan((monster_current_position.x - position_to_go.x) / (position_to_go.y - monster_current_position.y))) * 180 / PI)));
	}
	else if (monster_current_position.x < position_to_go.x && monster_current_position.y < position_to_go.y)
	{
		angle = 270 + ((atan((monster_current_position.x - position_to_go.x) / (position_to_go.y - monster_current_position.y))) * 180 / PI);
	}
	else if (monster_current_position.x > position_to_go.x && monster_current_position.y > position_to_go.y)
	{
		angle = (90 - ((atan((monster_current_position.x - position_to_go.x) / (monster_current_position.y - position_to_go.y)) * 180 / PI)));
	}
	else if (monster_current_position.x < position_to_go.x && monster_current_position.y > position_to_go.y)
	{
		angle = (180 - (((atan((position_to_go.y - monster_current_position.y) / (monster_current_position.x - position_to_go.x))) * 180 / PI)));
	}
	else if (monster_current_position.x == position_to_go.x && monster_current_position.y <= position_to_go.y)
	{
		angle = 270;
	}
	else if (monster_current_position.x == position_to_go.x && monster_current_position.y >= position_to_go.y)
	{
		angle = 90;
	}
	else if (monster_current_position.y == position_to_go.y && monster_current_position.x >= position_to_go.x)
	{
		angle = 0;
	}
	else if (monster_current_position.y == position_to_go.y && monster_current_position.x <= position_to_go.x)
	{
		angle = 180;
	}
	return angle;
}

void MiniGoat::GetNewPosition()
{
	sf::Vector2f monster_current_position = GetCurrentPosition();
	position_going_to = monster_current_position + sf::Vector2f(GlobalFunction::getRandomRange(25, 125), GlobalFunction::GlobalFunction::getRandomRange(25, 125));

	sf::Vector2f map_limit_maximum = ListObjectsSingleton::instance()->GetMapLimitSizeMaximum();
	sf::Vector2f map_limit_minimum = ListObjectsSingleton::instance()->GetMapLimitSizeMinimum();

	if (position_going_to.x < map_limit_minimum.x)
	{
		position_going_to.x = map_limit_minimum.x + 10;
	}
	else if (position_going_to.x > map_limit_maximum.x)
	{
		position_going_to.x = map_limit_maximum.x -10;
	}

	if (position_going_to.y < map_limit_minimum.y)
	{
		position_going_to.y = map_limit_minimum.y + 10;
	}
	else if (position_going_to.y > map_limit_maximum.y)
	{
		position_going_to.y = map_limit_maximum.y - 10;
	}

	angle_going = GetAngle(monster_current_position, position_going_to);
	monster_is_moving = true;
	if (monster_current_position.x >= position_going_to.x)
	{
		holder_cutting_position.y = 1;
	}
	else
	{
		holder_cutting_position.y = 0;
	}
}

float MiniGoat::GetDurationOfStun()
{
	return stun_duration;
}

#pragma region StunGestion
void MiniGoat::StunGestion()
{
	if (monster_is_stunned)
	{
		if (clock_check_if_still_stunned.getElapsedTime().asSeconds() >= time_being_stunned)
		{
			time_being_stunned = 0;
			monster_is_stunned = false;
			GetNewPosition();
			clock_check_if_still_stunned.restart();
		}
		else
		{
		}
	}
	StunBarGestion();
}

float MiniGoat::GetStunTime()
{
	return time_being_stunned;
}

void MiniGoat::StunBarGestion()
{
	if (monster_is_stunned)
	{
		float size = (1 - (clock_check_if_still_stunned.getElapsedTime().asSeconds() / time_being_stunned)) * size_monster.x;
		stun_bar.setSize(sf::Vector2f(size, 4));
		stun_bar.setPosition(sf::Vector2f(sprite_monster.getPosition().x - bar_total_health.getSize().x / 2, bar_total_health.getPosition().y - bar_total_health.getSize().y / 2 - stun_bar.getSize().y / 2));
	}
}

void MiniGoat::ChangeStunTime(float stun_time_received)
{
	monster_is_stunned = true;
	time_being_stunned = (time_being_stunned > stun_time_received ? time_being_stunned : stun_time_received);
	clock_check_if_still_stunned.restart();
}

bool MiniGoat::IsPlayerStunned()
{
	return monster_is_stunned;
}

#pragma endregion StunGestion

void MiniGoat::GetSlowed(int type_slow, float duration_slow, float percent_slow)
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

void MiniGoat::CalculateMovementSpeedWithSlows()
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

void MiniGoat::GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking)
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

void MiniGoat::Draw(sf::RenderWindow &window)
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

void MiniGoat::DrawShadow(sf::RenderWindow &window)
{
	if (been_drawn)
	{
		shadow.setPosition(sprite_monster.getPosition() + sf::Vector2f(0, size_monster.y / 2 - 3));
		window.draw(shadow);
	}
}

sf::Vector2f MiniGoat::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool MiniGoat::CanStun()
{
	return true;
}

void MiniGoat::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	if (CheckIdObject(id_object) && chasing_player)
	{
		int type_object = object_collided->GetTypeCollisionalObject();
		sf::Vector2f position_self = GetCurrentPosition();
		sf::Vector2f position_objet = object_collided->GetCurrentPosition();
		sf::Vector2f size_object = object_collided->GetSize();

		if (type_object == Player_E)
		{
			clock_between_attack.restart();
			chasing_player = false;
			monster_is_moving = false;
			taking_a_breath_after_running = true;
			speed = speed_initial;

			float damage_dealt = object_collided->GotDamaged(GetDamage(), id_monster, 0);

			if (CanPush())
			{
				object_collided->GetPushedAway(GetDistancePushing(), StrongPush, position_objet, position_self);
			}
			if (CanStun())
			{
				object_collided->ChangeStunTime(GetDurationOfStun());
			}
			if (CanChangeObjectStat())
			{
				for (int i = 0; i < GetNumberObjectStatChange(); i++)
				{
					object_collided->GivePlayerChangeStat(GetObjectStatChanging(i), GetObjectStatChangeDuration(i), GetObjectStatChangValue(i));
				}
			}
		}
	}
}

void MiniGoat::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool MiniGoat::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

void MiniGoat::HealObject(float heal_value)
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


