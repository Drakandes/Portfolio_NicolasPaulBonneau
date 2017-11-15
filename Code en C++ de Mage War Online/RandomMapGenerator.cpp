#include "stdafx.h"
#include "RandomMapGenerator.h"

RandomMapGenerator::RandomMapGenerator()
{
	listBiomes.push_back(Grass);
	listBiomes.push_back(Dirt);
	listBiomes.push_back(Sand);
}

RandomMapGenerator::~RandomMapGenerator()
{
}

std::vector<std::vector<sf::Vector2i>> RandomMapGenerator::GenerateOneMap(int number_tiles_x, int number_tiles_y)
{
	sf::Vector2i size_map{ number_tiles_x * TILESIZE, number_tiles_y*TILESIZE };

	number_biomes = number_tiles_x/4;

	for (int i = 0; i < number_biomes; i++)
	{
		sf::Vector2f point{ GlobalFunction::getRandomRangeIfFloat(1,size_map.x),GlobalFunction::getRandomRangeIfFloat(1,size_map.y) };
		listPoint.push_back(point);
		int random_number = GlobalFunction::getRandomRange(1, 100);
		if (random_number <= 55 )
		{
			listPointBiome.push_back(Grass_E);
		}
		else if (random_number <= 85)
		{
			listPointBiome.push_back(Sand_E);
		}
		else
		{
			listPointBiome.push_back(Dirt_E);
		}
	}

	for (int y = 0; y < number_tiles_y; y++)
	{
		std::vector<sf::Vector2i> vectorposition;
		std::vector<int> vectortype;
		for (int x = 0; x < number_tiles_x ; x++)
		{
			sf::Vector2i vector2i;
			int type = listPointBiome[GetCloserPoint(sf::Vector2f(x * TILESIZE, y * TILESIZE))];

			if (type == Grass_E)
			{
				if (GlobalFunction::getRandomRange(1, 1000) <= 10)
				{
					sf::Vector2f position_grass_patch{ static_cast<float>(x), static_cast<float>(y)};
					float range_grass_patch = GlobalFunction::getRandomRange(size_range_grass_patch.x, size_range_grass_patch.y);
					if (CheckGrassPatchIfFit(position_grass_patch, range_grass_patch))
					{
						listPointGrassPatch.push_back(position_grass_patch);
						listPointGrassPatchRange.push_back(range_grass_patch);
					}
				}
			}

			vector2i = GetRandomBasicTile(type);
			vectorposition.push_back(vector2i);
			vectortype.push_back(type);
		}
		maptypetile.push_back(vectortype);
		map.push_back(vectorposition);
	}

	AdjustAllTiles(number_tiles_x, number_tiles_y);
	CreateGrassPatch(number_tiles_x, number_tiles_y);

	return map;
}

int RandomMapGenerator::GetCloserPoint(sf::Vector2f position_tile)
{
	int point = -1; 
	float min_dist = 10000;
	for (int i = 0; i < listPoint.size(); i++)
	{
		float dist = GlobalFunction::GetDistanceBetweenTwoPositions(listPoint[i], position_tile);
		if (dist < min_dist)
		{
			min_dist = dist;
			point = i;
		}
	}
	return point;
}

sf::Vector2i RandomMapGenerator::GetRandomBasicTile(int type_tile) 
{
	if (type_tile == Grass_E)
	{
		return  GetGrassTile();
	}
	else if (type_tile == Dirt_E)
	{
		int random_number = GlobalFunction::getRandomRange(1, 100);

		if (random_number <= 95)
		{
			return sf::Vector2i(1,0);
		}
		else
		{
			return sf::Vector2i(1, GlobalFunction::getRandomRange(1, 11));
		}
	}
	else if (type_tile == Sand_E)
	{
		int random_number = GlobalFunction::getRandomRange(1, 100);

		if(random_number <= 94)
		{
			return sf::Vector2i(2, GlobalFunction::getRandomRange(1, 3)-1);
		}
		else
		{
			if (random_number <= 98)
			{
				return sf::Vector2i(2, GlobalFunction::getRandomRange(4, 6) - 1);
			}
			else
			{  
				return sf::Vector2i(2, GlobalFunction::getRandomRange(7, 12) - 1);
			}
		}
	}
	return sf::Vector2i(0, 0);
}

