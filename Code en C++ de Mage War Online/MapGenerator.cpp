#include "stdafx.h"
#include "MapGenerator.h"

MapGenerator::MapGenerator()
{
	sf::Vector2i grass_to_dirt{ 1,1 };
	sf::Vector2i dirt_to_grass{ 4,1 };
	sf::Vector2i sand_to_grass{ 7,1 };
	sf::Vector2i water_to_grass{ 10,1 };
	sf::Vector2i water_to_sand{ 13,1 };
	sf::Vector2i grass_to_sand{ 16,1 };
	sf::Vector2i dirt_double_grass{ 19,1 };
	sf::Vector2i sand_double_grass{ 22,1 };
	tile_set.push_back(grass_to_dirt);
	tile_set.push_back(dirt_to_grass);
	tile_set.push_back(sand_to_grass);
	tile_set.push_back(water_to_grass);
	tile_set.push_back(water_to_sand);
	tile_set.push_back(grass_to_sand);
	tile_set.push_back(dirt_double_grass);
	tile_set.push_back(sand_double_grass);
}

MapGenerator::~MapGenerator()
{
}

std::vector<std::vector<sf::Vector2i>> MapGenerator::GenerateOneMap(int number_tiles_x, int number_tiles_y)
{
	sf::Vector2i size_map{ number_tiles_x, number_tiles_y };
	for (int y = 0; y < number_tiles_y; y++)
	{
		std::vector<sf::Vector2i> vector;
		for (int x = 0; x < number_tiles_x; x++)
		{
			sf::Vector2i vector2i;
			vector2i = tile_set[GrassToDirt];
			vector.push_back(vector2i);
		}
		tile.push_back(vector);
	}

	for (int y = 0; y < number_tiles_y; y++)
	{
		std::vector<int> vector;
		for (int x = 0; x < number_tiles_x; x++)
		{
			int integer = Grass;
			vector.push_back(integer);
		}
		transition.push_back(vector);
	}

	int number_biome = getRandomRange(number_different_biome_range.x, number_different_biome_range.y);
	for (int number = 0; number < number_biome; number)
	{
		int new_biome_holder = getRandomRangeWithException(1, number_different_biome, Grass + 1);
		int new_biome = new_biome_holder - 1;
		int new_tile_set = GetTileSet(new_biome, Grass);
		if (new_biome == Water)
		{
			sf::Vector2i position_new_biome{ getRandomRange(1, number_tiles_x) - 1,getRandomRange(1, number_tiles_y) - 1 };
			sf::Vector2i size_new_biome{ getRandomRange(size_biome_water.x,size_biome_water.y), getRandomRange(size_biome_water.x,size_biome_water.y) };
			if (CheckTransitionAround(position_new_biome.x, position_new_biome.y, Grass, size_new_biome + sf::Vector2i(1, 1), size_map))
			{
				DrawEntireTileSet(position_new_biome, new_tile_set, size_map, new_biome, size_new_biome);
				number++;
			}
		}
		else
		{
			sf::Vector2i position_new_biome{ getRandomRange(1, number_tiles_x) - 1,getRandomRange(1, number_tiles_y) - 1 };
			sf::Vector2i size_new_biome{ getRandomRange(size_biome.x,size_biome.y), getRandomRange(size_biome.x,size_biome.y) };
			if (CheckTransitionAround(position_new_biome.x, position_new_biome.y, Grass, size_new_biome + sf::Vector2i(1, 1), size_map))
			{
				DrawEntireTileSet(position_new_biome, new_tile_set, size_map, new_biome, size_new_biome);
				number++;
			}
		}
	}
	ChangeGrassTile(size_map);
	return tile;
}

int MapGenerator::getRandomRange(int min, int max)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	int number = distr(eng);
	return  number;
}

int MapGenerator::getRandomRangeWithException(int min, int max, int exception)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	int number = distr(eng);

	for (number; number == exception; number)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> distr(min, max); // define the range
		number = distr(eng);
	}
	return number;
}

int MapGenerator::getRandomRangeWithTwoExceptions(int min, int max, int exception, int exception2)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	int number = distr(eng);

	for (number; number == exception; number++)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> distr(min, max); // define the range
		number = distr(eng);
	}
	return number;
}

