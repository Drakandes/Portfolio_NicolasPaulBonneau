#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>
#include "ListObjectsSingleton.h"
#include "TextBoxGenerator.h"
#include "IncludeAllSkills.h"

class AchievementInterface
{
private:
	static const int number_achievement = 12;
	sf::Font font;
	sf::Clock clock_click;
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();

	std::vector<sf::Texture> ListTextureInterface;

	sf::Sprite interface_achievements;
	sf::Texture texture_interface;
	sf::Vector2f position_interface{ 375,200 };
	sf::Vector2f size_interface{ 336,295 };

	sf::Text text_name_interface;
	sf::Vector2f position_name_interface{ sf::Vector2f(size_interface.x/2,54) + position_interface };

	sf::Text text_achievement[number_achievement];
	std::vector<sf::String> string_achievement;
	std::vector<sf::String> listStringAchievementInformation;
	sf::Vector2f position_text_achievement[number_achievement];
	sf::Vector2f position_first_text_achievement{ sf::Vector2f(25,100) + position_interface };

	void CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void CreateRectangleInformation(sf::Vector2f mouse_position, std::vector<float> listValueReached, std::vector<bool> listPossible, std::vector<bool> listSucceeded);
	void CreateListStringAchievementInformation();
public:
	AchievementInterface();
	~AchievementInterface();

	void Draw(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void UpdateStyleInterface(int style);
};
