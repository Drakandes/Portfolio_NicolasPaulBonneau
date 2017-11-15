#include "stdafx.h"
#include "Viking.h"

Viking::Viking()
{
	if (!monster_texture.loadFromFile("Viking.png"))
	{
		std::cout << "Error: Couldn't load Viking texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("VikingShadow.png"))
	{
		std::cout << "Error while loading VikingShadow texture" << std::endl;
	}
	if (!texture_ignition.loadFromFile("Burning_animation.png"))
	{
		std::cout << "Error: Couldn't load Burning_animation in Viking" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
	shadow.setOrigin(sf::Vector2f(monster_size.x / 2, 0));
}

Viking::~Viking()
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

void Viking::Init(int id_monster_received, sf::Vector2f position_monster)
{
	level_monster = 50;

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
				monster_fragments_given = 200;
			}
			else
			{
				monster_type_fragment_given = RunicFragment;
				monster_fragments_given = 650;
			}
		}
		else
		{
			monster_type_fragment_given = EnchantedFragment;
			monster_fragments_given = 1050;
		}
	}
	else
	{
		monster_type_fragment_given = StrongFragment;
		monster_fragments_given = 1500;
	}

#pragma endregion Fragment

	monster_maximum_health = GlobalFunction::getRandomRangeIfFloat(monster_maximum_health*0.95, monster_maximum_health*1.05);
	damage = GlobalFunction::getRandomRangeIfFloat(damage*0.95, damage*1.05);
	armor = GlobalFunction::getRandomRangeIfFloat(armor*0.95, armor*1.05);
	speed_initial = GlobalFunction::getRandomRangeIfFloat(speed_initial*0.95, speed_initial*1.05);

	int gamemode = ListObjectsSingleton::instance()->GetGameMode();
	//monster_maximum_health = monster_maximum_health*(0.5 + 0.25*gamemode);
	damage = damage*(0.5 + 0.25*gamemode);
	//armor = armor*(0.5 + 0.25*gamemode);

	sprite_monster.setPosition(position_monster);
	sprite_monster.setOrigin(sf::Vector2f(monster_size.x / 2, monster_size.y / 2));
	monster_holder_health = monster_maximum_health;
	monster_alive = true;
	sprite_monster.setTexture(monster_texture);
	monster_maximum_health_bar.setFillColor(sf::Color::Black);
	monster_maximum_health_bar.setOrigin(sf::Vector2f(monster_size.x / 2, 2));
	monster_health_bar.setFillColor(sf::Color::Red);
	monster_health_bar.setOrigin(sf::Vector2f(monster_size.x / 2, 2));
	id_monster = id_monster_received;
	sprite_ignition = GlobalFunction::CreateSprite(sprite_monster.getPosition(), size_sprite_ignition, texture_ignition);
	speed = speed_initial;
	stun_bar.setOrigin(0, 2);
	stun_bar.setFillColor(sf::Color::Blue);

	font.loadFromFile("Constantine.ttf");
	string_monster_name = "";
	string_monster_name = GlobalFunction::InsertNumberToString(string_monster_name, level_monster, string_monster_name.getSize());
	string_monster_name.insert(string_monster_name.getSize(), sf::String("   Sigmund"));
	
	string_monster_name.insert(string_monster_name.getSize(), sf::String(" BOSS"));

	text_monster_name = GlobalFunction::CreateText(sf::Vector2f(0, 0), string_monster_name, font, 17);
	text_monster_name.setStyle(sf::Text::Bold);

	sprite_monster.setTextureRect(sf::IntRect(monster_size.x * source_x, 0, monster_size.x, monster_size.y));
	shadow.setTextureRect(sf::IntRect(monster_size.x * source_x, 0, monster_size.x, monster_size.y));
}

