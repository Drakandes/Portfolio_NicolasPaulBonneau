#include "stdafx.h"
#include "Blob.h"
#include "GlobalEnum.h"

Blob::Blob()
{
	for (int i = 0; i < number_monster_elite_bonus; i++)
	{
		sf::Clock clock;
		listEliteBonusClock.push_back(clock);
		listEliteBonus.push_back(false);
		listEliteBonusCooldown.push_back(2);
	}
}

Blob::~Blob()
{
	if (can_drop && GlobalFunction::getRandomRange(1,1000) <= chance_to_drop_on_thousand)
	{
		std::shared_ptr<LootBag> loot_bag = std::shared_ptr<LootBag>(new LootBag());
		loot_bag->Init(GetCurrentPosition(), ListObjectsSingleton::instance()->GetNewID());
		loot_bag->AddRingToBag(CreateRing(level_monster));
		ProjectileGestion::instance()->AddObjectToList(loot_bag);
		MainQuadtree::instance()->insert(GetCurrentPosition(), loot_bag->GetSize(), loot_bag);
		loot_bag.reset();
	}


}

void Blob::Texture_loading()
{
	if (!texture.loadFromFile("Blob.png"))
	{
		std::cout << "Error: Couldn't load Blob texture" << std::endl;
	}

	if (!alert_texture.loadFromFile("Blob_alert.png"))
	{
		std::cout << "Error: Couldn't load alert point texture" << std::endl;
	}

	if (!texture_ignition.loadFromFile("Burning_animation.png"))
	{
		std::cout << "Error: Couldn't load Burning_animation in blob" << std::endl;
	}
}

void Blob::Init(int id_monster_received, sf::Vector2f position_spawn_r, int id_spawn_r, float size_spawn_r, int level_monster_r,sf::Vector2f position_monster, bool is_elite, bool is_monster_guardian)
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
	speed_of_blob_raging_modifier_addition = SpeedIncreaseGestion(speed_of_blob_raging_modifier_addition, level_monster_float);

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
	range_of_view = GlobalFunction::getRandomRangeIfFloat(range_of_view*0.95, range_of_view*1.05);
	speed_of_blob_raging_modifier_addition = GlobalFunction::getRandomRangeIfFloat(speed_of_blob_raging_modifier_addition*0.95, speed_of_blob_raging_modifier_addition*1.05);

	is_guardian = is_monster_guardian;
	monster_is_elite = is_elite;
	if (is_elite)
	{
		if (is_guardian)
		{
			texture.loadFromFile("BlobGuardian.png");
		}
		else
		{
			texture.loadFromFile("BlobElite.png");
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
	sprite_monster.setOrigin(sf::Vector2f(blob_size_x / 2, blob_size_y / 2));
	monster_holder_health = monster_maximum_health;
	monster_alive = true;
	sprite_monster.setTexture(texture);
	monster_maximum_health_bar.setFillColor(sf::Color::Black);
	monster_maximum_health_bar.setOrigin(sf::Vector2f(blob_size_x / 2, 2));
	blob_health_bar.setFillColor(sf::Color::Red);
	blob_health_bar.setOrigin(sf::Vector2f(blob_size_x / 2, 2));
	alert_point.setTexture(alert_texture);
	alert_point.setTextureRect(sf::IntRect(0, 0, alert_point_size.x, alert_point_size.y));
	alert_point.setOrigin(sf::Vector2f(alert_point_size.x / 2, alert_point_size.y / 2));
	sleeping_point.setTexture(alert_texture);
	sleeping_point.setOrigin(sf::Vector2f(sleeping_point_size.x / 2, sleeping_point_size.y / 2));
	id_monster = id_monster_received;
	sprite_ignition = GlobalFunction::CreateSprite(sprite_monster.getPosition(), size_sprite_ignition, texture_ignition);
	speed = speed_initial;
	stun_bar.setOrigin(0, 2);
	stun_bar.setFillColor(sf::Color::Blue);

	font.loadFromFile("Constantine.ttf");
	string_monster_name = "";
	string_monster_name = GlobalFunction::InsertNumberToString(string_monster_name, level_monster, string_monster_name.getSize());
	string_monster_name.insert(string_monster_name.getSize(), sf::String("   Blob"));
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

void Blob::MonsterEliteInit()
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

	if(listEliteBonus[ElectricShot_E])
	{
		listEliteBonus[GetRandomMonsterEliteBonus(listEliteBonus)] = true;
	}
	listEliteBonus[ElectricShot_E] = false;

	damage = damage*elite_percent_damage / 100;
	monster_maximum_health = monster_maximum_health*elite_percent_health / 100;

	if (listEliteBonus[HastyMonster_E])
	{
		speed_initial = speed_initial*elite_percent_speed / 100;
		speed_of_blob_raging_modifier_addition  = speed_of_blob_raging_modifier_addition*elite_percent_speed / 100;
	}

	if (listEliteBonus[DividedHealth_E])
	{
		monster_maximum_health = 20 +  std::ceil(25*level_monster / 100);
	}
}

void Blob::MonsterEliteGestion(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, sf::Vector2f velocity_player)
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
					projectile->Init(monster_position, damage, angle_to_player - 5 + 10*i, id_monster);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();
				}

				listEliteBonusCooldown[Trap_E] = GlobalFunction::getRandomRange(90, 140)/10;
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
				projectile->Init(monster_position + sf::Vector2f(0, -blob_size_y / 2), id_monster);
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
				listEliteBonusClock[Invisibility_E].restart();
			}
			else
			{
				is_invisible = true;
				listEliteBonusCooldown[Invisibility_E] = duration_invisibility;
				sprite_monster.setColor(sf::Color::Color(255, 255, 255, 30));
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
				projectile->Init(monster_position, damage*1.25, angle_aiming,id_monster, shared_from_this());
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
				sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(monster_position, position_target, velocity_player,1000);
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

				listEliteBonusCooldown[PushImpact_E] = GlobalFunction::getRandomRange(50, 90)/10;
				listEliteBonusClock[PushImpact_E].restart();
			}
		}
	}

	if (listEliteBonus[Regeneration_E])
	{
		if (listEliteBonusClock[Regeneration_E].getElapsedTime().asSeconds() >= 0.5)
		{
			if (monster_holder_health < monster_maximum_health)
			{
				monster_holder_health += monster_maximum_health*elite_percent_regeneration;
			}
			if (monster_holder_health > monster_maximum_health)
			{
				monster_holder_health = monster_maximum_health;
			}
			listEliteBonusClock[Regeneration_E].restart();
		}
	}
}

