#include "stdafx.h"
#include "TestJugement.h"

TestJugement::TestJugement()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error with green flame in skillinterface" << std::endl;
	}
	text = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 100), string, font, 24);
	size_rect = sf::Vector2f(text.getLocalBounds().width + 10, text.getLocalBounds().height + 10);
	rect = GlobalFunction::CreateRectangleWithOrigin(size_rect, sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 100 + size_rect.y / 2 - 5), sf::Color::Color(0, 0, 0, 0));
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Red);
}

TestJugement::~TestJugement()
{
}

void TestJugement::MoveCircle(float DELTATIME)
{
	listCircle[0]->Move(DELTATIME);
}

void TestJugement::DrawCircle(sf::RenderWindow &window)
{
	listCircle[0]->Draw(window);
}

void TestJugement::StartingGame(sf::RenderWindow &window)
{
	if (!pratice_mode)
	{
		DataTextManager::instance()->TestBallNextLine();
		std::string string_to_file = DataTextManager::instance()->GetDate();
		std::string holder = "Test de la balle rebondissante, essai # ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDString(string_to_file, number_try);
		holder = " : ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		DataTextManager::instance()->WriteInTestBall(string_to_file);
	}
	sf::String string_start[2];
	sf::Text text_start[2];
	string_start[1] = "Appuiez sur la touche B pour commencer le test";
	text_start[1] = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 150), string_start[1], font, 24);
	string_start[0] = "La balle doit arriver le plus près possible des rectangles sans les toucher. Appuyez sur espace pour changer la direction de la balle.";
	text_start[0] = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 250), string_start[0], font, 20);
	Ball* ball = new Ball();
	ball->Init(pratice_mode);
	listCircle.push_back(ball);
	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::B)))
	{
		window.clear();
		DrawCircle(window);
		window.draw(text_start[0]);
		window.draw(text_start[1]);
		window.display();
	}
}

void TestJugement::Win(sf::RenderWindow &window)
{

}

void TestJugement::GameOver(sf::RenderWindow &window)
{
	if (!pratice_mode)
	{
		std::string string_to_file = DataTextManager::instance()->GetDate();
		std::string holder = "Test de la balle rebondissante, essai # ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDString(string_to_file, number_try);
		holder = ". Moyenne de la distance en pixel : ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDStringFLOAT(string_to_file, listCircle[0]->GetAverageDistance());
		holder = ". Nombre de pénalités : ";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDString(string_to_file, listCircle[0]->number_penalities);
		DataTextManager::instance()->WriteInDataText(string_to_file);
	}
	sf::Text text3;
	sf::String string3 = "Votre distance moyenne lors des changements de direction est ";
	string3 = GlobalFunction::InsertNumberToString(string3, listCircle[0]->GetAverageDistance(), string3.getSize());
	string3.insert(string3.getSize(), " pixels!");
	text3 = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, 175), string3, font, 30);
	sf::String string;
	sf::Text text;
	sf::Text text2;
	sf::String string2 = "Vous avez terminé le test.";
	text2 = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, 100), string2, font, 30);
	string = "Appuyez sur B pour retourner au menu!";
	text = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2), string, font, 30);
	window.clear();
	window.draw(text);
	window.draw(text3);
	window.draw(text2);
	window.display();
	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::B)))
	{

	}
	listCircle.clear();
	in_game = false;
	number_try++;
}

void TestJugement::MainLoop(sf::RenderWindow &window, bool pratice_mode)
{
	this->pratice_mode = pratice_mode;
	StartingGame(window);
	listCircle[0]->PositionCenter();
	while (in_game)
	{
		DELTATIME = deltatime_gestion.GetDeltaTime();
		window.clear();

		MoveCircle(DELTATIME);
		DrawCircle(window);
		if (listCircle[0]->GetNumberStep() == 50)
		{
			GameOver(window);
		}

		window.display();
	}
	in_game = true;
}

bool TestJugement::WhileInMenu(sf::RenderWindow &window)
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
