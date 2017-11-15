#include "stdafx.h"
#include "Bubble.h"

Bubble::Bubble()
{
	if (!texture.loadFromFile("Bubble.png"))
	{
		std::cout << "Error: Couldn't load Bubble texture" << std::endl;
	}
	listAllSkills = ListObjectsSingleton::instance()->GetListSkill();
}

Bubble::~Bubble()
{
	parent.reset();
	listAllSkills.clear();
}

void Bubble::Texture_loading()
{
}

void Bubble::Init(sf::Vector2f &position_player, float angle_received, float player_damage, std::shared_ptr<Player> player,float speed_modifier)
{
	parent = player;
	player.reset();
	projectile_rotation = angle_received;
	projectile_position_origin = position_player;
	projectile = GlobalFunction::CreateSprite(position_player, size_projectile, texture);
	damage_initial = player_damage;
	damage = player_damage;
	projectile_rotation = projectile_rotation + angle_rotation;
	touching_projectile = false;
	projectile.setRotation(projectile_rotation);
	been_init = true;
	projectile_range = projectile_range * (parent->GetProjectileRangeBonus() / 100 + 1);
	speed_projectile = speed_projectile*speed_modifier;

	slow_percent = parent->GetSlowPercentDebuffOnHit();
	if (slow_percent > 0)
	{
		type_slow = TranquilizerTalentSlow_E;
		slow_duration = parent->GetSlowDurationDebuffOnHit();
		can_slow = true;
	}
	stun_duration = parent->GetStunDurationDebuffOnHit();
	if (stun_duration > 0)
	{
		can_stun = true;
	}
}

void Bubble::InitFromSkill(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, float stun_duration_received, std::shared_ptr<Player> player, float range_modifier, float speed_modifier)
{
	parent = player;
	player.reset();
	stun_duration = stun_duration_received;
	SetAngles(mouse_position, position_player);
	projectile_position_origin = position_player;
	projectile.setPosition(sf::Vector2f(position_player.x, position_player.y));
	projectile.setTexture(texture);
	projectile_animation = 0;
	projectile.setOrigin(sf::Vector2f(size_projectile.x / 2, size_projectile.y / 2));
	damage = player_damage;
	damage_initial = player_damage;
	projectile_rotation = projectile_rotation + angle_rotation;
	AngleGestion();
	init_from_skill = true;
	touching_projectile = false;
	projectile.setRotation(projectile_rotation);
	been_init = true;
	projectile_range = projectile_range*range_modifier;
	speed_projectile = speed_projectile*speed_modifier;
}

void Bubble::SetAngles(sf::Vector2f &mouse_position, sf::Vector2f &position)
{

#pragma region GetAngle
	if (mouse_position.x > position.x && mouse_position.y < position.y)
	{
		projectile_rotation = 270 + ((((atan((mouse_position.x - position.x) / (position.y - mouse_position.y))) * 180 / PI)));
	}
	if (mouse_position.x < position.x && mouse_position.y < position.y)
	{
		projectile_rotation = 270 + ((atan((mouse_position.x - position.x) / (position.y - mouse_position.y))) * 180 / PI);
	}
	if (mouse_position.x > position.x && mouse_position.y > position.y)
	{
		projectile_rotation = (90 - ((atan((mouse_position.x - position.x) / (mouse_position.y - position.y)) * 180 / PI)));
	}
	if (mouse_position.x < position.x && mouse_position.y > position.y)
	{
		projectile_rotation = (180 - (((atan((position.y - mouse_position.y) / (mouse_position.x - position.x))) * 180 / PI)));
	}
	if (mouse_position.x == position.x && mouse_position.y <= position.y)
	{
		projectile_rotation = 270;
	}
	if (mouse_position.x == position.x && mouse_position.y >= position.y)
	{
		projectile_rotation = 90;
	}
	if (mouse_position.y == position.y && mouse_position.x >= position.x)
	{
		projectile_rotation = 0;
	}
	if (mouse_position.y == position.y && mouse_position.x <= position.x)
	{
		projectile_rotation = 180;
	}
#pragma endregion GetAngle

	if (projectile_rotation <= 315 && projectile_rotation >= 225)
	{
		projectileDirectionToPlayer = Up;
	}
	if (projectile_rotation <= 135 && projectile_rotation >= 45)
	{
		projectileDirectionToPlayer = Down;
	}
	if ((projectile_rotation <= 45 && projectile_rotation >= 0) || (projectile_rotation >= 315 && projectile_rotation <= 360))
	{
		projectileDirectionToPlayer = Right;
	}
	if (projectile_rotation <= 225 && projectile_rotation >= 135)
	{
		projectileDirectionToPlayer = Left;
	}
}