void RandomMapGenerator::AdjustAllTiles(int number_tiles_x, int number_tiles_y)
{
	for (int y = 0; y < number_tiles_y; y++)
	{
		for (int x = 0; x < number_tiles_x; x++)
		{
			int current_type = maptypetile[x][y];
			if (current_type != Grass_E)
			{
				bool is_other_type[8]{ false,false,false,false,false,false,false,false };
				int counter = 0;
				if (x > 0 && y > 0 && x < number_tiles_x - 1 && y < number_tiles_y - 1)
				{
					if (maptypetile[x - 1][y - 1] != current_type)
					{
						counter++;
						is_other_type[0] = true;
					}
					if (maptypetile[x][y - 1] != current_type)
					{
						counter++;
						is_other_type[1] = true;
					}
					if (maptypetile[x + 1][y - 1] != current_type)
					{
						counter++;
						is_other_type[2] = true;
					}
					if (maptypetile[x - 1][y] != current_type)
					{
						counter++;
						is_other_type[3] = true;
					}
					if (maptypetile[x + 1][y] != current_type)
					{
						counter++;
						is_other_type[4] = true;
					}
					if (maptypetile[x - 1][y + 1] != current_type)
					{
						counter++;
						is_other_type[5] = true;
					}
					if (maptypetile[x][y + 1] != current_type)
					{
						counter++;
						is_other_type[6] = true;
					}
					if (maptypetile[x + 1][y + 1] != current_type)
					{
						counter++;
						is_other_type[7] = true;
					}
				}

				if (counter > 0 && counter < 5)
				{
					if (current_type == Dirt_E)
					{
						sf::Vector2i holder = GetPositionTextureTile(current_type, is_other_type);
						map[x][y] = holder + sf::Vector2i(3, 0);
					}
					else
					{
						sf::Vector2i holder = GetPositionTextureTile(current_type, is_other_type);
						map[x][y] = holder + sf::Vector2i(8, 0);
					}
				}
				else if (counter >= 5)
				{
					map[x][y] = GetGrassTile();
					maptypetile[x][y] = Grass_E;
					for (int j = y - 1; j <= y + 1; j++)
					{
						for (int i = x - 1; i <= x + 1; i++)
						{
							ModifyTileAfterTransformation(i, j, number_tiles_x,number_tiles_y);
						}
					}

					/*for (int j = y - 1; j <= y + 1; j++)
					{
						for (int i = x - 1; i <= x + 1; i++)
						{
							ModifyTileAfterTransformation(i, j, number_tiles_x, number_tiles_y);
						}
					}*/

					ModifyTileAfterTransformation(x, y, number_tiles_x, number_tiles_y);
				}
			}
		}
	}
}

