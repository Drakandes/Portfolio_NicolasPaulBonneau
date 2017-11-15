#pragma once
#include <SFML/Window.hpp>
#include "GlobalFunction.h"
#include <vector>

class RandomMapGenerator
{
private:
	enum TileSet { Grass_E, Dirt_E, Sand_E };
	enum Extensions{Left_Ext, Right_Ext, Top_Ext, Down_Ext};

	sf::Vector2i Grass{ 0,0 };
	sf::Vector2i Dirt{ 1,0 };
	sf::Vector2i Sand{ 2,0 };
	sf::Vector2i Red{ 0,3 };
	sf::Vector2i Yellow{ 1,3 };

	int number_biomes;

	sf::Vector2i size_range_patch_extension{ 3,5 };
	sf::Vector2i size_range_grass_patch{ 5,8 };
	float distance_between_grass_patch = 5 + size_range_grass_patch.y + size_range_patch_extension.y;
	std::vector<sf::Vector2f> listPointGrassPatch;
	std::vector<float> listPointGrassPatchRange;

	std::vector<std::vector<sf::Vector2i>> map;
	std::vector < std::vector<int>> maptypetile;
	std::vector<sf::Vector2f> listPoint;
	std::vector<int> listPointBiome;
	std::vector<sf::Vector2i> listBiomes;

	int GetCloserPoint(sf::Vector2f position_tile);
	sf::Vector2i GetRandomBasicTile(int type_tile);
	void AdjustAllTiles(int number_tiles_x, int number_tiles_y);
	sf::Vector2i GetPositionTextureTile(int type_tile, bool is_other_type[8]);
	void ModifyTileAfterTransformation(int x, int y, int number_tile_x, int number_tile_y);
	sf::Vector2i GetGrassTile();
	bool CheckGrassPatchIfFit(sf::Vector2f position, float range);
	void CreateGrassPatch(int number_tiles_x, int number_tiles_y);
	void AddExtension(int direction_extension, sf::Vector2i biggest_size_patch, int number_tiles_x, int number_tiles_y, int number_extensions_on_patch, int range, int x, int y, std::vector<int> listDirectionDone);
public:
	RandomMapGenerator();
	~RandomMapGenerator();

	std::vector<std::vector<sf::Vector2i>> GenerateOneMap(int number_tiles_x, int number_tiles_y);
	std::vector< std::vector<int>> GetListBiomes() { return maptypetile; }
	void ClearGenerator();
};