void Bubble::Update(float DELTATIME, sf::Vector2f player_position)
{
	Movement_of_projectile(DELTATIME);
	projectile_animation_gestion();
}

void Bubble::Movement_of_projectile(float DELTATIME)
{
	projectile.move((cos(projectile_rotation * PI / 180))*speed_projectile*DELTATIME, (sin(projectile_rotation * PI / 180))*speed_projectile*DELTATIME);

	sf::Vector2f position_2 = GetCurrentPosition();

	if (sqrt(((projectile_position_origin.x - position_2.x)*(projectile_position_origin.x - position_2.x)) + ((projectile_position_origin.y - position_2.y)*(projectile_position_origin.y - position_2.y))) >= projectile_range)
	{
		if (!init_from_skill)
		{
			parent->last_target_id = -3;
			parent->same_target_hit_time = 0;
		}
		is_to_delete = true;
	}
}

sf::Vector2f Bubble::GetCurrentPosition()
{
	return projectile.getPosition();
}

void Bubble::projectile_animation_gestion()
{
	if (clock_animation_of_projectile.getElapsedTime().asSeconds() >= 0.1)
	{
		been_drawed = true;
		float distance_traveled = GlobalFunction::GetDistanceBetweenTwoPositions(projectile_position_origin, GetCurrentPosition());
		float perten_of_progression = distance_traveled / projectile_range * 10;
		projectile_animation = floor(perten_of_progression);
		projectile.setTextureRect(sf::IntRect(projectile_animation * size_projectile.x, 0, size_projectile.x, size_projectile.y));
		clock_animation_of_projectile.restart();
	}
}

sf::Vector2f Bubble::GetSize()
{
	return size_projectile;
}

int Bubble::GetRayon()
{
	return rayon;
}

float Bubble::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool Bubble::IsNeedToDelete()
{
	return is_to_delete;
}

bool Bubble::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	/*if (GlobalFunction::Check_collision(rayon_1, GetRayon(), position_1, GetCurrentPosition(), size_1, GetSize()))
	{
		is_to_delete = true;
		if (!init_from_skill)
		{
			CheckPassiveSkills(id_object);
			return true;
		}
	}
	return false;*/

	if (projectile.getGlobalBounds().intersects(rect_collision))
	{
		is_to_delete = true;
		if (!init_from_skill)
		{
			CheckPassiveSkills(id_object);
			return true;
		}
	}
	return false;
}

void Bubble::ChangeProjectileRotation(float angle)
{
	projectile_rotation += angle;
}

void Bubble::Initialized(int player_id)
{
	id_parent = player_id;
}

bool Bubble::GetInitStatus()
{
	return been_init;
}

void Bubble::AngleGestion()
{
	if (projectile_rotation < 0)
	{
		projectile_rotation = 360 + projectile_rotation;
	}
	else if (projectile_rotation > 360)
	{
		projectile_rotation = projectile_rotation - 360;
	}
}

void Bubble::Draw(sf::RenderWindow &window)
{
	if (been_drawed)
	{
		window.draw(projectile);
	}
}

bool Bubble::CanAffectMonster() { return true; }

bool Bubble::CanAffectPlayer() { return false; }

