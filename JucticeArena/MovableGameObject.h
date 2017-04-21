#pragma once
#include "GameObject.h"
#include "Enums.h"
struct MovableGameObject: public GameObject
{
	MovableGameObject(const Rect& r, const Texture& texture, int move_speed, Direction dir = DOWN)
		: GameObject(r, texture), dir(dir), move_speed(move_speed) {}

	virtual ~MovableGameObject() {}

	int move_speed;
	Direction dir;
};