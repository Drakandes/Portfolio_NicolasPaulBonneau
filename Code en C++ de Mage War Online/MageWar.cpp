//@Copyright 2017 Nicolas Paul-Bonneau
//If you want to use any part of this code, you must first ask the permission.
//You cannot at any point use any part of this code for commercial use.
#define CRTDBG_MAP_ALLOC

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Network.hpp>
#include "Quadtree.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include "Fireball.h"
#include "Blob.h"
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "FireballGenerator.h"
#include "TextGenerator.h"
#include "UserInterface.h"
#include "MainInterface.h"
#include "Davbheer.h"
#include "MonsterGenerator.h"
#include "SkillManagement.h"
#include "SkillHugeFireball.h"
#include "SkillBase.h"
#include "PlayerStaticInterface.h"
#include "Davbheer.h"
#include "VineGenerator.h"
#include "FPS.h"
#include "DeltatimeGestion.h"
#include "BubbleGenerator.h"
#include "MapGenerator.h"
#include "NatureObjectGestion.h"
#include "PlayerGestion.h"
#include "ListObjectsSingleton.h"
#include "CollisionGestion.h"
#include "MainQuadtree.h"
#include "Minimap.h"
#include "TextBoxGenerator.h"
#include "BasicAttackGestion.h"
#include <stdlib.h>
#include <crtdbg.h>
#include "RandomMapGenerator.h"
#include "ModeSelectionInterface.h"
#include "NotificationSystem.h"
#include "SpawnPointGestion.h"
#include "PillarGestion.h"
#include "IncludeAllPets.h"
#include "PetGestion.h"
#include "SoundGestion.h"
#include "TutorialGestion.h"
#include "BossMapGestion.h"

#pragma region variables
sf::Font font;
const static int map_size_variable = 200;
bool collision_blob_fireball = false;
float window_height_f = 800;
float window_width_f = 1600;
int window_height_i = 800;
int window_width_i = 1600;
sf::Vector2i current_map_tile_size(map_size_variable, map_size_variable);
bool isPlaying = false;
bool do_once = false;
bool is_fullscreen = false;
bool loading_map_done = false;
bool loading_spawns_done = false;
sf::Vector2f size_map_activated{ 3200,1600 };
sf::Vector2f window_dimension{ 1600,800 };
std::vector<std::vector<sf::Vector2i>> map;//[map_size_variable][map_size_variable];
//sf::Vector2i loadcounter = sf::Vector2i(0, 0);
sf::Texture tiletexture;
std::vector<std::vector<sf::Vector2i>> map_demo;
float tile_map_size = TILESIZE;
sf::Vector2f map_size{ map_size_variable*tile_map_size,map_size_variable*tile_map_size };
float DELTATIME = 0;
sf::Sprite tile;
sf::Texture screen_layer_texture;
sf::Clock clock_test_option;
sf::Clock game_timer_before_start;
sf::Clock clock_restraining_fps_draw;
sf::Clock clock_restraining_fps_update;
sf::Clock clock_toggle_fullscreen;
sf::View view_player;
sf::View minimap_view;
sf::Vector2f position_minimap{ 1400,200 };
sf::Vector2f size_minimap;
sf::Vector2f position_view_player(0,0);
sf::RectangleShape rect_map_activated;
sf::Text text_name_tester = GlobalFunction::CreateTextWithNoOrigin(sf::Vector2f(25, 200), "Alpha", font, 40);
sf::Text text_loading;
sf::Sprite sprite_loading;
sf::Texture texture_loading;
int animation_holder = 0;
bool animation_holder_increasing = true;
sf::Clock clock_loading_animation;
#pragma endregion variables

#pragma region Calls
void textures_loading();
void set_view();
void TransformMap();
void MinimapGestion();
void TestOptions(sf::Vector2f mouse_position, sf::Vector2f position_player);
void WelcomeMessage();
void ResolutionGestion();
void FullscreenToggle();
void LoadingScreen(bool loading_map, bool loading_spawn);
void LoadMap();
void LoadSpawns();
void CenterMapGestion();
void SelectSave();
void GivePlayerPet();
void PlayerDeathGestion();
#pragma endregion Calls

PlayerGestion player_gestion;
BasicAttackGestion basic_attack_gestion;
MonsterGenerator monster_generator;
TextGenerator text_generator;
UserInterface user_interface;
SkillManagement skill_manager;
RandomMapGenerator map_generator;
FPS fps;
DeltatimeGestion deltatime_gestion;
NatureObjectGestion nature_object_gestion;
CollisionGestion collision_gestion;
ModeSelectionInterface mode_selection;
PillarGestion pillar_gestion;
PetGestion pet_gestion;
BossMapGestion boss_map_gestion;

sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Mage War Online");// , sf::Style::Fullscreen);

int main()
{
	sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
	ListObjectsSingleton::instance()->ChangeSizeWindow(sf::Vector2f(video_mode.width, video_mode.height));
	ResolutionGestion();
	window.clear(sf::Color::Black);
	window.display();

	text_name_tester.setFillColor(sf::Color::Color(255, 255, 255, 100));
	srand(time(NULL));
	textures_loading();
	rect_map_activated = GlobalFunction::CreateRectangleWithOrigin(size_map_activated, sf::Vector2f(0, 0), sf::Color::Color(255,0,0,25));

	MainQuadtree::instance()->Init(1, sf::Vector2f(map_size_variable*tile_map_size, tile_map_size*map_size_variable), sf::Vector2f(map_size_variable*tile_map_size / 2, tile_map_size*map_size_variable / 2), -1);
	DrawGestion::instance()->GiveWindowDimension(sf::Vector2f(window_width_f, window_height_f));
	ListObjectsSingleton::instance()->GiveMapLimitSize(sf::Vector2f(map_size_variable*tile_map_size - 124, tile_map_size*map_size_variable - 202));
	pillar_gestion.Init(map_size);

	player_gestion.AddPlayer(window_dimension);

	std::list<std::shared_ptr<Player>>::iterator iterator = player_gestion.listPlayers.begin();
	user_interface.InitAllInterfaces((*iterator));
	SpawnPointGestion::instance()->Init((*iterator), ListObjectsSingleton::instance()->GetCurrentLanguage(), sf::Vector2f(map_size_variable*tile_map_size, tile_map_size*map_size_variable));
	TutorialGestion::instance()->GivePointerPlayer((*iterator));

	sf::Thread thread_map(&LoadMap);
	thread_map.launch();
	LoadingScreen(true, false);

	animation_holder = 0;
	animation_holder_increasing = true;

	WelcomeMessage();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (user_interface.IsPlaying() && game_timer_before_start.getElapsedTime().asSeconds() >= 0.1)
		{
			if (!do_once)
			{
				game_timer_before_start.restart();
				do_once = true;
				SelectSave();
				std::list<std::shared_ptr<Player>>::iterator iterator = player_gestion.listPlayers.begin();
				(*iterator)->HealPlayer(999999);
				sf::Clock clock_;
				while (clock_.getElapsedTime().asSeconds() <= 0.05)
				{

				}
				
				sf::Thread thread_spawns(&LoadSpawns);
				thread_spawns.launch();
				LoadingScreen(false, true);
				continue;
			}
			if (clock_restraining_fps_update.getElapsedTime().asMilliseconds() >= 1000/60)
			{
				clock_restraining_fps_update.restart();

				FullscreenToggle();
				sf::Vector2f center_map_activated = (*iterator)->GetCurrentPosition();
				rect_map_activated.setPosition(center_map_activated);
				sf::FloatRect map_part_activated = rect_map_activated.getGlobalBounds();
				TestOptions(GlobalFunction::GetMousePosition(window, position_view_player), (*iterator)->GetCurrentPosition());

				MainQuadtree::instance()->UpdatePositionsObjects(map_part_activated);
				sf::Vector2f mouse_position = GlobalFunction::GetMousePosition(window, position_view_player);
				DELTATIME = deltatime_gestion.GetDeltaTime();
				player_gestion.UpdateAllPlayer(DELTATIME, skill_manager, mouse_position);

				set_view();
				window.setView(view_player);
				DrawGestion::instance()->GivePositionViewPlayerThisFrame(position_view_player);
				Minimap::instance()->UpdatePlayerInfo((*iterator)->GetCurrentPosition(), position_view_player,(*iterator)->GetPlayerRadarRangeModifier());
				fps.UpdateFPS(position_view_player);
				SpawnPointGestion::instance()->Update();

				user_interface.WhilePlayingInterfaceGestion((*iterator));
				user_interface.WhilePlayingAllInteractionInterface(GlobalFunction::GetMousePosition(window, position_view_player), position_view_player, (*iterator));
				(*iterator)->MoneyGestion();
				
				basic_attack_gestion.GenerateOneFireball(window, position_view_player, (*iterator)->GetCurrentPosition(), (*iterator)->GetDamage(), (*iterator)->GetAttackSpeed(), (*iterator));

#pragma region MonsterGenerator
				if (ListObjectsSingleton::instance()->GetIfNeedLoadSpawn())
				{
					monster_generator.ModifiySpawnWithSpawnPoint(SpawnPointGestion::instance()->GetSpawnPointPosition());
				}
				//monster_generator.GenerateEntities();
				monster_generator.Update(map_part_activated, (*iterator), text_generator, DELTATIME);
				sf::Vector2i from_return = pillar_gestion.Update((*iterator),DELTATIME);
				if (from_return.x == SpawnRandomNumberMonsters)
					monster_generator.SpawnRandomMonsterAroundArea((*iterator)->GetCurrentPosition(), from_return.y);
				else if (from_return.x == SpawnRandomNumberMonsters)
					monster_generator.SpawnMonsterInEachSpawn(from_return.y);
#pragma endregion MonsterGenerator

				boss_map_gestion.UpdateBossFight((*iterator),DELTATIME, position_view_player, text_generator);

				(*iterator)->Update( text_generator, window, DELTATIME, position_view_player,skill_manager);
				pet_gestion.UpdatePlayerPet(DELTATIME, (*iterator), monster_generator);
				PlayerDeathGestion();

				//ProjectileGestion must be after player and monsters update;
				ProjectileGestion::instance()->UpdateAllProjectiles(DELTATIME, (*iterator)->GetCurrentPosition());

				MainQuadtree::instance()->CheckCollision(map_part_activated);
				(*iterator)->AchievementUpdate(Minimap::instance()->GetNumberPointOnRadar(), ListObjectsSingleton::instance()->GetLevelMap());
				NotificationSystem::instance()->UpdateNotices(position_view_player, ListObjectsSingleton::instance()->GetSizeWindow());
				SoundGestion::instance()->Update();
				DeathAnimationGestion::instance()->Update();
				FeatGestion::instance()->Action(F_MapReached, ListObjectsSingleton::instance()->GetLevelMap()-1);
				CenterMapGestion();
				TutorialGestion::instance()->Update(position_view_player);
			}
			if (clock_restraining_fps_draw.getElapsedTime().asMilliseconds() >= 1000/60 )
			{
				clock_restraining_fps_draw.restart();
				window.clear();

				for (int y = 0; y < current_map_tile_size.y; ++y)
				{
					for (int x = 0; x < current_map_tile_size.x; ++x)
					{
						if (x * tile_map_size < position_view_player.x-window_width_f || x * tile_map_size > position_view_player.x + window_width_f || y * tile_map_size < position_view_player.y - window_height_f|| y * tile_map_size > position_view_player.y + window_height_f)
						{
						}
						else
						{
							tile.setPosition(x * tile_map_size, y * tile_map_size);
							tile.setTextureRect(sf::IntRect(map[x][y].x * tile_map_size, map[x][y].y * tile_map_size, tile_map_size, tile_map_size));
							window.draw(tile);
						}
					}
				}

				SpawnPointGestion::instance()->Draw(window);
				ProjectileGestion::instance()->AddListToDrawGestion();
				monster_generator.FirstDrawToScreen(text_generator, window, view_player);
				monster_generator.DrawToScreen(window, view_player);
				nature_object_gestion.AddNatureObjectToSpriteList();
				pillar_gestion.AddPillarDraw();
				player_gestion.AddPlayerToDrawList();
				boss_map_gestion.DrawBoss();
				DrawGestion::instance()->SortListSprite();
				DrawGestion::instance()->DrawAllObjectInList(window, position_view_player);
				nature_object_gestion.DrawWall(window, rect_map_activated.getGlobalBounds());
				(*iterator)->DrawToScreen(window, view_player, position_view_player);
				TextGenerator::instance()->DrawAllTextDamagePlayer(window);
				TextGenerator::instance()->DrawAllTextDamageBlob(window);
				//MainQuadtree::instance()->Draw(window);
				//MainQuadtree::instance()->DeleteEmptyNodes();
				Minimap::instance()->Draw(window,(*iterator)->GetPlayerListDrawback()[3],SpawnPointGestion::instance()->GetCenterPosition());
				user_interface.DrawToScreenOpenedInterfacesWhilePlaying(window, position_view_player, (*iterator)->GetCurrentOpenedInterface());
				NotificationSystem::instance()->Draw(window);
				TextBoxGenerator::instance()->AdjustPositionTextBox(position_view_player);
				TextBoxGenerator::instance()->DrawAllTextbox(window);
				boss_map_gestion.DrawBossInterface(window);

				fps.DrawFPS(window);

				text_name_tester.setPosition(sf::Vector2f(25, 125) + position_view_player);
				window.draw(text_name_tester);

				window.display();
			}
		}
		else
		{
			if (user_interface.IsToClose())
			{
				window.close();
			}
			user_interface.MainInterfaceInteraction(window);

			window.clear();

			user_interface.DrawToScreenMainInterface(window);

			window.display();
		}

	}

	/*for (int i = 0; i < map_tile_size.y; ++i) 
	{
		delete[map[i]];
	}
	delete[] map;*/
	(*iterator)->SaveInformations();
	//_CrtDumpMemoryLeaks();
	return 0;
}

