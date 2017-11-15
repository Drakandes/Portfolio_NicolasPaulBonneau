#include "stdafx.h"
#include "NotificationSystem.h"

NotificationSystem::NotificationSystem()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font player" << std::endl;
	}

	sf::Vector2f window_size{ 1600,800};
	for (int i = 0; i < 20; i++)
	{
		sf::Vector2f position{ window_size.x / 2, 15 + static_cast<float>(i * 15)};
		listPosition.push_back(position);
	}

	sf::Text text = GlobalFunction::CreateText(listPosition[0],"Welcome to Mage War",font,15);
	text.setStyle(sf::Text::Bold);
	listNotices.push_back(text);
	listEmpty.push_back(false);
	sf::Clock clock;
	listClock.push_back(clock);
}

NotificationSystem::~NotificationSystem()
{
}

void NotificationSystem::AddNoticeToList(sf::String str)
{
	bool added = false;
	for (int i = 0; i < listEmpty.size(); i++)
	{
		if (listEmpty[i])
		{
			listNotices[i].setString(str);
			listNotices[i].setFillColor(sf::Color::White);
			listNotices[i].setOrigin(listNotices[i].getGlobalBounds().width / 2, listNotices[i].getGlobalBounds().height / 2);
			listEmpty[i] = false;
			listClock[i].restart();
			added = true;
			break;
		}
	}

	if(!added && listEmpty.size() < 20)
	{
		sf::Text text = GlobalFunction::CreateText(listPosition[listEmpty.size()], str, font, 15);
		text.setStyle(sf::Text::Bold);
		listNotices.push_back(text);
		listEmpty.push_back(false);
		sf::Clock clock;
		listClock.push_back(clock);
	}
}

void NotificationSystem::UpdateNotices(sf::Vector2f position_view_player, sf::Vector2f window_size)
{
	listPosition.clear();
	for (int i = 0; i < 20; i++)
	{
		sf::Vector2f position{ window_size.x / 2, 15 + static_cast<float>(i * 15) };
		listPosition.push_back(position);
	}

	for(int i = 0; i < listNotices.size(); i++)
	{
		if (!listEmpty[i])
		{
			float time_passed = listClock[i].getElapsedTime().asSeconds();
			if (time_passed > TIMERNOTIFICATION)
			{
				listEmpty[i] = true;
			}
			else if (time_passed > TIMERNOTIFICATION - 1)
			{
				float holder = time_passed - (TIMERNOTIFICATION - 1);
				listNotices[i].setFillColor(sf::Color::Color(255,255,255,200*(1-holder)+50));
			}

			listNotices[i].setPosition(listPosition[i] + position_view_player);
		}
	}
}

void NotificationSystem::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < listNotices.size(); i++)
	{
		if (!listEmpty[i])
		{
			window.draw(listNotices[i]);
		}
	}
}

NotificationSystem* NotificationSystem::s_instance1 = 0;