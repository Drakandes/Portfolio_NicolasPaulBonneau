#pragma once
#define PI 3.14
#define Proportion 1
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <math.h>
#include <sstream>
#include <iomanip>
#include "DataTextManager.h"


class GlobalFunction
{
public:
	static int getRandomRange(int min, int max);
	static bool Check_collision(float rayon_1, float rayon_2, sf::Vector2f position_1, sf::Vector2f position_2, sf::Vector2f size_1, sf::Vector2f size_2);
	static sf::RectangleShape CreateRectangle(sf::Vector2f rectangle_size, sf::Vector2f rectangle_position);
	static sf::Text CreateText(sf::Vector2f text_position, sf::String text_string, sf::Font &font, int character_size);
	static sf::String InsertNumberToString(sf::String string, int number_to_add, int position_number_to_add);
	static sf::RectangleShape CreateRectangleWithOrigin(sf::Vector2f rectangle_size, sf::Vector2f rectangle_position, sf::Color color);
	static float GetDistanceBetweenTwoPositions(sf::Vector2f position_1, sf::Vector2f position_2);
	static sf::Vector2f GetMousePosition(sf::RenderWindow &window, sf::Vector2f position_view_player);
	static sf::Sprite CreateSprite(sf::Vector2f position_sprite, sf::Vector2f size_sprite, sf::Texture &texture_sprite);
	static bool CheckMouseOnSomethingWithOrigin(sf::Vector2f mouse_position, sf::Vector2f object_position, sf::Vector2f object_size);
	static sf::Text CreateTextWithNoOrigin(sf::Vector2f text_position, sf::String text_string, sf::Font &font, int character_size);
	static sf::Sprite CreateSpriteWithoutTexture(sf::Vector2f position_sprite, sf::Vector2f size_sprite);
	static sf::String InsertNumberToStringIfFloat(sf::String string, float number_to_add, int position_number_to_add);
	static sf::Sprite CreateSpriteWithoutOrigin(sf::Vector2f position_sprite, sf::Vector2f size_sprite, sf::Texture &texture_sprite);
	static int getRandomRangeWithException(int min, int max, int exception);
	static sf::CircleShape CreateCircleForCollision(sf::Vector2f position_circle, int rayon_circle, sf::Color color_circle);
	static bool CheckCollisionWithCircleIfBothWithOrigin(int rayon_circle, sf::Vector2f position_circle, sf::Vector2f position_entity, sf::Vector2f size_entity, int rayon_entity);
	static float GetInclineForLineFromTwoPoints(sf::Vector2f point_1, sf::Vector2f point_2);
	static float GetRotationBetweenTwoPositions(sf::Vector2f position_going_to, sf::Vector2f position_origin);
	static sf::CircleShape CreateCircle(sf::Vector2f position_circle, int rayon_circle, sf::Color color_circle);
	static sf::Color GetRandomColor();
	static std::string InsertNumberToSTDString(std::string, int number_to_add);
	static std::string InsertStringToString(std::string main_string, std::string string_to_add);
	static std::string InsertNumberToSTDStringFLOAT(std::string string, float number_to_add);
};

