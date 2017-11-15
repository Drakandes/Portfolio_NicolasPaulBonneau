#pragma once
#include "TextBoxGenerator.h"
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>
#include "ListObjectsSingleton.h"
#include "TextBoxGenerator.h"

class TalentTreeInterface
{
private:
	enum TalentCategory{DamageTree_Self,DefenseTree_Self,UtilityTree_Self,AllPointsUsed_Self};
	enum TalentType{FivePtsTalent_Self,ThreePtsTalent_Self};
	sf::Font font;
	sf::Clock clock_click;
	std::vector<std::shared_ptr<TalentBase>> listAllTalents;
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();

	std::vector<sf::Texture> ListTextureInterface;

	static const int number_talent = 30;

	sf::Sprite interface_talent;
	sf::Texture texture_interface; 
	sf::Vector2f size_interface{ 690,640 }; 
	sf::Vector2f position_interface{ 800 - size_interface.x/2,75 };

	sf::Text text_name_interface;
	sf::Vector2f position_name_interface{ position_interface + sf::Vector2f(size_interface.x / 2,50) };

	sf::Text text_points_left;
	sf::Vector2f position_text_points_left{ position_interface.x + 85, position_interface.y + 55 };

	sf::Text text_reset;
	sf::Vector2f position_text_reset{ position_interface.x + size_interface.x - 85, position_interface.y + 55 };

	sf::RectangleShape rect_talent[number_talent];
	sf::Vector2f size_small_rect_talent{ 38,38 };
	sf::Vector2f size_medium_rect_talent{ 44,44 };
	sf::Vector2f size_big_rect_talent{ 48,48 };
	sf::Vector2f position_first_rect_talent{ position_interface.x + 137,position_interface.y + 119 };
	sf::Vector2f position_rect_talent[number_talent];
	sf::Text text_talent[number_talent];
	sf::Vector2f position_text_talent[number_talent];
	bool array_rect_locked[number_talent];

	void CanLevelTalent(std::vector<int> player_talent_points_used );
	void UpdateTextTalent(std::vector<int> player_array_talent_level, std::vector<int> player_array_talent_increasement);
public:
	TalentTreeInterface();
	~TalentTreeInterface();

	void Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void Draw(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void CreateRectangleInformation(sf::Vector2f mouse_position);
	void UpdateStyleInterface(int style);
};

