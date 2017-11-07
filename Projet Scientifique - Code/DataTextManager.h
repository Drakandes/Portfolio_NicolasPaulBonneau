#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

class DataTextManager
{
private:
	static DataTextManager *s_instance;
public:
	DataTextManager();
	~DataTextManager();

	static void Initialize()
	{
		s_instance = new DataTextManager();
	}
	static DataTextManager *instance()
	{
		if (!s_instance)
			s_instance = new DataTextManager;
		return s_instance;
	}

	void WriteInDataText(std::string string);
	std::string GetDate();
	void TestBallNextLine();
	void WriteInTestBall(std::string string);
	void TestSquareNextLine();
	void WriteInTestSquare(std::string string);
};

