#pragma once
#include "MovableGameObject.h"
#include "Enums.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "Util.h"


struct Ability : public MovableGameObject
{
	virtual ~Ability() {}

    int froze_time;
    int time;

	Ability(const Rect& r, const Texture& texture, int move_speed, int damage, int time, 
		SoundEffect hit_effect = SoundEffect("dummy.wav"), Direction dir = UP, int froze_time = 0)
		: MovableGameObject(r, texture, move_speed, damage, hit_effect, dir), froze_time(froze_time), time(time) {}

	void move()
	{
		std::pair<int, int> c = move_coords(dir, move_speed);
		boundary.p.x += c.first;
		boundary.p.y += c.second;
        --time;
	}
	virtual void draw()
	{
		al_draw_bitmap(texture.texture, boundary.p.x, boundary.p.y, NULL);
	}
    bool in_range()
    {
        return time > 0;
    }


};