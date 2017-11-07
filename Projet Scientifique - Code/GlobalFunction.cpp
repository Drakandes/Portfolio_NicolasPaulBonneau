#include "stdafx.h"
#include "GlobalFunction.h"

int GlobalFunction::getRandomRange(int min, int max)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	int number = distr(eng);
	return  number;
}

int GlobalFunction::getRandomRangeWithException(int min, int max, int exception)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	int number = distr(eng);

	for (number; number == exception; number)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> distr(min, max); // define the range
		number = distr(eng);
	}
	return number;
}

bool GlobalFunction::Check_collision(float rayon_1, float rayon_2, sf::Vector2f position_1, sf::Vector2f position_2, sf::Vector2f size_1, sf::Vector2f size_2)
{
	float distance = sqrt(((position_1.x - position_2.x)*(position_1.x - position_2.x)) + ((position_1.y - position_2.y)*(position_1.y - position_2.y)));
	if (distance > rayon_1 + rayon_2)
	{
		return false;
	}
	else if (position_1.x - size_1.x / 2 <= position_2.x + size_2.x / 2 && position_1.x + size_1.x / 2 >= position_2.x - size_2.x / 2 && position_1.y - size_1.y / 2 <= position_2.y + size_2.y / 2 && position_1.y + size_1.y / 2 >= position_2.y - size_2.y / 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

sf::RectangleShape GlobalFunction::CreateRectangle(sf::Vector2f rectangle_size, sf::Vector2f rectangle_position)
{
	sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(rectangle_size.x, rectangle_size.y));
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setPosition(rectangle_position.x, rectangle_position.y);

	return rectangle;
}

sf::Text GlobalFunction::CreateText(sf::Vector2f text_position, sf::String text_string, sf::Font &font, int character_size)
{
	sf::Text text;
	text.setCharacterSize(character_size);
	text.setFont(font);
	text.setPosition(text_position.x, text_position.y);
	text.setString(text_string);
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2));
	return text;
}

sf::Text GlobalFunction::CreateTextWithNoOrigin(sf::Vector2f text_position, sf::String text_string, sf::Font &font, int character_size)
{
	sf::Text text;
	text.setCharacterSize(character_size);
	text.setFont(font);
	text.setPosition(text_position.x, text_position.y);
	text.setString(text_string);
	return text;
}

sf::String GlobalFunction::InsertNumberToString(sf::String string, int number_to_add, int position_number_to_add)
{
	sf::String string_to_add = std::to_string(number_to_add);
	string.insert(position_number_to_add, string_to_add);
	return string;
}

sf::String GlobalFunction::InsertNumberToStringIfFloat(sf::String string, float number_to_add, int position_number_to_add)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(7) << number_to_add;
	std::string mystring = ss.str();
	string.insert(position_number_to_add, mystring);
	return string;
}

sf::RectangleShape GlobalFunction::CreateRectangleWithOrigin(sf::Vector2f rectangle_size, sf::Vector2f rectangle_position, sf::Color color)
{
	sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(rectangle_size.x, rectangle_size.y));
	rectangle.setFillColor(color);
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
	rectangle.setPosition(rectangle_position.x, rectangle_position.y);
	return rectangle;
}

float GlobalFunction::GetDistanceBetweenTwoPositions(sf::Vector2f position_1, sf::Vector2f position_2)
{
	float distance = sqrt(((position_1.x - position_2.x)*(position_1.x - position_2.x)) + ((position_1.y - position_2.y)*(position_1.y - position_2.y)));
	return distance;
}

sf::Vector2f GlobalFunction::GetMousePosition(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	sf::Vector2f mouse_position;
	mouse_position.x = sf::Mouse::getPosition(window).x / Proportion + position_view_player.x;
	mouse_position.y = sf::Mouse::getPosition(window).y / Proportion + position_view_player.y;
	return mouse_position;
}

sf::Sprite GlobalFunction::CreateSprite(sf::Vector2f position_sprite, sf::Vector2f size_sprite, sf::Texture &texture_sprite)
{
	sf::Sprite sprite;
	sprite.setPosition(position_sprite);
	sprite.setTexture(texture_sprite);
	sprite.setTextureRect(sf::IntRect(0, 0, size_sprite.x, size_sprite.y));
	sprite.setOrigin(sf::Vector2f(size_sprite.x / 2, size_sprite.y / 2));
	return sprite;
}

sf::Sprite GlobalFunction::CreateSpriteWithoutOrigin(sf::Vector2f position_sprite, sf::Vector2f size_sprite, sf::Texture &texture_sprite)
{
	sf::Sprite sprite;
	sprite.setPosition(position_sprite);
	sprite.setTexture(texture_sprite);
	sprite.setTextureRect(sf::IntRect(0, 0, size_sprite.x, size_sprite.y));
	return sprite;
}

