#pragma once
#include "GameObject.h"
#include "Enums.h"
struct MovableGameObject : public GameObject
{
	MovableGameObject(const Rect& r, const Texture& texture, int move_speed, int damage, Direction dir = UP)
		: GameObject(r, texture), dir(dir), move_speed(move_speed), damage(damage) {}

	virtual ~MovableGameObject() {}

    int damage;
	int move_speed;
	Direction dir;
};