void Blob::Health_maintenance()
{
	if (monster_holder_health <= 0)
	{
		if (listEliteBonus[SecondLife_E])
		{
			listEliteBonus[SecondLife_E] = false;
			monster_holder_health = monster_maximum_health;
		}
		else
		{
			monster_alive = false;
			can_drop = true;
			if (is_guardian)
			{
				DeathAnimationGestion::instance()->Init(sf::Vector2f(80, 56), 15, 0.08, 2, GetCurrentPosition(), "BlobDeath.png");
			}
			else if (monster_is_elite)
			{
				DeathAnimationGestion::instance()->Init(sf::Vector2f(80, 56), 15, 0.08, 1, GetCurrentPosition(), "BlobDeath.png");
			}
			else
			{
				DeathAnimationGestion::instance()->Init(sf::Vector2f(80, 56), 15, 0.08, 0, GetCurrentPosition(), "BlobDeath.png");
			}
		}
	}
	
	if (monster_alive)
	{
		sf::Vector2f blob_position = sprite_monster.getPosition();
		monster_maximum_health_bar.setSize(sf::Vector2f(blob_size_x, 4));
		monster_maximum_health_bar.setPosition(sf::Vector2f(blob_position.x, blob_position.y - blob_size_y / 2 - 5));

		blob_health_bar.setSize(sf::Vector2f(blob_size_x * (monster_holder_health / monster_maximum_health), 4));
		blob_health_bar.setPosition(sf::Vector2f(blob_position.x, blob_position.y - blob_size_y / 2 - 5));

		text_monster_name.setPosition(sf::Vector2f(blob_position.x, blob_position.y - blob_size_y / 2 - 20));
	}
}

