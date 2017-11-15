#include "stdafx.h"
#include "DrawGestion.h"
#include "ListObjectsSingleton.h"

DrawGestion::DrawGestion()
{
}

DrawGestion::~DrawGestion()
{
	listAllSprites.clear();
	listPositionYSprite.clear();
}

void DrawGestion::DrawAllObjectInList(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	/*if (true)
	{
		std::vector<std::shared_ptr<SpriteBase>>::iterator iterator1 = listAllSpritesOnFloor.begin();
		while (iterator1 != listAllSpritesOnFloor.end())
		{
			(*iterator1)->Draw(window);
			iterator1++;
		}

		std::vector<std::shared_ptr<SpriteBase>>::iterator iterator = listAllSprites.begin();
		while (iterator != listAllSprites.end())
		{
			(*iterator)->Draw(window);
			iterator++;
		}
	}*/

	std::vector<std::shared_ptr<SpriteBase>>::iterator iterator1 = listAllSpritesOnFloor.begin();
	while (iterator1 != listAllSpritesOnFloor.end())
	{
		(*iterator1)->Draw(window);
		iterator1++;
	}
	listAllSpritesOnFloor.clear();
	listPositionYSpriteOnFloor.clear();

	int counter = 0;
	std::vector<std::shared_ptr<SpriteBase>>::iterator iterator = listAllSprites.begin();
	while (iterator != listAllSprites.end())
	{
		if (listIsShadowSprite[counter])
		{
			(*iterator)->DrawShadow(window);
		}
		else
		{
			(*iterator)->Draw(window);
		}
		iterator++;
		counter++;
	}
	listAllSprites.clear();
	listPositionYSprite.clear();
	listIsShadowSprite.clear();

	std::vector<sf::RectangleShape>::iterator i_rect = listAllRectangle.begin();
	while (i_rect != listAllRectangle.end())
	{
		window.draw((*i_rect));
		i_rect++;
	}
	listAllRectangle.clear();
}

void DrawGestion::AddObjectToList(std::shared_ptr<SpriteBase> ObjectToAdd)
{
	if (ObjectToAdd->DrawOnTheFloor())
	{
		sf::Vector2f sprite_position = ObjectToAdd->GetCurrentPosition();
		if (sprite_position.x < position_view_player.x + window_dimension.x / 2 + 150 && sprite_position.x > position_view_player.x - window_dimension.x / 2 - 150 && sprite_position.y > position_view_player.y - window_dimension.y / 2 - 150 && sprite_position.y < position_view_player.y + window_dimension.y / 2 + 150)
		{
			listAllSpritesOnFloor.push_back(ObjectToAdd);
			listPositionYSpriteOnFloor.push_back(sprite_position.y);
		}
	}
	else
	{
		sf::Vector2f sprite_position = ObjectToAdd->GetCurrentPosition();
		if (sprite_position.x < position_view_player.x + window_dimension.x / 2 + 150 && sprite_position.x > position_view_player.x - window_dimension.x / 2 - 150 && sprite_position.y > position_view_player.y - window_dimension.y / 2 - 150 && sprite_position.y < position_view_player.y + window_dimension.y / 2 + 150)
		{
			listAllSprites.push_back(ObjectToAdd);
			listPositionYSprite.push_back(sprite_position.y);
			listIsShadowSprite.push_back(false);

			sf::Vector2f shadow_position = ObjectToAdd->GetCurrentPositionShadow();
			listAllSprites.push_back(ObjectToAdd);
			listPositionYSprite.push_back(shadow_position.y);
			listIsShadowSprite.push_back(true);
		}
	}
}

void DrawGestion::GivePositionViewPlayerThisFrame(sf::Vector2f position_view_player_received)
{
	position_view_player = position_view_player_received + sf::Vector2f(window_dimension.x/2, window_dimension.y/2);
}

void DrawGestion::GiveWindowDimension(sf::Vector2f window_dimension_received)
{
	window_dimension = ListObjectsSingleton::instance()->GetSizeWindow();
}

void DrawGestion::SortListSprite()
{
	float tmp = 0;
	std::shared_ptr<SpriteBase> tmp2;
	bool tmp3 = false;
	int n = listPositionYSprite.size();

	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n-1; j++)
		{
			if (listPositionYSprite[j]>listPositionYSprite[j + 1])
			{
				tmp = listPositionYSprite[j];
				listPositionYSprite[j] = listPositionYSprite[j + 1];
				listPositionYSprite[j + 1] = tmp;

				tmp2 = listAllSprites[j];
				listAllSprites[j] = listAllSprites[j + 1];
				listAllSprites[j + 1] = tmp2;

				tmp3 = listIsShadowSprite[j];
				listIsShadowSprite[j] = listIsShadowSprite[j + 1];
				listIsShadowSprite[j + 1] = tmp3;
			}
		}
	}
	tmp2.reset();

	float tmptmp = 0;
	std::shared_ptr<SpriteBase> tmptmp2;
	bool tmptmp3 = false;
	int nn = listPositionYSpriteOnFloor.size();

	for (int i = 0; i<nn; i++)
	{
		for (int j = 0; j<nn - 1; j++)
		{
			if (listPositionYSpriteOnFloor[j]>listPositionYSpriteOnFloor[j + 1])
			{
				tmptmp = listPositionYSpriteOnFloor[j];
				listPositionYSpriteOnFloor[j] = listPositionYSpriteOnFloor[j + 1];
				listPositionYSpriteOnFloor[j + 1] = tmptmp;

				tmptmp2 = listAllSpritesOnFloor[j];
				listAllSpritesOnFloor[j] = listAllSpritesOnFloor[j + 1];
				listAllSpritesOnFloor[j + 1] = tmptmp2;
			}
		}
	}
	tmptmp2.reset();
}

DrawGestion* DrawGestion::s_instance = 0;

