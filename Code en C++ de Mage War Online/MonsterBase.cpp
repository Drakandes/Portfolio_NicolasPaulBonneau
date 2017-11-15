#include "stdafx.h"
#include "MonsterBase.h"

sf::Vector2f MonsterBase::GetCurrentPosition()
{
	return sf::Vector2f(0,0);
}

void MonsterBase::Update(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player)
{

}

bool MonsterBase::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	return false;
}

float MonsterBase::GetDamage()
{
	return 0;
}

float MonsterBase::GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent)
{
	return 0;
}

int MonsterBase::GetRayon()
{
	return 0;
}

sf::Vector2f MonsterBase::GetSize()
{
	return sf::Vector2f(0, 0);
}

float MonsterBase::GetDurationOfStun()
{
	return 0;
}

void MonsterBase::DrawToScreen(sf::RenderWindow &window, sf::View &view_player)
{

}

bool MonsterBase::IsNeedToDelete()
{
	return false;
}

int MonsterBase::GetExp()
{
	return 0;
}

sf::String MonsterBase::GetMonsterType()
{
	return "Unknown";
}

int MonsterBase::GetId()
{
	return 0;
}

sf::Vector2f MonsterBase::GetTypeAndNumberFragments()
{
	sf::Vector2f holder{ 0,0 };
	return holder;
}

void MonsterBase::FirstDraw(sf::RenderWindow &window)
{

}

bool MonsterBase::IsOnPuddleBeer()
{
	return false;
}

void MonsterBase::ModifyMovementSpeedFromPercent(float percent)
{

}

float MonsterBase::ReturnLastNumberPudleTouched()
{
	return 0;
}

void MonsterBase::GetIgnited(int type_ignition, float duration_ignition, float damage_ignition)
{

}

float MonsterBase::DamageFromAllIgnition()
{
	return 0;
}

void MonsterBase::CheckIfIgnited()
{
}

void MonsterBase::IgnitionAnimationGestion()
{

}

void MonsterBase::GiveNewCenterGroupPosition(sf::Vector2f new_position, sf::Vector2f next_new_group_position)
{

}

int MonsterBase::GetGroupMonster()
{
	return -1;
}

#pragma region StunGestion
void MonsterBase::StunGestion()
{

}

float MonsterBase::GetStunTime()
{
	return 0;
}

void MonsterBase::StunBarGestion()
{

}

void MonsterBase::ChangeStunTime(float stun_time_received)
{
	std::cout << "Error monster basse got stunned" << std::endl;
}

bool MonsterBase::IsPlayerStunned()
{
	return false;
}

#pragma endregion StunGestion

void MonsterBase::GetSlowed(int type_slow, float duration_slow, float percent_slow)
{

}

void MonsterBase::GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking)
{

}

void MonsterBase::Draw(sf::RenderWindow &window)
{

}

std::shared_ptr<MonsterBase> MonsterBase::SpawnChild()
{
	std::shared_ptr<MonsterBase> child = std::shared_ptr<MonsterBase>(new MonsterBase());
	return child;
}

bool MonsterBase::CanSpawnChild()
{
	return false;
}

void MonsterBase::Init(int id_received, bool is_elite)
{

}

void MonsterBase::GivePosition(sf::Vector2f position)
{

}

sf::Vector2f MonsterBase::GetChildPositionGoing()
{
	return sf::Vector2f(0, 0);
}

void MonsterBase::DeleteChild(int id_child)
{

}

bool MonsterBase::CanStun()
{
	return false;
}

bool MonsterBase::CheckIdObject(int id_object)
{
	return true;
}

float MonsterBase::GetExpGiven(int level_monster)
{
	return exp_given + exp_given * (0.5 + 1.43*level_monster / 100)*(level_monster - 1);
}

float MonsterBase::GetMoneyGiven(int level_monster)
{
	return money_given + money_given * (0.2 + 0.8*level_monster / 100)*(level_monster - 1);
}