void textures_loading()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font player" << std::endl;
	}

	if (!screen_layer_texture.loadFromFile("Screen_layer.png"))
		std::cout << "Error: Couldn't load the screen layer texture" << std::endl;

	if (!texture_loading.loadFromFile("LoadingScreen.png"))
	{
		std::cout << "Error while loading the loading screen texture" << std::endl;
	}
}

void set_view()
{
	view_player.setViewport(sf::FloatRect(0, 0, Proportion, Proportion));

	std::list<std::shared_ptr<Player>>::iterator iterator = player_gestion.listPlayers.begin();
	sf::Vector2f position = (*iterator)->GetCurrentPosition();

	position_view_player.x = std::round(position.x - (window_width_i / 2 / Proportion));
	position_view_player.y = std::round(position.y - (window_height_i / 2 / Proportion));

	sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();

	if (position_view_player.x < 64)
		position_view_player.x = 64;
	if (position_view_player.y < 64)
		position_view_player.y = 64;
	if (position_view_player.x > map_size_variable * TILESIZE - 64 - window_size.x)
		position_view_player.x = map_size_variable * TILESIZE - 64 - window_size.x;
	if (position_view_player.y> map_size_variable*TILESIZE - 64 - window_size.y)
		position_view_player.y = map_size_variable * TILESIZE - 64 - window_size.y;

	view_player.reset(sf::FloatRect(position_view_player.x, position_view_player.y, window_width_f, window_height_f));
}

