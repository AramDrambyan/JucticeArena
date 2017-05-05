#pragma once
#include "MovableGameObject.h"
#include "Enums.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "Util.h"

struct Ability : public MovableGameObject
{
	virtual ~Ability() {}

	int range;
    int froze_time;

	Ability(const Rect& r, const Texture& texture, int range, int move_speed, int damage, Direction dir = UP, int froze_time = 0)
		: MovableGameObject(r, texture,move_speed, damage, dir), range(range), froze_time(froze_time) {}

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