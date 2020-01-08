#include "Room.h"
#include "GameDefines.h"
#include "Powerup.h"
#include "Player.h"
#include "Food.h"
#include <iostream>

using namespace std;

// m_type(EMPTY)  -  Directly initalize member variable  [Using Symbol ()]
// m_type{EMPTY}  -  Uniformly initalize member variable  [Using Symbol {}]
Room::Room() : m_type{ EMPTY }, m_mapPosition{ 0, 0 }, m_powerup{ nullptr }, m_enemy{ nullptr }, m_food{ nullptr }
{
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
		if (m_enemy != nullptr) {
			std::cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
			break;
		}
		if (m_powerup != nullptr) {
			std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
			break;
		}
		if (m_food != nullptr) {
			std::cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ] ";
			break;
		}
		std::cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
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
		if (m_enemy != nullptr) 
		{
			cout << INDENT << RED << "BEWARE." << RESET_COLOR << " An enemy is approaching." << endl;
			break;
		}
		if (m_powerup != nullptr) 
		{
			cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate futher." << endl;
			break;
		}
		if (m_food != nullptr)
		{
			cout << INDENT << "You smell a recently extinguished campfire, perhaps left by a previous traveller." << endl;
			break;
		}
		cout << INDENT << "You are in an empty meadow. There is nothing of note here." << endl;
		break;

	case ENTRANCE:
		cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back." << endl;
		break;

	case EXIT:
		cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << endl;
		break;
	}
}
