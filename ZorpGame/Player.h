#pragma once

#include "Character.h"
#include <vector>

class Powerup;
class Room;
class Enemy;

class Player : public Character
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void executeCommand(int command, Room* pRoom);
	void draw();
	void drawDescription();
	void lookAt();

private:
	void pickup(Room* pRoom);
	void attack(Enemy* pEnemy);
};

