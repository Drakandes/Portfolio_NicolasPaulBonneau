#include "stdafx.h"
#include "Penguin.h"

Penguin::Penguin()
{
	if (!texture.loadFromFile("Penguin.png"))
	{
		std::cout << "Error while loading mini goat texture" << std::endl;
	}
	if (!texture_ignition.loadFromFile("Burning_animation.png"))
	{
		std::cout << "Error: Couldn't load Burning_animation in blob" << std::endl;
	}

	if (!shadow_texture.loadFromFile("PenguinShadow.png"))
	{
		std::cout << "Error while loading penguin projectile shadow texture" << std::endl;
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

Penguin::~Penguin()
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

void Penguin::Init(int id_received, sf::Vector2f position_spawn_r, int id_spawn_r, float size_spawn_r, int level_monster_r, sf::Vector2f position_monster, bool is_elite, bool is_monster_guardian)
{
	monster_is_elite = is_elite;
	level_monster = level_monster_r;
	position_of_spawn = position_spawn_r;
	id_spawn = id_spawn_r;
	size_spawn = size_spawn_r;

	float level_monster_float = level_monster;
	damage_while_raging = DamageIncreaseGestion(damage_while_raging, level_monster_float);
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
	damage_normal = GlobalFunction::getRandomRangeIfFloat(damage_normal*0.95, damage_normal*1.05);
	damage_while_raging = GlobalFunction::getRandomRangeIfFloat(damage_while_raging*0.95, damage_while_raging*1.05);
	armor = GlobalFunction::getRandomRangeIfFloat(armor*0.95, armor*1.05);
	attack_speed = GlobalFunction::getRandomRangeIfFloat(attack_speed*0.95*100, attack_speed*1.05*100)/100;
	speed_initial = GlobalFunction::getRandomRangeIfFloat(speed_initial*0.95, speed_initial*1.05);
	range_of_view = GlobalFunction::getRandomRangeIfFloat(range_of_view*0.95, range_of_view*1.05);

	is_guardian = is_monster_guardian;
	monster_is_elite = is_elite;
	if (is_elite)
	{
		if (is_guardian)
		{
			texture.loadFromFile("PenguinGuardian.png");
		}
		else
		{
			texture.loadFromFile("PenguinElite.png");
		}
		MonsterEliteInit();
		exp_given = exp_given * elite_percent_exp / 100;
		money_given = money_given*elite_percent_money / 100;
		monster_fragments_given = monster_fragments_given*elite_percent_fragments / 100;
	}

	int gamemode = ListObjectsSingleton::instance()->GetGameMode();
	//monster_maximum_health = monster_maximum_health*(0.5 + 0.25*gamemode);
	damage_normal = damage_normal*(0.5 + 0.25*gamemode);
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
	stun_bar.setOrigin(0, 2);
	stun_bar.setFillColor(sf::Color::Blue);
	damage = damage_normal;

	font.loadFromFile("Constantine.ttf");
	string_monster_name = "";
	string_monster_name = GlobalFunction::InsertNumberToString(string_monster_name, level_monster, string_monster_name.getSize());
	string_monster_name.insert(string_monster_name.getSize(), sf::String("   Penguin"));
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

void Penguin::MonsterEliteInit()
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

	damage_normal = damage_normal*elite_percent_damage / 100;
	damage_while_raging = damage_while_raging*elite_percent_damage / 100;
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

void Penguin::MonsterEliteGestion(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, sf::Vector2f velocity_player)
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

sf::Vector2f Penguin::GetCurrentPosition()
{
	return sprite_monster.getPosition();
}

void Penguin::Update(sf::Vector2f player_postion, float player_speed, sf::Vector2f player_position,  float DELTATIME, sf::Vector2f velocity_player)
{
	StunGestion();
	Health_maintenance();
	CuttingSprite();
	if (!monster_is_stunned)
	{
		RagingGestion();
		MovementGestion(player_position, DELTATIME);
		ThrowAnIceBall(player_position, player_speed,velocity_player);
		if (monster_is_elite)
		{
			MonsterEliteGestion(player_position, player_speed, player_position, velocity_player);
		}
	}
}

void Penguin::Health_maintenance()
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
				DeathAnimationGestion::instance()->Init(sf::Vector2f(48, 58), 20, 0.08, 2, GetCurrentPosition(), "PenguinDeath.png");
			}
			else if (monster_is_elite)
			{
				DeathAnimationGestion::instance()->Init(sf::Vector2f(48, 58), 20, 0.08, 1, GetCurrentPosition(), "PenguinDeath.png");
			}
			else
			{
				DeathAnimationGestion::instance()->Init(sf::Vector2f(48, 58), 20, 0.08, 0, GetCurrentPosition(), "PenguinDeath.png");
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

void Penguin::ThrowAnIceBall( sf::Vector2f player_position, float player_speed, sf::Vector2f velocity_player)
{
	sf::Vector2f position_shooter = sprite_monster.getPosition();
	if (clock_between_attack.getElapsedTime().asSeconds() >= 1 / attack_speed)
	{
		if (GlobalFunction::GetDistanceBetweenTwoPositions(position_shooter, player_position) <= range_of_shooting + 50)
		{
			sf::Vector2f position_target = player_position;
			angle_going = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, player_position);
			sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, position_target, velocity_player, speed_projectile_throwing);
			float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

			range_projectile_throwing = GlobalFunction::GetDistanceBetweenTwoPositions(position_shooter, position_aiming) + 10;
			float distance_two_entites = GlobalFunction::GetDistanceBetweenTwoPositions(position_shooter, position_target);

			if (range_projectile_throwing < distance_two_entites)
			{
				range_projectile_throwing = distance_two_entites + 50;
			}

			std::shared_ptr<IceBall> projectile = std::shared_ptr<IceBall>(new IceBall());
			projectile->Init(position_shooter, range_projectile_throwing, damage, angle_aiming, speed_projectile_throwing, id_monster);
			ProjectileGestion::instance()->AddObjectToList(projectile);
			projectile.reset();
			clock_between_attack.restart();

			SoundGestion::instance()->AddSound("SoundMonsterAttack.wav", 85, false);
		}
	}
}

void Penguin::GetRangeProjectile(sf::Vector2f player_position, float player_speed)
{
	float distance = GlobalFunction::GetDistanceBetweenTwoPositions(player_position, sprite_monster.getPosition());
	float speed_difference = speed_projectile_throwing - player_speed;
	range_projectile_throwing = speed_projectile_throwing*(distance / speed_difference);
}

void Penguin::CheckIfChasingPlayer(sf::Vector2f player_position)
{
	float distance_between_monster_and_player = GlobalFunction::GetDistanceBetweenTwoPositions(player_position, GetCurrentPosition());
	if (distance_between_monster_and_player <= range_of_view && distance_between_monster_and_player >= range_of_shooting)
	{
		SetAngle(player_position);
		if (!chasing_player)
		{
			holder_cutting_position.x = 0;
		}
		chasing_player = true;
	}
	else
	{
		if (chasing_player)
		{
			holder_cutting_position.x = 0;
		}
		holder_cutting_position.y = Standing;
		chasing_player = false;
	}
}

void Penguin::CheckEntityStillInMap()
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

void Penguin::MovementGestion(sf::Vector2f player_position, float DELTATIME)
{
	if (!being_pushed)
	{
		CheckIfChasingPlayer(player_position);
		if (chasing_player)
		{
			sprite_monster.move(-(cos(angle_going * PI / 180))*DELTATIME*speed, -(sin(angle_going * PI / 180))*DELTATIME*speed);
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

float Penguin::CollisionWithPlayer(int rayon_1, sf::Vector2f position_1, sf::Vector2f size_1)
{
	return 0;
}
 
float Penguin::GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent)
{
	damage_dealt = damage_dealt*GlobalFunction::GetArmorReductionModifier(armor*(1 - armor_penetration_percent / 100));
	if (damage_dealt > 0)
	{
		if (!listEliteBonus[DividedHealth_E])
		{
			monster_health -= damage_dealt;
		}
		else
		{
			damage_dealt = 1;
			monster_health -= damage_dealt;
		}
	}
	return damage_dealt;
}

int Penguin::GetRayon()
{
	return rayon_of_collision;
}

sf::Vector2f Penguin::GetSize()
{
	return size_monster;
}

void Penguin::CuttingSprite()
{
	been_drawn = true;
	if (!chasing_player)
	{
		if (clock_between_animation.getElapsedTime().asSeconds() >= time_between_animation)
		{
			sprite_monster.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, size_monster.y*holder_cutting_position.y, size_monster.x, size_monster.y));
			shadow.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, size_monster.y*holder_cutting_position.y, size_monster.x, size_monster.y));
			holder_cutting_position.x++;
			if (holder_cutting_position.x == dimension_monster_texture.x)
			{
				holder_cutting_position.x = 0;
			}
			clock_between_animation.restart();
		}
	}
	else
	{
		if (clock_between_animation.getElapsedTime().asSeconds() >= time_between_animation)
		{
			sprite_monster.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, size_monster.y*holder_cutting_position.y, size_monster.x, size_monster.y));
			shadow.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, size_monster.y*holder_cutting_position.y, size_monster.x, size_monster.y));
			holder_cutting_position.x++;
			if (holder_cutting_position.x == 8)
			{
				holder_cutting_position.x = 0;
			}
			clock_between_animation.restart();
		}
	}
}

