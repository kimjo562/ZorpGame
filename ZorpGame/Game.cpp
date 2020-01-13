#include "Game.h"
#include "Enemy.h"
#include "Food.h"
#include "Powerup.h"
#include <iostream>
#include <windows.h>
#include <random>
#include <time.h>

using namespace std;

Game::Game() : m_gameOver{ false }
{

}

Game::~Game()
{
	delete[] m_powerups;
	delete[] m_enemies;
	delete[] m_food;
}

bool Game::startup()
{
	if (enableVirtualTerminal() == false) {
		std::cout << "The virtual terminal processing mode could not be activated." << std::endl;
		std::cout << "Press 'Enter' to exit." << std::endl;
		std::cin.get();
		return false;
	}

	srand(time(nullptr));

	initializeMap();
	initializeEnemies();
	initializePowerups();
	initializeFood();

	m_player.setPosition(Point2D{ 0,0 });

	drawWelcomeMessage();

	return true;
}

void Game::update()
{
	Point2D playerPos = m_player.getPosition();

	if (m_map[playerPos.y][playerPos.x].getType() == EXIT) {
		m_gameOver = true;
		return;
	}

	int command = getCommand();

	if (command == QUIT) {
		m_gameOver = true;
		return;
	}

	m_player.executeCommand(command, &m_map[playerPos.y][playerPos.x]);

	for (int i = 0; i < m_enemyCount; i++) 
	{
		if (m_enemies[i].isAlive() == false) 
		{
			Point2D pos = m_enemies[i].getPosition();
			m_map[pos.y][pos.x].removeGameObject(&m_enemies[i]);
		}
	}
}

void Game::draw()
{
	Point2D playerPos = m_player.getPosition();

	// list the directions the player can take
	drawValidDirections();

	// draw the description of the current room
	m_map[playerPos.y][playerPos.x].drawDescription();

	// redraw the map
	drawMap();
	// draw the player on the map
	m_player.draw();
}

bool Game::isGameOver()
{
	return m_gameOver;
}

bool Game::enableVirtualTerminal()
{
	// Set output mode to handle virtual terminal sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		return false;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
	{
		return false;
	}
	return true;
}

void Game::initializeMap()
{
	srand(time(nullptr));

	// set room positions
	for (int y = 0; y < MAZE_HEIGHT; y++) 
	{
		for (int x = 0; x < MAZE_WIDTH; x++) 
		{
			m_map[y][x].setPosition(Point2D{ x, y });
		}
	}

	// set the entrance and exit of the maze
	m_map[0][0].setType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].setType(EXIT);
}

void Game::initializeEnemies()
{
	// create a dynamic array of enemies 
	// (the number of enemies will change every game)
	m_enemyCount = 1 + rand() % 4;
	m_enemies = new Enemy[m_enemyCount];

	// randomly place the enemies in rooms on the map
	for (int i = 0; i < m_enemyCount; i++)
	{
		// a bit of math ensures the enemies wont spawn direclty
		// on or next to the entrance
		int x = 2 + (rand() % (MAZE_WIDTH - 3));
		int y = 2 + (rand() % (MAZE_HEIGHT - 3));

		m_enemies[i].setPosition(Point2D{ x, y });
		m_map[y][x].addGameObject(&m_enemies[i]);
	}
}

void Game::initializePowerups()
{
	// create some powerups
	m_powerupCount = 3;
	m_powerups = new Powerup[m_powerupCount];
	// randomly place the food in the map
	for (int i = 0; i < m_powerupCount; i++)
	{
		char name[30] = "";
		int x = rand() % (MAZE_WIDTH - 1);
		int y = rand() % (MAZE_HEIGHT - 1);

		float HP = 1;
		float AT = 1;
		float DF = 1;

		switch (i) {
		case 0:
			strcpy_s(name, "Potion of ");
			m_powerups[i].setHealthMultiplier(1.1f);
			break;
		case 1:
			strcpy_s(name, "Sword of ");
			m_powerups[i].setAttackMultiplier(1.1f);
			break;
		case 2:
			strcpy_s(name, "Shield of ");
			m_powerups[i].setDefenceMultiplier(1.1f);
			break;
		}

		strncat_s(name, itemNames[(rand() % 15)], 30);
		m_powerups[i].setName(name);
		m_map[y][x].addGameObject(&m_powerups[i]);
	}
}

void Game::initializeFood()
{
	// create some food
	m_foodCount = 3;
	m_food = new Food[m_foodCount];
	// randomly place the food in the map
	for (int i = 0; i < m_foodCount; i++)
	{
		int x = rand() % (MAZE_WIDTH - 1);
		int y = rand() % (MAZE_HEIGHT - 1);
		m_map[y][x].addGameObject(&m_food[i]);
	}
}

void Game::drawWelcomeMessage()
{
	cout << TITLE << MAGENTA << "Welcome to ZORP!" << RESET_COLOR << endl;
	cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << endl;
	cout << INDENT << "It is definitely not related to any other text-based adventure game." << endl << endl;
}

void Game::drawMap()
{
	Point2D position = { 0, 0 };

	// reset draw colors 
	cout << RESET_COLOR;
	for (position.y = 0; position.y < MAZE_HEIGHT; position.y++)
	{
		cout << INDENT;
		for (position.x = 0; position.x < MAZE_WIDTH; position.x++)
		{
			m_map[position.y][position.x].draw();
		}
		cout << endl;
	}
}

void Game::drawValidDirections()
{
	Point2D position = m_player.getPosition();

	// reset draw colors
	cout << RESET_COLOR;
	// jump to the correct location
	cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	cout << INDENT << "You can see paths leading to the " <<
		((position.x > 0) ? "west, " : "") <<
		((position.x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((position.y > 0) ? "north, " : "") <<
		((position.y < MAZE_HEIGHT - 1) ? "south, " : "") << endl;
}

int Game::getCommand()
{
	// for now, we can't read commands longer than 50 characters 
	char input[50] = "\0";

	// jump to the correct location 
	cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

	// clear any existing text 
	cout << CSI << "5M";

	// Insert 5 blank lines to ensure the inventory output remains correct
	cout << CSI << "5L";

	cout << INDENT << "Enter a command.";

	// move cursor to position for player to enter input 
	cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

	// clear the input buffer, ready for player input 
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> input;
	cout << RESET_COLOR;

	bool bMove = false;
	bool bPickup = false;
	while (input)
	{
		if (strcmp(input, "move") == 0 || strcmp(input, "go") == 0)
		{
			bMove = true;
		}
		else if (bMove == true)
		{
			if (strcmp(input, "north") == 0 || strcmp(input, "up") == 0)
				return NORTH;
			if (strcmp(input, "south") == 0 || strcmp(input, "down") == 0)
				return SOUTH;
			if (strcmp(input, "east") == 0 || strcmp(input, "right") == 0)
				return EAST;
			if (strcmp(input, "west") == 0 || strcmp(input, "left") == 0)
				return WEST;
		}

		if (strcmp(input, "look") == 0)
		{
			return LOOK;
		}
		if (strcmp(input, "fight") == 0)
		{
			return FIGHT;
		}
		if (strcmp(input, "quit") == 0)
		{
			return QUIT;
		}
		if (strcmp(input, "pick") == 0)
		{
			bPickup = true;
		}
		else if (bPickup == true)
		{
			if (strcmp(input, "up") == 0)
				return PICKUP;
		}

		char next = cin.peek();
		if (next == '\n' || next == EOF)
			break;
		cin >> input;
	}
	return 0;
}