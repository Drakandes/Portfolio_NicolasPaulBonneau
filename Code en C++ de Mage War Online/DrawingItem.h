#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class DrawingItem
{
private:
	sf::Sprite myImage;
	float image_size_x = 24;
	float image_size_y = 31;
	sf::Texture myTexture;

	int source_x = 0;
	int source_y;
	int source_x_standing = 0;
public:
	DrawingItem();
	~DrawingItem();

	void Init(sf::Vector2f position);
	void DrawToScreen(sf::RenderWindow &window, sf::View &view);
	sf::Vector2f GetCurrentPosition();
};

