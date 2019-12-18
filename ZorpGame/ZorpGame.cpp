// ZorpGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

void main()
{
	char firstLetterOfName = 0;
	int height = 0;
	int playerHP = 0;

	cout << "Welcome to ZORP!" << endl;
	cout << "ZORP is a game of adventure, danger, and low cunning." << endl;
	cout << "It is definitely not related to any other text-based adventure game." << endl << endl;
	cout << "First, some questions..." << endl;
	cout << "How tall are you, in centimeters? " << endl;
	cin >> height;

	system("cls");

	cout << "You entered " << height << endl;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	if (cin.fail())
	{
		cout << "You have failed the first challenge and been killed by shenanigans." << endl;
	}
	else
	{
		cout << "You have entered " << height << " as your height" << endl<<endl;
	}

	cout << "What is the first letter of your name?" << endl;
	cin >> firstLetterOfName;

	if (cin.fail() || !isalpha(firstLetterOfName))
	{
		cout << "You have failed the second challenge and been killed by shenanigans." << endl;
	}
	else
	{
		cout << "You have entered " << firstLetterOfName << " as your First Letter." << endl;
	}

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());


	if (firstLetterOfName != 0)
	{
		playerHP = (float)height / (firstLetterOfName * 0.02f);
	}
	else
	{
		playerHP = 0;
	}

	cout << endl;
	cout << "Using a Yeet.Yote Health Machine, it has calculated that the machine has given you Yuh " << playerHP << " amount of health." << endl;


	cout << "Press any key to close the program...";
	cin.get();
	system("pause");
	system("cls");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
