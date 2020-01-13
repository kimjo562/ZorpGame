#include "Food.h"
#include "GameDefines.h"
#include <iostream>

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