bool Bubble::CanStun()
{ 
	if (init_from_skill || can_stun)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Bubble::GetStunTime() 
{ 
	return stun_duration; 
}

void Bubble::CheckPassiveSkills(int id_entity)
{
	int target_id = parent->last_target_id;

	if (parent->CheckIfPlayerHasSkill(AccurateShotEnum))
	{
		if (id_entity == target_id)
		{
			parent->same_target_hit_time++;
			damage += damage_initial * parent->same_target_hit_time / 100 * listAllSkills[AccurateShotEnum]->GetPassiveBonusValue(parent->GetLevelSpecificSkill(AccurateShotEnum), parent->GetCurrentClassPlayer(), parent->GetCurrentRuneForSpecificSkill(AccurateShotEnum));
			parent->same_target_hit_time++;
		}
		else
		{
			parent->last_target_id = id_entity;
			parent->same_target_hit_time = 0;
		}
	}
	if (parent->CheckIfPlayerHasSkill(BurningShotEnum))
	{
		int skill_level = parent->GetLevelSpecificSkill(BurningShotEnum);
		can_ignite = true;
		ignition_duration = listAllSkills[BurningShotEnum]->GetPassiveBonusDuration(skill_level, parent->GetCurrentClassPlayer(), parent->GetCurrentRuneForSpecificSkill(BurningShotEnum));
		type_ignition = listAllSkills[BurningShotEnum]->GetPassiveBonusType();
		ignition_damage = listAllSkills[BurningShotEnum]->GetPassiveBonusValue(skill_level, parent->GetCurrentClassPlayer(), parent->GetCurrentRuneForSpecificSkill(BurningShotEnum));
	}
}

bool Bubble::CanIgnite() { return can_ignite; }

int Bubble::GetTypeIgnition() { return type_ignition; }

float Bubble::GetIgnitionDuration() { return ignition_duration; }

float Bubble::GetIgnitionDamage() { return ignition_damage; }

void Bubble::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	int type_object = object_collided->GetTypeCollisionalObject();
	sf::Vector2f position_self = GetCurrentPosition();
	sf::Vector2f position_objet = object_collided->GetCurrentPosition();
	sf::Vector2f size_object = object_collided->GetSize();
	float armor_penetration = parent->GetArmorPenetrationPercent();

	if (type_object == Player_E)
	{
		if (CanAffectPlayer())
		{
			int id_object = object_collided->GetId();
			is_to_delete = true;
			if (!init_from_skill)
			{
				CheckPassiveSkills(id_object);
			}
			float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, armor_penetration);

			if (CanPush())
			{
				object_collided->GetPushedAway(GetDistancePushing(), StrongPush, position_objet, position_self);
			}
			if (CanStun())
			{
				object_collided->ChangeStunTime(GetStunTime());
			}
			if (CanChangeObjectStat())
			{
				for (int i = 0; i < GetNumberObjectStatChange(); i++)
				{
					object_collided->GivePlayerChangeStat(GetObjectStatChanging(i), GetObjectStatChangeDuration(i), GetObjectStatChangValue(i));
				}
			}
			if (CanChangeSkillCooldown())
			{
				object_collided->ChangeASkillCooldown(GetSkillCooldownChanging(), GetNewSkillCooldown());
			}
			if (CanSlow())
			{
				object_collided->GetSlowed(type_slow, GetDurationSlow(), GetPercentSlow());
			}
		}
	}

	if (type_object == Monster_E)
	{
		if (CanAffectMonster())
		{
			int id_object = object_collided->GetId();
			is_to_delete = true;
			if (!init_from_skill)
			{
				CheckPassiveSkills(id_object);
			}
			float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, armor_penetration);
			if (init_from_skill)
			{
				parent->OnHitGestion(id_object, damage_dealt, type_object, SkillProjectile_E);
			}
			else
			{
				parent->OnHitGestion(id_object, damage_dealt, type_object, BasicAttackProjectile_E);
			}
			
			TextGenerator::instance()->GenerateOneTextForBlob(position_objet, damage_dealt, size_object, object_collided);

			if (CanIgnite())
			{
				object_collided->GetIgnited(GetTypeIgnition(), GetIgnitionDuration(), GetIgnitionDamage());
			}
			if (CanPush())
			{
				object_collided->GetPushedAway(GetDistancePushing(), StrongPush, position_objet, position_self);
			}
			if (CanSlow())
			{
				object_collided->GetSlowed(type_slow, GetDurationSlow(), GetPercentSlow());
			}
			if (CanStun())
			{
				object_collided->ChangeStunTime(GetStunTime());
			}
		}
	}
	if (type_object == NatureObject_E)
	{
		if (!object_collided->CheckIfProjectileDisable())
		{
			is_to_delete = true;
		}
	}
}

void Bubble::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Bubble::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}