bool Penguin::IsNeedToDelete()
{
	return !monster_alive;
}

int Penguin::GetExp()
{
	return exp_given;
}

sf::String Penguin::GetMonsterType()
{
	return "Penguin";
}

int Penguin::GetId()
{
	return id_monster;
}

sf::Vector2f Penguin::GetTypeAndNumberFragments()
{
	sf::Vector2f holder{ monster_type_fragment_given,monster_fragments_given };
	return holder;
}

void Penguin::FirstDraw(sf::RenderWindow &window)
{

}

void Penguin::GetIgnited(int type_ignition, float duration_ignition, float damage_ignition)
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

float Penguin::DamageFromAllIgnition()
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

void Penguin::CheckIfIgnited()
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

float Penguin::GetDurationOfStun()
{
	return 0;
}

void Penguin::IgnitionAnimationGestion()
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

void Penguin::SetAngle(sf::Vector2f player_postion)
{
	sf::Vector2f monster_current_position = GetCurrentPosition();
	if (monster_current_position.x > player_postion.x && monster_current_position.y < player_postion.y)
	{
		angle_going = 270 + ((((atan((monster_current_position.x - player_postion.x) / (player_postion.y - monster_current_position.y))) * 180 / PI)));
	}
	else if (monster_current_position.x < player_postion.x && monster_current_position.y < player_postion.y)
	{
		angle_going = 270 + ((atan((monster_current_position.x - player_postion.x) / (player_postion.y - monster_current_position.y))) * 180 / PI);
	}
	else if (monster_current_position.x > player_postion.x && monster_current_position.y > player_postion.y)
	{
		angle_going = (90 - ((atan((monster_current_position.x - player_postion.x) / (monster_current_position.y - player_postion.y)) * 180 / PI)));
	}
	else if (monster_current_position.x < player_postion.x && monster_current_position.y > player_postion.y)
	{
		angle_going = (180 - (((atan((player_postion.y - monster_current_position.y) / (monster_current_position.x - player_postion.x))) * 180 / PI)));
	}
	else if (monster_current_position.x == player_postion.x && monster_current_position.y <= player_postion.y)
	{
		angle_going = 270;
	}
	else if (monster_current_position.x == player_postion.x && monster_current_position.y >= player_postion.y)
	{
		angle_going = 90;
	}
	else if (monster_current_position.y == player_postion.y && monster_current_position.x >= player_postion.x)
	{
		angle_going = 0;
	}
	else if (monster_current_position.y == player_postion.y && monster_current_position.x <= player_postion.x)
	{
		angle_going = 180;
	}
	if (angle_going <= 315 && angle_going >= 225)
	{
		holder_cutting_position.y = Down;
	}
	if (angle_going <= 135 && angle_going >= 45)
	{
		holder_cutting_position.y = Up;
	}
	if ((angle_going <= 45 && angle_going >= 0) || (angle_going >= 315 && angle_going <= 360))
	{
		holder_cutting_position.y = Right;
	}
	if (angle_going <= 225 && angle_going >= 135)
	{
		holder_cutting_position.y = Left;
	}
}

