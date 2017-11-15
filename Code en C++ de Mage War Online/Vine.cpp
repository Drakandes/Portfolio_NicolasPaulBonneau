#include "stdafx.h"
#include "Vine.h"

Vine::Vine()
{
	if (!texture_projectile.loadFromFile("Vine.png"))
	{
		std::cout << "Error while loading vine projectile texture" << std::endl;
	}
	listAllSkills = ListObjectsSingleton::instance()->GetListSkill();

	if (!shadow_texture.loadFromFile("VineShadow.png"))
	{
		std::cout << "Error while loading forcing bubble projectile shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
}

Vine::~Vine()
{
	parent.reset();
	listAllSkills.clear();
}

void Vine::Init(sf::Vector2f &position_player, float angle_received , float damage_received, std::shared_ptr<Player> player, float speed_modifier)
{
	parent = player;
	player.reset();
	damage_initial = damage_received;
	damage = damage_received;
	rotation_projectile = angle_received;
	position_origin = position_player;
	projectile = GlobalFunction::CreateSpriteWithoutOrigin(position_player, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(rotation_projectile);
	shadow.setRotation(rotation_projectile);
	shadow.setOrigin(0, size_projectile.y / 2);
	projectile.setOrigin(0, size_projectile.y / 2);
	rect_collision.setPosition(position_player);
	rect_collision.setSize(size_rect_collision);
	rect_collision.setRotation(rotation_projectile-90);
	rect_collision.setOrigin(sf::Vector2f(size_rect_collision.x / 2 + size_projectile.y / 4, size_rect_collision.y));
	rect_collision.setFillColor(sf::Color::Red);
	speed_projectile = speed_projectile - speed_projectile*(speed_modifier-1);

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

void Vine::InitFromSkill(sf::Vector2f &position_player, sf::Vector2f mouse_position, float damage_received,float stun_duration_received, std::shared_ptr<Player> player, float speed_modifier)
{
	parent = player;
	player.reset();
	damage_initial = damage_received;
	damage = damage_received;
	rotation_projectile = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, position_player);
	position_origin = position_player;
	projectile = GlobalFunction::CreateSpriteWithoutOrigin(position_player, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setRotation(rotation_projectile);
	shadow.setRotation(rotation_projectile);
	shadow.setOrigin(0, size_projectile.y / 2);
	projectile.setOrigin(0, size_projectile.y / 2);
	been_init = true;
	init_from_skill = true;
	if (!texture_projectile.loadFromFile("BlackVine.png"))
	{
		std::cout << "Error while loading vine projectile texture" << std::endl;
	}
	black_vine = true;
	stun_duration = stun_duration_received;
	rect_collision.setPosition(position_player);
	rect_collision.setSize(sf::Vector2f(25, size_projectile.y));
	rect_collision.setRotation(rotation_projectile);
	rect_collision.setOrigin(0, size_projectile.y / 2);
	rect_collision.setFillColor(sf::Color::Red);
	speed_projectile = speed_projectile - speed_projectile*(speed_modifier - 1);
}

void Vine::Update(float DELTATIME, sf::Vector2f player_position)
{
	CuttingSprite();
}

void Vine::Movement_of_fireball(sf::Vector2f player_position,sf::Vector2f mouse_position, float DELTATIME)
{
}

sf::Vector2f Vine::GetCurrentPosition()
{
	return rect_collision.getPosition();
}

sf::Vector2f Vine::GetSize()
{
	return size_rect_collision;
}

int Vine::GetRayon()
{
	return rayon;
}

float Vine::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool Vine::IsNeedToDelete()
{
	return is_to_delete;
}

bool Vine::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (projectile.getGlobalBounds().intersects(rect_collision))
	{
		is_to_delete = true;
		if (!init_from_skill)
		{
			CheckPassiveSkills(id_object);
		}
		return true;
	}
	return false;
}

void Vine::Initialized(int player_id)
{
	id_parent = player_id;
}

void Vine::CuttingSprite()
{
	if (clock_animation.getElapsedTime().asSeconds() >= speed_projectile && !is_reducing)
	{
		projectile.setTextureRect(sf::IntRect(0, size_projectile_for_cutting.y*holder_cuting_sprite.y, size_projectile_for_cutting.x, size_projectile_for_cutting.y));
		shadow.setTextureRect(sf::IntRect(0, size_projectile_for_cutting.y*holder_cuting_sprite.y, size_projectile_for_cutting.x, size_projectile_for_cutting.y));
		holder_cuting_sprite.y++;
		if (holder_cuting_sprite.y >= dimension_texture.y)
		{
			holder_cuting_sprite.y = dimension_texture.y - 1;
			is_reducing = true;
		}
		float current_size_vine = 25 * holder_cuting_sprite.y;
		rect_collision.setPosition(projectile.getPosition() + sf::Vector2f((cos(rotation_projectile * PI / 180))*current_size_vine, (sin(rotation_projectile * PI / 180))*current_size_vine));
		been_drawed = true;
		clock_animation.restart();
	}
	else if (clock_animation.getElapsedTime().asSeconds() >= speed_projectile && is_reducing)
	{
		projectile.setTextureRect(sf::IntRect(0, size_projectile_for_cutting.y * holder_cuting_sprite.y, size_projectile_for_cutting.x, size_projectile_for_cutting.y));
		shadow.setTextureRect(sf::IntRect(0, size_projectile_for_cutting.y * holder_cuting_sprite.y, size_projectile_for_cutting.x, size_projectile_for_cutting.y));
		holder_cuting_sprite.y--;
		if (holder_cuting_sprite.y < 0)
		{
			if (!init_from_skill)
			{
				parent->last_target_id = -3;
				parent->same_target_hit_time = 0;
			}
			is_to_delete = true;
		}
		float current_size_vine = 25 * (holder_cuting_sprite.y + 1);
		rect_collision.setPosition(	projectile.getPosition() + sf::Vector2f((cos(rotation_projectile * PI / 180))*current_size_vine, (sin(rotation_projectile * PI / 180))*current_size_vine));
		been_drawed = true;
		clock_animation.restart();
	}
}

bool Vine::GetInitStatus()
{
	return been_init;
}

void Vine::Draw(sf::RenderWindow &window)
{
	if (been_drawed)
	{
		
		window.draw(projectile);
	//	window.draw(rect_collision);
	}
}

void Vine::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(projectile.getPosition() + sf::Vector2f(0, 12));
	window.draw(shadow);
}

sf::Vector2f Vine::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool Vine::CanAffectMonster() { return true; }

bool Vine::CanAffectPlayer() { return false; }

bool Vine::CanStun()
{
	if (black_vine || can_stun)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Vine::GetStunTime()
{
	return stun_duration;
}

void Vine::CheckPassiveSkills(int id_entity)
{
	int target_id = parent->last_target_id;

	if (parent->CheckIfPlayerHasSkill(AccurateShotEnum))
	{
		if (id_entity == target_id)
		{
			damage += damage_initial * parent->same_target_hit_time / 100 * listAllSkills[AccurateShotEnum]->GetPassiveBonusValue(parent->GetLevelSpecificSkill(AccurateShotEnum), parent->GetCurrentClassPlayer(), parent->GetCurrentRuneForSpecificSkill(AccurateShotEnum));
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

bool Vine::CanIgnite() { return can_ignite; }

int Vine::GetTypeIgnition() { return type_ignition; }

float Vine::GetIgnitionDuration() { return ignition_duration; }

float Vine::GetIgnitionDamage() { return ignition_damage; }

void Vine::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (true)
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
				TextGenerator::instance()->GenerateOneTextForBlob(position_objet, damage_dealt, size_object, object_collided);
				if (init_from_skill)
				{
					parent->OnHitGestion(id_object, damage_dealt, type_object, SkillProjectile_E);
				}
				else
				{
					parent->OnHitGestion(id_object, damage_dealt, type_object, BasicAttackProjectile_E);
				}
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
}

void Vine::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Vine::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}