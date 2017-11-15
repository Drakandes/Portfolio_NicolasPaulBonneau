#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GlobalFunction.h"

class NotificationSystem
{
private:
	sf::Font font;
	std::vector<sf::Text> listNotices;
	std::vector<sf::Clock> listClock;
	std::vector<bool> listEmpty;
	std::vector<sf::Vector2f> listPosition;

	static NotificationSystem *s_instance1;
public:
	NotificationSystem();
	~NotificationSystem();

	static void Initialize()
	{
		s_instance1 = new NotificationSystem();
	}
	static NotificationSystem *instance()
	{
		if (!s_instance1)
			s_instance1 = new NotificationSystem;
		return s_instance1;
	}

	void AddNoticeToList(sf::String str);
	void UpdateNotices(sf::Vector2f position_view_player, sf::Vector2f size_window);
	void Draw(sf::RenderWindow &window);
};