void Viking::Health_maintenance()
{
	if (monster_holder_health <= 0)
	{
		monster_alive = false;
		can_drop = true;
	}

	if (monster_alive)
	{
		sf::Vector2f monster_position = sprite_monster.getPosition();
		monster_maximum_health_bar.setSize(sf::Vector2f(monster_size.x, 4));
		monster_maximum_health_bar.setPosition(sf::Vector2f(monster_position.x, monster_position.y - monster_size.y / 2 - 5));

		monster_health_bar.setSize(sf::Vector2f(monster_size.x * (monster_holder_health / monster_maximum_health), 4));
		monster_health_bar.setPosition(sf::Vector2f(monster_position.x, monster_position.y - monster_size.y / 2 - 5));

		text_monster_name.setPosition(sf::Vector2f(monster_position.x, monster_position.y - monster_size.y / 2 - 20));
	}
}

float Viking::GetDurationOfStun()
{
	return 0;
}

void Viking::CheckEntityStillInMap()
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

void Viking::Movement_gestion(float DELTATIME, sf::Vector2f player_position)
{
	CheckEntityStillInMap();
}

void Viking::AttackPlayer(sf::Vector2f player_position, sf::Vector2f velocity_player)
{
	if (!attacking)
	{
		if (clock_attack.getElapsedTime().asSeconds() >= 1 / attack_speed)
		{
			sf::Vector2f position_shooter = GetCurrentPosition();
			sf::Vector2f position_target = player_position;
			sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, position_target, velocity_player, 1500);
			position_aiming += GlobalFunction::GetRandomVectorBetweenRange(75);

			std::shared_ptr<VikingThunder> projectile = std::shared_ptr<VikingThunder>(new VikingThunder());
			projectile->Init(position_aiming, damage, id_monster, true, false);
			ProjectileGestion::instance()->AddObjectToList(projectile);
			projectile.reset();

			attack_speed += 0.01;

			source_x = 0;
			clock_attack.restart();
		}
	}

	if (clock_hammer.getElapsedTime().asSeconds() >= cooldown_hammer)
	{
		cooldown_hammer -= 0.25;
		if (cooldown_hammer <= 3)
		{
			cooldown_hammer = 3;
		}
		damage_hammer = damage;
		attacking = true;
		source_x = 0;
		clock_hammer.restart();
	}

	if (can_throw_hammer)
	{
		sf::Vector2f position_shooter = GetCurrentPosition();
		sf::Vector2f position_target = player_position;
		sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, position_target, velocity_player, speed_projectile_throwing);
		float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

		std::shared_ptr<VikingHammer> projectile = std::shared_ptr<VikingHammer>(new VikingHammer());
		projectile->Init(position_shooter, damage_hammer,angle_aiming, id_monster,speed_projectile_throwing, true, false);
		projectile->GiveStunEffect(0.25);
		ProjectileGestion::instance()->AddObjectToList(projectile);
		projectile.reset();
		can_throw_hammer = false;

		timer_animation -= 0.0025;
		if (timer_animation < 0.04)
		{
			timer_animation = 0.04;
		}
	}
}

void Viking::Cutting_sprite()
{
	if (!attacking)
	{
		float new_timer_animation = 1 / attack_speed / number_animation_attack;

		if (clock_animation.getElapsedTime().asSeconds() >= new_timer_animation)
		{
			sprite_monster.setTextureRect(sf::IntRect(monster_size.x * source_x, monster_size.y, monster_size.x, monster_size.y));
			shadow.setTextureRect(sf::IntRect(monster_size.x * source_x, monster_size.y, monster_size.x, monster_size.y));
			source_x++;
			if (source_x >= number_animation_attack)
			{
				source_x = 0;
			}

			clock_animation.restart();
		}
	}
	else
	{
		if (clock_animation.getElapsedTime().asSeconds() >= timer_animation)
		{
			sprite_monster.setTextureRect(sf::IntRect(monster_size.x * source_x, 0, monster_size.x, monster_size.y));
			shadow.setTextureRect(sf::IntRect(monster_size.x * source_x, 0, monster_size.x, monster_size.y));
			source_x++;
			if (source_x >= 4)
			{
				counter_hammer_charge++;
				if (counter_hammer_charge < number_hammer_charge)
				{
					source_x = 0;
					damage_hammer = damage_hammer*1.3;
				}
				else
				{
					source_x = 0;
					can_throw_hammer = true;
					attacking = false;
					counter_hammer_charge = 0;
					number_hammer_charge = GlobalFunction::getRandomRange(3, 7);
				}
			}

			clock_animation.restart();
		}
	}
}

