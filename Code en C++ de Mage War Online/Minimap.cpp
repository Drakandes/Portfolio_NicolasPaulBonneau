#include "stdafx.h"
#include "Minimap.h"

Minimap::Minimap()
{
	if (!texture_arrow.loadFromFile("ArrowRadar.png"))
	{
		std::cout << "Error while loading radar texture" << std::endl;
	}

	if (!texture_radar.loadFromFile("Radar_icone.png"))
	{
		std::cout << "Error while loading radar texture" << std::endl;
	}
	radar = GlobalFunction::CreateSprite(position_on_screen, size_texture_radar, texture_radar);
	/*radar.setRadius(radius_radar);
	radar.setPosition(position_on_screen);
	radar.setFillColor(sf::Color::Color(0, 0, 0, 150));
	radar.setOutlineColor(sf::Color::White);
	radar.setOutlineThickness(2);
	radar.setOrigin(sf::Vector2f(radius_radar, radius_radar));*/

	radar_view.setRadius(radius_radar_view);
	radar_view.setPosition(position_on_screen);
	radar_view.setFillColor(sf::Color::Transparent);
	radar_view.setOutlineColor(sf::Color::White);
	radar_view.setOutlineThickness(2);
	radar_view.setOrigin(sf::Vector2f(radius_radar_view, radius_radar_view));

	arrow[0] = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), size_arrow, texture_arrow);
	arrow[1] = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), size_arrow, texture_arrow);
	arrow[2] = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), size_arrow, texture_arrow);
}

Minimap::~Minimap()
{
}

void Minimap::AddPosition(sf::Vector2f position_received, int type_entity)
{
	if (GlobalFunction::GetDistanceBetweenTwoPositions(position_received, position_player) <= range_radar)
	{
		listPosition.push_back(position_received - position_player);
		listTypeEntity.push_back(type_entity);
	}
}

void Minimap::GiveGuardiansPosition(std::vector<sf::Vector2f> listPositionGuardian)
{
	this->listPositionGuardian = listPositionGuardian;
}

void Minimap::UpdatePlayerInfo(sf::Vector2f position_player, sf::Vector2f position_view_player,float player_modifier_range_radar)
{
	range_radar = range_radar_initial*player_modifier_range_radar;
	position_on_screen.x = ListObjectsSingleton::instance()->GetSizeWindow().x - size_texture_radar.x / 2 - 15;
	this->position_player = position_player;
	this->position_view_player = position_view_player;
	radar.setPosition(position_view_player + position_on_screen);
	//radar_view.setPosition(position_view_player + position_on_screen);
}

void Minimap::Draw(sf::RenderWindow &window, bool points_mixed_up, sf::Vector2f position_center)
{
	CreatePointOnRadar(points_mixed_up,position_center);

	window.draw(radar);
	//window.draw(radar_view);
	std::vector<sf::RectangleShape>::iterator i = listPoint.begin();
	while (i != listPoint.end())
	{
		window.draw((*i));
		i++;
	}

	listPoint.clear();
	listPosition.clear();
	listTypeEntity.clear();

	for (int i = 0; i < number_arrows; i++)
	{
		if (arrow_activated[i])
		{
			window.draw(arrow[i]);
		}
	}

	listPositionGuardian.clear();
}

void Minimap::CreatePointOnRadar(bool points_mixed_up, sf::Vector2f position_center)
{
	size_modifier = radius_radar / range_radar;
	size_point.x = std::ceil(size_point_initial.x * (range_radar_initial / range_radar));
	size_point.y = std::ceil(size_point_initial.y * (range_radar_initial / range_radar));

	sf::Vector2f origin_radar = radar.getPosition();

	if (listPositionGuardian.size() > 0)
	{
		for (int i = 0; i < listPositionGuardian.size(); i++)
		{
			float angle_to_center = GlobalFunction::GetRotationBetweenTwoPositions(position_player, listPositionGuardian[i]);
			arrow_activated[i] = true;
			position_arrow = GlobalFunction::AddDistanceWithAngleToVector(sf::Vector2f(0, 0), radius_radar + 5, angle_to_center = angle_to_center);
			arrow[i].setRotation(angle_to_center);
			arrow[i].setPosition(position_arrow + origin_radar);
			arrow[i].setTextureRect(sf::IntRect(size_arrow.x, 0, size_arrow.x, size_arrow.y));
		}
	}
	else
	{
		arrow_activated[0] = true;
		arrow_activated[1] = false;
		arrow_activated[2] = false;
		float angle_to_center = GlobalFunction::GetRotationBetweenTwoPositions(position_player, position_center);
		position_arrow = GlobalFunction::AddDistanceWithAngleToVector(sf::Vector2f(0, 0), radius_radar + 5, angle_to_center = angle_to_center);
		arrow[0].setRotation(angle_to_center);
		arrow[0].setPosition(position_arrow + origin_radar);
		arrow[0].setTextureRect(sf::IntRect(0, 0, size_arrow.x, size_arrow.y));
	}

	sf::RectangleShape point_player = GlobalFunction::CreateRectangleWithOrigin(size_point, origin_radar, sf::Color::Blue);
	listPoint.push_back(point_player);

	if (!points_mixed_up)
	{
		int counter = 0;
		std::vector<sf::Vector2f>::iterator i = listPosition.begin();
		while (i != listPosition.end())
		{
			sf::Vector2f position = (*i) * size_modifier + origin_radar;

			/*if (points_mixed_up)
			{
				float distance_from_center = GlobalFunction::GetDistanceBetweenTwoPositions(position, origin_radar);
				float angle_random = GlobalFunction::getRandomRange(1, 360);
				position = sf::Vector2f(-(cos(angle_random * PI / 180))*distance_from_center, -(sin(angle_random * PI / 180))*distance_from_center) + origin_radar;
			}*/

			sf::RectangleShape point = GlobalFunction::CreateRectangleWithOrigin(size_point, position, sf::Color::Red);
			listPoint.push_back(point);

			i++;
			counter++;
		}
	}
}

Minimap* Minimap::s_instance1 = 0;