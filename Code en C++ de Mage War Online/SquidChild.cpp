#include "stdafx.h"
#include "SquidChild.h"

SquidChild::SquidChild()
{
	if (!texture.loadFromFile("SquidChild.png"))
	{
		std::cout << "Error while loading sentry texture" << std::endl;
	}
	if (!texture_ignition.loadFromFile("Burning_animation.png"))
	{
		std::cout << "Error: Couldn't load Burning_animation in sentry" << std::endl;
	}

	if (!shadow_texture.loadFromFile("SquidChildShadow.png"))
	{
		std::cout << "Error while loading squid child projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
	shadow.setOrigin(sf::Vector2f(size_monster.x / 2, 0));
}

SquidChild::~SquidChild()
{
}

void SquidChild::Init(int id_received,bool is_elite)
{
	float level_monster_float = level_monster;
	damage += damage*(level_monster - 1)*(level_monster_float*2 / 500);
	monster_maximum_health += monster_maximum_health*(level_monster - 1)*(level_monster_float*2 / 500);
	armor += armor*(level_monster - 1)*(level_monster_float*2 / 500);
	speed_initial += speed_initial*0.005*(level_monster - 1);

	exp_given = 0;

	monster_maximum_health = GlobalFunction::getRandomRangeIfFloat(monster_maximum_health*0.95, monster_maximum_health*1.05);
	damage = GlobalFunction::getRandomRangeIfFloat(damage*0.95, damage*1.05);
	armor = GlobalFunction::getRandomRangeIfFloat(armor*0.95, armor*1.05);
	speed_initial = GlobalFunction::getRandomRangeIfFloat(speed_initial*0.95, speed_initial*1.05);

	if (monster_is_elite)
	{
		sprite_monster.setColor(sf::Color::Color(255, 25, 25));
	}

	int gamemode = ListObjectsSingleton::instance()->GetGameMode();
	//monster_maximum_health = monster_maximum_health*(0.5 + 0.25*gamemode);
	damage = damage*(0.5 + 0.25*gamemode);
	//armor = armor*(0.5 + 0.25*gamemode);

#pragma region Fragment
	
	monster_fragments_given = 0;

#pragma endregion Fragment

	sf::Vector2f position_origin(10,10);
	starting_position = position_origin;
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
	sprite_monster.setTextureRect(sf::IntRect(0, size_monster.y * 2, size_monster.x, size_monster.y));
	monster_is_elite = is_elite;
}

sf::Vector2f SquidChild::GetCurrentPosition()
{
	return sprite_monster.getPosition();
}

void SquidChild::Update(sf::Vector2f player_postion, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player)
{
	StunGestion();
	CuttingSprite();
	if (!monster_is_stunned)
	{
		MovementGestion(player_position, DELTATIME);
	}
	Health_maintenance();
}

void SquidChild::Health_maintenance()
{
	if (monster_alive)
	{
		sf::Vector2f monster_position = sprite_monster.getPosition();
		bar_total_health.setSize(sf::Vector2f(size_monster.x, 4));
		bar_total_health.setPosition(sf::Vector2f(monster_position.x, monster_position.y - size_monster.y / 2 - 5));

		bar_current_health.setSize(sf::Vector2f(size_monster.x * (monster_health / monster_maximum_health), 4));
		bar_current_health.setPosition(sf::Vector2f(monster_position.x, monster_position.y - size_monster.y / 2 - 5));
	}
}

void SquidChild::MovementGestion(sf::Vector2f player_position, float DELTATIME)
{
	angle_going = GlobalFunction::GetRotationBetweenTwoPositions(GetCurrentPosition(), player_position);

	if (!being_pushed)
	{
		if (growth)
		{
			sprite_monster.move(-(cos(angle_going * PI / 180))*speed*DELTATIME, -(sin(angle_going * PI / 180))*speed*DELTATIME);
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

float SquidChild::GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent)
{
	damage_dealt = damage_dealt*GlobalFunction::GetArmorReductionModifier(armor*(1 - armor_penetration_percent / 100));
	if (damage_dealt > 0)
	{
		destroyed_by_played = true;
		monster_health -= damage_dealt;
	}
	if (monster_health <= 0)
	{
		monster_alive = false;
	}
	return damage_dealt;
}

int SquidChild::GetRayon()
{
	return rayon_of_collision;
}

sf::Vector2f SquidChild::GetSize()
{
	return size_monster;
}

void SquidChild::CuttingSprite()
{
	been_drawn = true;
	if (growth)
	{
		if (clock_between_animation.getElapsedTime().asSeconds() >= time_between_animation)
		{
			if (angle_going > 180)
			{
				sprite_monster.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, 0, size_monster.x, size_monster.y));
				shadow.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, 0, size_monster.x, size_monster.y));
				holder_cutting_position.x++;
				if (holder_cutting_position.x == 4)
				{
					holder_cutting_position.x = 0;
				}
			}
			else
			{
				sprite_monster.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, size_monster.y, size_monster.x, size_monster.y));
				shadow.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, size_monster.y, size_monster.x, size_monster.y));
				holder_cutting_position.x++;
				if (holder_cutting_position.x == 4)
				{
					holder_cutting_position.x = 0;
				}
			}
		}
		clock_between_animation.restart();
	}
	else
	{
		if (clock_between_animation.getElapsedTime().asSeconds() >= 0.2)
		{
			sprite_monster.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, size_monster.y * 2, size_monster.x, size_monster.y));
			shadow.setTextureRect(sf::IntRect(size_monster.x * holder_cutting_position.x, size_monster.y * 2, size_monster.x, size_monster.y));
			holder_cutting_position.x++;
			if (holder_cutting_position.x == 4)
			{
				holder_cutting_position.x = 0;
				growth = true;
			}
			clock_between_animation.restart();
		}
	}
}

