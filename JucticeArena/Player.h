#pragma once
#include "MovableGameObject.h"
#include "Enums.h"

struct Player: public MovableGameObject 
{
	virtual ~Player() {}

	State state;
	// TODO: make spec1 and spec 2 return abilities 
	virtual void spec1() = 0;
	virtual void spec2() = 0;
};