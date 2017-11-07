#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include "DataTextManager.h"
#pragma warning(disable:4996)

DataTextManager::DataTextManager()
{
}

DataTextManager::~DataTextManager()
{
}

void DataTextManager::WriteInDataText(std::string string)
{
	using namespace std;

	ofstream myfile;
	myfile.open("1_DataText.txt", fstream::app);
	myfile.seekp(ios::end);
	myfile << endl;
	for (int number = 0; number < string.size(); number++)
	{
		myfile << string[number];
	}
	myfile.close();
}

std::string DataTextManager::GetDate()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	std::string str(buffer);
	std::string holder = " (D/M/Y) : ";

	std::stringstream fgd;
	fgd.clear();
	fgd << str;
	fgd << holder;
	str = fgd.str();

	return str;
}

DataTextManager* DataTextManager::s_instance = 0;

void DataTextManager::TestBallNextLine()
{
	using namespace std;

	ofstream myfile;
	myfile.open("TestBall.txt", fstream::app);
	myfile.seekp(ios::end);
	myfile << endl;
	myfile.close();
}

void DataTextManager::WriteInTestBall(std::string string)
{
	using namespace std;

	ofstream myfile;
	myfile.open("1_TestBall.txt", fstream::app);
	myfile.seekp(ios::end);
	for (int number = 0; number < string.size(); number++)
	{
		myfile << string[number];
	}
	myfile.close();
}

void DataTextManager::TestSquareNextLine()
{
	using namespace std;

	ofstream myfile;
	myfile.open("TestSquare.txt", fstream::app);
	myfile.seekp(ios::end);
	myfile << endl;
	myfile.close();
}

void DataTextManager::WriteInTestSquare(std::string string)
{
	using namespace std;

	ofstream myfile;
	myfile.open("1_TestSquare.txt", fstream::app);
	myfile.seekp(ios::end);
	for (int number = 0; number < string.size(); number++)
	{
		myfile << string[number];
	}
	myfile.close();
}