sf::Vector2i RandomMapGenerator::GetPositionTextureTile(int type_tile, bool is_other_type[8])
{
#pragma region NormalCheck
	if (is_other_type[0] && !is_other_type[2] && !is_other_type[5])
	{
		if (is_other_type[1])
		{
			if (is_other_type[3])
			{
				return sf::Vector2i(3, 2);
			}
			return sf::Vector2i(2, 0);
		}

		if (is_other_type[3])
		{
			if (is_other_type[2] && is_other_type[1] && is_other_type[4])
			{
				return Red;
			}
			return sf::Vector2i(4, 0);
		}

		if (is_other_type[7] && !is_other_type[6] && !is_other_type[5] && !is_other_type[4] && !is_other_type[3] && !is_other_type[2] && !is_other_type[1])
		{
			return sf::Vector2i(0, 2);
		}

		if (is_other_type[4] && !is_other_type[5] && !is_other_type[6])
		{
			return sf::Vector2i(3, 1);
		}

		if (is_other_type[6] && !is_other_type[2] && !is_other_type[4])
		{
			return sf::Vector2i(4, 1);
		}

		return sf::Vector2i(1, 1);
	}

	if (is_other_type[2] && !is_other_type[0] && !is_other_type[7])
	{
		if (is_other_type[1])
		{
			/*if (is_other_type[2] && is_other_type[1] && is_other_type[4])
			{
			return Red;
			}*/
			if (is_other_type[4])
			{
				return sf::Vector2i(3, 1);
			}
			return sf::Vector2i(2, 0);
		}

		if (is_other_type[4])
		{
			if (is_other_type[2] && is_other_type[1] && is_other_type[4])
			{
				return Red;
			}
			return sf::Vector2i(2, 1);
		}

		if (is_other_type[5] && !is_other_type[6] && !is_other_type[7] && !is_other_type[4] && !is_other_type[3] && !is_other_type[0] && !is_other_type[1])
		{
			return sf::Vector2i(1, 2);
		}

		if (is_other_type[3] && !is_other_type[6] && !is_other_type[7])
		{
			return sf::Vector2i(3, 2);
		}

		if (is_other_type[6] && !is_other_type[0] && !is_other_type[3])
		{
			return sf::Vector2i(2, 2);
		}
		return sf::Vector2i(0, 1);
	}

	if (is_other_type[5] && !is_other_type[0] && !is_other_type[7])
	{
		if (is_other_type[3])
		{
			/*if (is_other_type[2] && is_other_type[1] && is_other_type[4])
			{
			return Red;
			}*/

			if (is_other_type[6])
			{
				return sf::Vector2i(4, 1);
			}
			return sf::Vector2i(4, 0);
		}

		if (is_other_type[6])
		{
			if (is_other_type[2] && is_other_type[1] && is_other_type[4])
			{
				return Red;
			}
			return sf::Vector2i(3, 0);
		}

		if (is_other_type[2] && !is_other_type[6] && !is_other_type[3] && !is_other_type[4] && !is_other_type[1] && !is_other_type[7] && !is_other_type[0])
		{
			return sf::Vector2i(1, 2);
		}

		if (is_other_type[1] && !is_other_type[4] && !is_other_type[7])
		{
			return sf::Vector2i(3, 2);
		}

		if (is_other_type[4] && !is_other_type[1] && !is_other_type[0])
		{
			return sf::Vector2i(2, 2);
		}

		return sf::Vector2i(1, 0);
	}

	if (is_other_type[7] && !is_other_type[2] && !is_other_type[5])
	{
		if (is_other_type[6])
		{
			if (is_other_type[0] && is_other_type[1] && is_other_type[3])
			{
				return Red;
			}

			if (is_other_type[4])
			{
				return sf::Vector2i(2, 2);
			}
			return sf::Vector2i(3, 0);
		}

		if (is_other_type[4])
		{
			if (is_other_type[0] && is_other_type[1] && is_other_type[3])
			{
				return Red;
			}
			return sf::Vector2i(2, 1);
		}

		if (is_other_type[0] && !is_other_type[6] && !is_other_type[5] && !is_other_type[4] && !is_other_type[3] && !is_other_type[2] && !is_other_type[1])
		{
			return sf::Vector2i(2, 0);
		}

		if (is_other_type[3] && !is_other_type[1] && !is_other_type[2])
		{
			return sf::Vector2i(4, 2);
		}

		if (is_other_type[1] && !is_other_type[3] && !is_other_type[5])
		{
			return sf::Vector2i(3, 1);
		}

		return sf::Vector2i(0, 0);
	}
#pragma endregion NormalCheck

#pragma region ExceptionStyleL
	if (is_other_type[0] && is_other_type[1] && is_other_type[2] && is_other_type[3])
	{
		return sf::Vector2i(3, 2);
	}
	if (is_other_type[0] && is_other_type[1] && is_other_type[5] && is_other_type[3])
	{
		return sf::Vector2i(3, 2);
	}
	if (is_other_type[2] && is_other_type[1] && is_other_type[0] && is_other_type[4])
	{
		return sf::Vector2i(3, 1);
	}
	if (is_other_type[2] && is_other_type[1] && is_other_type[4] && is_other_type[7])
	{
		return sf::Vector2i(3, 1);
	}
	if (is_other_type[5] && is_other_type[3] && is_other_type[0] && is_other_type[6])
	{
		return sf::Vector2i(4, 1);
	}
	if (is_other_type[5] && is_other_type[3] && is_other_type[6] && is_other_type[7])
	{
		return sf::Vector2i(4, 1);
	}
	if (is_other_type[7] && is_other_type[5] && is_other_type[6] && is_other_type[4])
	{
		return sf::Vector2i(2, 2);
	}
	if (is_other_type[7] && is_other_type[6] && is_other_type[4] && is_other_type[2])
	{
		return sf::Vector2i(2, 2);
	}
#pragma endregion ExceptionStyleL

#pragma region ExceptionStyleLine
	if (is_other_type[0] && is_other_type[1] && is_other_type[2])
	{
		return sf::Vector2i(2, 0);
	}
	if (is_other_type[0] && is_other_type[3] && is_other_type[5])
	{
		return sf::Vector2i(4, 0);
	}
	if (is_other_type[7] && is_other_type[4] && is_other_type[2])
	{
		return sf::Vector2i(2, 1);
	}
	if (is_other_type[6] && is_other_type[7] && is_other_type[5])
	{
		return sf::Vector2i(3, 0);
	}
#pragma endregion ExceptionStyleLine

#pragma region ExceptionOneSide
	if (is_other_type[1])
	{
		return sf::Vector2i(2, 0);
	}
	if (is_other_type[3])
	{
		return sf::Vector2i(4, 0);
	}
	if (is_other_type[6])
	{
		return sf::Vector2i(3, 0);
	}
	if (is_other_type[4])
	{
		return sf::Vector2i(2, 1);
	}
#pragma endregion ExceptionOneSide

	return Yellow;
}

