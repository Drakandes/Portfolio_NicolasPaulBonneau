#include "stdafx.h"
#include "Tree.h"

Tree::Tree()
{
	if (!texture.loadFromFile("Tree.png"))
	{
		std::cout << "Error while loading trees texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("TreeShadow.png"))
	{
		std::cout << "Error while loading tree shadow texture" << std::endl;
	}
}

Tree::~Tree()
{
}

void Tree::Init(sf::Vector2f position, std::vector<sf::Vector2f> position_tree_received, std::vector<sf::Vector2i> size_tree_received, sf::RenderWindow &window)
{
	health = health_max;
	type_tree =  GlobalFunction::getRandomRange(1, size_tree_received.size()) - 1;
	position_for_cutting = position_tree_received[type_tree];
	sprite_size_cutting = size_tree_received[type_tree];
	sprite_position = position;
	sprite.setPosition(sf::Vector2f(std::round(sprite_position.x), std::round(sprite_position.y)));
	sprite.setTexture(texture); 
	sprite.setOrigin(sprite_size_cutting.x * tile_tree_size / 2, sprite_size_cutting.y * tile_tree_size);
	sprite.setTextureRect(sf::IntRect(position_for_cutting.x* tile_tree_size, position_for_cutting.y*tile_tree_size + 6*tile_tree_size*(health_max - health), sprite_size_cutting.x * tile_tree_size, sprite_size_cutting.y * tile_tree_size));
	sprite_position_collision = sprite.getPosition();
	rectangle_collision = GlobalFunction::CreateRectangleWithOrigin(sprite_size_collision, sprite_position_collision + sf::Vector2f(0, -sprite_size_collision.y / 2), sf::Color::Blue);
	rectangle_collision.setOrigin(sprite_size_collision.x / 2, sprite_size_collision.y/2);


	shadow.setPosition(sf::Vector2f(std::round(sprite_position.x), std::round(sprite_position.y) - 30));
	shadow.setTexture(shadow_texture);
	//shadow = GlobalFunction::CreateSprite(sprite_position_collision, sf::Vector2f(sprite_size_cutting.x* tile_tree_size, sprite_size_cutting.y* tile_tree_size), shadow_texture);
	shadow.setOrigin(sprite_size_cutting.x * tile_tree_size / 2, sprite_size_cutting.y * tile_tree_size);
	shadow.setTextureRect(sf::IntRect(position_for_cutting.x* tile_tree_size, position_for_cutting.y*tile_tree_size + 6 * tile_tree_size*(health_max - health), sprite_size_cutting.x * tile_tree_size, sprite_size_cutting.y * tile_tree_size));
	shadow.setRotation(180);
}
 
bool Tree::CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object)
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

void Tree::HealthGestion()
{
	if (clock_health.getElapsedTime().asSeconds() >= 30)
	{
		if (health < health_max)
		{
			number_stick_given += 2;
			health++;
			sprite.setTextureRect(sf::IntRect(position_for_cutting.x* tile_tree_size, position_for_cutting.y*tile_tree_size + 6 * tile_tree_size*(health_max - health), sprite_size_cutting.x * tile_tree_size, sprite_size_cutting.y * tile_tree_size));
			shadow.setTextureRect(sf::IntRect(position_for_cutting.x* tile_tree_size, position_for_cutting.y*tile_tree_size + 6 * tile_tree_size*(health_max - health), sprite_size_cutting.x * tile_tree_size, sprite_size_cutting.y * tile_tree_size));
		}
		if (health == health_max)
		{
			can_produce_material = true;
		}
		if (number_stick_given > 6)
		{
			number_stick_given = 6;
		}
		clock_health.restart();
	}
}

sf::Vector2f Tree::GetCurrentPosition()
{
	return rectangle_collision.getPosition();
}

void Tree::Draw(sf::RenderWindow &window)
{
	//HealthGestion();
	drawn = false;
	if (health > 0)
	{
		window.draw(sprite);
		//window.draw(rectangle_collision);
	}
}

void Tree::DrawShadow(sf::RenderWindow &window)
{
	if (health > 0)
	{
		window.draw(shadow);
	}
}

sf::Vector2f Tree::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, -10);
}

bool Tree::CanPush() { return true; }

float Tree::GetDistancePushing() { return 3; }

void Tree::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (!CheckIfProjectileDisable())
	{
		int type_object = object_collided->GetTypeCollisionalObject();
		sf::Vector2f position_self = GetCurrentPosition();
		sf::Vector2f position_objet = object_collided->GetCurrentPosition();
		sf::Vector2f size_object = object_collided->GetSize();

		if (type_object == Player_E)
		{
			float angle = GlobalFunction::GetRotationBetweenTwoPositions(position_self, position_objet);
			float distance_added = 3;

			if (angle < 315 && angle > 225)
			{
				sf::Vector2f new_position{ position_objet.x,position_self.y + sprite_size_collision.y/2+ size_object.y/2 + distance_added };
				object_collided->TeleportEntity(new_position, NatureObject_E);
			}
			if (angle < 135 && angle > 45)
			{
				sf::Vector2f new_position{ position_objet.x,position_self.y -sprite_size_collision.y / 2 - size_object.y / 2 - distance_added };
				object_collided->TeleportEntity(new_position, NatureObject_E);
			}
			if ((angle < 45 && angle > 0) || (angle > 315 && angle < 360))
			{
				sf::Vector2f new_position{ position_self.x -sprite_size_collision.x / 2 - size_object.x / 2 - distance_added, position_objet.y };
				object_collided->TeleportEntity(new_position, NatureObject_E);
			}
			if (angle < 225 && angle > 135)
			{
				sf::Vector2f new_position{ position_self.x + sprite_size_collision.x/2 + size_object.x/2 + distance_added, position_objet.y };
				object_collided->TeleportEntity(new_position, NatureObject_E);
			}

			object_collided->ChangeStunTime(0.09);
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
			if (object_collided->CanAffectMonster())
			{
				SoundGestion::instance()->AddSound("SoundTree.wav", 75, false);
			}
			if (health == 0)
			{
				for (int i = 0; i < 2; i++)
				{
					can_produce_material = false;
					std::shared_ptr<M_Stick> material_created = std::shared_ptr<M_Stick>(new M_Stick);
					material_created->Init(GetCurrentPosition(), ListObjectsSingleton::instance()->GetNewID());
					ProjectileGestion::instance()->AddObjectToList(material_created);
					MainQuadtree::instance()->insert(GetCurrentPosition(), material_created->GetSize(), material_created);
					material_created.reset();
				}

				is_to_delete = true;
			}
			sprite.setTextureRect(sf::IntRect(position_for_cutting.x* tile_tree_size, position_for_cutting.y* tile_tree_size + 6 * tile_tree_size*(health_max - health), sprite_size_cutting.x * tile_tree_size, sprite_size_cutting.y * tile_tree_size));
			shadow.setTextureRect(sf::IntRect(position_for_cutting.x* tile_tree_size, position_for_cutting.y* tile_tree_size + 6 * tile_tree_size*(health_max - health), sprite_size_cutting.x * tile_tree_size, sprite_size_cutting.y * tile_tree_size));
		}
	}
}

sf::Vector2f Tree::GetSize()
{
	return sf::Vector2f(sprite_size_cutting);
}