void MinimapGestion()
{
	minimap_view.setViewport(sf::FloatRect(0.75f, 0.25f, 1, 1));
	window.setView(minimap_view);

	sf::CircleShape radar;
	radar.setRadius(100);
	radar.setPosition(position_minimap);
	radar.setFillColor(sf::Color::Color(0, 0, 0, 150));
	radar.setOutlineColor(sf::Color::White);
	radar.setOutlineThickness(2);

	window.draw(radar);
}

void TransformMap()
{
	/*for (int y = 0; y < map_tile_size.y; ++y)
	{
		for (int x = 0; x < map_tile_size.y; ++x)
		{
			map[x][y] = map_demo[x][y];
		}
	}*/
	map = map_demo;
}

void TestOptions(sf::Vector2f mouse_position,sf::Vector2f position_player)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && clock_test_option.getElapsedTime().asSeconds() >= 0.2)
	{
		std::cout << "(" << mouse_position.x << "," << mouse_position.y << ")" << std::endl;
	}
}

void WelcomeMessage()
{
	window.clear();

	std::vector<int> listLetterSize;
	std::vector<sf::String> listString;
	std::vector<bool> listIfCentered;

	sf::String string1 = "-By clicking 'Next', you agree to not share, copy or sell any of part or the entirety of this game, including any part of the code and/or the pictures. You also agree to not use this game in any deemed harmful way.";
	sf::String string3 = "-En cliquant sur 'Next', vous consentez à ne pas partager, copier ou vendre une quelconque partie ou l'intégralité de ce jeu, incluant n'importe quelle partie du code et/ou des dessins. Vous consentez aussi à ne pas utiliser le jeu d'une façon qui pourrait être considérée comme nuisible.";
	sf::String string2 = "|                                                                    ";
	listLetterSize.push_back(34);
	listLetterSize.push_back(34);
	listLetterSize.push_back(34);
	listIfCentered.push_back(false);
	listIfCentered.push_back(false);
	listIfCentered.push_back(false);
	listString.push_back(string1);
	listString.push_back(string2);
	listString.push_back(string3);

	TextBoxGenerator::instance()->GenerateOneTextBoxWithSize(listString, listIfCentered, listLetterSize, sf::Vector2f(100,100),75);

	sf::Text text_next = GlobalFunction::CreateText(sf::Vector2f(800, 600), "Next", font, 40);
	window.draw(text_next);
	TextBoxGenerator::instance()->DrawAllTextbox(window);

	window.display();

	bool looping = true;
	while (looping)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (text_next.getGlobalBounds().contains(GlobalFunction::GetMousePosition(window, sf::Vector2f(0, 0))))
			{
				looping = false;
			}
		}
	}
}

