#pragma once
#include "GameObject.h"
#include "Enums.h"
struct MovableGameObject: public GameObject
{
	virtual ~MovableGameObject() {}

	Direction dir;
	virtual void move(Direction) = 0;
};