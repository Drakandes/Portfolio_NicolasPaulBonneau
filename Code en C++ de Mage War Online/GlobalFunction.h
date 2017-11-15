#pragma once
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "IncludaAllGems.h"
#include "IncludeAllArmors.h"
#include <random>
#include <math.h>
#include <sstream>
#include <iomanip>

class GlobalFunction
{
public:
	static bool CheckCollisionV2(sf::FloatRect CollisionRect1, sf::FloatRect CollisionRect2, int rayon1, int rayon2);
	static int getRandomRange(int min, int max);
	static bool Check_collision(float rayon_1, float rayon_2, sf::Vector2f position_1, sf::Vector2f position_2, sf::Vector2f size_1, sf::Vector2f size_2);
	static sf::RectangleShape CreateRectangle(sf::Vector2f rectangle_size, sf::Vector2f rectangle_position);
	static sf::Text CreateText(sf::Vector2f text_position, sf::String text_string, sf::Font &font, int character_size);
	static sf::String InsertNumberToString(sf::String string, int number_to_add, int position_number_to_add);
	static sf::Vector2f GetPlayerlevel(float player_experience, int player_level);
	static int GetPlayerExperienceNeeded(int player_level);
	static sf::RectangleShape CreateRectangleWithOrigin(sf::Vector2f rectangle_size, sf::Vector2f rectangle_position, sf::Color color);
	static float GetDistanceBetweenTwoPositions(sf::Vector2f position_1, sf::Vector2f position_2);
	static sf::Vector2f GetMousePosition(sf::RenderWindow &window, sf::Vector2f position_view_player);
	static sf::Sprite CreateSprite(sf::Vector2f position_sprite, sf::Vector2f size_sprite, sf::Texture &texture_sprite);
	static bool CheckMouseOnSomethingWithOrigin(sf::Vector2f mouse_position, sf::Vector2f object_position, sf::Vector2f object_size);
	static sf::String GetFragmentNeededForSkillUpgrade(int skill_level);
	static sf::Text CreateTextWithNoOrigin(sf::Vector2f text_position, sf::String text_string, sf::Font &font, int character_size);
	static sf::String GetTypeFragment(int number_type_fragment);
	static int GetNumberFragmentsNeeded(int skill_level);
	static int GetTypeFragmentNeeded(int skill_level);
	static bool CheckIfPlayerAlreadyHasSkill(int skill, std::vector<int> player_skill_array);
	static sf::Sprite CreateSpriteWithoutTexture(sf::Vector2f position_sprite, sf::Vector2f size_sprite);
	static sf::String InsertNumberToStringIfFloat(sf::String string, float number_to_add, int position_number_to_add);
	static float PlayerDamageGestion(float player_damage_initial, std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>> listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems);
	static float PlayerHealthGestion(float player_max_health_initial, std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>> listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems);
	static float PlayerDefenseGestion(float player_defense_initial, std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>> listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems);
	static float PlayerExperienceGestion(std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>> listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems);
	static float PlayerMovementSpeedGestion(float player_movement_speed_initial, std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>> listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems);
	static float PlayerCooldownReductionGestion(std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>> listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems);
	static sf::Sprite CreateSpriteWithoutOrigin(sf::Vector2f position_sprite, sf::Vector2f size_sprite, sf::Texture &texture_sprite);
	static int getRandomRangeWithException(int min, int max, int exception); 
	static int GetDirectionFromAngle(int angle);
	static sf::CircleShape CreateCircleForCollision(sf::Vector2f position_circle, int rayon_circle, sf::Color color_circle);
	static bool CheckCollisionWithCircleIfBothWithOrigin(int rayon_circle, sf::Vector2f position_circle, sf::Vector2f position_entity, sf::Vector2f size_entity, int rayon_entity);
	static float GetInclineForLineFromTwoPoints(sf::Vector2f point_1, sf::Vector2f point_2);
	static float GetRotationBetweenTwoPositions(sf::Vector2f objective_position, sf::Vector2f center_position);
	static sf::Vector2f PositionPrediction(sf::Vector2f position_shooter, sf::Vector2f position_target, sf::Vector2f velocity_target, float velocity_bullet);
	static sf::Vector2f quad(float a, float b, float c);
	static float getRandomRangeIfFloat(float min, float max);
	static int getRandomRangeWithUnknownException(int min, int max, std::vector<int> listException);
	static sf::CircleShape CreateCircleWithOrigin(sf::Vector2f position_circle, int rayon_circle);
	static int GetNumberFromFile(std::vector<char> listUnity);
	static float ConvertStringToFloat(std::string str);
	static int ConvertStringToInt(std::string str);
	static sf::Vector2f GetVectorFromFile(std::vector<char> listUnity);
	static sf::Vector2f AddDistanceWithAngleToVector(sf::Vector2f main_vector, float distance, float angle);
	static sf::String GetRarityString(int rarity, int language);
	static float AddAngleToAngle(float angle, float angle_to_add);
	static float GetArmorReductionModifier(float armor);
	static sf::Vector2f GetRandomVectorBetweenRange(float range);
};

