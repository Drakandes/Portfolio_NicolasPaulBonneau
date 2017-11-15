#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalFunction.h"
#include <vector>

#pragma once
class MapGenerator
{
private: 
	enum TileSet{GrassToDirt, DirtToGrass, SandToGrass, WaterToGrass, WaterToSand, GrassToSand, DirtDoubleGrass, SandDoubleSand};
	enum Biome{Grass, Dirt, Sand, Water,BiomeChanging, ModifiedSand, ModifiedDirt};

	int number_different_biome = 4;
	int number_tile_grass = 12;

	sf::Vector2i flower{ 3, 6 };
	sf::Vector2i flower_mushroom{ 7,10 };
	sf::Vector2i mushroom{ 11,12 };

	sf::Vector2i number_different_biome_range{ 15,20 };
	sf::Vector2i size_biome{ 20,25 };
	sf::Vector2i size_biome_water{ 2,4 };

	std::vector<sf::Vector2i> tile_set;
	sf::Vector2i top_left{ -1,-1 };
	sf::Vector2i top_middle{ 0,-1 };
	sf::Vector2i top_right{ 1,-1 };
	sf::Vector2i left_middle{ -1,0 };
	sf::Vector2i right_middle{ 1,0 };
	sf::Vector2i bottom_left{ -1,1 };
	sf::Vector2i bottom_middle{ 0,1 };
	sf::Vector2i bottom_right{ 1,1 };

	std::vector<std::vector<sf::Vector2i>> tile;
	std::vector<std::vector<int>> transition;
public:
	MapGenerator();
	~MapGenerator();

	std::vector<std::vector<sf::Vector2i>> GenerateOneMap(int number_tiles_x, int number_tiles_y);
	int getRandomRange(int min, int max);
	int getRandomRangeWithException(int min, int max, int exception);
	bool CheckTransitionAround(int x, int y, int current_tile_type, sf::Vector2i size_checking, sf::Vector2i size_map);
	void DrawEntireTileSet(sf::Vector2i position, int tile_set_using, sf::Vector2i size_map, int new_biome, sf::Vector2i size_new_biome);
	int GetTileSet(int new_biome, int biome_around);
	int GetInverseTileSetUsing(int tile_set_using);
	int getRandomRangeWithTwoExceptions(int min, int max, int exception, int exception2);
	void CreateHoleInBiome(sf::Vector2i position, int new_biome, sf::Vector2i size_map, int tile_set_using);
	void ChangeGrassTile(sf::Vector2i size_map);
	sf::Vector2i PositioningTile(bool top, bool down, bool left, bool right, bool top_right_bool, bool top_left_bool, bool down_left_bool, bool down_right_bool);
	void DrawMapTransition(sf::Vector2i size_map);
	bool CheckCreatedHoleAround(sf::Vector2i position, std::vector<sf::Vector2i> &tile_changed, sf::Vector2i size_map, int new_biome, sf::Vector2i position_initial_biome, sf::Vector2i size_new_biome);
	std::vector<std::vector<int>> GetTransition();
	int GetSameBiomeTileType(int new_biome);
};