void ResolutionGestion()
{
	window_dimension = ListObjectsSingleton::instance()->GetSizeWindow();
	window_height_f = window_dimension.y;
	window_height_i = window_dimension.y;
	window_width_i = window_dimension.x;
	window_width_f = window_dimension.x;
	window.setSize(sf::Vector2u(static_cast<unsigned int>(window_dimension.x), static_cast<unsigned int>(window_dimension.y)));
}

void FullscreenToggle()
{
	if (clock_toggle_fullscreen.getElapsedTime().asSeconds() >= 0.5)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
		{
			if (is_fullscreen)
			{
				window.create(sf::VideoMode::VideoMode(1600, 800), "Mage War Online");
				window.setPosition(sf::Vector2i(-8, 0));
				ListObjectsSingleton::instance()->ChangeSizeWindow(sf::Vector2f(1600, 800));
				ResolutionGestion();
				is_fullscreen = false;
			}
			else
			{
				window.create(sf::VideoMode::getDesktopMode(), "Mage War Online", sf::Style::Fullscreen);
				ListObjectsSingleton::instance()->ChangeSizeWindow(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
				ResolutionGestion();
				is_fullscreen = true;
			}
			clock_toggle_fullscreen.restart();
		}
	}
}

void LoadingScreen(bool loading_map, bool loading_spawn)
{
	sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();
	text_loading = GlobalFunction::CreateText(sf::Vector2f(window_size.x / 2 - 100, window_size.y / 2 - 75), "Loading...", font, 40);
	text_loading.setStyle(sf::Text::Bold);
	sprite_loading = GlobalFunction::CreateSprite(sf::Vector2f(window_size.x / 2 + 100, window_size.y / 2 - 75), sf::Vector2f(120, 116), texture_loading);
	sf::Text text_loading_tips = GlobalFunction::CreateText(sf::Vector2f(window_size.x / 2, window_size.y / 2 + 75), "Tips", font, 28);
	text_loading_tips.setStyle(sf::Text::Bold);
	text_loading_tips.setString(ListObjectsSingleton::instance()->GetRandomStringTip());
	text_loading_tips.setOrigin(text_loading_tips.getGlobalBounds().width / 2, text_loading_tips.getGlobalBounds().height / 2);
	sf::Clock clock_tips;
	sf::Clock clock_running_time;

	if (loading_map)
	{
		while (!loading_map_done)
		{
			if (clock_running_time.getElapsedTime().asMilliseconds() >= 1000 / 30)
			{
				if (clock_loading_animation.getElapsedTime().asSeconds() >= 0.03)
				{
					sprite_loading.setTextureRect(sf::IntRect(120 * animation_holder, 0, 120, 116));
					if (animation_holder_increasing)
					{
						animation_holder++;
						if (animation_holder == 34)
						{
							animation_holder_increasing = !animation_holder_increasing;
						}
					}
					else
					{
						animation_holder--;
						if (animation_holder == 0)
						{
							animation_holder_increasing = !animation_holder_increasing;
						}
					}
					clock_loading_animation.restart();
				}

				if (clock_tips.getElapsedTime().asSeconds() >= 7)
				{
					text_loading_tips.setString(ListObjectsSingleton::instance()->GetRandomStringTip());
					text_loading_tips.setOrigin(text_loading_tips.getGlobalBounds().width / 2, text_loading_tips.getGlobalBounds().height / 2);
					clock_tips.restart();
				}
				window.clear();
				window.draw(sprite_loading);
				window.draw(text_loading);
				window.draw(text_loading_tips);
				window.display();
				clock_running_time.restart();
			}
		}
	}
	if (loading_spawn)
	{
		while (!loading_spawns_done)
		{
			if (clock_running_time.getElapsedTime().asMilliseconds() >= 1000 / 30)
			{
				if (clock_loading_animation.getElapsedTime().asSeconds() >= 0.03)
				{
					sprite_loading.setTextureRect(sf::IntRect(120 * animation_holder, 0, 120, 116));
					if (animation_holder_increasing)
					{
						animation_holder++;
						if (animation_holder == 34)
						{
							animation_holder_increasing = !animation_holder_increasing;
						}
					}
					else
					{
						animation_holder--;
						if (animation_holder == 0)
						{
							animation_holder_increasing = !animation_holder_increasing;
						}
					}
					clock_loading_animation.restart();
				}
				if (clock_tips.getElapsedTime().asSeconds() >= 7)
				{
					text_loading_tips.setString(ListObjectsSingleton::instance()->GetRandomStringTip());
					text_loading_tips.setOrigin(text_loading_tips.getGlobalBounds().width / 2, text_loading_tips.getGlobalBounds().height / 2);
					clock_tips.restart();
				}
				window.clear();
				window.draw(sprite_loading);
				window.draw(text_loading);
				window.draw(text_loading_tips);
				window.display();
				clock_running_time.restart();
			}
		}
	}
}

