#include "stdafx.h"
#include "Demon.h"

Demon::Demon()
{
	if (!texture.loadFromFile("Demon.png"))
	{
		std::cout << "Error while loading mini goat texture" << std::endl;
	}
	if (!texture_splashing.loadFromFile("Demon_splashing.png"))
	{
		std::cout << "Error while loading mini goat texture" << std::endl;
	}
	if (!texture_ignition.loadFromFile("Burning_animation.png"))
	{
		std::cout << "Error: Couldn't load Burning_animation in blob" << std::endl;
	}

	if (!shadow_texture.loadFromFile("DemonShadow.png"))
	{
		std::cout << "Error while loading demon projectile shadow texture" << std::endl;
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

Demon::~Demon()
{
	std::list<std::shared_ptr<DarkOrb>>::iterator i = ListAllDarkOrbs.begin();
	while (i != ListAllDarkOrbs.end())
	{
		(*i)->SetToDelete();
		i++;
	}
	ListAllDarkOrbs.clear();

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

void Demon::Init(int id_received, sf::Vector2f position_spawn_r, int id_spawn_r, float size_spawn_r, int level_monster_r, sf::Vector2f position_monster,bool is_elite, bool is_monster_guardian)
{
	level_monster = level_monster_r;
	position_of_spawn = position_spawn_r;
	id_spawn = id_spawn_r;
	size_spawn = size_spawn_r;

	float level_monster_float = level_monster;
	damage = DamageIncreaseGestion(damage, level_monster_float);
	monster_maximum_health = HealthIncreaseGestion(monster_maximum_health, level_monster_float);
	armor = ArmorIncreaseGestion(armor, level_monster_float);
	stun_from_orb += stun_from_orb*0.005*(level_monster - 1);

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
	range_of_view = GlobalFunction::getRandomRangeIfFloat(range_of_view*0.95, range_of_view*1.05);
	stun_from_orb = GlobalFunction::getRandomRangeIfFloat(stun_from_orb*0.95, stun_from_orb*1.05);

	is_guardian = is_monster_guardian;
	monster_is_elite = is_elite;
	if (is_elite)
	{
		if (is_guardian)
		{
			texture.loadFromFile("DemonGuardian.png");
		}
		else
		{
			texture.loadFromFile("DemonElite.png");
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
	monster_holder_health = monster_maximum_health;
	monster_alive = true;
	bar_total_health.setFillColor(sf::Color::Black);
	bar_total_health.setOrigin(sf::Vector2f(size_monster.x / 2, 2));
	bar_current_health.setFillColor(sf::Color::Red);
	bar_current_health.setOrigin(sf::Vector2f(size_monster.x / 2, 2));
	id_monster = id_received;
	position_current_monster = sprite_monster.getPosition();
	sprite_ignition = GlobalFunction::CreateSprite(position_current_monster, size_sprite_ignition, texture_ignition);
	number_wings_roation_maximum = GlobalFunction::getRandomRange(number_wings_rotation_range.x, number_wings_rotation_range.y);
	sprite_splashing = GlobalFunction::CreateSprite(sprite_monster.getPosition(), size_texture_splashing, texture_splashing);
	stun_bar.setOrigin(0, 2);
	stun_bar.setFillColor(sf::Color::Blue);
	for (int number = 0; number < number_graviting_darkorb; number++)
	{
		rotation_graviting_darkorb[number] = 360 / 5 * (number+1);
		std::shared_ptr<DarkOrb> darkorb = std::shared_ptr<DarkOrb>(new DarkOrb());
		darkorb->Init(GiveNewId(),position_current_monster, darkorb_distance_from_caster, damage, rotation_graviting_darkorb[number],shared_from_this());
		ListAllDarkOrbs.push_back(darkorb);
		ProjectileGestion::instance()->AddObjectToList(darkorb);
		darkorb.reset();
	}

	font.loadFromFile("Constantine.ttf");
	string_monster_name = "";
	string_monster_name = GlobalFunction::InsertNumberToString(string_monster_name, level_monster, string_monster_name.getSize());
	string_monster_name.insert(string_monster_name.getSize(), sf::String("   Demon"));
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

void Demon::MonsterEliteInit()
{
	int number_bonus = GetNumberMonsterEliteBonus(level_monster);
	listEliteBonus[HastyMonster_E] = true;
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

	if (listEliteBonus[DividedHealth_E])
	{
		monster_maximum_health = 20 + std::ceil(25 * level_monster / 100);
	}
}

void Demon::MonsterEliteGestion(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, sf::Vector2f velocity_player)
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

sf::Vector2f Demon::GetCurrentPosition()
{
	return sprite_monster.getPosition();
}

void Demon::Update(sf::Vector2f player_postion, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player)
{
	StunGestion();
	Health_maintenance();
	CuttingSprite();
	if (!monster_is_stunned)
	{
		MovementGestion(player_position, DELTATIME);
		SplashingGestion();
		ChasingPlayer(player_postion);
		if (chasing_player)
		{
			NumberDarkOrbGestion();
		}

		std::list<std::shared_ptr<DarkOrb>>::iterator iterator = ListAllDarkOrbs.begin();
		while (iterator != ListAllDarkOrbs.end())
		{
			(*iterator)->CanBeActivatedThisFrame();
			iterator++;
		}
	}
	if (monster_is_elite)
	{
		MonsterEliteGestion(player_position, player_speed, player_position, velocity_player);
	}
}

void Demon::Health_maintenance()
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
			std::list<std::shared_ptr<DarkOrb>>::iterator i = ListAllDarkOrbs.begin();
			while (i != ListAllDarkOrbs.end())
			{
				(*i)->SetToDelete();
				i++;
			}
			ListAllDarkOrbs.clear();
			can_drop = true;
			monster_alive = false;

			if (is_guardian)
			{
				DeathAnimationGestion::instance()->Init(sf::Vector2f(75, 75), 15, 0.08, 2, GetCurrentPosition(), "DemonDeath.png");
			}
			else if (monster_is_elite)
			{
				DeathAnimationGestion::instance()->Init(sf::Vector2f(75, 75), 15, 0.08, 1, GetCurrentPosition(), "DemonDeath.png");
			}
			else
			{
				DeathAnimationGestion::instance()->Init(sf::Vector2f(75, 75), 15, 0.08, 0, GetCurrentPosition(), "DemonDeath.png");
			}
		}
	}

	if (monster_alive)
	{
		bar_total_health.setSize(sf::Vector2f(size_monster.x, 4));
		bar_total_health.setPosition(sf::Vector2f(position_current_monster.x, position_current_monster.y - size_monster.y / 2 - 5));

		bar_current_health.setSize(sf::Vector2f(size_monster.x * (monster_holder_health / monster_maximum_health), 4));
		bar_current_health.setPosition(sf::Vector2f(position_current_monster.x, position_current_monster.y - size_monster.y / 2 - 5));

		text_monster_name.setPosition(sf::Vector2f(position_current_monster.x, position_current_monster.y - size_monster.y / 2 - 20));
	}
}

float Demon::GetDurationOfStun()
{
	return stun_from_demon;
}

void Demon::CheckEntityStillInMap()
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

void Demon::MovementGestion(sf::Vector2f player_position, float DELTATIME)
{
	if (being_pushed)
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
	if (number_wings_rotation > number_wings_roation_maximum)
	{
		number_wings_rotation = 0;
		number_wings_roation_maximum = GlobalFunction::getRandomRange(number_wings_rotation_range.x, number_wings_rotation_range.y);
		is_teleporting = true;
		holder_cutting_position.x = 0;
	}
	CheckEntityStillInMap();
}

float Demon::GetDamage()
{
	if (is_splashing && splashing_can_do_damage)
	{
		splashing_can_do_damage = false;
		return damage;
	}
	return 0;
}

bool Demon::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (is_splashing && splashing_can_do_damage)
	{
		if (sprite_monster.getGlobalBounds().intersects(rect_collision))
		{
			return true;
		}
	}
	return false;
}

float Demon::GotDamaged(float damage_dealt, int id_attacker, float armor_penetration_percent)
{
	damage_dealt = damage_dealt*GlobalFunction::GetArmorReductionModifier(armor*(1 - armor_penetration_percent / 100));
	if (damage_dealt > 0)
	{
		if (is_teleporting)
		{
			damage_dealt = damage_dealt / 10;
		}
		if (!listEliteBonus[DividedHealth_E])
		{
			monster_holder_health -= damage_dealt;
			if (!is_teleporting && !monster_is_stunned)
			{
				number_wings_rotation = 0;
				number_wings_roation_maximum = GlobalFunction::getRandomRange(number_wings_rotation_range.x, number_wings_rotation_range.y);
				is_teleporting = true;
				holder_cutting_position.x = 0;
			}
		}
		else
		{
			damage_dealt = 1;
			monster_holder_health -= damage_dealt;

			if (!is_teleporting && !monster_is_stunned)
			{
				number_wings_rotation = 0;
				number_wings_roation_maximum = GlobalFunction::getRandomRange(number_wings_rotation_range.x, number_wings_rotation_range.y);
				is_teleporting = true;       
				holder_cutting_position.x = 0;
			}
		}
	}
	return damage_dealt;
}

int Demon::GetRayon()
{
	return rayon_of_collision;
}

sf::Vector2f Demon::GetSize()
{
	return size_monster;
}

void Demon::CuttingSprite()
{
	been_drawn = true;
	if (!is_teleporting)
	{
		if (clock_between_animation.getElapsedTime().asSeconds() >= time_between_animation)
		{
			sprite_monster.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, size_monster.y*holder_cutting_position.y, size_monster.x, size_monster.y));
			shadow.setTextureRect(sf::IntRect(shadow_size.x * holder_cutting_position.x, shadow_size.y*holder_cutting_position.y, shadow_size.x, shadow_size.y));
			holder_cutting_position.x++;
			if (holder_cutting_position.x == dimension_monster_texture.x)
			{
				number_wings_rotation++;
				holder_cutting_position.x = 0;
			}
			clock_between_animation.restart();
		}
	}
	else
	{
		holder_cutting_position.y = 1;
		if (clock_between_animation.getElapsedTime().asSeconds() >= time_between_animation)
		{
			sprite_monster.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, size_monster.y*holder_cutting_position.y, size_monster.x, size_monster.y));
			shadow.setTextureRect(sf::IntRect(shadow_size.x * holder_cutting_position.x, shadow_size.y*holder_cutting_position.y, shadow_size.x, shadow_size.y));
			holder_cutting_position.x++;
			if (holder_cutting_position.x == 9)
			{
				Teleportation();
				holder_cutting_position.y = 0;
				holder_cutting_position.x = 0;

			}
			clock_between_animation.restart();
		}
	}
}

