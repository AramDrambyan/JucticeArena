#pragma once
#include "GameObject.h"
#include "Enums.h"
struct MovableGameObject: public GameObject
{
	MovableGameObject(const Rectangle& r, const Texture& texture, Direction dir = DOWN)
		: GameObject(r, texture), dir(dir) {}

	virtual ~MovableGameObject() {}

	Direction dir;
	virtual void move(Direction) = 0;
};