void LoadMap()
{
	tiletexture.loadFromFile("MapTileSet.png");
	tile.setTexture(tiletexture);
	map_demo = map_generator.GenerateOneMap(map_size_variable, map_size_variable);
	TransformMap();
	nature_object_gestion.CreateAllNatureObject(map_generator.GetListBiomes(), sf::Vector2i(map_size_variable, map_size_variable), tile_map_size, window);
	loading_map_done = true;
}

void LoadSpawns()
{
	monster_generator.CreateSpawns(sf::Vector2f(map_size_variable*tile_map_size, map_size_variable*tile_map_size), ListObjectsSingleton::instance()->GetLevelMap(), SpawnPointGestion::instance()->GetSpawnPointPosition());
	loading_spawns_done = true;
}

void CenterMapGestion()
{
	if (boss_map_gestion.GetIfBossDefeated())
	{
		std::list<std::shared_ptr<Player>>::iterator iterator = player_gestion.listPlayers.begin();

		nature_object_gestion.DeleteListNatureObject();
		map_generator.ClearGenerator();
		monster_generator.ClearSpawns();
		(*iterator)->MapPortalGestion();
		int level_current_map = ListObjectsSingleton::instance()->GetLevelMap();
		ListObjectsSingleton::instance()->ChangeLevelMap(level_current_map + 1);

		position_view_player = sf::Vector2f(0, 0);
		view_player.reset(sf::FloatRect(position_view_player.x, position_view_player.y, window_width_f, window_height_f));
		window.setView(view_player);

		loading_map_done = false;
		sf::Thread thread_map(&LoadMap);
		thread_map.launch();
		LoadingScreen(true, false);

		loading_spawns_done = false;
		sf::Thread thread_spawns(&LoadSpawns);
		thread_spawns.launch();
		LoadingScreen(false, true);

		pillar_gestion.ResetPillar();
		SpawnPointGestion::instance()->PlayerChangedMapGestion();

		tiletexture.loadFromFile("MapTileSet.png");
		current_map_tile_size = sf::Vector2i(map_size_variable, map_size_variable);
	}
	else if (!boss_map_gestion.GetIfBossFightStarted())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			std::list<std::shared_ptr<Player>>::iterator iterator = player_gestion.listPlayers.begin();
			if ((*iterator)->GetNumberMonsterHearts() >= 25)
			{
				monster_generator.StartRitual((*iterator)->GetCurrentPosition());
			}
			if ((*iterator)->GetIfPlayerRitualDone())
			{
				if ((*iterator)->GetCollisionRect().intersects(SpawnPointGestion::instance()->GetAltarCollisionRect()))
				{
					nature_object_gestion.DeleteListNatureObject();
					map_generator.ClearGenerator();
					monster_generator.ClearSpawns();
					int level_current_map = ListObjectsSingleton::instance()->GetLevelMap();
					if (level_current_map != 5)
					{
						ListObjectsSingleton::instance()->ChangeLevelMap(level_current_map + 1);
						(*iterator)->MapPortalGestion();
						position_view_player = sf::Vector2f(0, 0);
						view_player.reset(sf::FloatRect(position_view_player.x, position_view_player.y, window_width_f, window_height_f));
						window.setView(view_player);

						loading_map_done = false;
						sf::Thread thread_map(&LoadMap);
						thread_map.launch();
						LoadingScreen(true, false);

						loading_spawns_done = false;
						sf::Thread thread_spawns(&LoadSpawns);
						thread_spawns.launch();
						LoadingScreen(false, true);

						pillar_gestion.ResetPillar();
						SpawnPointGestion::instance()->PlayerChangedMapGestion();

						tiletexture.loadFromFile("MapTileSet.png");
						current_map_tile_size = sf::Vector2i(map_size_variable, map_size_variable);
					}
					else
					{
						map = boss_map_gestion.GetBossMap(BossViking,(*iterator));
						tiletexture.loadFromFile("MapTileSetBossMapViking.png");
						current_map_tile_size = boss_map_gestion.GetBossMapNumberTile();
						boss_map_gestion.StartBossFight(BossViking);

						(*iterator)->TeleportEntity(sf::Vector2f(2335, 2000),0);
					}
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon))
	{
		std::list<std::shared_ptr<Player>>::iterator iterator = player_gestion.listPlayers.begin();

		nature_object_gestion.DeleteListNatureObject();
		map_generator.ClearGenerator();
		monster_generator.ClearSpawns();

		map = boss_map_gestion.GetBossMap(BossViking, (*iterator));
		tiletexture.loadFromFile("MapTileSetBossMapViking.png");
		current_map_tile_size = boss_map_gestion.GetBossMapNumberTile();
		boss_map_gestion.StartBossFight(BossViking);

		(*iterator)->TeleportEntity(sf::Vector2f(2335, 2000), 0);
	}
}

