#include "stdafx.h"
#include "TestCercle.h"

TestCercle::TestCercle()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error with green flame in skillinterface" << std::endl;
	}
	white_spot = GlobalFunction::CreateCircle(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2), 3, sf::Color::White);
	text = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 200), string, font ,24);
	size_rect = sf::Vector2f(text.getLocalBounds().width + 10, text.getLocalBounds().height + 10);
	rect = GlobalFunction::CreateRectangleWithOrigin(size_rect, sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 200 + size_rect.y/2 - 5), sf::Color::Color(0, 0, 0, 0));
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Red);
}

TestCercle::~TestCercle()
{
}

void TestCercle::AddCircleToList()
{
	Circle* circle = new Circle();
	circle->Init(pallier);
	listCircle.push_back(circle);
}

void TestCercle::MoveCircle(float DELTATIME)
{
	std::vector<Circle*>::iterator iterator = listCircle.begin();
	while (iterator != listCircle.end())
	{
		if (DELTATIME <= 0.5)
		{
			(*iterator)->Move(DELTATIME);
		}
		iterator++;
	}
}

void TestCercle::DrawCircle(sf::RenderWindow &window)
{
	std::vector<Circle*>::iterator iterator = listCircle.begin();
	while (iterator != listCircle.end())
	{
		(*iterator)->Draw(window);
		iterator++;
	}
}

void TestCercle::CircleAddingGestion(sf::RenderWindow &window)
{
	if (listCircle.size() <= maximum_circle)
	{
		if (clock_adding_circle.getElapsedTime().asSeconds() >= 0.2)
		{
			AddCircleToList();
			clock_adding_circle.restart();
		}
	}
}

void TestCercle::BackgroundColorGestion(sf::RenderWindow &window)
{
	if (clock_background_color.getElapsedTime().asSeconds() >= 0.05)
	{
		for (int number = 0; number < 3; number++)
		{
			if (background_color_increasing[number] == 1)
			{
				background_color_number[number] += background_color_increasing_color_rate[number];
			}
			else
			{
				background_color_number[number] -= background_color_increasing_color_rate[number];
			}
			if (background_color_number[number] >= 250 || background_color_number[number] <= 5)
			{
				background_color_increasing[number] *= -1;
				background_color_increasing_color_rate[number] = GlobalFunction::getRandomRange(1, 3);
			}
		}
		background_color = sf::Color::Color(background_color_number[0], background_color_number[1], background_color_number[2]);
		clock_background_color.restart();
	}
}

void TestCercle::StartingGame(sf::RenderWindow &window)
{
	if (skipped_pallier)
	{
		UpgradePallier();
	}
	else
	{
		skipped_pallier = true;
	}
	sf::String warningstring = "Nous vous recommandons de toujours regarder le point blanc au milieu de l'écran";
	sf::Text warningtext;
	warningtext = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 +200), warningstring, font, 20);
	sf::String string_start[2];
	sf::Text text_start[2];
	string_start[1] = "Appuiez sur la touche Espace pour commencer le test";
	text_start[1] = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 200), string_start[1], font, 24);
	string_start[0] = "Vous devez suivre la trajectoire des cercles rouges. Bonne chance!";
	text_start[0] = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 300), string_start[0], font, 30);
	for (int number = 0; number < maximum_circle; number++)
	{
		AddCircleToList();
		if (number < starting_circle)
		{
			listCircle[number]->ChooseAsFollowedCircle();
		}
	}
	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
	{
		window.clear();
		DrawCircle(window);
		window.draw(text_start[0]);
		window.draw(warningtext);
		window.draw(text_start[1]);
		window.display();
	}

	std::vector<Circle*>::iterator iterator = listCircle.begin();
	while (iterator != listCircle.end())
	{
		(*iterator)->RestartClockLifetime();
		iterator++;
	}

	clock_game.restart();
	clock_adding_circle.restart();
	clock_background_color.restart();
}

void TestCercle::CheckIfFollowingRightCircle(sf::RenderWindow &window)
{
	sf::Vector2f mouse_position;
	bool game_over = false;
	int number_right_circle = 0;
	bool looping = true;
	while (looping)
	{
		if (clock_mouse_click_timer.getElapsedTime().asSeconds() >= 0.2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				mouse_position = GlobalFunction::GetMousePosition(window, sf::Vector2f(0, 0));
				std::vector<Circle*>::iterator iterator = listCircle.begin();
				sf::String result = "Wrong";
				while (iterator != listCircle.end())
				{
					sf::String holder = (*iterator)->CheckIfRightCircle(mouse_position);
					if (holder == "Right")
					{
						result = "Right";
						break;
					}
					else if (holder == "Checked")
					{
						result = "Checked";
					}
					else
					{
						if (!(result == "Checked"))
						{
							result = "Wrong";
						}
					}
					iterator++;
				}
				if (result == "Right")
				{
					number_right_circle++;
				}
				else if (result == "Checked")
				{

				}
				else
				{
					game_over = true;
					break;
				}
				clock_mouse_click_timer.restart();
			}
		}
		if (number_right_circle == starting_circle)
		{
			looping = false;
		}
	}
	if (game_over)
	{
		GameOver(window);
	}
	else
	{
		Win(window);
	}
}

