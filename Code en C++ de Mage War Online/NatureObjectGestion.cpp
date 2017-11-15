 #include "stdafx.h"
#include "NatureObjectGestion.h"

NatureObjectGestion::NatureObjectGestion()
{
	sf::Vector2f position1(0, 0);
	sf::Vector2f position2( 5, 0);
	sf::Vector2f position3(10 , 0);
	sf::Vector2f position4(15 , 0);
	sf::Vector2f position5(20, 0);
	sf::Vector2f position6(23, 0);


	position_tree.push_back(position1);
	position_tree.push_back(position2);
	position_tree.push_back(position3);
	position_tree.push_back(position4);
	position_tree.push_back(position5);
	position_tree.push_back(position6);

	sf::Vector2i size1(5, 6);
	sf::Vector2i size2(5, 6);
	sf::Vector2i size3(5, 6);
	sf::Vector2i size4(5, 6);
	sf::Vector2i size5(3, 6);
	sf::Vector2i size6(3, 6);

	size_tree.push_back(size1);
	size_tree.push_back(size2);
	size_tree.push_back(size3);
	size_tree.push_back(size4);
	size_tree.push_back(size5);
	size_tree.push_back(size6); 

	if (!texture_wall.loadFromFile("Wall.png"))
	{
		std::cout << "Error while loading wall texture" << std::endl;
	}
}

NatureObjectGestion::~NatureObjectGestion()
{
	list_nature_object.clear();
}

