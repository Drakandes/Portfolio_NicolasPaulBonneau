#include "stdafx.h"
#include "Quadtree.h"

Quadtree::Quadtree(int plevel, sf::Vector2f size_received, sf::Vector2f position_received, int index)
{
	level = plevel;
	size_quadtree = size_received;
	position_quadtree = position_received;
	rect = GlobalFunction::CreateRectangleWithOrigin(size_quadtree, position_quadtree, sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(2);
	this->index = index;
	floatrect = rect.getGlobalBounds();
}

Quadtree::~Quadtree()
{
	ObjectsMonster.clear();
	ObjectsPlayer.clear();
	ObjectsProjectile.clear();
	ObjectsNature.clear();
}

void Quadtree::Clear()
{
	if(nodes.size() > 0)
	{
		for (size_t i = 0; i < nodes.size(); i++)
		{
			nodes[i]->Clear();
		}
	}
	nodes.clear();
	ObjectsMonster.clear();
	ObjectsPlayer.clear();
	ObjectsProjectile.clear();
	ObjectsNature.clear();
}

void Quadtree::Split()
{
	sf::Vector2f size_nodes = sf::Vector2f(size_quadtree.x / 2, size_quadtree.y / 2);
	float x = size_quadtree.x / 4;
	float y = size_quadtree.y / 4;
	int new_level = level + 1;
	std::shared_ptr<Quadtree> quadtree1 = std::shared_ptr<Quadtree>(new Quadtree(new_level, size_nodes, sf::Vector2f(position_quadtree.x + x, position_quadtree.y + y), TopLeftQuadrant));
	std::shared_ptr<Quadtree> quadtree2 = std::shared_ptr<Quadtree>(new Quadtree(new_level, size_nodes, sf::Vector2f(position_quadtree.x - x, position_quadtree.y + y),BottomLeftQuadrant));
	std::shared_ptr<Quadtree> quadtree3 = std::shared_ptr<Quadtree>(new Quadtree(new_level, size_nodes, sf::Vector2f(position_quadtree.x - x, position_quadtree.y - y),BottomRightQuadrant));
	std::shared_ptr<Quadtree> quadtree4 = std::shared_ptr<Quadtree>(new Quadtree(new_level, size_nodes, sf::Vector2f(position_quadtree.x + x, position_quadtree.y - y), TopRightQuadrant));
	nodes.push_back(quadtree1);
	nodes.push_back(quadtree2);
	nodes.push_back(quadtree3);
	nodes.push_back(quadtree4);
	quadtree1.reset();
	quadtree2.reset();
	quadtree3.reset();
	quadtree4.reset();
}

bool Quadtree::CheckIfStillIn(sf::FloatRect object_collision_box)
{
	if (rect.getGlobalBounds().intersects(object_collision_box))
	{
		return true;
	}
	return false;
}

bool Quadtree::getIndex(sf::FloatRect object_collision_box)
{
	if (rect.getGlobalBounds().intersects(object_collision_box))
	{
		return true;
	}
	return false;
}

void Quadtree::insert(std::shared_ptr<CollisionalObject> object)
{
	if (object->GetTypeCollisionalObject() != NatureObject_E)
	{
		if (nodes.size() > 0)
		{
			/*int holder = getIndex(position_object, size_object);

			if(holder != -1)
			{
				nodes[holder]->insert(position_object, size_object, object);
			}
			else
			{
				ObjectsWithinQuadtree.push_back(object);
			}*/
			bool found_node_fitting = false;
			for (size_t holder = 0; holder < nodes.size(); holder++)
			{
				if (nodes[holder]->getIndex(object->GetCollisionRect()))
				{
					nodes[holder]->insert(object);
					found_node_fitting = true;
				}
			}
			if (!found_node_fitting)
			{
				AddObjectInList(object);
			}
		}
		else
		{
			AddObjectInList(object);
		}
	}
	else
	{
		if (nodes.size() > 0)
		{
			bool found_node_fitting = false;
			for (size_t holder = 0; holder < nodes.size(); holder++)
			{
				if (nodes[holder]->getIndex(object->GetCollisionRect()))
				{
					nodes[holder]->insert(object);
					found_node_fitting = true;
				}
			}
			if (!found_node_fitting)
			{
				ObjectsNature.push_back(object);
			}
		}
		else
		{
			ObjectsNature.push_back(object);
		}
	}
	if (ObjectsMonster.size() + ObjectsPlayer.size() + ObjectsProjectile.size() + ObjectsNature.size() > MAX_OBJECTS && level < MAX_LEVELS)
	{
		if (nodes.size() == 0)
		{
			Split();
		}

		std::list<std::shared_ptr<CollisionalObject>>::iterator i_player = ObjectsPlayer.begin();
		while (i_player != ObjectsPlayer.end())
		{
			bool removed = false;
			for (size_t holder = 0; holder < nodes.size(); holder++)
			{
				if (nodes[holder]->getIndex((*i_player)->GetCollisionRect()))
				{
					nodes[holder]->insert( *i_player);
					removed = true;
				}
			}
			if (!removed)
			{
				i_player++;
			}
			else
			{
				ObjectsPlayer.erase(i_player++);
			}
		}

		std::list<std::shared_ptr<CollisionalObject>>::iterator i_monster = ObjectsMonster.begin();
		while (i_monster != ObjectsMonster.end())
		{
			bool removed = false;
			for (size_t holder = 0; holder < nodes.size(); holder++)
			{
				if (nodes[holder]->getIndex((*i_monster)->GetCollisionRect()))
				{
					nodes[holder]->insert( *i_monster);
					removed = true;
				}
			}
			if (!removed)
			{
				i_monster++;
			}
			else
			{
				ObjectsMonster.erase(i_monster++);
			}
		}

		std::list<std::shared_ptr<CollisionalObject>>::iterator i_projectile = ObjectsProjectile.begin();
		while (i_projectile != ObjectsProjectile.end())
		{
			bool removed = false;
			for (size_t holder = 0; holder < nodes.size(); holder++)
			{
				if (nodes[holder]->getIndex((*i_projectile)->GetCollisionRect()))
				{
					nodes[holder]->insert(*i_projectile);
					removed = true;
				}
			}
			if (!removed)
			{
				i_projectile++;
			}
			else
			{
				ObjectsProjectile.erase(i_projectile++);
			}
		}

		std::list<std::shared_ptr<CollisionalObject>>::iterator ii = ObjectsNature.begin();
		while (ii != ObjectsNature.end())
		{
			bool removed = false;
			for (size_t holder = 0; holder < nodes.size(); holder++)
			{
				if (nodes[holder]->getIndex((*ii)->GetCollisionRect()))
				{
					nodes[holder]->insert(*ii);
					removed = true;
				}
			}
			if (!removed)
			{
				ii++;
			}
			else
			{
				ObjectsNature.erase(ii++);
			}
		}
	}
}

void Quadtree::CheckCollision(sf::FloatRect map_part_activated)
{
	if (nodes.size() > 0)
	{
		for (size_t i = 0; i < nodes.size(); i++)
		{
			if (i > 3)
			{
				std::cout << "Error" << std::endl;
			}
			nodes[i]->CheckCollision(map_part_activated);
		}
	}

	if (clock_collision.getElapsedTime().asMilliseconds() >= 1000 / 40)
	{
		clock_collision.restart();

#pragma region ProjectileCollisionAgainstEverything
		std::list<std::shared_ptr<CollisionalObject>>::iterator projectile = ObjectsProjectile.begin();
		while (projectile != ObjectsProjectile.end())
		{
			bool to_delete = (*projectile)->IsNeedToDelete();
			if (to_delete)
			{
				projectile++;
				continue;
			}
			std::list<std::shared_ptr<CollisionalObject>>::iterator projectile_2nd_list = ObjectsProjectile.begin();
			while (projectile_2nd_list != ObjectsProjectile.end())
			{
				bool to_delete_first_object = (*projectile)->IsNeedToDelete();
				if (to_delete_first_object)
				{
					break;
				}

				if (projectile != projectile_2nd_list)
				{
					bool to_delete_second_object = (*projectile_2nd_list)->IsNeedToDelete();
					if (to_delete_second_object)
					{
						projectile_2nd_list++;
						continue;
					}
					else
					{
						if ((*projectile)->GetCollisionRect().intersects((*projectile_2nd_list)->GetCollisionRect()))
						{
							(*projectile)->DealWithCollision(*projectile_2nd_list);
							(*projectile_2nd_list)->DealWithCollision(*projectile);
						}
						projectile_2nd_list++;
					}
				}
				else
				{
					projectile_2nd_list++;
				}
			}

			std::list<std::shared_ptr<CollisionalObject>>::iterator nature = ObjectsNature.begin();
			while (nature != ObjectsNature.end())
			{
				bool to_delete = (*projectile)->IsNeedToDelete();
				if (to_delete)
				{
					break;
				}
				else
				{
					if ((*projectile)->GetCollisionRect().intersects((*nature)->GetCollisionRect()))
					{
						(*projectile)->DealWithCollision(*nature);
						(*nature)->DealWithCollision(*projectile);
					}
				}
				nature++;
			}

			std::list<std::shared_ptr<CollisionalObject>>::iterator monster = ObjectsMonster.begin();
			while (monster != ObjectsMonster.end())
			{
				bool to_delete = (*projectile)->IsNeedToDelete();
				if (to_delete)
				{
					break;
				}
				else
				{
					if ((*projectile)->GetCollisionRect().intersects((*monster)->GetCollisionRect()))
					{
						(*projectile)->DealWithCollision(*monster);
						(*monster)->DealWithCollision(*projectile);
					}
				}
				if ((*monster)->IsNeedToDelete())
				{
					ObjectsMonster.erase(monster++);
				}
				else
				{
					monster++;
				}
			}

			std::list<std::shared_ptr<CollisionalObject>>::iterator player = ObjectsPlayer.begin();
			while (player != ObjectsPlayer.end())
			{
				bool to_delete = (*projectile)->IsNeedToDelete();
				if (to_delete)
				{
					break;
				}
				else
				{
					if ((*projectile)->GetCollisionRect().intersects((*player)->GetCollisionRect()))
					{
						(*projectile)->DealWithCollision(*player);
						if (ObjectsPlayer.size() != 0 && ObjectsProjectile.size() != 0)
						{
							if (player != ObjectsPlayer.end() && projectile != ObjectsProjectile.end())
							{
								if ((*projectile) != NULL && (*player) != NULL)
								{
									(*player)->DealWithCollision(*projectile);
								}
							}
						}
					}
				}
				if (ObjectsPlayer.size() != 0)
				{
					if ((*player)->IsNeedToDelete())
					{
						ObjectsPlayer.erase(player++);
					}
					else
					{
						player++;
					}
				}
			}

			projectile++;
		}
#pragma endregion ProjectileCollisionAgainstEverything

#pragma region PlayerAgainstMonsterAndNature
		std::list<std::shared_ptr<CollisionalObject>>::iterator player = ObjectsPlayer.begin();
		while (player != ObjectsPlayer.end())
		{
			std::list<std::shared_ptr<CollisionalObject>>::iterator monster = ObjectsMonster.begin();
			while (monster != ObjectsMonster.end())
			{
				bool to_delete = (*player)->IsNeedToDelete();
				if (to_delete)
				{
					break;
				}
				else
				{
					if ((*player)->GetCollisionRect().intersects((*monster)->GetCollisionRect()))
					{
						(*player)->DealWithCollision(*monster);
						(*monster)->DealWithCollision(*player);
					}
				}
				if ((*monster)->IsNeedToDelete())
				{
					ObjectsMonster.erase(monster++);
				}
				else
				{
					monster++;
				}
			}

			std::list<std::shared_ptr<CollisionalObject>>::iterator material = ObjectsMaterial.begin();
			while (material != ObjectsMaterial.end())
			{
				bool to_delete = (*player)->IsNeedToDelete();
				if (to_delete)
				{
					break;
				}
				else
				{
					if ((*player)->GetCollisionRect().intersects((*material)->GetCollisionRect()))
					{
						(*player)->DealWithCollision(*material);
						(*material)->DealWithCollision(*player);
					}
				}
				if ((*material)->IsNeedToDelete())
				{
					ObjectsMaterial.erase(material++);
				}
				else
				{
					material++;
				}
			}

			std::list<std::shared_ptr<CollisionalObject>>::iterator nature = ObjectsNature.begin();
			while (nature != ObjectsNature.end())
			{
				bool to_delete = (*player)->IsNeedToDelete();
				if (to_delete)
				{
					break;
				}
				else
				{
					if ((*player)->GetCollisionRect().intersects((*nature)->GetCollisionRect()))
					{
						(*player)->DealWithCollision(*nature);
						(*nature)->DealWithCollision(*player);
					}
				}
				nature++;
			}

			if ((*player)->IsNeedToDelete())
			{
				ObjectsPlayer.erase(player++);
			}
			else
			{
				player++;
			}
		}
#pragma endregion PlayerAgainstMonsterMaterialAndNature

#pragma region MonsterAgainstnature
		std::list<std::shared_ptr<CollisionalObject>>::iterator monster = ObjectsMonster.begin();
		while (monster != ObjectsMonster.end())
		{
			std::list<std::shared_ptr<CollisionalObject>>::iterator nature = ObjectsNature.begin();
			while (nature != ObjectsNature.end())
			{
				bool to_delete = (*monster)->IsNeedToDelete();
				if (to_delete)
				{
					break;
				}
				else
				{
					if ((*monster)->GetCollisionRect().intersects((*nature)->GetCollisionRect()))
					{
						(*monster)->DealWithCollision(*nature);
						(*nature)->DealWithCollision(*monster);
					}
				}
				nature++;
			}
			if ((*monster)->IsNeedToDelete())
			{
				ObjectsMonster.erase(monster++);
			}
			else
			{
				monster++;
			}
		}
#pragma endregion MonsterAgainstnature

		std::list<std::shared_ptr<CollisionalObject>>::iterator i = ObjectsProjectile.begin();
		while (i != ObjectsProjectile.end())
		{
			bool need_to_delete = (*i)->IsNeedToDelete();
			if (need_to_delete)
			{
				ObjectsProjectile.erase(i++);
			}
			else
			{
				i++;
			}
		}
	}
}

void Quadtree::Draw(sf::RenderWindow &window)
{
	window.draw(rect);

	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (nodes.size() > 0)
		{
			nodes[i]->Draw(window);
		}
	}
}

