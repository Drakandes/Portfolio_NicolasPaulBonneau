#include "stdafx.h"
#include "TextGenerator.h"

TextGenerator::TextGenerator()
{
}

TextGenerator::~TextGenerator()
{
	listTextDamageBlob.clear();
	listTextDamagePlayer.clear();
}

void TextGenerator::GenerateOneTextForPlayer( sf::Vector2f &entity_position, int damage_dealt, sf::Vector2f entity_size, std::shared_ptr<CollisionalObject> parent)
{
	if (damage_dealt > 0)
	{
		std::shared_ptr<Text>  text = std::shared_ptr<Text>(new Text());
		text->Init(entity_position, damage_dealt, entity_size,parent);
		listTextDamagePlayer.push_back(text);
		text.reset();
	}
}

void TextGenerator::GenerateOneTextForBlob( sf::Vector2f &entity_position, float damage_dealt, sf::Vector2f entity_size, std::shared_ptr<CollisionalObject> parent)
{
	if (damage_dealt > 0)
	{
		std::shared_ptr<Text>  text = std::shared_ptr<Text>(new Text());
		text->Init(entity_position, damage_dealt, entity_size,parent);
		listTextDamageBlob.push_back(text);
		text.reset();
	}
}

void TextGenerator::DrawAllTextDamagePlayer(sf::RenderWindow &window)
{
	std::list<std::shared_ptr<Text>>::iterator iterator = listTextDamagePlayer.begin();
	while (iterator != listTextDamagePlayer.end())
	{
		bool isNeedToDelete = (*iterator)->IsNeedToDelete();
		if (isNeedToDelete)
		{
			listTextDamagePlayer.erase(iterator++);
		}
		else
		{
			(*iterator)->MoveText();
			(*iterator)->Draw_text(window);
			++iterator;
		}
	}
}

void TextGenerator::DrawAllTextDamageBlob(sf::RenderWindow &window)
{
	std::list<std::shared_ptr<Text>>::iterator iterator = listTextDamageBlob.begin();
	while (iterator != listTextDamageBlob.end())
	{
		bool isNeedToDelete = (*iterator)->IsNeedToDelete();
		if (isNeedToDelete)
		{
			listTextDamageBlob.erase(iterator++);
		}
		else
		{
			(*iterator)->MoveText();
			(*iterator)->Draw_text(window);
			++iterator;
		}
	}
}

void TextGenerator::GenerateOneTextPlayerColorSpecified(sf::Vector2f &entity_position, int value, sf::Vector2f entity_size, sf::Color color, std::shared_ptr<CollisionalObject> parent)
{
	if (value > 0)
	{
		std::shared_ptr<Text>  text = std::shared_ptr<Text>(new Text());
		text->Init(entity_position, value, entity_size,parent);
		text->ChangeTextColor(color);
		listTextDamagePlayer.push_back(text);
		text.reset();
	}
}

void TextGenerator::GenerateOneTextStringAndColor(sf::Vector2f &entity_position, sf::String value, sf::Vector2f entity_size, sf::Color color, std::shared_ptr<CollisionalObject> parent)
{
	std::shared_ptr<Text>  text = std::shared_ptr<Text>(new Text());
	text->Init(entity_position, value, entity_size, parent);
	text->ChangeTextColor(color);
	listTextDamagePlayer.push_back(text);
	text.reset();
}

TextGenerator* TextGenerator::s_instance = 0;