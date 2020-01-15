#include "Food.h"
#include "GameDefines.h"
#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

Food::Food() : m_healthPoints{ 10 }
{
	m_priority = PRIORITY_FOOD;
};

Food::Food(Point2D position) : GameObject{ position }
{
	m_priority = PRIORITY_FOOD;
};

void Food::draw()
{
	cout << "[ " << BLUE << "\xcf" << RESET_COLOR << " ] ";
}

void Food::drawDescription()
{
	cout << INDENT << "You smell a recently extinguished campfire, perhaps left by a previous traveller." << endl;
}

void Food::lookAt()
{
	cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some food here. It should be edible." << endl;
}

void Food::save(std::ofstream& out)
{
	if (!out.is_open())
		return;

	out << m_priority << ",";
	out << m_mapPosition.x << ",";
	out << m_mapPosition.y << ",";
	out << m_healthPoints << std::endl;
}

bool Food::load(std::ifstream& in, const Game* game)
{
	if (!in.is_open())
		return false;

	char buffer[50] = { 0 };

	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
		return false;
	m_priority = std::stoi(buffer);

	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
		return false;
	m_mapPosition.x = std::stoi(buffer);

	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
		return false;
	m_mapPosition.y = std::stoi(buffer);

	in.ignore(1);
	in.getline(buffer, 50);
	if (in.rdstate() || buffer[0] == 0)
		return false;
	m_healthPoints = std::stoi(buffer);
}