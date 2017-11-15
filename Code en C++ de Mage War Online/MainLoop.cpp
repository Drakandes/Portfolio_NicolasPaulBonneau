#include "stdafx.h"
#include "MainLoop.h"


int MainLoop::Starter(sf::RenderWindow &window)
{
	//window = aWindow;// sf::RenderWindow(sf::VideoMode(window_width_i, window_height_i), "Rogue-like Game");
	font.loadFromFile("GreenFlame.ttf");
	srand(time(NULL));
	map_loading();
	textures_loading();
	entity_creation();
	window.setPosition(sf::Vector2i(0, 0));
	player.Init(sf::Vector2f(100, 100), position_view_player, skill_manager);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (user_interface.IsPlaying() && game_timer_before_start.getElapsedTime().asSeconds() >= 1)
		{
			set_view();
			player.UsingSkill(skill_manager, window, position_view_player);
			skill_manager.InitAllUnitializedSkill(window, position_view_player, player.GetCurrentPosition(), player.GetDamage(), GlobalFunction::GetMousePosition(window, position_view_player), player);

			user_interface.WhilePlayingInterfaceGestion(player.GetHealth(), player.GetMaximumHealth());
			user_interface.WhilePlayingOpenedInterfaceUpdate(player.GetHealth(), player.GetMaximumHealth());

			skill_manager.MoveAllSkill(explosion_generator, player.GetCurrentPosition());

			fireballgenerator.MovementAllFireball(player.GetAttackSpeed());
			fireballgenerator.GenerateOneFireball(window, position_view_player, player.GetCurrentPosition(), player.GetDamage(), player.GetAttackSpeed());
			monster_generator.GenerateOneBlob();
			for (size_t i = 0; i < skill_manager.listAllSkill.size(); i++)
			{
				monster_generator.Update(window, fireballgenerator, player, text_generator, *skill_manager.listAllSkill[i], explosion_generator);
			}
			player.CalculateMovement();
			player.player_health_maintenance();
			player.CuttingSprite();
			window.clear();

			for (int i = 0; i < loadcounter.x; i++)
			{
				for (int j = 0; j < loadcounter.y; j++)
				{
					if (map[i][j].x != -1 && map[i][j].y != -1)
					{
						tile.setPosition(i * tile_map_size, j * tile_map_size);
						tile.setTextureRect(sf::IntRect(map[i][j].x * tile_map_size, map[i][j].y * tile_map_size, tile_map_size, tile_map_size));
						window.draw(tile);
					}
				}
			}

			monster_generator.DrawToScreen(text_generator, window, view_player);
			fireballgenerator.DrawAllFireball(window, view_player);
			skill_manager.DrawAllSkill(window, view_player, player);
			player.DrawToScreen(window, view_player, position_view_player);
			explosion_generator.DrawAllExplosion(window);
			text_generator.DrawAllTextDamagePlayer(window, player.GetCurrentPosition(), player.GetSize(), player.GetId());
			user_interface.DrawToScreenOpenedInterfacesWhilePlaying(window, position_view_player);
			window.display();
		}
		else
		{
			if (user_interface.IsToClose())
			{
				window.close();
			}
			test_interface_creation();
			user_interface.MainInterfaceInteraction(window);

			window.clear();

			user_interface.DrawToScreenMainInterface(window);

			window.display();
		}

	}

	return 0;
}

void MainLoop::textures_loading()
{
	/*	if (!fireball_texture.loadFromFile("Fireball.png"))
	std::cout << "Error: Couldn't load Fireball texture" << std::endl;*/

	if (!screen_layer_texture.loadFromFile("Screen_layer.png"))
		std::cout << "Error: Couldn't load the screen layer texture" << std::endl;
}

void MainLoop::map_loading()
{
	std::ifstream openfile("Map_text.txt");

	if (openfile.is_open())
	{
		std::string tileLocation;
		openfile >> tileLocation;
		tiletexture.loadFromFile(tileLocation);
		tile.setTexture(tiletexture);
		while (!openfile.eof())
		{
			std::string str;
			openfile >> str;
			char x = str[0], y = str[2];
			if (!isdigit(x) || !isdigit(y))
				map[loadcounter.x][loadcounter.y] = sf::Vector2i(-1, -1);
			else
				map[loadcounter.x][loadcounter.y] = sf::Vector2i(x - '0', y - '0');

			if (openfile.peek() == '\n')
			{
				loadcounter.x = 0;
				loadcounter.y++;
			}
			else
				loadcounter.x++;
		}
		loadcounter.y++;
	}

}

void MainLoop::set_view()
{
	view_player.setViewport(sf::FloatRect(0, 0, Proportion, Proportion));

	sf::Vector2f position = player.GetCurrentPosition();
	position_view_player.x = position.x - (window_width_i / 2 / Proportion);
	position_view_player.y = position.y - (window_height_i / 2 / Proportion);

	if (position_view_player.x < 0)
		position_view_player.x = 0;
	if (position_view_player.y < 0)
		position_view_player.y = 0;

	view_player.reset(sf::FloatRect(position_view_player.x, position_view_player.y, window_width_f, window_height_f));
}

void MainLoop::entity_creation()
{
	player = Player::Player();
}

void MainLoop::test_interface_creation()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//std::cout << sf::Mouse::getPosition(window).x << "," << sf::Mouse::getPosition(window).y << std::endl;
	}
	rect_test.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));

	text.setCharacterSize(35);
	text.setFont(font);
	text.setPosition(rect_test.getPosition().x, rect_test.getPosition().y);
	text.setString("This has 22 characters");

	float width = text.getGlobalBounds().width;
	float height = text.getGlobalBounds().height;
	rect_test.setSize(sf::Vector2f(width, height*1.8f));
	rect_test.setFillColor(sf::Color::Blue);



}

