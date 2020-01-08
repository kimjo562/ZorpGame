// ZorpGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <windows.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <string>
#include <ctime>
#include <random>
#include <time.h>
#include "Game.h"

using namespace std;

void main()
{
	Game game;

	if (game.startup() == false)
		return;

	// game loop
	while (!game.isGameOver())
	{
		game.draw();

		game.update();
	} // end game loop

	std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";	// jump to the correct location
	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
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



