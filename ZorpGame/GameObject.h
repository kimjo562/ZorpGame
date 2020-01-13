#pragma once
#include "Point2D.h"

class GameObject
{
public:
	GameObject();
	GameObject(Point2D position);
	~GameObject();

	Point2D getPosition() { return m_mapPosition; }
	void setPosition(const Point2D& position) { m_mapPosition = position; }

	virtual void draw() = 0;
	virtual void drawDescription() = 0;
	virtual void lookAt() = 0;

	static bool compare(const GameObject* p1, const GameObject* p2);

protected:
	Point2D m_mapPosition;
	int m_priority;
};