void SquidChild::DrawToScreen(sf::RenderWindow &window, sf::View &view_player)
{
	/*if (been_drawn)
	{
	window.draw(bar_total_health);
	window.draw(bar_current_health);
	window.draw(sprite_monster);
	}
	CheckIfIgnited();
	if (is_ignite)
	{
	window.draw(sprite_ignition);
	}
	if (monster_is_stunned)
	{
	window.draw(stun_bar);
	}*/
}

bool SquidChild::IsNeedToDelete()
{
	return !monster_alive;
}

int SquidChild::GetExp()
{
	return 0;
}

sf::String SquidChild::GetMonsterType()
{
	return "SquidChild";
}

int SquidChild::GetId()
{
	return id_monster;
}

sf::Vector2f SquidChild::GetTypeAndNumberFragments()
{
	sf::Vector2f holder{ monster_type_fragment_given,monster_fragments_given };
	return holder;
}

void SquidChild::FirstDraw(sf::RenderWindow &window)
{

}

bool SquidChild::IsOnPuddleBeer()
{
	return false;
}

void SquidChild::ModifyMovementSpeedFromPercent(float percent)
{

}

float SquidChild::ReturnLastNumberPudleTouched()
{
	return 0;
}

void SquidChild::GetIgnited(int type_ignition, float duration_ignition, float damage_ignition)
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

float SquidChild::DamageFromAllIgnition()
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

	TextGenerator::instance()->GenerateOneTextForBlob(GetCurrentPosition(), damage_from_all_ignition, GetSize(), shared_from_this());

	return damage_from_all_ignition;
}

void SquidChild::CheckIfIgnited()
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

float SquidChild::GetDurationOfStun()
{
	return 0;
}

void SquidChild::IgnitionAnimationGestion()
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

#pragma region StunGestion
void SquidChild::StunGestion()
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

float SquidChild::GetStunTime()
{
	return time_being_stunned;
}

void SquidChild::StunBarGestion()
{
	if (monster_is_stunned)
	{
		float size = (1 - (clock_check_if_still_stunned.getElapsedTime().asSeconds() / time_being_stunned)) * size_monster.x;
		stun_bar.setSize(sf::Vector2f(size, 4));
		stun_bar.setPosition(sf::Vector2f(sprite_monster.getPosition().x - bar_total_health.getSize().x / 2, bar_total_health.getPosition().y - bar_total_health.getSize().y / 2 - stun_bar.getSize().y / 2));
	}
}

void SquidChild::ChangeStunTime(float stun_time_received)
{
	monster_is_stunned = true;
	time_being_stunned = (time_being_stunned > stun_time_received ? time_being_stunned : stun_time_received);
	clock_check_if_still_stunned.restart();
}

bool SquidChild::IsPlayerStunned()
{
	return monster_is_stunned;
}

#pragma endregion StunGestion

void SquidChild::GetSlowed(int type_slow, float duration_slow, float percent_slow)
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

void SquidChild::CalculateMovementSpeedWithSlows()
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

void SquidChild::GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking)
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

void SquidChild::Draw(sf::RenderWindow &window)
{
	if (been_drawn)
	{
		shadow.setPosition(sprite_monster.getPosition() + sf::Vector2f(0, 5 + size_monster.y/2));
		window.draw(shadow);

		window.draw(bar_total_health);
		window.draw(bar_current_health);
		window.draw(sprite_monster);
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
	/*std::list<SquidChildProjectile*>::iterator iterator = list_Projectile.begin();
	while (iterator != list_Projectile.end())
	{
	(*iterator)->Draw(window);
	iterator++;
	}*/
}

void SquidChild::DrawShadow(sf::RenderWindow &window)
{
	if (been_drawn)
	{
		shadow.setPosition(sprite_monster.getPosition() + sf::Vector2f(0, 5 + size_monster.y / 2));
		window.draw(shadow);
	}
}

sf::Vector2f SquidChild::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

void SquidChild::GivePosition(sf::Vector2f position)
{
	sprite_monster.setPosition(position);
}

float SquidChild::GetDamage()
{
	return damage;
}

void SquidChild::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int id_object = object_collided->GetId();
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();

	if (type_object == Player_E)
	{
		monster_alive = false;
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
	else if (type_object == Projectile_E)
	{
		monster_alive = false;
	}
}

void SquidChild::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool SquidChild::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}