void SelectSave()
{
	sf::Texture texture_cancel;
	texture_cancel.loadFromFile("Sprite_erase_skill.png");
	sf::Clock clock_click_save_selection;

	sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();
	sf::Text text;
	sf::Text text_save_1;
	sf::Text text_save_2;
	sf::Text text_save_3;
	if (ListObjectsSingleton::instance()->GetCurrentLanguage() == English_E)
	{
		text = GlobalFunction::CreateText(sf::Vector2f(window_size.x / 2, 200), "Select A Save", font, 40);
		text_save_1 = GlobalFunction::CreateText(sf::Vector2f(window_size.x / 2 - 250, window_size.y/2), "Save 1", font, 30);
		text_save_2 = GlobalFunction::CreateText(sf::Vector2f(window_size.x / 2, window_size.y / 2), "Save 2", font, 30);
		text_save_3 = GlobalFunction::CreateText(sf::Vector2f(window_size.x / 2 + 250, window_size.y / 2), "Save 3", font, 30);
	}
	else
	{
		text = GlobalFunction::CreateText(sf::Vector2f(window_size.x / 2, 200), "Choississez Une Partie", font, 40);
		text_save_1 = GlobalFunction::CreateText(sf::Vector2f(window_size.x / 2 - 250, window_size.y / 2), "Partie 1", font, 30);
		text_save_2 = GlobalFunction::CreateText(sf::Vector2f(window_size.x / 2, window_size.y / 2), "Partie 2", font, 30);
		text_save_3 = GlobalFunction::CreateText(sf::Vector2f(window_size.x / 2 + 250, window_size.y / 2), "Partie 3", font, 30);
	}

	sf::Sprite sprite_cancel_1 = GlobalFunction::CreateSprite(sf::Vector2f(window_size.x / 2 - 250, window_size.y / 2 + 100),sf::Vector2f(54,54), texture_cancel);
	sf::Sprite sprite_cancel_2 = GlobalFunction::CreateSprite(sf::Vector2f(window_size.x / 2 , window_size.y / 2 + 100), sf::Vector2f(54, 54), texture_cancel);
	sf::Sprite sprite_cancel_3 = GlobalFunction::CreateSprite(sf::Vector2f(window_size.x / 2 + 250, window_size.y / 2 + 100), sf::Vector2f(54, 54), texture_cancel);

	bool looping = true;
	while (looping)
	{
		if (clock_click_save_selection.getElapsedTime().asSeconds() >= 0.2)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::list<std::shared_ptr<Player>>::iterator iterator = player_gestion.listPlayers.begin();

				sf::Vector2f mouse_position = GlobalFunction::GetMousePosition(window, position_view_player);
				if (text_save_1.getGlobalBounds().contains(mouse_position))
				{
					if (!ListObjectsSingleton::instance()->GetIfSaveUsed()[FirstSave_E])
					{
						while (mode_selection.ChooseGameMode(window))
						{

						}
					}
					ListObjectsSingleton::instance()->SetCurrentSave(FirstSave_E);
					(*iterator)->LoadInformations();
					pet_gestion.LoadPetInformation((*iterator));
					looping = false;
				}
				else if (text_save_2.getGlobalBounds().contains(mouse_position))
				{
					if (!ListObjectsSingleton::instance()->GetIfSaveUsed()[SecondSave_E])
					{
						while (mode_selection.ChooseGameMode(window))
						{

						}
					}

					ListObjectsSingleton::instance()->SetCurrentSave(SecondSave_E);
					(*iterator)->LoadInformations();
					pet_gestion.LoadPetInformation((*iterator));
					looping = false;
				}
				else if (text_save_3.getGlobalBounds().contains(mouse_position))
				{
					if (!ListObjectsSingleton::instance()->GetIfSaveUsed()[ThirdSave_E])
					{
						while (mode_selection.ChooseGameMode(window))
						{

						}
					}

					ListObjectsSingleton::instance()->SetCurrentSave(ThirdSave_E);
					(*iterator)->LoadInformations();
					pet_gestion.LoadPetInformation((*iterator));
					looping = false;
				}
				else if (sprite_cancel_1.getGlobalBounds().contains(mouse_position))
				{
					(*iterator)->DeleteSave(FirstSave_E);
					ListObjectsSingleton::instance()->SetSaveNotUsed(FirstSave_E);
				}
				else if (sprite_cancel_2.getGlobalBounds().contains(mouse_position))
				{
					(*iterator)->DeleteSave(SecondSave_E);
					ListObjectsSingleton::instance()->SetSaveNotUsed(SecondSave_E);
				}
				else if (sprite_cancel_3.getGlobalBounds().contains(mouse_position))
				{
					(*iterator)->DeleteSave(ThirdSave_E);
					ListObjectsSingleton::instance()->SetSaveNotUsed(ThirdSave_E);
				}
				clock_click_save_selection.restart();
			}
		}

		if (looping)
		{
			window.clear();
			window.draw(text);
			window.draw(text_save_1);
			window.draw(text_save_2);
			window.draw(text_save_3);
			window.draw(sprite_cancel_1);
			window.draw(sprite_cancel_2);
			window.draw(sprite_cancel_3);
			window.display();
		}
		else
		{
			window.clear();
			window.display();
		}
	}

	
}