int MonsterBase::GetRandomMonsterEliteBonus(std::vector<bool> listAlreadyBonus)
{
	std::vector<int> BonusAlreadyAquired;
	for (int i = 0; i < listAlreadyBonus.size(); i++)
	{
		if (listAlreadyBonus[i])
		{
			BonusAlreadyAquired.push_back(i+1);
		}
	}

	if (BonusAlreadyAquired.size() > 1)
	{
		return GlobalFunction::getRandomRangeWithUnknownException(1, number_monster_elite_bonus, BonusAlreadyAquired)-1;
	}
	else if (BonusAlreadyAquired.size() == 1)
	{
		return GlobalFunction::getRandomRangeWithException(1, number_monster_elite_bonus, BonusAlreadyAquired[0])-1;
	}
	else
	{
		return GlobalFunction::getRandomRange(1, number_monster_elite_bonus)-1;
	}
}

int MonsterBase::GetNumberMonsterEliteBonus(int monster_level)
{
	if (monster_level >= 75)
	{
		return 5;
	}
	if (monster_level >= 50)
	{
		return 4;
	}
	if (monster_level >= 25)
	{
		return 3;
	}
	return 2;
}

std::shared_ptr<E_Ring> MonsterBase::CreateRing(int level_monster)
{

	int ring_ilvl = level_monster;
	if (GlobalFunction::getRandomRange(1, 1000) <= 500)
	{
		ring_ilvl += GlobalFunction::getRandomRange(1, 3);
	}
	else
	{
		ring_ilvl -= GlobalFunction::getRandomRange(1, 3);
	}
	if (ring_ilvl < 1)
	{
		ring_ilvl = 1;
	}
	int ring_rarity = GetRarityItem(ring_ilvl);
	std::vector<bool> listRingHaveBonus{ false,false,false,false,false,false,false,false,false,false,false,false,false };
	std::vector<float> listRingBonus{ 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	std::vector<sf::Vector2f> listRingRangeBonus{ sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0) ,sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0) };

	int number_bonus = 2;
	int holder = ring_ilvl;
	while (holder > 0)
	{
		if (holder - 25 >= 0)
		{
			number_bonus++;
		}
		holder -= 33;
	}
	if (number_bonus > 5)
	{
		number_bonus = 5;
	}

#pragma region RarityGestion

	if (ring_rarity == Uncommon_E)
	{
		number_bonus++;
	}
	if (ring_rarity == Epic_E)
	{
		number_bonus++;
	}

#pragma endregion RarityGestion

	std::vector<int> ListExceptions;
	for (int i = 0; i < number_bonus; i++)
	{
		int random_number = GlobalFunction::getRandomRangeWithUnknownException(1, number_ring_bonus_maximum, ListExceptions);
		ListExceptions.push_back(random_number);
		listRingHaveBonus[random_number - 1] = true;

		sf::Vector2f range_bonus = GetRangeBonus(random_number-1, ring_ilvl);
		float bonus = GlobalFunction::getRandomRangeIfFloat(range_bonus.x * 100, range_bonus.y * 100) / 100;
		listRingBonus[random_number - 1] = bonus;
		listRingRangeBonus[random_number - 1] = range_bonus;
	}

	std::shared_ptr<E_Ring> ring = std::shared_ptr<E_Ring>(new E_Ring(ListObjectsSingleton::instance()->GetCurrentLanguage(), ListObjectsSingleton::instance()->GetCurrentSave()));
	ring->Init(ring_ilvl,listRingHaveBonus, listRingBonus, listRingRangeBonus, ListObjectsSingleton::instance()->GetNewIDEquipment(), ring_rarity,number_ring_bonus_maximum);
	return ring;
}

int MonsterBase::GetRarityItem(int item_level)
{
	float percent_item_level_max = static_cast<float>(item_level - 1) / 100;
	float percent_item_level_min = static_cast<float>(101 - item_level) / 100;
	float modifier = 100000;
	float random_number = GlobalFunction::getRandomRange(1, modifier);
	float percent_passed = 0;

	for (int i = 0; i < RarityItemRange.size(); i++)
	{
		float chance = (RarityItemRange[i].x*percent_item_level_min + RarityItemRange[i].y*percent_item_level_max) / 100 * modifier;
		if (percent_passed + chance > random_number)
		{
			return i;
		}
		else
		{
			percent_passed += chance;
		}
	}

	return Legendary_E;
}

