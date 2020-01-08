#include "Player.h"
#include "GameDefines.h"
#include <iostream>

using namespace std;

Player::Player()
{
	m_mapPosition.x = 0;
	m_mapPosition.y = 0;
}

Player::Player(int x, int y)
{
	m_mapPosition.x = x;
	m_mapPosition.y = y;
}


Player::~Player()
{
}


void Player::setPosition(Point2D position)
{
	m_mapPosition = position;
}

Point2D Player::getPosition()
{
	return m_mapPosition;
}

void Player::draw()
{
	Point2D outPos = {
		INDENT_X + (6 * m_mapPosition.x) + 3,
		MAP_Y + m_mapPosition.y };

	// draw the player's position on the map
	// move cursor to map pos and delete character at current position
	cout << CSI << outPos.y << ";" << outPos.x << "H";
	cout << MAGENTA << "\x81" << RESET_COLOR;
}

bool Player::executeCommand(int command)
{
	switch (command) {
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1)
			m_mapPosition.x++;
		return true;
	case WEST:
		if (m_mapPosition.x > 0)
			m_mapPosition.x--;
		return true;
	case NORTH:
		if (m_mapPosition.y > 0)
			m_mapPosition.y--;
		return true;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1)
			m_mapPosition.y++;
		return true;
	}
	return false;
}