void Quadtree::UpdatePositionsObjects(sf::FloatRect map_part_activated)
{
	if (nodes.size() > 0)
	{
		for (size_t i = 0; i < nodes.size(); i++)
		{
			nodes[i]->UpdatePositionsObjects(map_part_activated);
		}
	}

	std::list<std::shared_ptr<CollisionalObject>>::iterator i_monster = ObjectsMonster.begin();
	while (i_monster != ObjectsMonster.end())
	{
		/*if (!(CheckIfStillIn((*i_monster)->GetCollisionRect())))
		{*/
			(*i_monster)->PutItBackInQuadtree();
			ObjectsMonster.erase(i_monster++);
		/*}
		else
		{
			i_monster++;
		}*/
	}

	std::list<std::shared_ptr<CollisionalObject>>::iterator i_player = ObjectsPlayer.begin();
	while (i_player != ObjectsPlayer.end())
	{
		if (!(CheckIfStillIn((*i_player)->GetCollisionRect())))
		{
			(*i_player)->PutItBackInQuadtree();
			ObjectsPlayer.erase(i_player++);
		}
		else
		{
			i_player++;
		}
	}

	std::list<std::shared_ptr<CollisionalObject>>::iterator i_projectile = ObjectsProjectile.begin();
	while (i_projectile != ObjectsProjectile.end())
	{
		//if (!(CheckIfStillIn((*i_projectile)->GetCollisionRect())))
		//{
			(*i_projectile)->PutItBackInQuadtree();
			ObjectsProjectile.erase(i_projectile++);
		/*}
		else
		{
			i_projectile++;
		}*/
	}

	std::list<std::shared_ptr<CollisionalObject>>::iterator i_material = ObjectsMaterial.begin();
	while (i_material != ObjectsMaterial.end())
	{
		if (!(CheckIfStillIn((*i_material)->GetCollisionRect())))
		{
			(*i_material)->PutItBackInQuadtree();
			ObjectsMaterial.erase(i_material++);
		}
		else
		{
			i_material++;
		}
	}
	std::list<std::shared_ptr<CollisionalObject>>::iterator i_nature = ObjectsNature.begin();
	while (i_nature != ObjectsNature.end())
	{
		if ((*i_nature)->IsNeedToDelete())
		{
			ObjectsNature.erase(i_nature++);
		}
		else
		{
			i_nature++;
		}
	}
}

bool Quadtree::CheckIfToDelete()
{
	if (ObjectsMonster.size() > 0)
	{
		return false;
	}
	if (ObjectsPlayer.size() > 0)
	{
		return false;
	}
	if (ObjectsProjectile.size() > 0)
	{
		return false;
	}
	if (ObjectsNature.size() > 0)
	{
		return false;
	}

	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (!(nodes[i]->CheckIfToDelete()))
		{
			return false;
		}
	}

	nodes.clear();

	return true;
}

void Quadtree::AddObjectInList(std::shared_ptr<CollisionalObject> object)
{
	int type_object = object->GetTypeCollisionalObject();

	if (type_object == Monster_E)
	{
		ObjectsMonster.push_back(object);
	}
	else if (type_object == Projectile_E)
	{
		ObjectsProjectile.push_back(object);
	}
	else if (type_object == NatureObject_E)
	{
		ObjectsNature.push_back(object);
	}
	else if (type_object == Player_E)
	{
		ObjectsPlayer.push_back(object);
	}
	else if (type_object == Material_E || type_object == LootBag_E)
	{
		ObjectsMaterial.push_back(object);
	}
}