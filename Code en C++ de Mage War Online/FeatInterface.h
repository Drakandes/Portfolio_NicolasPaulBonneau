#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>
#include "ListObjectsSingleton.h"
#include "TextBoxGenerator.h"
#include "FeatGestion.h"

class FeatInterface
{
private:
	static const int number_feats = 10;
	sf::Font font;
	sf::Clock clock_click;
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();

	std::vector<sf::Texture> ListTextureInterface;

	sf::Sprite interface_feat;
	sf::Texture texture_interface;
	sf::Vector2f position_interface{ 150,100 };
	sf::Vector2f size_interface{ 640,600 };

	sf::Text text_name_interface;
	sf::Vector2f position_name_interface{ sf::Vector2f(size_interface.x / 2,54) + position_interface };

	sf::Text text_feat[number_feats];
	sf::String string_feat[number_feats];
	sf::Vector2f position_text_feat[number_feats];
	sf::Vector2f position_first_text_feat{ sf::Vector2f(54,186) + position_interface };
	
	sf::Text text_description;
	sf::Vector2f position_text_description{ sf::Vector2f(74,141) + position_interface };

	sf::Text text_current_value;
	sf::Vector2f position_text_current_value{ sf::Vector2f(326,147) + position_interface };
	sf::Text text_current_value_number[number_feats];
	float current_value_distance = 252;

	sf::Text text_best;
	sf::Vector2f position_text_best{ sf::Vector2f(428,147) + position_interface };
	sf::Text text_best_number[number_feats];
	float best_distance = 360;

	sf::Text text_bonus;
	sf::Vector2f position_text_bonus{ sf::Vector2f(541,147) + position_interface };
	sf::Text text_bonus_number[number_feats];
	float bonus_distance = 468;

	sf::String listStringFeatInformation[number_feats];

	void CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void CreateRectangleInformation(sf::Vector2f mouse_position);
	void CreateListInformation();
public:
	FeatInterface();
	~FeatInterface();

	void Draw(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void UpdateStyleInterface(int style);
};