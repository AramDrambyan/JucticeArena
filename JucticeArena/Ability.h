#pragma once
#include "MovableGameObject.h"
#include "Enums.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "Util.h"

struct Ability: public MovableGameObject
{
	virtual ~Ability() {}


	int range;

	Ability(const Rect& r, const Texture& texture, int range, int move_speed, int damage, Direction dir = DOWN)
		: MovableGameObject(r, texture,move_speed, damage, dir), range(range) {}

	void move()
	{
		std::pair<int, int> c = move_coords(dir, move_speed);
		boundary.p.x += c.first;
		boundary.p.y += c.second;
		range -= move_speed;
	}

	virtual void draw()
	{
		al_draw_bitmap(texture.texture, boundary.p.x, boundary.p.y, NULL);
	}
};