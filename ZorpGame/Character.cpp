#include "Character.h"
#include "Powerup.h"
#include <algorithm>

Character::Character() : GameObject{ { 0, 0 } }, m_healthPoints{ 0 }, m_attackPoints{ 0 }, m_defendPoints{ 0 }
{

}

Character::Character(Point2D position, int health, int attack, int defend) :
	GameObject{ position }, m_healthPoints{ health }, m_attackPoints{ attack }, m_defendPoints{ defend }
{
}

Character::~Character()
{
}

void Character::addPowerup(Powerup* pPowerup)
{
	m_powerups.push_back(pPowerup);

	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::compare);
}
