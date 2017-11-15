#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <iostream>
#include <list>
#include <vector>
#include "SpriteBase.h"
#include "GlobalFunction.h"

class DeathAnimationBase : public SpriteBase
{
private:
	sf::Texture texture;
	sf::Vector2f size_sprite;
	sf::Sprite sprite;
	int counter = 0;
	int number_animation = 0;
	int position_y = 0;
	float frame_per_second = 0.1;
	sf::Vector2f position;
	bool to_delete = false;
	sf::Clock clock;
	
public:
	DeathAnimationBase();
	~DeathAnimationBase();

	void Init( sf::Vector2f size_sprite, int number_animation, float frame_per_second, int position_y, sf::Vector2f position, sf::String string_texture);
	virtual sf::Vector2f GetCurrentPosition() { return sprite.getPosition(); }
	virtual void Draw(sf::RenderWindow &window) { window.draw(sprite); }
	bool CheckIfToDelete() { return to_delete; }
	void Update();
};

