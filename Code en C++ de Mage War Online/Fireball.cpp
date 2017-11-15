#include "stdafx.h"
#include "Fireball.h"
#include <iostream>
#include "GlobalFunction.h"
#include "GlobalEnum.h"

Fireball::Fireball()
{
	if (!fireball_texture.loadFromFile("Fireball.png"))
	{
		std::cout << "Error: Couldn't load Fireball texture" << std::endl;
	}

	listAllSkills = ListObjectsSingleton::instance()->GetListSkill();

	if (!shadow_texture.loadFromFile("FireballShadow.png"))
	{
		std::cout << "Error while loading fireball projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

Fireball::~Fireball()
{
	parent.reset();
	listAllSkills.clear();
}

void Fireball::Texture_loading()
{
	if (!fireball_texture.loadFromFile("Fireball.png"))
	{
		std::cout << "Error: Couldn't load Fireball texture" << std::endl;
	}
	parent.reset();
}

void Fireball::Init(sf::Vector2f &position_player, float angle_received, float player_damage, std::shared_ptr<Player> player, float speed_modifier)
{
	parent = player;
	player.reset();
	fireball_image_rotation = angle_received;
	fireball_image_position_origin = position_player;
	fireball_image = GlobalFunction::CreateSprite(position_player, sf::Vector2f(fireball_image_size_x, fireball_image_size_y), fireball_texture);
	fireball_image.setTexture(fireball_texture);
	fireball_image_animation = 0;
	fireball_reapparition = false;
	fireball_speed = speed_of_fireball;
	fireball_damage_initial = player_damage;
	fireball_damage = player_damage;
	fireball_image_rotation = fireball_image_rotation + angle_rotation;
	touching_fireball = false;
	fireball_image.setRotation(fireball_image_rotation);
	shadow.setRotation(fireball_image_rotation);
	been_init = true;
	fireball_range = fireball_range * (parent->GetProjectileRangeBonus() / 100 + 1);
	speed_of_fireball = speed_of_fireball * speed_modifier;
	speed_of_fireball_accelerated_3 = speed_of_fireball * 3;
	speed_of_fireball_accelerated_2 = speed_of_fireball * 2;

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

void Fireball::InitFromSkill(sf::Vector2f &position_player, int player_damage, float fireball_range_modified, float fireball_speed_modifier, sf::Vector2f mouse_position, std::shared_ptr<Player> player, float speed_modifier)
{
	parent = player;
	player.reset();
	SetAngles(mouse_position, position_player);
	fireball_image = GlobalFunction::CreateSprite(position_player, sf::Vector2f(fireball_image_size_x, fireball_image_size_y), fireball_texture);
	fireball_image_animation = 0;
	fireball_reapparition = false;
	fireball_speed = speed_of_fireball;
	fireball_image.setOrigin(sf::Vector2f(fireball_image_size_x / 2, fireball_image_size_y / 2));
	fireball_damage = player_damage;
	fireball_image_rotation = fireball_image_rotation + angle_rotation;
	touching_fireball = false;
	fireball_image_position_origin = position_player;
	fireball_image.setRotation(fireball_image_rotation);
	shadow.setRotation(fireball_image_rotation);
	been_init = true;
	init_from_skill = true;
	fireball_range = fireball_range_modified;
	speed_of_fireball = 225 * speed_modifier*fireball_speed_modifier;
	speed_of_fireball_accelerated_3 = speed_of_fireball * 3;
	speed_of_fireball_accelerated_2 = speed_of_fireball * 2;
}

void Fireball::SetAngles(sf::Vector2f &mouse_position, sf::Vector2f &position)
{

#pragma region GetAngle
	if (mouse_position.x > position.x && mouse_position.y < position.y)
	{
		fireball_image_rotation = 270 + ((((atan((mouse_position.x - position.x) / (position.y - mouse_position.y))) * 180 / PI)));
	}
	if (mouse_position.x < position.x && mouse_position.y < position.y)
	{
		fireball_image_rotation = 270 + ((atan((mouse_position.x - position.x) / (position.y - mouse_position.y))) * 180 / PI);
	}
	if (mouse_position.x > position.x && mouse_position.y > position.y)
	{
		fireball_image_rotation = (90 - ((atan((mouse_position.x - position.x) / (mouse_position.y - position.y)) * 180 / PI)));
	}
	if (mouse_position.x < position.x && mouse_position.y > position.y)
	{
		fireball_image_rotation = (180 - (((atan((position.y - mouse_position.y) / (mouse_position.x - position.x))) * 180 / PI)));
	}
	if (mouse_position.x == position.x && mouse_position.y <= position.y)
	{
		fireball_image_rotation = 270;
	}
	if (mouse_position.x == position.x && mouse_position.y >= position.y)
	{
		fireball_image_rotation = 90;
	}
	if (mouse_position.y == position.y && mouse_position.x >= position.x)
	{
		fireball_image_rotation = 0;
	}
	if (mouse_position.y == position.y && mouse_position.x <= position.x)
	{
		fireball_image_rotation = 180;
	}
#pragma endregion GetAngle

	if (fireball_image_rotation <= 315 && fireball_image_rotation >= 225)
	{
		fireballDirectionToPlayer = Up;
	}
	if (fireball_image_rotation <= 135 && fireball_image_rotation >= 45)
	{
		fireballDirectionToPlayer = Down;
	}
	if ((fireball_image_rotation <= 45 && fireball_image_rotation >= 0) || (fireball_image_rotation >= 315 && fireball_image_rotation <= 360))
	{
		fireballDirectionToPlayer = Right;
	}
	if (fireball_image_rotation <= 225 && fireball_image_rotation >= 135)
	{
		fireballDirectionToPlayer = Left;
	}
}

void Fireball::Update(float DELTATIME, sf::Vector2f player_position)
{
	Movement_of_fireball(DELTATIME);
	fireball_animation_gestion();
}

void Fireball::Movement_of_fireball(float DELTATIME)
{
	fireball_image.move((cos(fireball_image_rotation * PI / 180))*fireball_speed*DELTATIME, (sin(fireball_image_rotation * PI / 180))*fireball_speed*DELTATIME);

	sf::Vector2f position_2 = GetCurrentPosition();

	if (sqrt(((fireball_image_position_origin.x - position_2.x)*(fireball_image_position_origin.x - position_2.x)) + ((fireball_image_position_origin.y - position_2.y)*(fireball_image_position_origin.y - position_2.y))) >= fireball_range)
	{
		if (!init_from_skill)
		{
			parent->last_target_id = -3;
			parent->same_target_hit_time = 0;
		}
		is_to_delete = true;
	}
}

sf::Vector2f Fireball::GetCurrentPosition()
{
	return fireball_image.getPosition();
}

void Fireball::fireball_animation_gestion()
{
	if (fireball_image_animation == 0 || fireball_image_animation == 10 || fireball_image_animation == 11)
	{
		fireball_speed = speed_of_fireball_accelerated_3;
	}
	else if (fireball_image_animation == 1 || fireball_image_animation == 2 || fireball_image_animation == 3 || fireball_image_animation == 4)
	{
		fireball_speed = speed_of_fireball_accelerated_2;
	}
	else if (fireball_image_animation == 9)
	{
		fireball_speed = 0;
	}
	else
	{
		fireball_speed = speed_of_fireball;
	}

	if (clock_animation_of_fireball.getElapsedTime().asSeconds() >= 0.1)
	{
		drawed = true;
		fireball_image.setTextureRect(sf::IntRect(fireball_image_animation * fireball_image_size_x, 0, fireball_image_size_x, fireball_image_size_y));
		shadow.setTextureRect(sf::IntRect(fireball_image_animation * shadow_size.x, 0, shadow_size.x, shadow_size.y));
		animation_started = true;

		if (!fireball_reapparition)
			fireball_image_animation++;
		if (fireball_image_animation >= 12 && !fireball_reapparition)
		{
			fireball_image_animation = 0;
			fireball_reapparition = true;
		}
		clock_animation_of_fireball.restart();
	}
}

sf::Vector2f Fireball::GetSize()
{
	sf::Vector2f size(fireball_image_size_x, fireball_image_size_y);
	return size;
}

int Fireball::GetRayon()
{
	return rayon;
}

float Fireball::GetDamage()
{
	is_to_delete = true;
	return fireball_damage;
}

bool Fireball::IsNeedToDelete()
{
	return is_to_delete;
}

void Fireball::ChangeFireballRotation(float angle)
{
	angle_rotation = angle;
}

void Fireball::Initialized(int player_id)
{
	id_parent = player_id;
}

bool Fireball::GetInitStatus()
{
	return been_init;
}

bool Fireball::GetAnimationStarted()
{
	return animation_started;
}

void Fireball::Draw(sf::RenderWindow &window)
{
	if (init_from_skill)
	{
		if (drawed)
		{
			window.draw(fireball_image);
		}
	}
	else
	{
		window.draw(fireball_image);
	}
}

void Fireball::DrawShadow(sf::RenderWindow &window)
{
	if (init_from_skill)
	{
		if (drawed)
		{
			shadow.setPosition(fireball_image.getPosition() + sf::Vector2f(0, 30));
			window.draw(shadow);

		}
	}
	else
	{
		shadow.setPosition(fireball_image.getPosition() + sf::Vector2f(0, 18));
		window.draw(shadow);
	}
}

sf::Vector2f Fireball::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, -fireball_image_size_y);
}

bool Fireball::CanAffectMonster() { return true; }

bool Fireball::CanAffectPlayer() { return false; }

void Fireball::CheckPassiveSkills(int id_entity)
{
	int target_id = parent->last_target_id;

	if (parent->CheckIfPlayerHasSkill(AccurateShotEnum))
	{
		if (id_entity == target_id)
		{
			fireball_damage += fireball_damage_initial * parent->same_target_hit_time / 100 * listAllSkills[AccurateShotEnum]->GetPassiveBonusValue(parent->GetLevelSpecificSkill(AccurateShotEnum), parent->GetCurrentClassPlayer(), parent->GetCurrentRuneForSpecificSkill(AccurateShotEnum));
			parent->same_target_hit_time++;
		}
		else
		{
			parent->same_target_hit_time++;
			parent->last_target_id = id_entity;
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

bool Fireball::CanIgnite() { return can_ignite; }

int Fireball::GetTypeIgnition() { return type_ignition; }

float Fireball::GetIgnitionDuration() { return ignition_duration; }

float Fireball::GetIgnitionDamage() { return ignition_damage; }

void Fireball::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
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

void Fireball::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Fireball::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}