void RandomMapGenerator::ModifyTileAfterTransformation(int x, int y , int number_tile_x, int number_tile_y)
{
	int current_type = maptypetile[x][y];
	if (current_type != Grass_E)
	{
		bool is_other_type[8]{ false,false,false,false,false,false,false,false };
		int counter = 0;
		if (x > 0 && y > 0 && x < number_tile_x - 1 && y < number_tile_y - 1)
		{
			if (maptypetile[x - 1][y - 1] != current_type)
			{
				counter++;
				is_other_type[0] = true;
			}
			if (maptypetile[x][y - 1] != current_type)
			{
				counter++;
				is_other_type[1] = true;
			}
			if (maptypetile[x + 1][y - 1] != current_type)
			{
				counter++;
				is_other_type[2] = true;
			}
			if (maptypetile[x - 1][y] != current_type)
			{
				counter++;
				is_other_type[3] = true;
			}
			if (maptypetile[x + 1][y] != current_type)
			{
				counter++;
				is_other_type[4] = true;
			}
			if (maptypetile[x - 1][y + 1] != current_type)
			{
				counter++;
				is_other_type[5] = true;
			}
			if (maptypetile[x][y + 1] != current_type)
			{
				counter++;
				is_other_type[6] = true;
			}
			if (maptypetile[x + 1][y + 1] != current_type)
			{
				counter++;
				is_other_type[7] = true;
			}
		}

		if (counter > 0 && counter < 5)
		{
			if (current_type == Dirt_E)
			{
				map[x][y] = GetPositionTextureTile(current_type, is_other_type) + sf::Vector2i(3, 0);
			}
			else
			{
				map[x][y] = GetPositionTextureTile(current_type, is_other_type) + sf::Vector2i(8, 0);
			}
		}
		else if (counter >= 5)
		{
			map[x][y] = GetGrassTile();
			maptypetile[x][y] = Grass_E;

			for (int j = y - 1; j <= y + 1; j++)
			{
				for (int i = x - 1; i <= x + 1; i++)
				{
					ModifyTileAfterTransformation(i, j, number_tile_x, number_tile_y);
				}
			}
		}
	}
}

sf::Vector2i RandomMapGenerator::GetGrassTile()
{
	int number = GlobalFunction::getRandomRange(1, 1000);
	if (number <= 990)
	{
		return sf::Vector2i(0, 0);
	}
	else //if( number <= 995)
	{
		return sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
	}
	/*else
	{
		return sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
	}*/
}

bool  RandomMapGenerator::CheckGrassPatchIfFit(sf::Vector2f position, float range)
{
	for (int i = 0; i < listPointGrassPatch.size(); i++)
	{
		if (GlobalFunction::GetDistanceBetweenTwoPositions(position, listPointGrassPatch[i]) < range + listPointGrassPatchRange[i] + distance_between_grass_patch)
		{
			return false;
		}
	}
	return true;
}