sf::Vector2f MonsterBase::GetRangeBonus(int type_bonus, float item_level)
{
	switch (type_bonus)
	{
	case RingHpRecovery:
		return sf::Vector2f(7 + (item_level - 1)*0.85 - 3 - (item_level - 1)*0.1, 7 + (item_level - 1)*0.85 + 3 + (item_level - 1)*0.1);

	case RingHpPercentRevoery:
		return sf::Vector2f(0.3 + (item_level - 1)*0.017 - 0.1 - (item_level - 1)*0.004, 0.3 + (item_level - 1)*0.017 + 0.1 + (item_level - 1)*0.004);

	case RingMovementSpeedAddition:
		return sf::Vector2f(6 + (item_level - 1)*0.6 - 2 - (item_level - 1)*0.08, 6 + (item_level - 1)*0.6 + 2 + (item_level - 1)*0.08);

	case RingDamagePercent:
		return sf::Vector2f(3 + (item_level - 1)*0.12 - 1 - (item_level - 1)*0.04, 3 + (item_level - 1)*0.12 + 1 + (item_level - 1)*0.04);

	case RingDamageAddition:
		return sf::Vector2f(13 + (item_level - 1)*0.35 - 4 - (item_level - 1)*0.07, 13 + (item_level - 1)*0.35 + 4 + (item_level - 1)*0.07);

	case RingExperiencePercent:
		return sf::Vector2f(3 + (item_level - 1)*0.12 - 1 - (item_level - 1)*0.04, 3 + (item_level - 1)*0.12 + 1 + (item_level - 1)*0.04);

	case RingHealthAddition:
		return sf::Vector2f(100 + (item_level - 1)*6.5 - 15 - (item_level - 1), 50 + (item_level - 1)*6.5 + 15 + (item_level - 1));

	case RingHealthPercent:
		return sf::Vector2f(3 + (item_level - 1)*0.12 - 1 - (item_level - 1)*0.04, 3 + (item_level - 1)*0.12 + 1 + (item_level - 1)*0.04);

	case RingArmorAddition:
		return sf::Vector2f(3 + (item_level - 1)*0.27 - 1 - (item_level - 1)*0.05, 3 + (item_level - 1)*0.27 + 1 + (item_level - 1)*0.05);

	case RingArmorPercent:
		return sf::Vector2f(3 + (item_level - 1)*0.12 - 1 - (item_level - 1)*0.04, 3 + (item_level - 1)*0.12 + 1 + (item_level - 1)*0.04);

	case RingCooldown:
		return sf::Vector2f(3 + (item_level - 1)*0.12 - 1 - (item_level - 1)*0.04, 3 + (item_level - 1)*0.12 + 1 + (item_level - 1)*0.04);

	case RingAttackSpeedPercent:
		return sf::Vector2f(4 + (item_level - 1)*0.14 - 1.5 - (item_level - 1)*0.05, 4 + (item_level - 1)*0.14 + 1.5 + (item_level - 1)*0.05);

	case RingLifeSteal:
		return sf::Vector2f(3 + (item_level - 1)*0.12 - 1 - (item_level - 1)*0.04, 3 + (item_level - 1)*0.12 + 1 + (item_level - 1)*0.04);
	}
}

float MonsterBase::DamageIncreaseGestion(float value, float level_monster)
{
	level_monster--;
	if (level_monster > 0)
	{
		value += value*((0.08 + 0.007*level_monster / 4)*level_monster);
	}
	return value;
}

float MonsterBase::HealthIncreaseGestion(float value, float level_monster)
{
	level_monster--;
	if (level_monster > 0)
	{
		value += value*((0.08 + 0.017*level_monster/4)*level_monster);
	}
	return value;
}

float MonsterBase::ArmorIncreaseGestion(float value, float level_monster)
{
	level_monster--;
	if (level_monster > 0)
	{
		value += value*((0.00085 + 0.0005*level_monster / 4)*level_monster);
	}
	return value;
}

float MonsterBase::SpeedIncreaseGestion(float value, float level_monster)
{
	level_monster--;
	if (level_monster > 0)
	{
		value += value*((0.001 + 0.00008*level_monster / 4)*level_monster);
	}
	return value;
}

float MonsterBase::AttackSpeedIncreaseGestion(float value, float level_monster)
{
	level_monster--;
	if (level_monster > 0)
	{
		value += value += value*((0.0008 + 0.000065*level_monster / 4)*level_monster);
	}
	return value;
}