bool GlobalFunction::CheckMouseOnSomethingWithOrigin(sf::Vector2f mouse_position, sf::Vector2f object_position, sf::Vector2f object_size)
{
	if (object_position.x - object_size.x / 2 <= mouse_position.x && object_position.x + object_size.x / 2 >= mouse_position.x && object_position.y - object_size.y / 2 <= mouse_position.y && object_position.y + object_size.y / 2 >= mouse_position.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

sf::Sprite GlobalFunction::CreateSpriteWithoutTexture(sf::Vector2f position_sprite, sf::Vector2f size_sprite)
{
	sf::Sprite sprite;
	sprite.setPosition(position_sprite);
	sprite.setTextureRect(sf::IntRect(0, 0, size_sprite.x, size_sprite.y));
	sprite.setOrigin(sf::Vector2f(size_sprite.x / 2, size_sprite.y / 2));
	return sprite;
}

sf::CircleShape GlobalFunction::CreateCircleForCollision(sf::Vector2f position_circle, int rayon_circle, sf::Color color_circle)
{
	sf::CircleShape circle;
	circle.setRadius(rayon_circle);
	circle.setPosition(position_circle);
	circle.setOutlineThickness(2);
	circle.setOutlineColor(color_circle);
	circle.setFillColor(sf::Color::Color(0, 0, 0, 0));
	circle.setOrigin(rayon_circle, rayon_circle);
	return circle;
}

bool GlobalFunction::CheckCollisionWithCircleIfBothWithOrigin(int rayon_circle, sf::Vector2f position_circle, sf::Vector2f position_entity, sf::Vector2f size_entity, int rayon_entity)
{
	float distance = sqrt(((position_circle.x - position_entity.x)*(position_circle.x - position_entity.x)) + ((position_circle.y - position_entity.y)*(position_circle.y - position_entity.y)));
	if (distance <= rayon_circle + rayon_entity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float GlobalFunction::GetInclineForLineFromTwoPoints(sf::Vector2f point_1, sf::Vector2f point_2)
{
	float incline;
	if (point_1.x > point_2.x)
	{
		incline = -1 * ((point_1.y - point_2.y) / (point_1.x - point_2.x));
		return incline;
	}
	else if (point_1.x < point_2.x)
	{
		incline = -1 * ((point_2.y - point_1.y) / (point_2.x - point_1.x));
		return incline;
	}
	else
	{
		return 0;
	}
}

float GlobalFunction::GetRotationBetweenTwoPositions(sf::Vector2f position, sf::Vector2f position_center)
{
	float rotation = 0;
	if (position.x > position_center.x && position.y < position_center.y)
	{
		rotation = 270 + ((((atan((position.x - position_center.x) / (position_center.y - position.y))) * 180 / PI)));
	}
	else if (position.x < position_center.x && position.y < position_center.y)
	{
		rotation = 270 + ((atan((position.x - position_center.x) / (position_center.y - position.y))) * 180 / PI);
	}
	else if (position.x > position_center.x && position.y > position_center.y)
	{
		rotation = (90 - ((atan((position.x - position_center.x) / (position.y - position_center.y)) * 180 / PI)));
	}
	else if (position.x < position_center.x && position.y > position_center.y)
	{
		rotation = (180 - (((atan((position_center.y - position.y) / (position.x - position_center.x))) * 180 / PI)));
	}
	else if (position.x == position_center.x && position.y <= position_center.y)
	{
		rotation = 270;
	}
	else if (position.x == position_center.x && position.y >= position_center.y)
	{
		rotation = 90;
	}
	else if (position.y == position_center.y && position.x >= position_center.x)
	{
		rotation = 0;
	}
	else if (position.y == position_center.y && position.x <= position_center.x)
	{
		rotation = 180;
	}
	return rotation;
}

sf::CircleShape GlobalFunction::CreateCircle(sf::Vector2f position_circle, int rayon_circle, sf::Color color_circle)
{
	sf::CircleShape circle;
	circle.setRadius(rayon_circle);
	circle.setPosition(position_circle);
	circle.setOutlineThickness(0);
	//circle.setOutlineColor(color_circle);
	circle.setFillColor(color_circle);
	//circle.setFillColor(sf::Color::Color(0, 0, 0, 0));
	circle.setOrigin(rayon_circle, rayon_circle);
	return circle;
}

sf::Color GlobalFunction::GetRandomColor()
{
	int number = getRandomRange(1, 3);
	
	switch (number)
	{
	case 1: return sf::Color::Blue;
	case 2: return sf::Color::Red;
	case 3: return sf::Color::Yellow;
	case 4: return sf::Color::White;
	case 5: return sf::Color::Green;
	default: return sf::Color::Cyan;
		break;
	}
}

std::string GlobalFunction::InsertNumberToSTDString(std::string string, int number_to_add)
{
	std::stringstream Stream;
	Stream << string;
	Stream << number_to_add;
	string = Stream.str();
	return string;
}

std::string GlobalFunction::InsertNumberToSTDStringFLOAT(std::string string, float number_to_add)
{
	std::stringstream Stream;
	Stream << std::fixed << std::setprecision(3);
	Stream << string;
	Stream << number_to_add;
	string = Stream.str();
	return string;
}

std::string GlobalFunction::InsertStringToString(std::string main_string, std::string string_to_add)
{
	std::stringstream Stream;
	Stream << main_string;
	Stream << string_to_add;
	main_string = Stream.str();
	return main_string;
}