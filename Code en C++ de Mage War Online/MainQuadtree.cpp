#include "stdafx.h"
#include "MainQuadtree.h"

MainQuadtree::MainQuadtree()
{

}

MainQuadtree::~MainQuadtree()
{
	ObjectsNature.clear();
	ObjectsWithinQuadtree.clear();
}

void MainQuadtree::Init(int plevel, sf::Vector2f size_received, sf::Vector2f position_received, int index)
{
	level = plevel;
	size_quadtree = size_received;
	position_quadtree = position_received;
	rect = GlobalFunction::CreateRectangleWithOrigin(size_quadtree, position_quadtree, sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(2);
	this->index = index;

	Split();
}

void MainQuadtree::Clear()
{
	if (nodes.size() > 0)
	{
		for (size_t i = 0; i < nodes.size(); i++)
		{
			nodes[i]->Clear();
		}
	}
	nodes.clear();
	ObjectsWithinQuadtree.clear();
	ObjectsNature.clear();
}

void MainQuadtree::UpdatePositionsObjects(sf::FloatRect map_part_activated)
{
	if (nodes.size() > 0)
	{
		for (size_t i = 0; i < nodes.size(); i++)
		{
			nodes[i]->UpdatePositionsObjects(map_part_activated);
		}
	}
}

void MainQuadtree::Split()
{
	sf::Vector2f size_nodes = sf::Vector2f(size_quadtree.x / 2, size_quadtree.y / 2);
	float x = size_quadtree.x / 4;
	float y = size_quadtree.y / 4;
	int new_level = level + 1;
	std::shared_ptr<Quadtree> quadtree1 = std::shared_ptr<Quadtree>(new Quadtree(new_level, size_nodes, sf::Vector2f(position_quadtree.x + x, position_quadtree.y + y), TopLeftQuadrant));
	std::shared_ptr<Quadtree> quadtree2 = std::shared_ptr<Quadtree>(new Quadtree(new_level, size_nodes, sf::Vector2f(position_quadtree.x - x, position_quadtree.y + y), BottomLeftQuadrant));
	std::shared_ptr<Quadtree> quadtree3 = std::shared_ptr<Quadtree>(new Quadtree(new_level, size_nodes, sf::Vector2f(position_quadtree.x - x, position_quadtree.y - y), BottomRightQuadrant));
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

int MainQuadtree::getIndex(sf::Vector2f position_object, sf::Vector2f size_object)
{
	/*int holder = -1;

	bool topQuadrant = (position_object.y - size_object.y/2 < position_quadtree.y && position_object.y + size_object.y/2 < position_quadtree.y);
	bool bottomQaudrant = (position_object.y  - size_object.y/2 > position_quadtree.y && position_object.y + size_object.y/2 > position_quadtree.y);
	if(position_object.x - size_object.x/2 < position_quadtree.x && position_object.x + size_object.x/2 < position_quadtree.x)
	{
	if (topQuadrant)
	{
	holder = 1;
	}
	else if(bottomQaudrant)
	{
	holder = 2;
	}
	}

	if (position_object.x - size_object.x/2 > position_quadtree.x && position_object.x + size_object.x/2 > position_quadtree.x)
	{
	if (topQuadrant)
	{
	holder = 0;
	}
	else if (bottomQaudrant)
	{
	holder = 3;
	}
	}*/

	int holder = -1;
	float top_side_object = position_object.y - size_object.y / 2;
	float left_side_object = position_object.x - size_object.x / 2;
	float bottom_side_object = position_object.y + size_object.y / 2;
	float right_side_object = position_object.x + size_object.x / 2;

	float top_side_node = position_quadtree.y - size_quadtree.y / 2;
	float left_side_node = position_quadtree.x - size_quadtree.x / 2;
	float bottom_side_node = position_quadtree.y + size_quadtree.y / 2;
	float right_side_node = position_quadtree.x + size_quadtree.x / 2;

	if (top_side_object > top_side_node && left_side_object > left_side_node && right_side_object < right_side_node && bottom_side_object < bottom_side_node)
	{
		holder = holder;
	}

	return holder;

	/*if (rect.getGlobalBounds().intersects(rectCollision))
	{
		return true;
	}
	else
	{
		return false;
	}*/
}

void MainQuadtree::insert(sf::Vector2f position_object, sf::Vector2f size_object, std::shared_ptr<CollisionalObject> object)
{
	/*if (object->GetTypeCollisionalObject() != NatureObject_E)
	{
		if (nodes.size() > 0)
		{
			bool found_node_fitting = false;
			for (size_t holder = 0; holder < nodes.size(); holder++)
			{
				if (nodes[holder]->getIndex(object->GetCurrentPosition(), object->GetSize()) != -1)
				{
					nodes[holder]->insert(object->GetCurrentPosition(), object->GetSize(), object);
					found_node_fitting = true;
					//holder = 5;
				}
			}
			if (!found_node_fitting)
			{
				ObjectsWithinQuadtree.push_back(object);
			}
		}
		else
		{
			ObjectsWithinQuadtree.push_back(object);
		}
	}
	else
	{
		if (nodes.size() > 0)
		{
			bool found_node_fitting = false;
			for (size_t holder = 0; holder < nodes.size(); holder++)
			{
				if (nodes[holder]->getIndex(object->GetCurrentPosition(), object->GetSize()) != -1)
				{
					nodes[holder]->insert(object->GetCurrentPosition(), object->GetSize(), object);
					found_node_fitting = true;
					//holder = 5;
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
	if (ObjectsWithinQuadtree.size() + ObjectsNature.size() > MAX_OBJECTS && level < MAX_LEVELS)
	{
		if (nodes.size() == 0)
		{
			Split();
		}

		std::list<std::shared_ptr<CollisionalObject>>::iterator i = ObjectsWithinQuadtree.begin();
		while (i != ObjectsWithinQuadtree.end())
		{

			bool removed = false;
			for (size_t holder = 0; holder < nodes.size(); holder++)
			{
				int holder = nodes[holder]->getIndex(object->GetCurrentPosition(), object->GetSize());
				if (holder != -1)
				{
					nodes[holder]->insert((*i)->GetCurrentPosition(), (*i)->GetSize(), *i);
					removed = true;
					//holder = 5;
				}
			}
			if (!removed)
			{
				i++;
			}
			else
			{
				ObjectsWithinQuadtree.erase(i++);
			}
		}

		std::list<std::shared_ptr<CollisionalObject>>::iterator ii = ObjectsNature.begin();
		while (ii != ObjectsNature.end())
		{
			bool removed = false;
			for (size_t holder = 0; holder < nodes.size(); holder++)
			{
				int holder = nodes[holder]->getIndex((*ii)->GetCurrentPosition(), (*ii)->GetSize());
				if (holder != -1)
				{
					nodes[holder]->insert((*ii)->GetCurrentPosition(), (*ii)->GetSize(), *ii);
					removed = true;
					//holder = 5;
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
	}*/

	bool inserted = false;

	for (size_t holder = 0; holder < nodes.size(); holder++)
	{
		if (nodes[holder]->getIndex(object->GetCollisionRect()))
		{
			nodes[holder]->insert(object);
			inserted = true;
		}
	}

	if (!inserted)
	{
		object->PutItBackInQuadtree();
	}
}

void MainQuadtree::CheckCollision(sf::FloatRect map_part_activated)
{
	if (clock_collision.getElapsedTime().asMilliseconds() >= 1000 / 30)
	{
		if (nodes.size() > 0)
		{
			for (size_t i = 0; i < nodes.size(); i++)
			{
				nodes[i]->CheckCollision(map_part_activated);
			}
		}
		clock_collision.restart();
	}
}

void MainQuadtree::Draw(sf::RenderWindow &window)
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

void MainQuadtree::DeleteEmptyNodes()
{
	for (size_t i = 0; i < nodes.size(); i++)
	{
		nodes[i]->CheckIfToDelete();
	}
}

MainQuadtree* MainQuadtree::s_instance = 0;