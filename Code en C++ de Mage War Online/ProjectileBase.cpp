#include "stdafx.h"
#include "ProjectileBase.h"

ProjectileBase::ProjectileBase()
{
}

ProjectileBase::~ProjectileBase()
{
}

sf::Vector2f ProjectileBase::GetSize()
{
	return sf::Vector2f(0, 0);
 }

int ProjectileBase::GetRayon()
{
	return 1000;
 }

float ProjectileBase::GetDamage()
{
	return 0;
 }

void ProjectileBase::Update(float DELTATIME, sf::Vector2f player_position)
{

 }

bool ProjectileBase::IsNeedToDelete()
{
	return false;
 }

void ProjectileBase::Draw(sf::RenderWindow &window)
{

 }

sf::Vector2f ProjectileBase::GetCurrentPosition()
{
	return sf::Vector2f(0, 0);
 }

bool ProjectileBase::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	return false;
 }

 bool ProjectileBase::CanPush() { return false; }

float ProjectileBase::GetDistancePushing(){ return 0; }

bool ProjectileBase::CanSlow() { return false; }

float ProjectileBase::GetDurationSlow(){ return 0; }

float ProjectileBase::GetPercentSlow(){ return 0; }

bool ProjectileBase::CanStun(){ return false; }

float ProjectileBase::GetStunTime(){ return 0; }

bool ProjectileBase::CanChangeSkillCooldown(){ return 0; }

int ProjectileBase::GetSkillCooldownChanging(){ return 0; }

float ProjectileBase::GetNewSkillCooldown(){ return 0; }

bool ProjectileBase::CanChangeObjectStat(){ return false; }

int ProjectileBase::GetNumberObjectStatChange() { return 0; }

int ProjectileBase::GetObjectStatChanging(int number){ return 0; }

float ProjectileBase::GetObjectStatChangeDuration(int number ){ return 0; }

float ProjectileBase::GetObjectStatChangValue(int number){ return 0; }

bool ProjectileBase::CanIgnite(){ return false; }

int ProjectileBase::GetTypeIgnition() { return 0; }

float ProjectileBase::GetIgnitionDuration(){ return 0; }

float ProjectileBase::GetIgnitionDamage() { return 0; }

bool ProjectileBase::CanCreateExplosion() { return false; }

sf::Vector2f ProjectileBase::GetSizeExplosion() { return sf::Vector2f(0,0); }

float ProjectileBase::GetDamageExplosion() { return 0; }

float ProjectileBase::GetSizeExplosionModifier() { return 0; }

bool ProjectileBase::CanAffectMonster() { return false; }

bool ProjectileBase::CanAffectPlayer() { return false; }

void ProjectileBase::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	std::cout << "Projectile base had to deal with collision" << std::endl;
}

