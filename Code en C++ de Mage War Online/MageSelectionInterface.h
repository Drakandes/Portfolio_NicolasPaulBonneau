#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>
#include "ListObjectsSingleton.h"
#include "TextBoxGenerator.h"
#include "SpawnPointGestion.h"

class MageSelectionInterface
{
private:
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	const static int number_interface = 5;
	sf::Font font;
	sf::Clock clock_click;

	std::vector<sf::Texture> ListTextureInterface;

	std::vector<sf::String> ListCharacteristicPros;
	std::vector<sf::String> ListCharacteristicProsDescription;
	std::vector<sf::String> ListCharacteristicCons;
	std::vector<sf::String> ListCharacteristicConsDescription;
	std::vector<float> ListCharacteristicValue{ 15,15,15,30,10,20,20,15,25,5,25,15,20,25,2 };
	std::vector<sf::String> ListDrawback;
	std::vector<sf::String> ListDrawbackDescription;
	std::vector<sf::String> ListNameMage;

	sf::Sprite interface_mage_selection[number_interface];
	sf::Texture texture_interface;
	float distance_between_interfaces = 20;
	sf::Vector2f position_interface[number_interface];
	sf::Vector2f size_interface{ 213,315 };
	sf::Vector2f position_first_interface{800 - 5*size_interface.x/2 - distance_between_interfaces*2,200 };
	bool displaying_interface[number_interface]{ true,true,true,true,true };
	int number_interface_disabled = 0;

	sf::Sprite sprite_cancel[number_interface];
	sf::Vector2f position_sprite_cancel[number_interface];
	sf::Vector2f size_sprite_cancel{ 54,54 };
	sf::Texture texture_erase_skill;
	sf::Vector2f position_first_sprite_cancel{ size_interface.x / 2, size_interface.y + size_sprite_cancel.y };

	sf::Text text_name_interface[number_interface];
	sf::Vector2f position_first_name_interface{ 108,55 };
	sf::Vector2f position_name_interface[number_interface];
	int name_gotten[ number_interface ];

	std::vector<bool> ListCharacteristicMages[number_interface];
	std::vector<int> ListCharacteristicProsOrCons[number_interface];
	std::vector<bool> ListDrawbackMages[number_interface];
	std::vector<int> ListCharacteristicGotten[number_interface];
	int drawback_gotten[number_interface];

	sf::Text text_attributes[number_interface][4];
	sf::Vector2f position_text_attributes[number_interface][4];
	sf::Vector2f position_first_text_attributes{ 114,128 };
	float distance_between_text_attributes = 45;

	sf::Text text_without_mage;
	sf::Vector2f position_text_without_mage{400 ,625};

	void CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void CreateRectangleInformation(sf::Vector2f mouse_position);
	void CreateListStringAttributeDescriptions();
	void GetNewFiveMages();
public:
	MageSelectionInterface();
	~MageSelectionInterface();

	void Draw(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void UpdateStyleInterface(int style);
};