bool MapGenerator::CheckTransitionAround(int x, int y, int current_tile_type, sf::Vector2i size_checking, sf::Vector2i size_map)
{	
	for (int j = 0 - size_checking.y; j <= size_checking.y; j++)
	{
		for (int i = 0 - size_checking.x; i <= size_checking.x; i++)
		{
			if ((x+i >= 0 && y+j >= 0) && (x + i < size_map.x && y + j < size_map.y))
			{
				if (!(transition[x+i][y+j] == current_tile_type) && !(transition[x + i][y + j] == GetSameBiomeTileType(current_tile_type)))
				{
					return false;
				}
			}
		}
	}
	return true;
}

void MapGenerator::DrawEntireTileSet(sf::Vector2i position, int tile_set_using, sf::Vector2i size_map, int new_biome, sf::Vector2i size_new_biome)
{
	sf::Vector2i position_initial_biome = position;
	for (int j = -size_new_biome.y; j <= size_new_biome.y; j++)
	{
		for (int i = -size_new_biome.x; i <= size_new_biome.x; i++)
		{
			if ((position.x + i >= 0 && position.y + j >= 0) && (position.x + i < size_map.x && position.y + j < size_map.y))
			{
#pragma region DrawingBasicBiome
				if (i == -size_new_biome.x && j == -size_new_biome.y)
				{
					tile[position.x + i][position.y + j] = tile_set[tile_set_using] + top_left;
					transition[position.x + i][position.y + j] = new_biome;
				}
				else if (i == +size_new_biome.x && j == -size_new_biome.y)
				{
					tile[position.x + i][position.y + j] = tile_set[tile_set_using] + top_right;
					transition[position.x + i][position.y + j] = GetSameBiomeTileType(new_biome);
				}
				else if (j == -size_new_biome.y)
				{
					tile[position.x + i][position.y + j] = tile_set[tile_set_using] + top_middle;
					transition[position.x + i][position.y + j] = GetSameBiomeTileType(new_biome);
				}
				else if (i == -size_new_biome.x && j == +size_new_biome.y)
				{
					tile[position.x + i][position.y + j] = tile_set[tile_set_using] + bottom_left;
					transition[position.x + i][position.y + j] = GetSameBiomeTileType(new_biome);
				}
				else if (i == +size_new_biome.x && j == +size_new_biome.y)
				{
					tile[position.x + i][position.y + j] = tile_set[tile_set_using] + bottom_right;
					transition[position.x + i][position.y + j] = GetSameBiomeTileType(new_biome);
				}
				else if (j == +size_new_biome.y)
				{
					tile[position.x + i][position.y + j] = tile_set[tile_set_using] + bottom_middle;
					transition[position.x + i][position.y + j] = GetSameBiomeTileType(new_biome);
				}
				else if (i == +size_new_biome.x)
				{
					tile[position.x + i][position.y + j] = tile_set[tile_set_using] + right_middle;
					transition[position.x + i][position.y + j] = GetSameBiomeTileType(new_biome);
				}
				else if (i == -size_new_biome.x)
				{
					tile[position.x + i][position.y + j] = tile_set[tile_set_using] + left_middle;
					transition[position.x + i][position.y + j] = GetSameBiomeTileType(new_biome);
				}
				else
				{
					tile[position.x + i][position.y + j] = tile_set[tile_set_using];
					transition[position.x + i][position.y + j] = new_biome;
				}
#pragma endregion DrawingBasicBiome
			}
		}
	}
#pragma region GrassAroundTheBiome
	if (!(tile_set_using == WaterToGrass || tile_set_using == WaterToSand))
	{
		for (int j = -size_new_biome.y; j <= size_new_biome.y; j++)
		{
			for (int i = -size_new_biome.x; i <= size_new_biome.x; i++)
			{
				if ((position.x + i >= 0 && position.y + j >= 0) && (position.x + i < size_map.x && position.y + j < size_map.y))
				{
					if (getRandomRange(1, 100) >= 60)
					{
						if (position.x + i == -size_new_biome.x)
						{
							transition[position.x + i][position.y + j] = Grass;
							tile[position.x + i][position.y + j] = tile_set[GrassToDirt];
							CreateHoleInBiome(sf::Vector2i(position.x + i, position.y + j), new_biome, size_map, tile_set_using);
						}
						else if (i == size_new_biome.x)
						{
							transition[position.x + i][position.y + j] = Grass;
							tile[position.x + i][position.y + j] = tile_set[GrassToDirt];
							CreateHoleInBiome(sf::Vector2i(position.x + i, position.y + j), new_biome, size_map, tile_set_using);
						}
						else if (j == -size_new_biome.y)
						{
							transition[position.x + i][position.y + j] = Grass;
							tile[position.x + i][position.y + j] = tile_set[GrassToDirt];
							CreateHoleInBiome(sf::Vector2i(position.x + i, position.y + j), new_biome, size_map, tile_set_using);
						}
						else if (j == size_new_biome.y)
						{
							transition[position.x + i][position.y + j] = Grass;
							tile[position.x + i][position.y + j] = tile_set[GrassToDirt];
							CreateHoleInBiome(sf::Vector2i(position.x + i, position.y + j), new_biome, size_map, tile_set_using);
						}
					}
					else
					{
						if (getRandomRange(1, 100) >= 95)
						{
							if ((position.x + i <= position.x - (size_new_biome.x*3/4) || position.x + i >= position.x + (size_new_biome.x*3/4)) || (position.y + j <= position.y - (size_new_biome.y * 3 / 4) || position.y + j >= position.y + (size_new_biome.y * 3 / 4)))
							{
								std::vector<sf::Vector2i> list_tile_changed;

								int x_holder = 0;
								int y_holder = 0;
								bool stop = true;
								for (int number = 0; getRandomRange(1,100) > 4; number++)
								{
									if (CheckCreatedHoleAround(sf::Vector2i(position.x + i + x_holder, position.y + j + y_holder), list_tile_changed, size_map, new_biome, position_initial_biome, size_new_biome))
									{
										if ((position.x + i + x_holder >= 0 && position.y + j + y_holder >= 0) && (position.x + i + x_holder < size_map.x && position.y + j + y_holder < size_map.y))
										{
											transition[position.x + i + x_holder][position.y + j + y_holder] = Grass;
											tile[position.x + i + x_holder][position.y + j + y_holder] = tile_set[GrassToDirt];
											CreateHoleInBiome(sf::Vector2i(position.x + i + x_holder, position.y + j + y_holder), new_biome, size_map, tile_set_using);
											list_tile_changed.push_back(sf::Vector2i(position.x + i + x_holder,position.y + j + y_holder));

											if (getRandomRange(1, 2) == 1)
											{
												if (getRandomRange(1, 2) == 1)
												{
													x_holder++;
												}
												else
												{
													x_holder--;
												}
											}
											else
											{
												if (getRandomRange(1, 2) == 1)
												{
													y_holder++;
												}
												else
												{
													y_holder--;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
#pragma endregion GrassAroundTheBiome

}

void MapGenerator::ChangeGrassTile(sf::Vector2i size_map)
{
	for (int j = 0; j < size_map.y; j++)
	{
		for (int i = 0; i < size_map.x; i++)
		{
			if (transition[i][j] == Grass)
			{
				int random_number = getRandomRange(1, 100);
				if (random_number >= 95)
				{
					sf::Vector2i new_position_grass_tile;
					int type = getRandomRange(1, 100);
					if (type >= 35)
					{
						new_position_grass_tile.y = getRandomRange(flower.x, flower.y);
					}
					else if (type >= 10)
					{
						new_position_grass_tile.y = getRandomRange(flower_mushroom.x, flower_mushroom.y);
					}
					else
					{
						new_position_grass_tile.y = getRandomRange(mushroom.x, mushroom.y);
					}
					new_position_grass_tile.x = getRandomRange(1, number_tile_grass) - 1;
					tile[i][j] = new_position_grass_tile;
				}
			}
		}
	}
}

int MapGenerator::GetTileSet(int new_biome, int biome_around)
{
	if (new_biome == Grass && biome_around == Sand)
	{
		return GrassToSand;
	}
	if (new_biome == Grass && biome_around == Dirt)
	{
		return GrassToDirt;
	}
	if (new_biome == Water && biome_around == Grass)
	{
		return WaterToGrass;
	}

	if (new_biome == Water && biome_around == Sand)
	{
		return WaterToSand;
	}
	if (new_biome == Sand && biome_around == Grass)
	{
		return SandToGrass;
	}
	if (new_biome == Dirt && biome_around == Grass)
	{
		return DirtToGrass;
	}
}

void MapGenerator::CreateHoleInBiome(sf::Vector2i position, int new_biome, sf::Vector2i size_map, int tile_set_using)
{
	for (int j = -1; j <= 1; j++)
	{
		for (int i = -1; i <= 1; i++)
		{
			if (!((j == 0) && (i == 0)))
			{
				bool top_same = false;
				bool left_same = false;
				bool down_same = false;
				bool right_same = false;
				bool top_left_same = false;
				bool top_right_same = false;
				bool down_left_same = false;
				bool down_right_same = false;

				if (position.x + i - 1 >= 0 && position.y + j - 1 >= 0 && position.x + i + 1 < size_map.x && position.y + j + 1 < size_map.y)
				{
					if (transition[position.x + i][position.y + j] == new_biome || transition[position.x + i ][position.y + j] == GetSameBiomeTileType(new_biome))
					{
						if (transition[position.x + i - 1][position.y + j] == new_biome || transition[position.x + i - 1][position.y + j] == GetSameBiomeTileType(new_biome))
						{
							left_same = true;
						}
						if (transition[position.x + i + 1][position.y + j] == new_biome || transition[position.x + i + 1][position.y + j] == GetSameBiomeTileType(new_biome))
						{
							right_same = true;
						}
						if (transition[position.x + i][position.y + j - 1] == new_biome || transition[position.x + i][position.y + j -1] == GetSameBiomeTileType(new_biome))
						{
							top_same = true;
						}
						if (transition[position.x + i][position.y + j + 1] == new_biome || transition[position.x + i][position.y + j +1] == GetSameBiomeTileType(new_biome))
						{
							down_same = true;
						}
						if (transition[position.x + i + 1][position.y + j + 1] == new_biome || transition[position.x + i + 1][position.y + j+1] == GetSameBiomeTileType(new_biome))
						{
							down_right_same = true;
						}
						if (transition[position.x + i - 1][position.y + j + 1] == new_biome || transition[position.x + i - 1][position.y + j+1] == GetSameBiomeTileType(new_biome))
						{
							down_left_same = true;
						}
						if (transition[position.x + i - 1][position.y + j - 1] == new_biome || transition[position.x + i - 1][position.y + j -1] == GetSameBiomeTileType(new_biome))
						{
							top_left_same = true;
						}
						if (transition[position.x + i + 1][position.y + j - 1] == new_biome || transition[position.x + i + 1][position.y + j -1] == GetSameBiomeTileType(new_biome))
						{
							top_right_same = true;
						}

						int tile_set_inverse = GetInverseTileSetUsing(tile_set_using);
						sf::Vector2i position_checking{ i,j };
						if (position_checking == top_left)
						{
							tile[position.x + i][position.y + j] = tile_set[tile_set_inverse] + top_left;
						}
						else if (position_checking == top_right)
						{
							tile[position.x + i][position.y + j] = tile_set[tile_set_inverse] + top_right;
						}
						else if (position_checking == bottom_left)
						{
							tile[position.x + i][position.y + j] = tile_set[tile_set_inverse] + bottom_left;
						}
						else if (position_checking == bottom_right)
						{
							tile[position.x + i][position.y + j] = tile_set[tile_set_inverse] + bottom_right;
						}

						sf::Vector2i holder = PositioningTile(top_same, down_same, left_same, right_same, top_right_same, top_left_same, down_left_same, down_right_same);
						if (!(holder == tile_set[DirtDoubleGrass] + bottom_right) && !(holder == tile_set[DirtDoubleGrass] + bottom_left))
						{
							if (!(holder == sf::Vector2i(-5, -5)) && !(holder == sf::Vector2i(0, 0)))
							{
								tile[position.x + i][position.y + j] = tile_set[tile_set_using] + holder;
								transition[position.x + i][position.y + j] = GetSameBiomeTileType(new_biome);
							}
							else if (holder == sf::Vector2i(0, 0))
							{

							}
							else
							{
								tile[position.x + i][position.y + j] = tile_set[GrassToSand];
								transition[position.x + i][position.y + j] = Grass;
								CreateHoleInBiome(sf::Vector2i(position.x + i, position.y + j), new_biome, size_map, tile_set_using);
							}
						}
						else
						{
							if (new_biome == Sand)
							{
								holder += sf::Vector2i(3, 0);
							}
							tile[position.x + i][position.y + j] = holder;
							transition[position.x + i][position.y + j] = GetSameBiomeTileType(new_biome);
						}
					}
				}
			}
		}
	}
}

sf::Vector2i MapGenerator::PositioningTile(bool top, bool down, bool left, bool right, bool top_right_bool, bool top_left_bool, bool down_left_bool, bool down_right_bool)
{
	int number_same_tyle_around = 0;
	if (top)
	{
		number_same_tyle_around++;
	}
	if (down)
	{
		number_same_tyle_around++;
	}
	if (left)
	{
		number_same_tyle_around++;
	}
	if (right)
	{
		number_same_tyle_around++;
	}
	if (!top_left_bool && !down_right_bool && top_right_bool && down_left_bool)
	{
		return tile_set[DirtDoubleGrass] + bottom_right;
	}
	if (top_left_bool && down_right_bool && !top_right_bool && !down_left_bool)
	{
		return tile_set[DirtDoubleGrass] + bottom_left;
	}
	if (number_same_tyle_around >= 2)
	{
		if (top && down && left && right)
		{
			return sf::Vector2i(0, 0);
		}
		else if (!top && down && left && right)
		{
			return top_middle;
		}
		else if (!top && down && left && !right)
		{
			return top_right;
		}
		else if (!top && down && !left && right)
		{
			return top_left;
		}
		else if (top && !down && left && right)
		{
			return bottom_middle;
		}
		else if (top && !down && !left && right)
		{
			return bottom_left;
		}
		else if (top && !down && left && !right)
		{
			return bottom_right;
		}
		else if (top && down && !left && right)
		{
			return left_middle;
		}
		else if (top && down && left && !right)
		{
			return right_middle;
		}
	}
	return sf::Vector2i(-5,-5);
}

void MapGenerator::DrawMapTransition(sf::Vector2i size_map)
{
	for (int j = 0; j < size_map.y; j++)
	{
		std::cout << std::endl;
		for (int i = 0; i < size_map.x; i++)
		{
			std::cout << transition[i][j] << " ";
		}
	}
}

int MapGenerator::GetInverseTileSetUsing(int tile_set_using)
{
	if (tile_set_using == GrassToDirt)
	{
		return DirtToGrass;
	}
	if (tile_set_using == GrassToSand)
	{
		return SandToGrass;
	}
	if (tile_set_using == SandToGrass)
	{
		return GrassToSand;
	}
	if (tile_set_using == DirtToGrass)
	{
		return GrassToDirt;
	}
	return GrassToSand;
}

bool MapGenerator::CheckCreatedHoleAround(sf::Vector2i position, std::vector<sf::Vector2i> &tile_changed, sf::Vector2i size_map, int new_biome, sf::Vector2i position_initial_biome, sf::Vector2i size_new_biome)
{
	for (int j = -3; j <= 3; j++)
	{
		for (int i = -3; i <= 3; i++)
		{
			if(!(i == 0) && !(j==0))
			{
				sf::Vector2i position_checking(position.x + i, position.y + j);
				if (!(position_initial_biome.x - size_new_biome.x <= position_checking.x) || !(position_initial_biome.x + size_new_biome.x >= position_checking.x) || !(position_initial_biome.y - size_new_biome.y <= position_checking.y) || !(position_initial_biome.y + size_new_biome.y >= position_checking.y))
				{
					return true;
				}
				else
				{
					if (position.x + i >= 0 && position.y + j >= 0 && position.x + i < size_map.x && position.y + j < size_map.y)
					{
						bool same_hole = false;
						for (int number = 0; number < tile_changed.size(); number++)
						{
							if (tile_changed[number] == position_checking)
							{
								same_hole = true;
							}
						}
						if (transition[position.x + i][position.y + j] == new_biome || transition[position.x + i][position.y + j] == GetSameBiomeTileType(new_biome))
						{

						}
						else if (same_hole)
						{

						}
						else
						{
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

std::vector<std::vector<int>> MapGenerator::GetTransition()
{
	return transition;
}

int MapGenerator::GetSameBiomeTileType(int new_biome)
{
	if (new_biome == Sand)
	{
		return ModifiedSand;
	}
	else if (new_biome == Dirt)
	{
		return ModifiedDirt;
	}
}
