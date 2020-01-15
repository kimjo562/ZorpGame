#include "Player.h"
#include "GameDefines.h"
#include "Powerup.h"
#include "Room.h"
#include "Enemy.h"
#include "Food.h"
#include <iostream>
#include <algorithm>

using namespace std;

Player::Player() : Character({ 0, 0 }, 100, 20, 20)
{
	m_priority = PRIORITY_PLAYER;
}

Player::Player(int x, int y) : Character({ x, y }, 100, 20, 20)
{
}

Player::~Player()
{
}

void Player::draw()
{
	Point2D outPos = 
	{
		INDENT_X + (6 * m_mapPosition.x) + 3,
		MAP_Y + m_mapPosition.y 
	};

	// draw the player's position on the map
	// move cursor to map pos and delete character at current position
	cout << CSI << outPos.y << ";" << outPos.x << "H";
	cout << MAGENTA << "\x81" << RESET_COLOR;

	cout << INVENTORY_OUTPUT_POS;
	// clear any existing text
	cout << CSI << "1M";
	for (auto it = m_powerups.begin(); it < m_powerups.end(); it++) 
	{
		cout << (*it)->getName() << "\t";
	}
}

void Player::drawDescription()
{

}

void Player::lookAt()
{
	cout << EXTRA_OUTPUT_POS << RESET_COLOR << "Hmmm, I look good!" << endl;
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
		pRoom->lookAt();
		break;
	case FIGHT:
		attack(pRoom->getEnemy());
		break;
	case PICKUP:
		pickup(pRoom);
		break;
	case SAVE:
	case LOAD:
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
	if (pRoom->getPowerup() != nullptr) {
		Powerup* powerup = pRoom->getPowerup();
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You pick up the " << powerup->getName() << endl;
		// add the powerup to the player's inventory

		addPowerup(powerup);
		// remove the powerup from the room 
		// (but don't delete it, the player owns it now)
		pRoom->removeGameObject(powerup);
	}
	else if (pRoom->getFood() != nullptr) {
		Food* food = pRoom->getFood();
		// eat the food
		m_healthPoints += food->getHP();
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You feel refreshed. Your health is now " << m_healthPoints << endl;
		// remove the food from the room
		pRoom->removeGameObject(food);
	}
	else {
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is nothing here to pick up." << endl;
	}
}

void Player::attack(Enemy* pEnemy)
{
	if (pEnemy == nullptr) {
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here you can fight with." << endl;
	}
	else {
		pEnemy->onAttacked(m_attackPoints);

		if (pEnemy->isAlive() == false) {
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a slime and kill it." << endl;
		}
		else {
			int damage = pEnemy->getAT() - m_defendPoints;
			if (damage < 0)
				damage = 1 + rand() % 10;

			m_healthPoints -= damage;

			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a slime and take " << damage << " points damage. Your healh is now at " << m_healthPoints << endl;
			cout << INDENT << "The slime has " << pEnemy->getHP() << " health remaining." << endl;
		}
	}
}