float Blob::GetDurationOfStun()
{
	return stun_duration;
}

void Blob::CheckEntityStillInMap()
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

void Blob::Movement_gestion(float DELTATIME)
{
	if (!being_pushed)
	{
		if (!monster_is_stunned)
		{
			if (blob_chasing_player)
			{
				if (clock_blob_update.getElapsedTime().asSeconds() >= 0.01)
				{
					if (Is_blob_standing_still())
					{
						CalculateMovementSpeedWithSlows();
						sprite_monster.move(-(cos(angle_going * PI / 180))*speed*DELTATIME, -(sin(angle_going * PI / 180))*speed*DELTATIME);
					}

					clock_blob_update.restart();
				}
			}
			else if (!blob_standing_still)
			{
				blob_standing_still = true;
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

void Blob::Get_angle(sf::Vector2f player_Position)
{
	if(!monster_is_stunned)
	{
		sf::Vector2f blob_position = sprite_monster.getPosition();
		angle_going = GlobalFunction::GetRotationBetweenTwoPositions(blob_position, player_Position);
	}
}

void Blob::Cutting_blob_sprite(sf::Vector2f player_Position)
{
	if (!blob_standing_still)
	{
		if (clock_blob_animation.getElapsedTime().asSeconds() >= 0.05)
		{
			sprite_monster.setTextureRect(sf::IntRect(blob_size_x * source_x, source_y * blob_size_y, blob_size_x, blob_size_y));
			source_x++;
			if (source_x >= 13)
			{
				Get_angle(player_Position);
				source_x = 0;
			}

			clock_blob_animation.restart();
		}
	}
	else if (!blob_sleeping)
	{
		if (clock_blob_animation.getElapsedTime().asSeconds() >= 0.1)
		{
			sprite_monster.setTextureRect(sf::IntRect(blob_size_x * source_x, 2 * blob_size_y, blob_size_x, blob_size_y));
			source_x++;
			if (source_x >= 13)
			{
				blob_sleeping = true;
				source_x = 0;
			}

			clock_blob_animation.restart();
		}
	}
	else
	{
		if (clock_blob_animation.getElapsedTime().asSeconds() >= 0.2)
		{
			sprite_monster.setTextureRect(sf::IntRect(blob_size_x * source_x, 2 * blob_size_y, blob_size_x, blob_size_y));
			source_x++;

			if (source_x >= 26)
			{
				source_x = 19;
				if (!blob_sleeping_alert_created)
				{
					source_y_sleeping_point = 0;
					blob_is_sleeping_alert = true;
					blob_sleeping_alert_created = true;
				}
			}

			clock_blob_animation.restart();
		}
	}
}

bool Blob::Is_blob_standing_still()
{
	if (source_x == 0 || source_x == 8 || source_x == 9 || source_x == 10 || source_x == 11 || source_x == 0 || source_x == 12)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Blob::Blob_orientation()
{
	if (angle_going <= 315 && angle_going >= 225)
	{
		source_y = Down;
	}
	if (angle_going <= 135 && angle_going >= 45)
	{
		source_y = Up;
	}
	if ((angle_going <= 45 && angle_going >= 0) || (angle_going >= 315 && angle_going <= 360))
	{
		source_y = Left;
	}
	if (angle_going <= 225 && angle_going >= 135)
	{
		source_y = Right;
	}
}

sf::Vector2f Blob::GetCurrentPosition()
{
	return sprite_monster.getPosition();
}

sf::Vector2f Blob::GetSize()
{
	sf::Vector2f size(blob_size_x, blob_size_y);
	return size;
}

int Blob::GetRayon()
{
	return rayon;
}
 
float Blob::GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent)
{
	damage_dealt = damage_dealt*GlobalFunction::GetArmorReductionModifier(armor*(1 - armor_penetration_percent / 100));
	if (damage_dealt > 0)
	{
		if (!listEliteBonus[DividedHealth_E])
		{
			if (clock_blob_alert.getElapsedTime().asSeconds() > 1 && !blob_is_raging)
			{
				clock_blob_alert.restart();
			}
			blob_is_just_starting_chasing = true;
			blob_is_sleeping_alert = false;
			blob_sleeping_alert_created = false;
			blob_sleeping = false;
			blob_chasing_player = true;
			blob_standing_still = false;
			if (!blob_is_raging)
			{
				speed += speed_initial*speed_of_blob_raging_modifier_addition;
			}
			blob_is_raging = true;
			clock_blob_raging.restart();
			monster_holder_health = monster_holder_health - damage_dealt;
		}
		else
		{
			damage_dealt = 1;
			if (clock_blob_alert.getElapsedTime().asSeconds() > 1 && !blob_is_raging)
			{
				clock_blob_alert.restart();
			}
			blob_is_just_starting_chasing = true;
			blob_is_sleeping_alert = false;
			blob_sleeping_alert_created = false;
			blob_sleeping = false;
			blob_chasing_player = true;
			blob_standing_still = false;
			if (!blob_is_raging)
			{
				speed += speed_initial*speed_of_blob_raging_modifier_addition;
				blob_is_raging = true;
				clock_blob_raging.restart();
			}
			monster_holder_health -= damage_dealt;
		}
	}
	return damage_dealt;
}

bool Blob::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	/*if (player_collision_timer.getElapsedTime().asSeconds() >= 0.5)
	{
		if (GlobalFunction::Check_collision(rayon_1, GetRayon(), position_1, GetCurrentPosition(), size_1, GetSize()))
		{
			player_collision_timer.restart();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}*/

	if (CheckIdObject(id_object))
	{
		if (sprite_monster.getGlobalBounds().intersects(rect_collision))
		{
			return true;
		}
	}
	return false;
}

void Blob::AlertPointMaintenance()
{
	alert_point.setPosition(monster_maximum_health_bar.getPosition().x, monster_maximum_health_bar.getPosition().y - 24);
}

void Blob::ChasingPlayerMaintenance(sf::Vector2f position_player)
{
	if (!blob_is_raging && !monster_is_stunned)
	{
		sf::Vector2f blob_position = GetCurrentPosition();
		if (GlobalFunction::GetDistanceBetweenTwoPositions(position_player,blob_position) <= range_of_view)
		{
			if (!blob_is_just_starting_chasing)
			{
				clock_blob_alert.restart();
				blob_is_just_starting_chasing = true;
				blob_is_sleeping_alert = false;
				blob_sleeping_alert_created = false;
			}
			blob_sleeping = false;
			blob_chasing_player = true;
			blob_standing_still = false;
		}
		else
		{
			blob_is_just_starting_chasing = false;
			blob_chasing_player = false;
		}
	}
}

float Blob::GetDamage()
{
	return damage;
}

void Blob::SleepingPointMaintenance()
{
	sleeping_point.setPosition(monster_maximum_health_bar.getPosition().x, monster_maximum_health_bar.getPosition().y - 12);
	if(blob_is_sleeping_alert)
	{
		if (clock_blob_sleeping_point.getElapsedTime().asSeconds() >= 0.5)
		{
			sleeping_point.setTextureRect(sf::IntRect(0, 26 + (sleeping_point_size.y*source_y_sleeping_point), sleeping_point_size.x, sleeping_point_size.y));
			source_y_sleeping_point++;

			if (source_y_sleeping_point >= 3)
			{
				source_y_sleeping_point = 0;
			}
			clock_blob_sleeping_point.restart();
		}
	}
}

void Blob::BlobRagingMaintenance()
{
	if (blob_is_raging && !monster_is_stunned)
	{
		if (clock_blob_raging.getElapsedTime().asSeconds() >= 5)
		{
			blob_is_raging = false;
			speed -= speed_initial*speed_of_blob_raging_modifier_addition;
			clock_blob_raging.restart();
		}
		else
		{
			blob_is_just_starting_chasing = true;
			blob_is_sleeping_alert = false;
			blob_sleeping_alert_created = false;
			blob_sleeping = false;
			blob_chasing_player = true;
			blob_standing_still = false;
		}
	}
}

void Blob::Update(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player)
{
	StunGestion();
	BlobRagingMaintenance();
	ChasingPlayerMaintenance(playerPosition);
	Health_maintenance();
	Movement_gestion(DELTATIME);
	Cutting_blob_sprite(playerPosition);
	Blob_orientation();
	AlertPointMaintenance();
	SleepingPointMaintenance();
	if (monster_is_elite)
	{
		MonsterEliteGestion(playerPosition, player_speed, player_position, velocity_player);
	}
}

bool Blob::IsNeedToDelete()
{
	return !monster_alive;
}

int Blob::GetExp()
{
	return exp_given;
}

sf::String Blob::GetMonsterType()
{
	return "Blob";
}

int Blob::GetId()
{
	int id_monster_holder = id_monster;
	return id_monster_holder;
}

sf::Vector2f Blob::GetTypeAndNumberFragments()
{
	return sf::Vector2f(monster_type_fragment_given, monster_fragments_given);
}

void Blob::GetIgnited(int type_ignition, float duration_ignition, float damage_ignition)
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

float Blob::DamageFromAllIgnition()
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

void Blob::CheckIfIgnited()
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

void Blob::IgnitionAnimationGestion()
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

void Blob::GetSlowed(int type_slow, float duration_slow,float percent_slow)
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

void Blob::CalculateMovementSpeedWithSlows()
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
			percent_all_slow = percent_all_slow*(1-((*iterator_percent)/100));
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
	float slow_applied = (1-(percent_all_slow))*speed;
	if (slow_applied > speed)
	{
		slow_applied = speed;
	}
	speed -= slow_applied;
	last_slow_percent = slow_applied;
}

int Blob::GetGroupMonster()
{
	return -1;
}

#pragma region StunGestion
void Blob::StunGestion()
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
			blob_standing_still = true;
		}
	}
	StunBarGestion();
}