void RandomMapGenerator::CreateGrassPatch(int number_tiles_x, int number_tiles_y)
{
	for (int iterator = 0; iterator < listPointGrassPatch.size(); iterator++)
	{
		int x = listPointGrassPatch[iterator].x;
		int y = listPointGrassPatch[iterator].y;
		sf::Vector2i biggest_size_patch{ 0,0 };

		int range = listPointGrassPatchRange[iterator] + 2;

		for (int j = y - range; j < y + range + 1; j++)
		{
			if (j < 0 || j > number_tiles_x - 2)
			{
				continue;
			}
			for (int i = x - range; i < x + range + 1; i++)
			{
				if (i < 0 || i > number_tiles_y - 2)
				{
					continue;
				}

				if (maptypetile[i][j] == Grass_E)
				{
					float dist = GlobalFunction::GetDistanceBetweenTwoPositions(sf::Vector2f(x, y), sf::Vector2f(i, j));
					if (dist <= range - 2)
					{
						if (abs(x - i) > biggest_size_patch.x)
						{
							biggest_size_patch.x = abs(x - i);
						}
						if (abs(y - j) > biggest_size_patch.y)
						{
							biggest_size_patch.y = abs(y - j);
						}
						map[i][j] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
					}
					else if (dist > range - 2 && dist <= range)
					{
						map[i][j] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
					}
				}
			}
		}
		biggest_size_patch -= sf::Vector2i(2, 2);
		/*if (GlobalFunction::getRandomRange(1, 100) <= 100)
		{
			std::vector<int> empty_vector;
			int random_number = GlobalFunction::getRandomRange(1, 100);
			if (random_number <= 25)
			{
				AddExtension(Left_Ext, biggest_size_patch, number_tiles_x, number_tiles_y, 0, range, x, y, empty_vector);
			}
			else if (random_number <= 50)
			{
				AddExtension(Right_Ext, biggest_size_patch, number_tiles_x, number_tiles_y, 0, range, x, y, empty_vector);
			}
			else if (random_number <= 75)
			{
				AddExtension(Down_Ext, biggest_size_patch, number_tiles_x, number_tiles_y, 0, range, x, y, empty_vector);
			}
			else
			{
				AddExtension(Top_Ext, biggest_size_patch, number_tiles_x, number_tiles_y, 0, range, x, y, empty_vector);
			}
		}*/
	}
}

