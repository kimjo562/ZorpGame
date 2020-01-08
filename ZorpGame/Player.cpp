#include "Player.h"
#include "GameDefines.h"
#include "Powerup.h"
#include "Room.h"
#include "Enemy.h"
#include "Food.h"
#include <iostream>
#include <algorithm>

using namespace std;

Player::Player() : m_mapPosition { 0, 0 }, m_healthPoints{ 100 }, m_attackPoints{ 20 }, m_defendPoints{ 20 }
{ 

} 

Player::Player(int x, int y) : m_mapPosition{ x, y }, m_healthPoints{ 100 }, m_attackPoints{ 20 }, m_defendPoints{ 20 }
{

}


Player::~Player()
{

}


void Player::setPosition(const Point2D& position)
{
	m_mapPosition = position;
}

Point2D Player::getPosition()
{
	return m_mapPosition;
}

void Player::addPowerup(Powerup* pPowerup)
{
	m_powerups.push_back(pPowerup);

	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::compare);
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

	cout << INVENTORY_OUTPUT_POS;
	for (auto it = m_powerups.begin(); it < m_powerups.end(); it++)
	{
		cout << (*it)->getName() << "\t";
	}
}

void Player::executeCommand(int command, Room* pRoom)
{
	switch (command)
	{
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1)
			m_mapPosition.x++;
		return;

	case WEST:
		if (m_mapPosition.x > 0)
			m_mapPosition.x--;
		return;

	case NORTH:
		if (m_mapPosition.y > 0)
			m_mapPosition.y--;
		return;

	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1)
			m_mapPosition.y++;
		return;

	case LOOK:
		if (pRoom->getEnemy() != nullptr)
		{
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "LOOK OUT! An enemy is approaching." << std::endl;
		}
		else if (pRoom->getPowerup() != nullptr)
		{
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here. It looks small enough to pick up." << std::endl;
		}
		else if (pRoom->getFood() != nullptr)
		{
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some food here. It should be edible." << std::endl;
		}
		else
		{
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning" << std::endl;
		}
		break;

	case FIGHT:
		attack(pRoom->getEnemy());
		break;

	case PICKUP:
		pickup(pRoom);
		break;

	default:
		// the direction was not valid,
		// do nothing, go back to the top of the loop and ask again
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << endl;
		break;
	}

	cout << INDENT << "Press 'Enter' to continue.";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();

}

void Player::pickup(Room* pRoom)
{
	if (pRoom->getPowerup() != nullptr) 
	{
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You pick up the " << pRoom->getPowerup()->getName() << std::endl;
		// add the powerup to the player's inventory
		addPowerup(pRoom->getPowerup());
		// remove the powerup from the room 
		// (but don't delete it, the player owns it now)
		pRoom->setPowerup(nullptr);
	}
	else if (pRoom->getFood() != nullptr) 
	{
		// eat the food
		m_healthPoints += pRoom->getFood()->getHP();
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You feel refreshed. Your health is now " << m_healthPoints << std::endl;
		// remove the food from the room
		pRoom->setFood(nullptr);
	}
	else 
	{
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is nothing here to pick up." << std::endl;
	}
}


void Player::attack(Enemy* pEnemy)
{
	if (pEnemy == nullptr)
	{
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here you can fight with." << std::endl;
	}
	else
	{
		pEnemy->onAttacked(m_attackPoints);

		if (pEnemy->isAlive() == false)
		{
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a grue and kill it." << std::endl;
		}
		else
		{
			int damage = pEnemy->getAT() - m_defendPoints;
			m_healthPoints -= damage;

			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a grue and take " << damage <<
				" points damage. Your healh is now at " << m_healthPoints << std::endl;
			std::cout << INDENT << "The grue has " << pEnemy->getHP() << " health remaining." << std::endl;
		}
	}
}