bool Demon::IsNeedToDelete()
{
	return !monster_alive;
}

int Demon::GetExp()
{
	return exp_given;
}

sf::String Demon::GetMonsterType()
{
	return "Demon";
}

int Demon::GetId()
{
	return id_monster;
}

sf::Vector2f Demon::GetTypeAndNumberFragments()
{
	sf::Vector2f holder{ monster_type_fragment_given,monster_fragments_given };
	return holder;
}

void Demon::FirstDraw(sf::RenderWindow &window)
{

}

bool Demon::IsOnPuddleBeer()
{
	return false;
}

float Demon::ReturnLastNumberPudleTouched()
{
	return 0;
}

void Demon::GetIgnited(int type_ignition, float duration_ignition, float damage_ignition)
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

float Demon::DamageFromAllIgnition()
{
	if (!is_teleporting)
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
}

void Demon::CheckIfIgnited()
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

void Demon::IgnitionAnimationGestion()
{
	if (clock_ignition_animation.getElapsedTime().asSeconds() >= 0.1)
	{
		sprite_ignition.setPosition(position_current_monster);
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

void Demon::SetAngle(sf::Vector2f player_postion)
{
	sf::Vector2f monster_current_position = GetCurrentPosition();
	if (monster_current_position.x > player_postion.x && monster_current_position.y < player_postion.y)
	{
		angle = 270 + ((((atan((monster_current_position.x - player_postion.x) / (player_postion.y - monster_current_position.y))) * 180 / PI)));
	}
	else if (monster_current_position.x < player_postion.x && monster_current_position.y < player_postion.y)
	{
		angle = 270 + ((atan((monster_current_position.x - player_postion.x) / (player_postion.y - monster_current_position.y))) * 180 / PI);
	}
	else if (monster_current_position.x > player_postion.x && monster_current_position.y > player_postion.y)
	{
		angle = (90 - ((atan((monster_current_position.x - player_postion.x) / (monster_current_position.y - player_postion.y)) * 180 / PI)));
	}
	else if (monster_current_position.x < player_postion.x && monster_current_position.y > player_postion.y)
	{
		angle = (180 - (((atan((player_postion.y - monster_current_position.y) / (monster_current_position.x - player_postion.x))) * 180 / PI)));
	}
	else if (monster_current_position.x == player_postion.x && monster_current_position.y <= player_postion.y)
	{
		angle = 270;
	}
	else if (monster_current_position.x == player_postion.x && monster_current_position.y >= player_postion.y)
	{
		angle = 90;
	}
	else if (monster_current_position.y == player_postion.y && monster_current_position.x >= player_postion.x)
	{
		angle = 0;
	}
	else if (monster_current_position.y == player_postion.y && monster_current_position.x <= player_postion.x)
	{
		angle = 180;
	}
	if (angle <= 315 && angle >= 225)
	{
		holder_cutting_position.y = Down;
	}
	if (angle <= 135 && angle >= 45)
	{
		holder_cutting_position.y = Up;
	}
	if ((angle <= 45 && angle >= 0) || (angle >= 315 && angle <= 360))
	{
		holder_cutting_position.y = Right;
	}
	if (angle <= 225 && angle >= 135)
	{
		holder_cutting_position.y = Left;
	}
}

void Demon::Teleportation()
{
	is_splashing = true;
	is_teleporting = false;
	splashing_can_do_damage = true;
	sf::Vector2f monster_current_position = GetCurrentPosition();
	float new_distance_to_go = GlobalFunction::getRandomRange(0, range_of_teleportation);
	float new_direction_to_go = GlobalFunction::getRandomRange(1, 360);
	sf::Vector2f distance = sf::Vector2f(cos(new_direction_to_go*PI / 180)*new_distance_to_go, sin(new_direction_to_go*PI / 180)*new_distance_to_go);
	sprite_monster.setPosition(distance + monster_current_position);
	position_current_monster = sprite_monster.getPosition();
	std::list<std::shared_ptr<DarkOrb>>::iterator iterator = ListAllDarkOrbs.begin();
	while (iterator != ListAllDarkOrbs.end())
	{
		(*iterator)->UpdateAfterTeleportation(position_current_monster);
		iterator++;
	}
}

void Demon::SplashingGestion()
{
	if (is_splashing)
	{
		sprite_splashing.setPosition(sprite_monster.getPosition());
		if (clock_splashing_animation.getElapsedTime().asSeconds() >= time_between_splashing_animation)
		{
			sprite_splashing.setTextureRect(sf::IntRect(size_texture_splashing.x*holder_demon_splashing, 0, size_texture_splashing.x, size_texture_splashing.y));
			holder_demon_splashing++;
			if (holder_demon_splashing == 6)
			{
				holder_demon_splashing = 0;
				is_splashing = false;
			}
			clock_splashing_animation.restart();
		}
	}
}

void Demon::ChasingPlayer(sf::Vector2f player_postion)
{
	float distance_from_target = GlobalFunction::GetDistanceBetweenTwoPositions(player_postion, position_current_monster);
	if (distance_from_target <= range_of_view)
	{
		chasing_player = true;
		if (distance_from_target <= range_of_orbs)
		{
			darkorb_distance_from_caster = distance_from_target;
		}
		else
		{
			darkorb_distance_from_caster = range_of_orbs;
		}
	}
	else
	{
		chasing_player = false;
		darkorb_distance_from_caster = darkorbit_distance_from_caster_initial;

		std::list<std::shared_ptr<DarkOrb>>::iterator i = ListAllDarkOrbs.begin();
		while (i != ListAllDarkOrbs.end())
		{
			(*i)->SetToDelete();
			i++;
		}
		ListAllDarkOrbs.clear();
	}
}

void Demon::NumberDarkOrbGestion()
{
	if (clock_creation_darkorb.getElapsedTime().asSeconds() >= 1)
	{
		if (ListAllDarkOrbs.size() == 0)
		{
			for (int number = 0; number < number_graviting_darkorb; number++)
			{
				rotation_graviting_darkorb[number] = 360 / 5 * (number + 1);
				std::shared_ptr<DarkOrb> darkorb = std::shared_ptr<DarkOrb>(new DarkOrb());
				darkorb->Init(GiveNewId(),position_current_monster, darkorb_distance_from_caster, damage, rotation_graviting_darkorb[number],shared_from_this());
				ListAllDarkOrbs.push_back(darkorb);
				ProjectileGestion::instance()->AddObjectToList(darkorb);
				darkorb.reset();
			}
		}
		clock_creation_darkorb.restart();
	}
}

#pragma region StunGestion
void Demon::StunGestion()
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
		}
	}
	StunBarGestion();
}

