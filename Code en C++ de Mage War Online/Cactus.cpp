#include "stdafx.h"
#include "Cactus.h"

Cactus::Cactus()
{
	if (!texture.loadFromFile("Cactus.png"))
	{
		std::cout << "Error while loading cactus texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("CactusShadow.png"))
	{
		std::cout << "Error while loading cactus shadow texture" << std::endl;
	}
}

Cactus::~Cactus()
{
}

void Cactus::Init(sf::Vector2f position, sf::RenderWindow &window)
{
	health = health_max;
	type_cactus = GlobalFunction::getRandomRange(1, number_different_trees) - 1;
	sprite_position = position;
	sprite.setPosition(sprite_position);
	sprite.setTexture(texture);
	sprite.setOrigin(sprite_size_cutting.x / 2, sprite_size_cutting.y);
	sprite.setTextureRect(sf::IntRect(type_cactus * sprite_size_cutting.x,0, sprite_size_cutting.x, sprite_size_cutting.y));
	sprite_position_collision = sprite_position - sf::Vector2f(0, sprite_size_collision.y / 2);
	rectangle_collision = GlobalFunction::CreateRectangle(sprite_size_collision, sprite_position_collision);
	rectangle_collision.setOrigin(sprite_size_collision.x / 2, sprite_size_collision.y / 2);
	rectangle_collision.setFillColor(sf::Color::Blue);
	//window.draw(sprite);

	shadow = GlobalFunction::CreateSprite(sprite.getPosition() + sf::Vector2f(0, sprite_size_cutting.y / 2 - 10), sf::Vector2f(sprite_size_cutting.x, sprite_size_cutting.y), shadow_texture);
	shadow.setOrigin(sf::Vector2f(sprite_size_cutting.x / 2, sprite_size_cutting.y / 2));
	shadow.setTextureRect(sf::IntRect(type_cactus * sprite_size_cutting.x, 0, sprite_size_cutting.x, sprite_size_cutting.y));
}

bool Cactus::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
{
	if (health > 0)
	{
		if (sprite.getGlobalBounds().intersects(rect_collision))
		{
			if (id_object == 1)
			{
				clock_health.restart();
				health--;
			}
			return true;
		}
	}
	return false;
}

void Cactus::HealthGestion()
{
	if (clock_health.getElapsedTime().asSeconds() >= 30)
	{
		if (health < health_max)
		{
			health++;
			sprite.setTextureRect(sf::IntRect(type_cactus * sprite_size_cutting.x, tile_cactus_height*(health_max - health), sprite_size_cutting.x, sprite_size_cutting.y));
			shadow.setTextureRect(sf::IntRect(type_cactus * sprite_size_cutting.x, tile_cactus_height*(health_max - health), sprite_size_cutting.x, sprite_size_cutting.y));
		}
		if (health == health_max)
		{
			can_produce_material = true;
		}
		clock_health.restart();
	}
}

sf::Vector2f Cactus::GetCurrentPosition()
{
	return rectangle_collision.getPosition();
}

void Cactus::Draw(sf::RenderWindow &window)
{
	//HealthGestion();
	drawn = false;
	if (health > 0)
	{
		window.draw(sprite);
		//window.draw(rectangle_collision);
	}
}

void Cactus::DrawShadow(sf::RenderWindow &window)
{
	if (health > 0)
	{
		window.draw(shadow);
	}
}

sf::Vector2f Cactus::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

bool Cactus::CanPush() { return true; }

float Cactus::GetDistancePushing() { return 3; }

float Cactus::GetDamage()
{
	return 5;
}

void Cactus::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (!CheckIfProjectileDisable())
	{
		int type_object = object_collided->GetTypeCollisionalObject();
		sf::Vector2f position_self = GetCurrentPosition();
		sf::Vector2f position_objet = object_collided->GetCurrentPosition();
		sf::Vector2f size_object = object_collided->GetSize();

		if (type_object == Player_E)
		{
			float damage_dealt = object_collided->GotDamaged(GetDamage(),-1,0);

			float angle = GlobalFunction::GetRotationBetweenTwoPositions(position_self, position_objet);
			float distance_added = 1;

			if (angle < 315 && angle > 225)
			{
				sf::Vector2f new_position{ position_objet.x,position_self.y + sprite_size_collision.y / 2 + size_object.y / 2 + distance_added };
				object_collided->TeleportEntity(new_position, NatureObject_E);
			}
			if (angle < 135 && angle > 45)
			{
				sf::Vector2f new_position{ position_objet.x,position_self.y - sprite_size_collision.y / 2 - size_object.y / 2 - distance_added };
				object_collided->TeleportEntity(new_position, NatureObject_E);
			}
			if ((angle < 45 && angle > 0) || (angle > 315 && angle < 360))
			{
				sf::Vector2f new_position{ position_self.x - sprite_size_collision.x / 2 - size_object.x / 2 - distance_added, position_objet.y };
				object_collided->TeleportEntity(new_position, NatureObject_E);
			}
			if (angle < 225 && angle > 135)
			{
				sf::Vector2f new_position{ position_self.x + sprite_size_collision.x / 2 + size_object.x / 2 + distance_added, position_objet.y };
				object_collided->TeleportEntity(new_position, NatureObject_E);
			}

			object_collided->ChangeStunTime(0.13);
		}

		if (type_object == Monster_E)
		{
			if (CanPush())
			{
				object_collided->GetPushedAway(GetDistancePushing(), StrongPush, position_objet, position_self);
			}
		}
		if (type_object == Projectile_E)
		{
			clock_health.restart();
			health--;
			if (health == 0)
			{
				if (GlobalFunction::getRandomRange(1, 1000) <= 500)
				{
					can_produce_material = false;
					std::shared_ptr<M_MagicSand> material_created = std::shared_ptr<M_MagicSand>(new M_MagicSand);
					material_created->Init(GetCurrentPosition(), ListObjectsSingleton::instance()->GetNewID());
					ProjectileGestion::instance()->AddObjectToList(material_created);
					MainQuadtree::instance()->insert(GetCurrentPosition(), material_created->GetSize(), material_created);
					material_created.reset();
				}

				is_to_delete = true;
			}
			sprite.setTextureRect(sf::IntRect(type_cactus * sprite_size_cutting.x, tile_cactus_height*(health_max - health), sprite_size_cutting.x, sprite_size_cutting.y));
			shadow.setTextureRect(sf::IntRect(type_cactus * sprite_size_cutting.x, tile_cactus_height*(health_max - health), sprite_size_cutting.x, sprite_size_cutting.y));
		}
	}
}

sf::Vector2f Cactus::GetSize()
{
	return sf::Vector2f(sprite_size_cutting);
}