void Penguin::GiveNewCenterGroupPosition(sf::Vector2f new_position, int group_concerned, sf::Vector2f next_new_group_position)
{
	
}

void Penguin::RagingGestion()
{
	if (!chasing_player)
	{
		damage = damage_while_raging;
	}
	else
	{
		damage = damage_normal;
	}
}

#pragma region StunGestion
void Penguin::StunGestion()
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
			chasing_player = false;
			holder_cutting_position.y = Standing;
		}
	}
	StunBarGestion();
}

float Penguin::GetStunTime()
{
	return time_being_stunned;
}

void Penguin::StunBarGestion()
{
	if (monster_is_stunned)
	{
		float size = (1 - (clock_check_if_still_stunned.getElapsedTime().asSeconds() / time_being_stunned)) * size_monster.x;
		stun_bar.setSize(sf::Vector2f(size, 4));
		stun_bar.setPosition(sf::Vector2f(sprite_monster.getPosition().x - bar_total_health.getSize().x / 2, bar_total_health.getPosition().y - bar_total_health.getSize().y / 2 - stun_bar.getSize().y / 2));
	}
}

void Penguin::ChangeStunTime(float stun_time_received)
{
	monster_is_stunned = true;
	time_being_stunned = (time_being_stunned > stun_time_received ? time_being_stunned : stun_time_received);
	clock_check_if_still_stunned.restart();
}

bool Penguin::IsPlayerStunned()
{
	return monster_is_stunned;
}

#pragma endregion StunGestion

void Penguin::GetSlowed(int type_slow, float duration_slow, float percent_slow)
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

void Penguin::CalculateMovementSpeedWithSlows()
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

void Penguin::GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking)
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

void Penguin::Draw(sf::RenderWindow &window)
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

void Penguin::DrawShadow(sf::RenderWindow &window)
{
	if (been_drawn)
	{
		shadow.setPosition(sprite_monster.getPosition() + sf::Vector2f(0, size_monster.y / 2 - 2));
		window.draw(shadow);
	}
}

sf::Vector2f Penguin::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

void Penguin::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Penguin::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

void Penguin::HealObject(float heal_value)
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