void NatureObjectGestion::CreateAllNatureObject(std::vector<std::vector<int>> maptiletype, sf::Vector2i size_map, float size_tile, sf::RenderWindow &window)
{
	int number_forest = size_map.x / 20;

	for (int i = 0; i < number_forest; i++)
	{
		sf::Vector2f point{ GlobalFunction::getRandomRangeIfFloat(size_tile + size_wall.x + 400,size_map.x*size_tile - size_wall.x - size_tile - 400),GlobalFunction::getRandomRangeIfFloat(size_tile + size_wall.y * 3 + 600,size_map.y*size_tile - size_wall.y - size_tile - 600) };
		ListPositionForest.push_back(point);
	}

	for (int j = 0; j < size_map.y; j++)
	{
		for (int i = 0; i < size_map.x; i++)
		{
			if (i*size_tile > size_tile + size_wall.x + 200 && i*size_tile < size_map.x*size_tile - size_wall.x - size_tile - 200)
			{
				if(j*size_tile > size_tile + size_wall.y*3 + 300 && j*size_tile < size_map.y*size_tile - size_wall.y - size_tile - 300)
				{
					if (maptiletype[i][j] == Grass_E)
					{
						int random_number = GlobalFunction::getRandomRange(1, 1000);
						if (random_number >= 950)
						{
							if (CheckIfForest(sf::Vector2f(i*size_tile, j*size_tile)))
							{
								std::shared_ptr<Tree> sprite = std::shared_ptr<Tree>(new Tree());
								sprite->Init(sf::Vector2f(i*size_tile, j*size_tile) + GetNatureObjectPositionModifier(), position_tree, size_tree, window);
								list_nature_object.push_back(sprite);
								MainQuadtree::instance()->insert(sprite->GetCurrentPosition(), sprite->GetSize(), sprite);
								sprite.reset();

							}
							else
							{
								if (random_number >= 992)
								{
									std::shared_ptr<Tree> sprite = std::shared_ptr<Tree>(new Tree());
									sprite->Init(sf::Vector2f(i*size_tile, j*size_tile) + GetNatureObjectPositionModifier(), position_tree, size_tree, window);
									list_nature_object.push_back(sprite);
									MainQuadtree::instance()->insert(sprite->GetCurrentPosition(), sprite->GetSize(), sprite);
									sprite.reset();
								}
							}
						}
					}
					else if (maptiletype[i][j] == Sand_E)
					{
						if (GlobalFunction::getRandomRange(1, 1000) >= 992)
						{
							std::shared_ptr<Cactus> sprite = std::shared_ptr<Cactus>(new Cactus());
							sprite->Init(sf::Vector2f(i*size_tile, j*size_tile) + GetNatureObjectPositionModifier(), window);
							list_nature_object.push_back(sprite);
							MainQuadtree::instance()->insert(sprite->GetCurrentPosition(), sprite->GetSize(), sprite);
							sprite.reset();
						}
					}
					else if (maptiletype[i][j] == Dirt_E)
					{
						if (GlobalFunction::getRandomRange(1, 1000) >= 996)
						{
							std::shared_ptr<Rock> sprite = std::shared_ptr<Rock>(new Rock());
							sprite->Init(sf::Vector2f(i*size_tile, j*size_tile) + GetNatureObjectPositionModifier(), window);
							list_nature_object.push_back(sprite);
							MainQuadtree::instance()->insert(sprite->GetCurrentPosition(), sprite->GetSize(), sprite);
							sprite.reset();
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < std::ceil(size_map.x*size_tile / size_wall.x); i++)
	{
		for (int ii = 0; ii < 3; ii++)
		{
			sf::Sprite wall = GlobalFunction::CreateSpriteWithoutOrigin(sf::Vector2f(i*size_wall.x,ii*size_wall.y + size_tile), size_wall, texture_wall);
			if (ii == 0)
			{
				wall.setTextureRect(sf::IntRect((GlobalFunction::getRandomRange(1, 5) - 1)*size_wall.x, GlobalFunction::getRandomRange(3, 5)*size_wall.y, size_wall.x, size_wall.y));
			}
			else
			{
				wall.setTextureRect(sf::IntRect((GlobalFunction::getRandomRange(1, 5) - 1)*size_wall.x, (GlobalFunction::getRandomRange(1, 3) - 1)*size_wall.y, size_wall.x, size_wall.y));
			}
			listWall.push_back(wall);
		}

		for (int ii = 0; ii < 3; ii++)
		{
			sf::Sprite wall = GlobalFunction::CreateSpriteWithoutOrigin(sf::Vector2f(i*size_wall.x, size_map.y*size_tile - size_wall.y*3 +  ii*size_wall.y - size_tile), size_wall, texture_wall);
			if (ii == 0)
			{
				wall.setTextureRect(sf::IntRect((GlobalFunction::getRandomRange(1, 5) - 1)*size_wall.x, GlobalFunction::getRandomRange(3, 5)*size_wall.y, size_wall.x, size_wall.y));
			}
			else
			{
				wall.setTextureRect(sf::IntRect((GlobalFunction::getRandomRange(1, 5) - 1)*size_wall.x, (GlobalFunction::getRandomRange(1, 3) - 1)*size_wall.y, size_wall.x, size_wall.y));
			}
			listWall.push_back(wall);
		}
	}

	for (int i = 0; i < std::ceil(size_map.y*size_tile / size_wall.y); i++)
	{
		sf::Sprite wall = GlobalFunction::CreateSpriteWithoutOrigin(sf::Vector2f(size_tile, size_map.y*size_tile - size_tile - i*size_wall.y), size_wall, texture_wall);
		if (i == 0 || i == 1 || i == 2)
		{
			wall.setTextureRect(sf::IntRect(5*size_wall.x, 0, size_wall.x, size_wall.y));
		}
		else if (i == 3)
		{
			wall.setTextureRect(sf::IntRect(5 * size_wall.x, size_wall.y, size_wall.x, size_wall.y));
		}
		else
		{
			wall.setTextureRect(sf::IntRect(6 * size_wall.x, 0, size_wall.x, size_wall.y));
		}
		listWall.push_back(wall);

		sf::Sprite wall1 = GlobalFunction::CreateSpriteWithoutOrigin(sf::Vector2f(size_tile*size_map.x - size_tile - size_wall.x, size_map.y*size_tile - size_tile - i*size_wall.y), size_wall, texture_wall);
		if (i == 0 || i == 1 || i == 2)
		{
			wall1.setTextureRect(sf::IntRect(5 * size_wall.x, 2* size_wall.y, size_wall.x, size_wall.y));
		}
		else if (i == 3)
		{
			wall1.setTextureRect(sf::IntRect(5 * size_wall.x, 3*size_wall.y, size_wall.x, size_wall.y));
		}
		else
		{
			wall1.setTextureRect(sf::IntRect(6 * size_wall.x, 0, size_wall.x, size_wall.y));
		}
		listWall.push_back(wall);
		listWall.push_back(wall1);
	}
}

void NatureObjectGestion::AddANatureObject(sf::Vector2f position)
{
}

void NatureObjectGestion::AddNatureObjectToSpriteList()
{
	std::list<std::shared_ptr<ProjectileBase>>::iterator iterator = list_nature_object.begin();
	while (iterator != list_nature_object.end())
	{
		if ((*iterator)->IsNeedToDelete())
		{
			list_nature_object.erase(iterator++);
		}
		else
		{
			DrawGestion::instance()->AddObjectToList((*iterator));
			iterator++;
		}
	}
}

void NatureObjectGestion::DrawWall( sf::RenderWindow &window, sf::FloatRect part_map_activated)
{
	std::list<sf::Sprite>::iterator i = listWall.begin();
	while (i != listWall.end())
	{
		if ((*i).getGlobalBounds().intersects(part_map_activated))
		{
			window.draw((*i));
		}
		i++;
	}
}

sf::Vector2f NatureObjectGestion::GetNatureObjectPositionModifier()
{
	sf::Vector2f position;

	if (GlobalFunction::getRandomRange(1, 1000) < 500)
	{
		position.x = GlobalFunction::getRandomRange(1, 50);
	}
	else
	{
		position.x= -GlobalFunction::getRandomRange(1, 50);
	}


	if (GlobalFunction::getRandomRange(1, 1000) < 500)
	{
		position.y = GlobalFunction::getRandomRange(1, 50);
	}
	else
	{
		position.y = -GlobalFunction::getRandomRange(1, 50);
	}

	return position;
}

bool NatureObjectGestion::CheckIfForest(sf::Vector2f position_tree)
{
	for (int i = 0; i < ListPositionForest.size(); i++)
	{
		float dist = GlobalFunction::GetDistanceBetweenTwoPositions(ListPositionForest[i], position_tree);
		if (dist <= distance_forest)
		{
			return true;
		}
	}
	return false;
}

std::list<std::shared_ptr<ProjectileBase>> NatureObjectGestion::GetListAllNatureObjects()
{
	return list_nature_object;
}

void NatureObjectGestion::DeleteListNatureObject()
{
	std::list<std::shared_ptr<ProjectileBase>>::iterator iterator = list_nature_object.begin();
	while (iterator != list_nature_object.end())
	{
		(*iterator)->SetToDelete();
		list_nature_object.erase(iterator++);
	}
}