float Blob::GetStunTime()
{
	return time_being_stunned;
}

void Blob::StunBarGestion()
{
	if (monster_is_stunned)
	{
		float size = (1 - (clock_check_if_still_stunned.getElapsedTime().asSeconds() / time_being_stunned)) * blob_size_x;
		stun_bar.setSize(sf::Vector2f(size, 4));
		stun_bar.setPosition(sf::Vector2f(sprite_monster.getPosition().x - monster_maximum_health_bar.getSize().x / 2, monster_maximum_health_bar.getPosition().y - monster_maximum_health_bar.getSize().y / 2 - stun_bar.getSize().y / 2));
	}
}

void Blob::ChangeStunTime(float stun_time_received)
{
	monster_is_stunned = true;
	time_being_stunned = (time_being_stunned > stun_time_received ? time_being_stunned : stun_time_received);
	clock_check_if_still_stunned.restart();
}

bool Blob::IsPlayerStunned()
{
	return monster_is_stunned;
}

#pragma endregion StunGestion

void Blob::GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking)
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

void Blob::Draw(sf::RenderWindow &window)
{
	window.draw(sprite_monster);
	if (!is_invisible)
	{
		window.draw(monster_maximum_health_bar);
		window.draw(blob_health_bar);
		window.draw(text_monster_name);
		if (clock_blob_alert.getElapsedTime().asSeconds() <= 1)
		{
			window.draw(alert_point);
		}
		if (blob_is_sleeping_alert)
		{
			window.draw(sleeping_point);
		}
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

void Blob::DrawShadow(sf::RenderWindow &window)
{
	
}

bool Blob::CanStun()
{
	return true;
}

bool Blob::CheckIdObject(int id_object)
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

void Blob::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	if (CheckIdObject(id_object))
	{
		int type_object = object_collided->GetTypeCollisionalObject();
		sf::Vector2f position_self = GetCurrentPosition();
		sf::Vector2f position_objet = object_collided->GetCurrentPosition();
		sf::Vector2f size_object = object_collided->GetSize();

		if (type_object == Player_E)
		{
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

void Blob::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Blob::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

void Blob::HealObject(float heal_value)
{
	if (!listEliteBonus[DividedHealth_E])
	{
		monster_holder_health += heal_value;
		if (monster_holder_health > monster_maximum_health)
		{
			monster_holder_health = monster_maximum_health;
		}
	}
	else
	{
		monster_holder_health += 2;
		if (monster_holder_health > monster_maximum_health)
		{
			monster_holder_health = monster_maximum_health;
		}
	}
}