void RandomMapGenerator::AddExtension(int direction_extension, sf::Vector2i biggest_size_patch, int number_tiles_x, int number_tiles_y, int number_extensions_on_patch, int range, int x, int y, std::vector<int> listDirectionDone)
{
	if (direction_extension == Left_Ext)
	{
		//left
		int position_x_adding = x - range + 2;
		int position_y_adding = -10;

		if (biggest_size_patch.y > 0)
		{
			int random_number2 = GlobalFunction::getRandomRange(1, 1000);
			if (random_number2 <= 400)
			{
				position_y_adding = y - GlobalFunction::getRandomRange(1, biggest_size_patch.y);
			}
			else if (random_number2 <= 800)
			{
				position_y_adding = y + GlobalFunction::getRandomRange(1, biggest_size_patch.y);
			}
			else
			{
				position_y_adding = y;
			}
		}
		else
		{
			position_y_adding = y;
		}

#pragma region AddExtensionLeft

		if (position_x_adding >= 0 && position_y_adding >= 0 && position_x_adding <= number_tiles_x - 2 && position_y_adding <= number_tiles_y - 2)
		{
			if (maptypetile[position_x_adding][position_y_adding] == Grass_E)
			{
				map[position_x_adding][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));

				int size_extension = GlobalFunction::getRandomRange(size_range_patch_extension.x, size_range_patch_extension.y);
				int width_extension = GlobalFunction::getRandomRange(1, 3) - 1;
				for (int i = 1; i <= size_extension; i++)
				{
					if (position_y_adding - width_extension - 1 >= 0 && position_y_adding + width_extension + 1 <= number_tiles_y - 2 && position_x_adding - i >= 0)
					{
						for (int ii = 0; ii <= width_extension; ii++)
						{
							if (maptypetile[position_x_adding - i][position_y_adding + ii] == Grass_E && maptypetile[position_x_adding - i][position_y_adding - ii] == Grass_E)
							{
								map[position_x_adding - i][position_y_adding + ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
								map[position_x_adding - i][position_y_adding - ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
							}
							map[position_x_adding - i][position_y_adding + width_extension + 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
							map[position_x_adding - i][position_y_adding - width_extension - 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						}
					}
				}

				if (position_y_adding - width_extension - 1 >= 0 && position_y_adding + width_extension + 1 <= number_tiles_y - 2 && position_x_adding - 1 - size_extension >= 0 && position_x_adding + 2 <= number_tiles_x - 2)
				{
					for (int ii = 0; ii <= width_extension; ii++)
					{
						if (maptypetile[position_x_adding - 1 - size_extension][position_y_adding + ii] == Grass_E && maptypetile[position_x_adding - 1 - size_extension][position_y_adding - ii] == Grass_E)
						{
							map[position_x_adding - size_extension - 1][position_y_adding - ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
							map[position_x_adding - size_extension - 1][position_y_adding + ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						}
					}

					for (int ii = 0; ii <= width_extension; ii++)
					{
						if (maptypetile[position_x_adding][position_y_adding + ii] == Grass_E && maptypetile[position_x_adding][position_y_adding - ii] == Grass_E)
						{
							map[position_x_adding][position_y_adding - ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
							map[position_x_adding][position_y_adding + ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(6, 6));
						}
					}

					if (maptypetile[position_x_adding][position_y_adding + width_extension + 1] == Grass_E && maptypetile[position_x_adding][position_y_adding -width_extension - 1] == Grass_E)
					{
						map[position_x_adding][position_y_adding - width_extension - 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						map[position_x_adding][position_y_adding + width_extension + 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
					}
				}
			}
		}

#pragma endregion AddExtensionLeft

		listDirectionDone.push_back(direction_extension);

		if (listDirectionDone.size() <= 3)
		{
			if (GlobalFunction::getRandomRange(1, 100) <= 75 - number_extensions_on_patch * 25)
			{
				AddExtension(GlobalFunction::getRandomRangeWithUnknownException(1, 4, listDirectionDone) - 1, biggest_size_patch, number_tiles_x, number_tiles_y, number_extensions_on_patch + 1, range, x, y, listDirectionDone);
			}
		}
	}
	else if (direction_extension == Right_Ext)
	{
		//right
		int position_x_adding = x + range - 2;
		int position_y_adding = -10;

		if (biggest_size_patch.y > 0)
		{
			int random_number2 = GlobalFunction::getRandomRange(1, 1000);
			if (random_number2 <= 400)
			{
				position_y_adding = y - GlobalFunction::getRandomRange(1, biggest_size_patch.y);
			}
			else if (random_number2 <= 800)
			{
				position_y_adding = y + GlobalFunction::getRandomRange(1, biggest_size_patch.y);
			}
			else
			{
				position_y_adding = y;

			}
		}
		else
		{
			position_y_adding = y;
		}

#pragma region AddExtensionRight
		if (position_x_adding >= 0 && position_y_adding >= 0 && position_x_adding <= number_tiles_x - 2 && position_y_adding <= number_tiles_y - 2)
		{
			if (maptypetile[position_x_adding][position_y_adding] == Grass_E)
			{
				map[position_x_adding][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));

				int size_extension = GlobalFunction::getRandomRange(size_range_patch_extension.x, size_range_patch_extension.y);
				int width_extension = GlobalFunction::getRandomRange(1, 3) - 1;
				for (int i = 1; i <= size_extension; i++)
				{
					if (position_y_adding - width_extension - 1 >= 0 && position_y_adding + width_extension + 1 <= number_tiles_y - 2 && position_x_adding + i <= number_tiles_x - 2)
					{
						for (int ii = 0; ii <= width_extension; ii++)
						{
							if (maptypetile[position_x_adding + i][position_y_adding + ii] == Grass_E && maptypetile[position_x_adding + i][position_y_adding - ii] == Grass_E)
							{
								map[position_x_adding + i][position_y_adding + ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
								map[position_x_adding + i][position_y_adding - ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
							}
							map[position_x_adding + i][position_y_adding + width_extension + 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
							map[position_x_adding + i][position_y_adding - width_extension - 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						}
					}
				}

				if (position_y_adding - width_extension - 1 >= 0 && position_y_adding + width_extension + 1 <= number_tiles_y - 2 && position_x_adding + 1 + size_extension <= number_tiles_x - 2 && position_x_adding - 2 >= 0)
				{
					for (int ii = 0; ii <= width_extension; ii++)
					{
						if (maptypetile[position_x_adding + 1 + size_extension][position_y_adding + ii] == Grass_E && maptypetile[position_x_adding + 1 + size_extension][position_y_adding - ii] == Grass_E)
						{
							map[position_x_adding + size_extension + 1][position_y_adding - ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
							map[position_x_adding + size_extension + 1][position_y_adding + ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						}
					}

					for (int ii = 0; ii <= width_extension; ii++)
					{
						if (maptypetile[position_x_adding][position_y_adding + ii] == Grass_E && maptypetile[position_x_adding][position_y_adding - ii] == Grass_E)
						{
							map[position_x_adding][position_y_adding - ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
							map[position_x_adding][position_y_adding + ii] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
						}
					}

					if (maptypetile[position_x_adding][position_y_adding + width_extension + 1] == Grass_E && maptypetile[position_x_adding][position_y_adding - width_extension - 1] == Grass_E)
					{
						map[position_x_adding][position_y_adding - width_extension - 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						map[position_x_adding][position_y_adding + width_extension + 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
					}
				}
			}
		}
#pragma endregion AddExtensionRight

		listDirectionDone.push_back(direction_extension);

		if (listDirectionDone.size() <= 3)
		{
			if (GlobalFunction::getRandomRange(1, 100) <= 75 - number_extensions_on_patch * 25)
			{
				AddExtension(GlobalFunction::getRandomRangeWithUnknownException(1, 4, listDirectionDone) - 1, biggest_size_patch, number_tiles_x, number_tiles_y, number_extensions_on_patch + 1, range, x, y, listDirectionDone);
			}
		}
	}
	else if (direction_extension == Top_Ext)
	{
		//top
		int position_x_adding = -10;
		int position_y_adding = y - range + 2;

		if (biggest_size_patch.x > 0)
		{
			int random_number2 = GlobalFunction::getRandomRange(1, 1000);
			if (random_number2 <= 400)
			{
				position_x_adding = x - GlobalFunction::getRandomRange(1, biggest_size_patch.x);
			}
			else if (random_number2 <= 800)
			{
				while (GlobalFunction::GetDistanceBetweenTwoPositions(sf::Vector2f(x, y), sf::Vector2f(position_x_adding, position_y_adding)) <= range)
				{
					position_x_adding = x + GlobalFunction::getRandomRange(1, biggest_size_patch.x);
				}
			}
			else
			{
				position_x_adding = x;
			}
		}
		else
		{
			position_x_adding = x;
		}

#pragma region AddExtensionTop
		if (position_x_adding >= 0 && position_y_adding >= 0 && position_x_adding <= number_tiles_x - 2 && position_y_adding <= number_tiles_y - 2)
		{
			if (maptypetile[position_x_adding][position_y_adding] == Grass_E)
			{
				map[position_x_adding][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));

				int size_extension = GlobalFunction::getRandomRange(size_range_patch_extension.x, size_range_patch_extension.y);
				int width_extension = GlobalFunction::getRandomRange(1, 3) - 1;
				for (int i = 1; i <= size_extension; i++)
				{
					if (position_x_adding - width_extension - 1 >= 0 && position_y_adding - i >= 0 && position_x_adding + width_extension + 1 <= number_tiles_x - 2)
					{
						for (int ii = 0; ii <= width_extension; ii++)
						{
							if (maptypetile[position_x_adding - ii][position_y_adding - i] == Grass_E && maptypetile[position_x_adding + ii][position_y_adding - i] == Grass_E)
							{
								map[position_x_adding - ii][position_y_adding - i] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
								map[position_x_adding + ii][position_y_adding - i] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
							}
						}
						map[position_x_adding + width_extension + 1][position_y_adding - i] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						map[position_x_adding - width_extension - 1][position_y_adding - i] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
					}
				}

				if (position_x_adding - width_extension - 1 >= 0 && position_x_adding + width_extension + 1 <= number_tiles_x - 2 && position_y_adding - size_extension - 1 >= 0 && position_y_adding + 2 <= number_tiles_y - 2)
				{
					for (int ii = 0; ii <= width_extension; ii++)
					{
						if (maptypetile[position_x_adding + ii][position_y_adding - size_extension - 1] == Grass_E && maptypetile[position_x_adding - ii][position_y_adding - size_extension - 1] == Grass_E)
						{
							map[position_x_adding - ii][position_y_adding - size_extension - 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
							map[position_x_adding + ii][position_y_adding - size_extension - 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						}
					}

					for (int ii = 0; ii <= width_extension; ii++)
					{
						if (maptypetile[position_x_adding - ii][position_y_adding] == Grass_E && maptypetile[position_x_adding + ii][position_y_adding] == Grass_E)
						{
							map[position_x_adding - ii][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
							map[position_x_adding + ii][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
						}
					}

					if (maptypetile[position_x_adding + width_extension ][position_y_adding] == Grass_E && maptypetile[position_x_adding - 1 - width_extension][position_y_adding] == Grass_E)
					{
						map[position_x_adding - width_extension - 1][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						map[position_x_adding + width_extension + 1][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
					}
				}
			}
		}
#pragma endregion AddExtensionTop

		listDirectionDone.push_back(direction_extension);

		if (listDirectionDone.size() <= 3)
		{
			if (GlobalFunction::getRandomRange(1, 100) <= 75 - number_extensions_on_patch * 25)
			{
				AddExtension(GlobalFunction::getRandomRangeWithUnknownException(1, 4, listDirectionDone) - 1, biggest_size_patch, number_tiles_x, number_tiles_y, number_extensions_on_patch + 1, range, x, y, listDirectionDone);
			}
		}
	}
	else
	{
		int position_x_adding = -10;
		int position_y_adding = y + range - 2;

		if (biggest_size_patch.x > 0)
		{
			int random_number2 = GlobalFunction::getRandomRange(1, 1000);
			if (random_number2 <= 400)
			{
				position_x_adding = x - GlobalFunction::getRandomRange(1, biggest_size_patch.x);
			}
			else if (random_number2 <= 800)
			{
				position_x_adding = x + GlobalFunction::getRandomRange(1, biggest_size_patch.y);
			}
			else
			{
				position_x_adding = x;
			}
		}
		else
		{
			position_x_adding = x;
		}

#pragma region AddExtensionDown
		if (position_x_adding >= 0 && position_y_adding >= 0 && position_x_adding <= number_tiles_x - 2 && position_y_adding <= number_tiles_y - 2)
		{
			if (maptypetile[position_x_adding][position_y_adding] == Grass_E)
			{
				map[position_x_adding][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));

				int size_extension = GlobalFunction::getRandomRange(size_range_patch_extension.x, size_range_patch_extension.y);
				int width_extension = GlobalFunction::getRandomRange(1,3)-1;
				for (int i = 1; i <= size_extension; i++)
				{
					if (position_x_adding - width_extension - 1 >= 0 && position_x_adding + width_extension + 1 <= number_tiles_x - 2 && position_y_adding + i <= number_tiles_y - 2)
					{
						for (int ii = 0; ii <= width_extension; ii++)
						{
							if (maptypetile[position_x_adding - ii][position_y_adding + i] == Grass_E && maptypetile[position_x_adding + ii][position_y_adding + i] == Grass_E)
							{
								map[position_x_adding - ii][position_y_adding + i] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
								map[position_x_adding + ii][position_y_adding + i] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
							}
						}
						map[position_x_adding + width_extension + 1][position_y_adding + i] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						map[position_x_adding - width_extension - 1][position_y_adding + i] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
					}
				}

				if (position_x_adding - width_extension - 1 >= 0 && position_x_adding + width_extension + 1 <= number_tiles_x - 2 && position_y_adding + size_extension + 1 <= number_tiles_y - 2 && position_y_adding - 2 >= 0)
				{
					for (int ii = 0; ii <= width_extension; ii++)
					{
						if (maptypetile[position_x_adding + ii][position_y_adding + size_extension + 1] == Grass_E && maptypetile[position_x_adding - ii][position_y_adding + size_extension + 1] == Grass_E)
						{
							map[position_x_adding - ii][position_y_adding + size_extension + 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
							map[position_x_adding + ii][position_y_adding + size_extension + 1] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						}
					}

					for (int ii = 0; ii <= width_extension; ii++)
					{
						if (maptypetile[position_x_adding - ii][position_y_adding] == Grass_E && maptypetile[position_x_adding + ii][position_y_adding] == Grass_E)
						{
							map[position_x_adding - ii][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
							map[position_x_adding + ii][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(4, 6));
						}
					}

					if (maptypetile[position_x_adding + width_extension + 1][position_y_adding] == Grass_E && maptypetile[position_x_adding - 1 - width_extension][position_y_adding] == Grass_E)
					{
						map[position_x_adding - width_extension - 1][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
						map[position_x_adding + width_extension + 1][position_y_adding] = sf::Vector2i(0, GlobalFunction::getRandomRange(1, 3));
					}
				}
			}
		}
#pragma endregion AddExtensionDown

		listDirectionDone.push_back(direction_extension);

		if (listDirectionDone.size() <= 3)
		{
			if (GlobalFunction::getRandomRange(1, 100) <= 75 - number_extensions_on_patch * 25)
			{
				AddExtension(GlobalFunction::getRandomRangeWithUnknownException(1, 4, listDirectionDone) - 1, biggest_size_patch, number_tiles_x, number_tiles_y, number_extensions_on_patch + 1, range, x, y, listDirectionDone);
			}
		}
	}
}

void RandomMapGenerator::ClearGenerator()
{
	listPointBiome.clear();
	listPoint.clear();
	listPointGrassPatch.clear();
	listPointGrassPatchRange.clear();
	maptypetile.clear();
	map.clear();
}

