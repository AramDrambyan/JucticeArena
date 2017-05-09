#pragma once
#include "GameObject.h"
#include "Enums.h"
#include "SoundEffects.h"

struct MovableGameObject : public GameObject
{
    MovableGameObject(const Rect& r, const Texture& texture, int move_speed, int damage,
        SoundEffect hit_effect = SoundEffect("dummy.wav"), Direction dir = UP)
        : GameObject(r, texture), dir(dir), move_speed(move_speed), damage(damage), hit_effect(hit_effect) {}

	virtual ~MovableGameObject() {}

    SoundEffect hit_effect;
    int damage;
	int move_speed;
	Direction dir;
};