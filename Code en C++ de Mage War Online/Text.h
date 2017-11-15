#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include <iostream>
#include <list>
#include "CollisionalObject.h"
#include <sstream>
#include <iomanip>

class Text
{
private:
	std::shared_ptr<CollisionalObject> parent;
	sf::Font font;
	sf::Text text;
	sf::String string_of_text = "Error";
	sf::Clock Time_until_text_disappear;
	float text_speed = 25;
	float angle_going = GlobalFunction::getRandomRange(45, 135);
	float time_alive = 0.75;
	bool dps_text = false;
	sf::Vector2f position_random;
public:
	Text();
	~Text();

	bool IsNeedToDelete();
	template <typename T1> void Init(sf::Vector2f entity_position, T1 damage_dealt, sf::Vector2f entity_size, std::shared_ptr<CollisionalObject> parent_received) {
		parent = parent_received; 
		std::stringstream ss;
		ss << std::fixed << std::setprecision(0) << damage_dealt;
		std::string mystring = ss.str();
		text.setString(mystring);
		text.setCharacterSize(18);
		text.setFont(font);
		text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 4, text.getGlobalBounds().height / 2));
		text.setPosition(entity_position.x, entity_position.y - 5 - entity_size.y);
	}
	template <> void Init(sf::Vector2f entity_position, sf::String damage_dealt, sf::Vector2f entity_size, std::shared_ptr<CollisionalObject> parent_received) {
		std::string str_converted = damage_dealt.toAnsiString();
		if (str_converted.compare(0, 3, "DPS") == 0)
		{
			dps_text = true;
		}
		parent = parent_received;
		text.setString(damage_dealt);
		text.setCharacterSize(18);
		text.setFont(font);
		text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 4, text.getGlobalBounds().height / 2));
		text.setPosition(entity_position.x, entity_position.y - 5 - entity_size.y);
	}
	void Draw_text(sf::RenderWindow &window);
	void MoveText();
	void ChangeTextColor(sf::Color color);
};

