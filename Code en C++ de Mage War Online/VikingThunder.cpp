#include "stdafx.h"
#include "VikingThunder.h"

VikingThunder::VikingThunder()
{
	texture_projectile.loadFromFile("VikingThunder.png");
}

VikingThunder::~VikingThunder()
{
}

void VikingThunder::Init(sf::Vector2f &position_initial, float damage_received, int id_caster, bool can_affect_player, bool can_affect_monster)
{
	id_parent = id_caster;
	damage_initial = damage_received;
	damage = damage_received;
	size_projectile = sf::Vector2f(60, 600);
	position_origin = position_initial - sf::Vector2f(0,size_projectile.y);

	this->can_affect_player = can_affect_player;
	this->can_affect_monster = can_affect_monster;

	rect_hitbox = GlobalFunction::CreateCircleWithOrigin(position_origin, rayon + bonus_size);
	rect_hitbox.setFillColor(sf::Color::Red);
	projectile = GlobalFunction::CreateSprite(position_origin, size_projectile, texture_projectile);
	projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, size_projectile.y));
	projectile.setOrigin(size_projectile.x / 2, 0);

	circle_impact = GlobalFunction::CreateCircleWithOrigin(position_initial, rayon);
	circle_impact.setFillColor(sf::Color::Transparent);
	circle_impact.setOutlineColor(sf::Color::Color(64, 64, 64,125));
	circle_impact.setOutlineThickness(3);
	circle_channeling = GlobalFunction::CreateCircleWithOrigin(position_initial, 0);
	circle_channeling.setFillColor(sf::Color::Color(64, 64, 64,125));
}

void VikingThunder::Update(float DELTATIME, sf::Vector2f player_position)
{
	if (!spawned)
	{
		if (clock_duration.getElapsedTime().asSeconds() >= time_before_attack - time_lighting*2)
		{
			spawned = true;
			projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, 0));
		}

		circle_channeling.setRadius(rayon*clock_duration.getElapsedTime().asSeconds() / time_before_attack);
		circle_channeling.setOrigin(sf::Vector2f(circle_channeling.getRadius(), circle_channeling.getRadius()));
	}
	else
	{

		float time_passed = clock_duration.getElapsedTime().asSeconds();
		float height_lighting_percent = (time_passed - time_before_attack + time_lighting) / time_lighting;
		float height_lightning = height_lighting_percent * size_projectile.y;

		if (height_lightning > size_projectile.y)
		{
			height_lightning = size_projectile.y;
		}

		if (height_lightning < 0)
		{
			height_lightning = 0;
		}

		projectile.setTextureRect(sf::IntRect(0, 0, size_projectile.x, height_lightning));
		rect_hitbox.setPosition(position_origin + sf::Vector2f(0, height_lightning));

		if (time_passed < time_to_do_damage)
		{
			circle_channeling.setRadius(rayon*clock_duration.getElapsedTime().asSeconds() / time_before_attack);
			circle_channeling.setOrigin(sf::Vector2f(circle_channeling.getRadius(), circle_channeling.getRadius()));
		}
		else
		{
			circle_channeling.setRadius(rayon);
			circle_channeling.setOrigin(sf::Vector2f(circle_channeling.getRadius(), circle_channeling.getRadius()));
			circle_channeling.setFillColor(sf::Color::Color(146, 54, 54, 125));
			circle_impact.setOutlineColor(sf::Color::Color(146, 54, 54, 125));
		}
	}

	if (clock_duration.getElapsedTime().asSeconds() >= time_before_attack + time_lighting + 0.1)
	{
		is_to_delete = true;
	}
}

float VikingThunder::GetDamage()
{
	return damage;
}

void VikingThunder::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (clock_duration.getElapsedTime().asSeconds() >= time_to_do_damage)
	{
		int id_object = object_collided->GetId();
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

				if (CanChangeObjectStat())
				{
					for (int i = 0; i < GetNumberObjectStatChange(); i++)
					{
						object_collided->GivePlayerChangeStat(MovementSpeedPercent, 0.25, -30);
					}
				}
			}
		}
	}
}

void VikingThunder::Draw(sf::RenderWindow &window)
{
	if (!spawned)
	{
		window.draw(circle_channeling);
	}
	else
	{
		window.draw(circle_channeling);
		window.draw(projectile);
		//window.draw(rect_hitbox);
	}
}