float Demon::GetStunTime()
{
	return time_being_stunned;
}

void Demon::StunBarGestion()
{
	if (monster_is_stunned)
	{
		float size = (1 - (clock_check_if_still_stunned.getElapsedTime().asSeconds() / time_being_stunned)) * size_monster.x;
		stun_bar.setSize(sf::Vector2f(size, 4));
		stun_bar.setPosition(sf::Vector2f(sprite_monster.getPosition().x - bar_total_health.getSize().x / 2, bar_total_health.getPosition().y - bar_total_health.getSize().y / 2 - stun_bar.getSize().y / 2));
	}
}

void Demon::ChangeStunTime(float stun_time_received)
{
	monster_is_stunned = true;
	time_being_stunned = (time_being_stunned > stun_time_received ? time_being_stunned : stun_time_received);
	clock_check_if_still_stunned.restart();
}

bool Demon::IsPlayerStunned()
{
	return monster_is_stunned;
}

#pragma endregion StunGestion

void Demon::GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking)
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

void Demon::Draw(sf::RenderWindow &window)
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
			if (is_splashing)
			{
				window.draw(sprite_splashing);
			}

			if (monster_is_stunned)
			{
				window.draw(stun_bar);
			}
		}
	}
	std::list<std::shared_ptr<DarkOrb>>::iterator iterator = ListAllDarkOrbs.begin();
	while (iterator != ListAllDarkOrbs.end())
	{
		if ((*iterator)->IsNeedToDelete())
		{
			ListAllDarkOrbs.erase(iterator++);
		}
		else
		{
			(*iterator)->Draw(window);
			iterator++;
		}
	}
}

void Demon::DrawShadow(sf::RenderWindow &window)
{
	if (been_drawn)
	{
		shadow.setPosition(sprite_monster.getPosition() + sf::Vector2f(0, size_monster.y / 2));
		window.draw(shadow);
	}
}

sf::Vector2f Demon::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

sf::Vector2f Demon::GetChildPositionGoing()
{
	return sf::Vector2f(darkorb_distance_from_caster,0);
}

void Demon::DeleteChild(int id_child)
{
}

int Demon::GiveNewId()
{
	id_giving_to_projectile++;
	return id_giving_to_projectile - 1;
}

void Demon::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	if (is_splashing && splashing_can_do_damage)
	{
		int type_object = object_collided->GetTypeCollisionalObject();
		sf::Vector2f position_self = GetCurrentPosition();
		sf::Vector2f position_objet = object_collided->GetCurrentPosition();
		sf::Vector2f size_object = object_collided->GetSize();

		if (type_object == Player_E)
		{
			float damage_dealt = object_collided->GotDamaged(GetDamage(),id_monster,0);

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

void Demon::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Demon::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

void Demon::HealObject(float heal_value)
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