void GivePlayerPet()
{
	if (true)
	{
		std::list<std::shared_ptr<Player>>::iterator iterator = player_gestion.listPlayers.begin();

		std::shared_ptr<Knight> pet = std::shared_ptr<Knight>(new Knight(ListObjectsSingleton::instance()->GetNewID()));
		(*iterator)->GivePet(pet);
		pet.reset();
	}
	if (true)
	{
		std::list<std::shared_ptr<Player>>::iterator iterator = player_gestion.listPlayers.begin();

		std::shared_ptr<Fairy> pet = std::shared_ptr<Fairy>(new Fairy(ListObjectsSingleton::instance()->GetNewID()));
		(*iterator)->GivePet(pet);
		pet.reset();
	}
	if (true)
	{
		std::list<std::shared_ptr<Player>>::iterator iterator = player_gestion.listPlayers.begin();

		std::shared_ptr<Ninja> pet = std::shared_ptr<Ninja>(new Ninja(ListObjectsSingleton::instance()->GetNewID()));
		(*iterator)->GivePet(pet);
		pet.reset();
	}
}

void PlayerDeathGestion()
{
	std::list<std::shared_ptr<Player>>::iterator iterator = player_gestion.listPlayers.begin();

	if ((*iterator)->GetIfPlayerDied())
	{
		ListObjectsSingleton::instance()->ChangeLevelMap(1);
		boss_map_gestion.FightOver(false, (*iterator));

		nature_object_gestion.DeleteListNatureObject();
		map_generator.ClearGenerator();
		monster_generator.ClearSpawns();
		(*iterator)->MapPortalGestion();

		position_view_player = sf::Vector2f(0, 0);
		view_player.reset(sf::FloatRect(position_view_player.x, position_view_player.y, window_width_f, window_height_f));
		window.setView(view_player);

		loading_map_done = false;
		sf::Thread thread_map(&LoadMap);
		thread_map.launch();
		LoadingScreen(true, false);

		loading_spawns_done = false;
		sf::Thread thread_spawns(&LoadSpawns);
		thread_spawns.launch();
		LoadingScreen(false, true);

		pillar_gestion.ResetPillar();
		SpawnPointGestion::instance()->PlayerChangedMapGestion();

		tiletexture.loadFromFile("MapTileSet.png");
		current_map_tile_size = sf::Vector2i(map_size_variable, map_size_variable);
	}
}



