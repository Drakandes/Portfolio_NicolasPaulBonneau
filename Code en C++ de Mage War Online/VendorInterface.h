#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>
#include "ListObjectsSingleton.h"
#include "TextBoxGenerator.h"
#include "E_WizardHat.h"
#include "IncludeAllSkills.h"

class VendorInterface
{
private:
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	std::vector<std::shared_ptr<SkillBase>> listAllSkill;
	sf::Font font;
	sf::Clock clock_click;
	std::vector<sf::Vector2f> RarityItemRange{ sf::Vector2f(39.5,17),sf::Vector2f(32.5,33),sf::Vector2f(15,25),sf::Vector2f(7.5,15),sf::Vector2f(3,10) };
	std::vector<int> PoolAllBonus{ DamagePerLevel,AttackSpeedPerLevel,HealthPerLevel,ArmorPerLevel,SpeedPerLevel,CooldownRedutionPerLevel };
	std::vector<int> PoolFireSkill{ HugeFireballEnum,AblazeTheFireEnum,TripleFireballEnum,BurningShotEnum,IgniteEnum,LavaFloorEnum };
	std::vector<int> PoolGrassSkill{ BlackVineEnum,FlowerBulbProtectionEnum,LeafGuardZoneEnum,WoodSkinEnum,LeafStormEnum,RestrainingLeafBladeEnum };
	std::vector<int> PoolWaterSkill{ ForcingBubbleEnum,ReplenishingWaterEnum,IceWallEnum,MagicalBubbleEnum , ZoneHealingEnum, LiquidBodyEnum};
	std::vector<int> PoolRockSkill{RockPikeEnum,RockArmorEnum,ReinforcementEnum, RockBeltEnum,ReviveEnum,UndergroundEnum };
	std::vector<int> PoolPlayerClass{ ClassFire,ClassGrass,ClassWater, ClassRock };

	std::vector<sf::Texture> ListTextureInterface;

	sf::Sprite interface_vendor;
	sf::Texture texture_interface;
	sf::Vector2f position_interface{ 375,200 };
	sf::Vector2f size_interface{ 336,295 };

	sf::Text text_name_interface;
	sf::Vector2f position_name_interface{ sf::Vector2f(169,54) + position_interface };

	sf::Text text_ilvl;
	sf::String string_ilvl;
	sf::Vector2f position_text_ilvl{ sf::Vector2f(180,192) + position_interface };
	float hat_ilvl = 1;

	sf::Text text_hat_cost;
	sf::String string_hat_cost;
	sf::Vector2f position_text_hat_cost{ sf::Vector2f(200,145) + position_interface };
	float base_hat_cost = 1000;
	float hat_cost_per_ilvl = 5000;
	float hat_cost = 1;

	sf::Text text_hp_pot_cost;
	sf::String string_hp_pot_cost;
	sf::Vector2f position_text_hp_pot_cost{ sf::Vector2f(200,250) + position_interface };
	float base_hp_pot_cost = 750;
	float hp_pot_cost = 1;

	sf::RectangleShape rect_hat;
	sf::Vector2f position_hat{ sf::Vector2f(77,131) + position_interface };
	sf::Vector2f size_hat{ 40,40 };

	sf::RectangleShape rect_buy_hat;
	sf::Vector2f position_buy_hat{ sf::Vector2f(160,133) + position_interface };
	sf::Vector2f size_buy_hat{ 111,38 };

	sf::CircleShape sprite_increase_ilvl_hat;
	sf::CircleShape sprite_decrease_ilvl_hat;
	sf::Vector2f position_decrease_ilvl_hat{ sf::Vector2f(242,198) + position_interface };
	sf::Vector2f position_increase_ilvl_hat{ sf::Vector2f(262,198) + position_interface };
	int rayon_increase_ilvl = 7;

	sf::RectangleShape rect_health_potion;
	sf::Vector2f position_health_potion{ sf::Vector2f(76,235) + position_interface };
	sf::Vector2f size_health_potion{ 40,40 };

	sf::RectangleShape rect_buy_health_potion;
	sf::Vector2f position_buy_health_potion{ sf::Vector2f(159,236) + position_interface };
	sf::Vector2f size_buy_health_potion{ 111,38 };

	void CreateRectangleInformation(sf::Vector2f mouse_position, int player_money);
	void CheckPlayerAction(std::shared_ptr<Player> &player, sf::Vector2f mouse_position, int player_money);
	void GivePlayerNewHat(std::shared_ptr<Player> &player);
	int GetRarityItem();
public:
	VendorInterface();
	~VendorInterface();

	void Draw(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void Update(std::shared_ptr<Player> &player, sf::Vector2f mouse_position);
	void UpdateStyleInterface(int style);
};

