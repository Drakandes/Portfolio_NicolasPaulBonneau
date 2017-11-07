#include "stdafx.h"
#include "TestReflexe.h"

TestReflexe::TestReflexe()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error with green flame in skillinterface" << std::endl;
	}
	white_spot = GlobalFunction::CreateCircle(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2), 3, sf::Color::White);
	text = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 ), string, font, 24);
	size_rect = sf::Vector2f(text.getLocalBounds().width + 10, text.getLocalBounds().height + 10);
	rect = GlobalFunction::CreateRectangleWithOrigin(size_rect, sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 + size_rect.y / 2 - 5), sf::Color::Color(0, 0, 0, 0));
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Red);
}

TestReflexe::~TestReflexe()
{
}

void TestReflexe::StartingGame(sf::RenderWindow &window)
{
	if (!pratice_mode)
	{
		DataTextManager::instance()->TestSquareNextLine();
		std::string string_to_file = DataTextManager::instance()->GetDate();
		std::string holder = "Test des apparitions, essai # ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDString(string_to_file, number_try);
		holder = " : ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		DataTextManager::instance()->WriteInTestSquare(string_to_file);
	}
	sf::String warningstring = "Nous vous recommandons de toujours regarder le point blanc au milieu de l'écran";
	sf::Text warningtext;
	warningtext = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 +200), warningstring, font, 20);
	sf::String string_start[2];
	sf::Text text_start[2];
	string_start[1] = "Appuiez sur la touche Espace pour commencer le test";
	text_start[1] = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 200), string_start[1], font, 24);
	string_start[0] = "Appuyez sur Espace le plus rapidement possible lorsqu'un carré blanc apparaît";
	text_start[0] = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 300), string_start[0], font, 20);

	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
	{
		window.clear();
		window.draw(white_spot);
		window.draw(text_start[0]);
		window.draw(warningtext);
		window.draw(text_start[1]);
		window.display();
	}
	clock_game.restart();
}

void TestReflexe::Win(sf::RenderWindow &window)
{
	if (!pratice_mode)
	{
		std::string string_to_file = DataTextManager::instance()->GetDate();
		std::string holder = "Test des apparitions, essai # ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDString(string_to_file, number_try);
		holder = ". Temps de réaction moyen : ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDStringFLOAT(string_to_file, reaction_time_total / number_rect_max);
		holder = ". Meilleur temps de réaction : ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDStringFLOAT(string_to_file, best_reaction);
		holder = ". Pire temps de réaction : ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDStringFLOAT(string_to_file, worst_reaction);
		holder = ". Nombre de pénalités : ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDString(string_to_file, number_penalties);
		DataTextManager::instance()->WriteInDataText(string_to_file);
	}
	sf::String string3 =  "Votre meilleur temps de réaction est ";
	sf::Text text3;
	string3 = GlobalFunction::InsertNumberToStringIfFloat(string3, best_reaction, string3.getSize());
	string3.insert(string3.getSize(), " seconde!");
	text3 = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 150), string3, font, 26);
	sf::String string4 = "Votre moins bon temps de réaction est ";
	sf::Text text4;
	string4 = GlobalFunction::InsertNumberToStringIfFloat(string4, worst_reaction, string4.getSize());
	string4.insert(string4.getSize(), " seconde!");
	text4 = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 100), string4, font, 26);
	sf::String string;
	sf::Text text;
	sf::String string2 = "Votre temps de réaction moyen est de ";
	sf::Text text2;
	string2 = GlobalFunction::InsertNumberToStringIfFloat(string2, reaction_time_total/number_rect_max, string2.getSize());
	string2.insert(string2.getSize(), " seconde(s)!");
	string = "Le test est terminé, félicitation! Appuyez sur B pour retourner au menu";
	text = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 +50), string, font, 26);
	text2 = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 -50), string2, font, 26);
	window.clear();
	window.draw(text);
	window.draw(text2);
	window.draw(text3);
	window.draw(text4);
	window.display();
	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::B)))
	{
	}
	in_game = false;
	number_spawned_rect = 0;
	listRect.clear();
	number_try++;
	number_penalties = 0;
	best_reaction = 5;
	worst_reaction = 0;
	reaction_time_total = 0;
}

void TestReflexe::GameOver(sf::RenderWindow &window)
{

}

void TestReflexe::MainLoop(sf::RenderWindow &window, bool pratice_mode)
{
	this->pratice_mode = pratice_mode;
	StartingGame(window);
	while (in_game)
	{
		DELTATIME = deltatime_gestion.GetDeltaTime();
		window.clear();
		window.draw(white_spot);
		if (clock_game.getElapsedTime().asSeconds() >= time_reset)
		{
			SpawnRectangle(window);
			time_reset = static_cast<float>(GlobalFunction::getRandomRange(500, 2500)) / 1000;
			clock_game.restart();
		}

		if (number_spawned_rect == number_rect_max)
		{
			Win(window);
		}

		window.display();
	}
	in_game = true;
}

bool TestReflexe::WhileInMenu(sf::RenderWindow &window)
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

void TestReflexe::SpawnRectangle(sf::RenderWindow &window)
{
	sf::Clock clock;
	Square* square = new Square();
	square->Init();
	listRect.push_back(square);
	bool over_time_limit = false;
	bool looping = true;
	while (looping)
	{
		if (clock.getElapsedTime().asSeconds() >= 1.5)
		{
			over_time_limit = true;
			looping = false;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			looping = false;
		}
		window.clear();
		window.draw(white_spot);
		std::list<Square*>::iterator iterator = listRect.begin();
		while (iterator != listRect.end())
		{
			bool is_to_delete = (*iterator)->CheckIfToDelete();
			if (!(is_to_delete))
			{
				(*iterator)->Draw(window);
				iterator++;
			}
			else
			{
				listRect.erase(iterator++);
			}
		}
		window.display();
	}
	if (over_time_limit)
	{
		reaction_time_total += 0.75;
		number_penalties++;
		if (!pratice_mode)
		{
			std::string string_to_file;
			std::string holder = "-";
			string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
			string_to_file = GlobalFunction::InsertNumberToSTDStringFLOAT(string_to_file, 0.75);
			holder = "-";
			string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
			DataTextManager::instance()->WriteInTestSquare(string_to_file);
		}
	}
	else
	{
		float reaction_time = clock.getElapsedTime().asSeconds();
		reaction_time_total += reaction_time;
		if (reaction_time > worst_reaction)
		{
			worst_reaction = reaction_time;
		}
		if (reaction_time < best_reaction)
		{
			best_reaction = reaction_time;
		}
		if (!pratice_mode)
		{
			std::string string_to_file;
			std::string holder = "-";
			string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
			string_to_file = GlobalFunction::InsertNumberToSTDStringFLOAT(string_to_file, reaction_time);
			holder = "-";
			string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
			DataTextManager::instance()->WriteInTestSquare(string_to_file);
		}
	}
	number_spawned_rect++;
}