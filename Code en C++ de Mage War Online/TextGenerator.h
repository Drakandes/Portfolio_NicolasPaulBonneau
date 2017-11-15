#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Text.h"
#include <iostream>
#include <list>
#include "CollisionalObject.h"

class TextGenerator
{
private:
	std::list<std::shared_ptr<Text>> listTextDamagePlayer;
	std::list<std::shared_ptr<Text>> listTextDamageBlob;
	static TextGenerator *s_instance;
public:
	TextGenerator();
	~TextGenerator();

	static void Initialize()
	{
		s_instance = new TextGenerator();
	}
	static TextGenerator *instance()
	{
		if (!s_instance)
			s_instance = new TextGenerator;
		return s_instance;
	}

	void GenerateOneTextForPlayer(sf::Vector2f &entity_position, int damage_dealt, sf::Vector2f entity_size, std::shared_ptr<CollisionalObject> parent);
	void GenerateOneTextForBlob( sf::Vector2f &entity_position, float damage_dealt, sf::Vector2f entity_size, std::shared_ptr<CollisionalObject> parent);
	void DrawAllTextDamagePlayer(sf::RenderWindow &window);
	void DrawAllTextDamageBlob(sf::RenderWindow &window);
	void GenerateOneTextPlayerColorSpecified( sf::Vector2f &entity_position, int value, sf::Vector2f entity_size, sf::Color color, std::shared_ptr<CollisionalObject> parent);
	void GenerateOneTextStringAndColor(sf::Vector2f &entity_position, sf::String value, sf::Vector2f entity_size, sf::Color color, std::shared_ptr<CollisionalObject> parent);
};

