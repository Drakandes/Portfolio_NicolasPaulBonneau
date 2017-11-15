#pragma once
#include "SFML\Graphics.hpp"
#include "GlobalFunction.h"
#include <list>
#include "ListObjectsSingleton.h"

class Minimap
{
private:
	const static int number_arrows = 3;
	static Minimap *s_instance1;
	sf::Sprite radar;
	sf::Texture texture_radar;
	sf::CircleShape radar_view;
	std::vector<sf::Vector2f> listPosition;
	std::vector<int> listTypeEntity;
	std::vector<sf::RectangleShape> listPoint;
	std::vector<sf::Vector2f> listPositionGuardian;

	float range_radar_initial = 2500;
	float range_radar = 2500;
	float radius_radar = 100;
	float radius_radar_view = radius_radar-20;
	float size_modifier = radius_radar / range_radar;
	float radius_point = 1.5;

	sf::Texture texture_arrow;
	sf::Sprite arrow[number_arrows];
	sf::Vector2f size_arrow{ 18,11 };
	sf::Vector2f position_arrow;
	bool arrow_activated[number_arrows]{ true, false, false };

	sf::Vector2f position_view_player;
	sf::Vector2f position_player;
	sf::Vector2f size_texture_radar{ 222,222 };
	sf::Vector2f position_on_screen{ ListObjectsSingleton::instance()->GetSizeWindow().x - size_texture_radar.x/2 - 5,15 + size_texture_radar.y/2 };
	sf::Vector2f size_point_initial{ 4,4 };
	sf::Vector2f size_point{ 4,4 };

public:
	Minimap();
	~Minimap();

	static void Initialize()
	{
		s_instance1 = new Minimap();
	}
	static Minimap *instance()
	{
		if (!s_instance1)
			s_instance1 = new Minimap;
		return s_instance1;
	}

	void CreatePointOnRadar(bool points_mixed_up,sf::Vector2f position_center);
	void AddPosition(sf::Vector2f position_received, int type_entity);
	void UpdatePlayerInfo(sf::Vector2f position_player, sf::Vector2f position_view_player, float player_modifier_range_radar);
	void Draw(sf::RenderWindow &window, bool points_mixed_up, sf::Vector2f position_center);
	void GiveGuardiansPosition(std::vector<sf::Vector2f> listPositionGuardian);
	int GetNumberPointOnRadar() { return listPosition.size(); }
};