sf::Vector2f Viking::GetCurrentPosition()
{
	return sprite_monster.getPosition();
}

sf::Vector2f Viking::GetSize()
{
	return monster_size;
}

int Viking::GetRayon()
{
	return rayon;
}

float Viking::GotDamaged(float damage_dealt, int id_attacker, float armor_penetration_percent)
{
	damage_dealt = damage_dealt*GlobalFunction::GetArmorReductionModifier(armor*(1 - armor_penetration_percent / 100));
	if (damage_dealt > 0)
	{
		monster_holder_health = monster_holder_health - damage_dealt;
	}

	return damage_dealt;
}

float Viking::GetDamage()
{
	return damage;
}

void Viking::Update(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player)
{
	StunGestion();
	Health_maintenance();
	Movement_gestion(DELTATIME, player_position);
	AttackPlayer(player_position, velocity_player);
	Cutting_sprite();
}

bool Viking::IsNeedToDelete()
{
	return !monster_alive;
}

int Viking::GetExp()
{
	return exp_given;
}

sf::String Viking::GetMonsterType()
{
	return "Viking";
}

int Viking::GetId()
{
	int id_monster_holder = id_monster;
	return id_monster_holder;
}

sf::Vector2f Viking::GetTypeAndNumberFragments()
{
	return sf::Vector2f(monster_type_fragment_given, monster_fragments_given);
}

void Viking::GetIgnited(int type_ignition, float duration_ignition, float damage_ignition)
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

float Viking::DamageFromAllIgnition()
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

void Viking::CheckIfIgnited()
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

void Viking::IgnitionAnimationGestion()
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

void Viking::GetSlowed(int type_slow, float duration_slow, float percent_slow)
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

void Viking::CalculateMovementSpeedWithSlows()
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
void Viking::StunGestion()
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

		}
	}
	StunBarGestion();
}

float Viking::GetStunTime()
{
	return time_being_stunned;
}

void Viking::StunBarGestion()
{
	if (monster_is_stunned)
	{
		float size = (1 - (clock_check_if_still_stunned.getElapsedTime().asSeconds() / time_being_stunned)) * monster_size.x;
		stun_bar.setSize(sf::Vector2f(size, 4));
		stun_bar.setPosition(sf::Vector2f(sprite_monster.getPosition().x - monster_maximum_health_bar.getSize().x / 2, monster_maximum_health_bar.getPosition().y - monster_maximum_health_bar.getSize().y / 2 - stun_bar.getSize().y / 2));
	}
}

void Viking::ChangeStunTime(float stun_time_received)
{
	stun_time_received = stun_time_received*0.15;
	monster_is_stunned = true;
	time_being_stunned = (time_being_stunned > stun_time_received ? time_being_stunned : stun_time_received);
	clock_check_if_still_stunned.restart();
}

bool Viking::IsPlayerStunned()
{
	return monster_is_stunned;
}

#pragma endregion StunGestion

void Viking::GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking)
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

void Viking::Draw(sf::RenderWindow &window)
{
	window.draw(sprite_monster);
	window.draw(monster_maximum_health_bar);
	window.draw(monster_health_bar);
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

void Viking::DrawShadow(sf::RenderWindow &window)
{

	shadow.setPosition(sprite_monster.getPosition() + sf::Vector2f(0, monster_size.y / 2));
	window.draw(shadow);
}

bool Viking::CanStun()
{
	return false;
}

void Viking::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
}

void Viking::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Viking::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

void Viking::HealObject(float heal_value)
{
	monster_holder_health += heal_value;
	if (monster_holder_health > monster_maximum_health)
	{
		monster_holder_health = monster_maximum_health;
	}
}