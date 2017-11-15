#include "stdafx.h"
#include "PushImpact.h"

PushImpact::PushImpact()
{

}

PushImpact::~PushImpact()
{
}

void  PushImpact::Init(sf::Vector2f &position_initial, float damage_received, int id_caster)
{
	id_parent = id_caster;
	damage = damage_received;
	position_origin = position_initial;
	circle_impact = GlobalFunction::CreateCircleWithOrigin(position_initial, rayon);
	circle_impact.setFillColor(sf::Color::Transparent);
	circle_impact.setOutlineColor(sf::Color::Color(151, 26, 19));
	circle_impact.setOutlineThickness(3);
	circle_channeling = GlobalFunction::CreateCircleWithOrigin(position_initial, 0);
	circle_channeling.setFillColor(sf::Color::Color(151, 26, 19));
}

void PushImpact::Update(float DELTATIME, sf::Vector2f player_position)
{
	circle_channeling.setRadius(rayon*clock_creation.getElapsedTime().asSeconds() / time_channeling);
	circle_channeling.setOrigin(sf::Vector2f(circle_channeling.getRadius(), circle_channeling.getRadius()));

	if (clock_creation.getElapsedTime().asSeconds() > time_channeling)
	{
		std::shared_ptr<Explosion> projectile = std::shared_ptr<Explosion>(new Explosion());
		projectile->Init(position_origin, damage,  id_parent, push_distance);
		ProjectileGestion::instance()->AddObjectToList(projectile);
		projectile.reset();
		is_to_delete = true;
	}
}

sf::Vector2f  PushImpact::GetCurrentPosition()
{
	return circle_impact.getPosition();
}

int  PushImpact::GetRayon()
{
	return rayon;
}

float  PushImpact::GetDamage()
{
	is_to_delete = true;
	return damage;
}

bool  PushImpact::IsNeedToDelete()
{
	return is_to_delete;
}

void PushImpact::Draw(sf::RenderWindow &window)
{
	window.draw(circle_impact);
	window.draw(circle_channeling);
}

bool PushImpact::CanAffectMonster() { return false; }

bool PushImpact::CanAffectPlayer() { return true; }

void PushImpact::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (channeled)
	{
		int type_object = object_collided->GetTypeCollisionalObject();
		sf::Vector2f position_self = GetCurrentPosition();
		sf::Vector2f position_objet = object_collided->GetCurrentPosition();
		sf::Vector2f size_object = object_collided->GetSize();

		if (type_object == Player_E)
		{
			if (CanAffectPlayer())
			{
				is_to_delete = true;
				float damage_dealt = object_collided->GotDamaged(GetDamage(), id_parent, 0);

				if (CanPush())
				{
					object_collided->GetPushedAway(GetDistancePushing(), StrongPush, position_objet, position_self);
				}
			}
		}
	}
}

void PushImpact::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool PushImpact::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}