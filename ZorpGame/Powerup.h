#pragma once
#include "GameObject.h"

class Powerup : public GameObject
{
public:
	Powerup();
	Powerup(const char name[30], float health, float attack, float defence);
	~Powerup();

	char* getName();
	float getHealthMultiplier() { return m_healthMultiplier; }
	float getAttackMultiplier() { return m_attackMultiplier; }
	float getDefenceMultiplier() { return m_defenceMultiplier; }

	void setName(const char* pStr);
	void setHealthMultiplier(float health) { m_healthMultiplier = health; }
	void setAttackMultiplier(float attack) { m_attackMultiplier = attack; }
	void setDefenceMultiplier(float defence) { m_defenceMultiplier = defence; }

	static bool compare(const Powerup* p1, const Powerup* p2);

	void draw();
	void drawDescription();
	void lookAt();

	virtual void save(std::ofstream& out);
	virtual bool load(std::ifstream& in, const Game* game);

private:
	char m_name[30];

	float m_healthMultiplier;
	float m_attackMultiplier;
	float m_defenceMultiplier;
};

