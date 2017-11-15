#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>
#include "ListObjectsSingleton.h"
#include "E_Weapon.h"
#include "TextBoxGenerator.h"

class ClassMenu_interface
{
	sf::Font font;

	sf::Clock clock_click;
	static const int number_class = 4;
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();

	std::vector<sf::Texture> ListTextureInterface;

	sf::Sprite interface_class_menu;
	sf::Texture texture_interface;
	sf::Vector2f position_interface{ 578,40 };
	sf::Vector2f size_interface{ 444,308 };

	sf::Text text_name_interface;
	sf::Vector2f position_name_interface{ position_interface + sf::Vector2f(size_interface.x/2,44) };

	sf::RectangleShape rect_class[number_class];
	sf::Vector2f position_first_rect_class{ position_interface + sf::Vector2f(83,110)};
	sf::Vector2f size_rect_class{ 60,70 };
	float position_between_rect_class = 110;
public:
	ClassMenu_interface();
	~ClassMenu_interface();

	void Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void Draw(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void CreateRectangleInformation(sf::Vector2f mouse_position);
	void UpdateStyleInterface(int style);
};