void TestCercle::Win(sf::RenderWindow &window)
{
	sf::String string;
	sf::Text text;
	sf::Text text2;
	sf::String string2 = "Appuyez sur B pour débuter le prochain pallier.";
	string = "Vous avez réussi à suivre le(s) bon(s) cercle(s). Félicitation!";
	text = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2-50), string, font, 20);
	text2 = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2+50), string2, font, 20);
	window.clear();
	window.draw(text);
	window.draw(text2);
	window.display();
	bool looping = true;
	while (looping)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			looping = false;
		}
	}
	listCircle.clear();
	clock_adding_circle.restart();
	clock_game.restart();
	clock_background_color.restart();
	pallier++;

	StartingGame(window);
	for (size_t i = 0; i < starting_circle; i++)
	{
		AddCircleToList();
	}
	std::vector<Circle*>::iterator iterator = listCircle.begin();
	while (iterator != listCircle.end())
	{
		(*iterator)->speed = speed;
		iterator++;
	}
}

void TestCercle::GameOver(sf::RenderWindow &window)
{
	if (!pratice_mode)
	{
		std::string string_to_file = DataTextManager::instance()->GetDate();
		std::string holder = "Test des cercles, essai # ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDString(string_to_file, number_try);
		holder = ". Palliers réussis : ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDString(string_to_file, pallier-1);
		DataTextManager::instance()->WriteInDataText(string_to_file);
	}
	sf::String string;
	sf::Text text;
	string = "Vous n'avez pas réussi à suivre le(s) bon(s) cercle(s). Appuyez sur espace pour retourner au menu!";
	text = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2), string, font, 20);
	window.clear();
	window.draw(text);
	window.display();
	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
	{

	}
	listCircle.clear();
	clock_adding_circle.restart();
	clock_game.restart();
	clock_background_color.restart();
	in_game = false;
	starting_circle = initial_starting_circle;
	maximum_circle = initial_maximum_circle;
	skipped_pallier = false;
	pallier = 0;
	number_try++;
}

void TestCercle::MainLoop(sf::RenderWindow &window, bool pratice_mode)
{
	this->pratice_mode = pratice_mode;
	if (!skipped_pallier)
	{
		SkipPallier();
	}
	StartingGame(window);
	for (size_t i = 0; i < starting_circle; i++)
	{
		AddCircleToList();
	}
	std::vector<Circle*>::iterator iterator = listCircle.begin();
	while (iterator != listCircle.end())
	{
		(*iterator)->speed = speed;
		iterator++;
	}
	while (in_game)
	{
		DELTATIME = deltatime_gestion.GetDeltaTime();
		window.clear();

		MoveCircle(DELTATIME);
		DrawCircle(window);
		PallierOnScreen(window);

		if (clock_game.getElapsedTime().asSeconds() >= 10)
		{
			CheckIfFollowingRightCircle(window);
		}
		window.draw(white_spot);
		window.display();
	}
	in_game = true;
}

bool TestCercle::WhileInMenu(sf::RenderWindow &window)
{
	sf::Vector2f mouse_position = GlobalFunction::GetMousePosition(window, sf::Vector2f(0, 0));
	window.draw(rect);
	window.draw(text);
	if (GlobalFunction::CheckMouseOnSomethingWithOrigin(mouse_position, rect.getPosition(), size_rect) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return true;
	}
	return false;
}

void TestCercle::UpgradePallier()
{
	if (pallier > 0)
	{
		if (pallier < 46)
		{
			speed += 10;
			maximum_circle += 2;
		}
		else
		{
			maximum_circle += 3;
			speed += 10;
		}
		if (pallier == 11 || pallier == 21 || pallier == 40)
		{
			maximum_circle = initial_maximum_circle;
			starting_circle++;
			speed = initial_speed;
		}
		if (pallier == 31)
		{
			initial_maximum_circle = 20;
			starting_circle = 3;
			initial_starting_circle = 3;
			initial_speed = 300;
			maximum_circle = initial_maximum_circle;
			speed = initial_speed;
		}
	}
}

void TestCercle::SkipPallier()
{
	for (int number = 0; number < skipping_pallier; number++)
	{
		pallier++;
		UpgradePallier();
	}
}

void TestCercle::PallierOnScreen(sf::RenderWindow &window)
{
	string_pallier.clear();
	string_pallier = "Pallier(s): ";
	string_pallier = GlobalFunction::InsertNumberToString(string_pallier, pallier, string_pallier.getSize());
	text_pallier = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x - 95, window_dimension.y - 30),string_pallier,font,24);
	window.draw(text_pallier);
}