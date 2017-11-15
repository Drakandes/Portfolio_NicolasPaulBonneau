#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>
#include "ListObjectsSingleton.h"
#include "TextBoxGenerator.h"
#include "PetBase.h"

class PetInterface
{
	enum PetSKill { NoSkill };
	const static int number_maximum_pet = 10;
	const static int number_pet_attributes = 4;
	const static int number_abilities_available = 10;
	sf::Font font;
	sf::Clock clock_click;
	sf::Clock clock_animation;
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	float timer_animation = 0.2;

	std::vector<sf::Texture> ListTextureInterface;

	std::vector<sf::String> listStringAttributesPet;

	sf::Sprite interface_pet;
	sf::Texture texture_interface;
	sf::Vector2f position_interface{ 300,250 };
	sf::Vector2f size_interface{ 700,365 };

	sf::Texture texture_icone_pet;
	sf::Sprite sprite_icone_pet[number_maximum_pet];
	sf::Vector2f size_icone{ 32,32 };
	sf::Vector2f position_first_icone{sf::Vector2f(52,134)};
	sf::Vector2f position_icone[number_maximum_pet];
	int listTypePet[number_maximum_pet]{ NoPet_E,NoPet_E,NoPet_E,NoPet_E,NoPet_E,NoPet_E,NoPet_E,NoPet_E,NoPet_E,NoPet_E };
	int number_player_current_pets = 0;

	sf::Sprite sprite_summoned;
	sf::Texture texture_summoned;
	sf::Vector2f position_icone_summoned;

	sf::Text text_attributes[number_pet_attributes];
	sf::Vector2f position_first_text_attribute{ 201,153 };
	sf::Vector2f position_text_attribute[number_pet_attributes];
	float distance_between_text_attribute = 51;

	sf::RectangleShape rect_up_attribute[number_pet_attributes];
	sf::Vector2f size_rect_up{ 15,15 };
	sf::Vector2f position_first_rect_up{246,150 };
	sf::Vector2f position_rect_up[number_pet_attributes]; 
	float distance_between_rect_up = 51;

	sf::Text text_attributes_pts_left;
	sf::Vector2f position_text_attribute_pts_left{ sf::Vector2f(205,340) + position_interface };

	sf::RectangleShape rect_exp_bar;
	sf::Vector2f size_exp_bar{124,30};
	sf::Vector2f position_rect_exp_bar{ sf::Vector2f( 274,290) + position_interface };
	sf::RectangleShape rect_full_exp_bar;

	sf::Text text_level;
	sf::Vector2f position_text_level{sf::Vector2f(332,301) + position_interface };

	sf::Text text_summon;
	sf::Vector2f position_text_summon{ sf::Vector2f(333,243) + position_interface };

	sf::Text text_release;
	sf::Vector2f position_text_release{ sf::Vector2f(334,268) + position_interface };

	sf::Sprite sprite_pet_animation;
	sf::Texture texture_pet_animation;
	sf::Vector2f size_pet_animation{ 96,96 };
	sf::Vector2f position_pet_animation{ sf::Vector2f(288,126) + position_interface };
	int source = 0;

	sf::Text text_name_interface;
	sf::Vector2f position_name_interface{ position_interface + sf::Vector2f(size_interface.x / 2,44) };

	sf::RectangleShape rect_ability[number_abilities_available];
	sf::Vector2f size_rect_ability{120,29};
	sf::Vector2f position_rect_ability[number_abilities_available];
	sf::Vector2f position_first_rect_ability{ 417,123 };
	bool can_draw_rect_ability[number_abilities_available];

	sf::Text text_ability[number_abilities_available];
	sf::Vector2f position_text_ability[number_abilities_available];
	sf::Vector2f position_first_text_ability{ 480,135 };

	sf::Texture texture_locked;
	sf::Sprite sprite_locked[number_abilities_available];
	sf::Vector2f position_locked[number_abilities_available];
	sf::Vector2f size_locked{ 40,40 };
	bool can_draw_locked[number_abilities_available];

	int current_pet_summoned = -1;
	int current_pet_checking = 0;
	std::shared_ptr<PetBase> current_pet;

	void CreateListStrings();
public:
	PetInterface();
	~PetInterface();

	void Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void Draw(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void CreateRectangleInformation(sf::Vector2f mouse_position);
	void UpdateStyleInterface(int style);
};