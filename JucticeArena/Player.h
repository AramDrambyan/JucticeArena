#pragma once
#include "MovableGameObject.h"
#include "Enums.h"

struct Player: public MovableGameObject 
{
	Player(const Rectangle& r, const Texture& texture, Direction dir = DOWN, State state = IDLE)
		: MovableGameObject(r, texture, dir), state(state) {}

	virtual ~Player() {}

	State state;
	// TODO: make spec1 and spec 2 return abilities 
	virtual void spec1() = 0;
	virtual void spec2() = 0;
};