#include "Room.h"
#include "GameDefines.h"
#include <iostream>

using namespace std;

Room::Room()
{
	m_type = EMPTY;
	m_mapPosition.x = 0;
	m_mapPosition.y = 0;
}

Room::~Room()
{
}

void Room::setPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::setType(int type)
{
	m_type = type;
}

int Room::getType()
{
	return m_type;
}


void Room::draw()
{
	// find the console output position 
	int outX = INDENT_X + (6 * m_mapPosition.x) + 1;
	int outY = MAP_Y + m_mapPosition.y;

	// jump to the correct location
	cout << CSI << outY << ";" << outX << "H";

	// draw the room 
	switch (m_type)
	{
	case EMPTY:
		cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
		break;

	case ENEMY:
		cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
		break;

	case TREASURE: cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
		break;

	case FOOD:
		cout << "[ " << CYAN << "\xcf" << RESET_COLOR << " ] ";
		break;

	case ENTRANCE:
		cout << "[ " << WHITE << "\x9d" << RESET_COLOR << " ] ";
		break;

	case EXIT:
		cout << "[ " << WHITE << "\xFE" << RESET_COLOR << " ] ";
		break;
	}
}

void Room::drawDescription()
{
	// reset draw colors
	cout << RESET_COLOR;
	// jump to the correct location 
	cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";
	// Delete 4 lines and insert 4 empty lines 
	cout << CSI << "4M" << CSI << "4L" << endl;

	// write description of current room 
	switch (m_type)
	{
	case EMPTY:
		cout << INDENT << "You are in an empty meadow. There is nothing of note here." << endl;
		break;

	case ENEMY:
		cout << INDENT << RED << "BEWARE." << RESET_COLOR << " An enemy is approaching." << endl;
		break;

	case TREASURE:
		cout << INDENT << "Your journey has been rewarded. You have found some treasure." << endl;
		break;

	case FOOD:
		cout << INDENT << "At last! You collect some food to sustain you on your journey." << endl;
		break;

	case ENTRANCE:
		cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back." << endl;
		break;

	case EXIT:
		cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << endl;
		break;
	}
}

bool Room::executeCommand(int command)
{
	switch (command)
	{
	case LOOK:
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning" << endl;
		cout << INDENT << "Press 'Enter' to continue.";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.get();
		break;

	case FIGHT:
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You could try to fight, but you don't have a weapon." << endl;
		cout << INDENT << "Press 'Enter' to continue.";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.get();
		break;
	default:
		// the direction was not valid, 
		// do nothing, go back to the top of the loop and ask again
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << endl;
		cout << INDENT << "Press 'Enter' to continute.";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.get();
		break;
	}
	return false;
}