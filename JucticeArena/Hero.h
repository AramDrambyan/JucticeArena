#pragma once
#include "Ability.h"

struct Hero: public MovableGameObject 
{
	Hero(const Rect& r, const Texture& texture, const Texture& autoattack_animation, const Texture& ability_animation,
		int move_speed, Direction dir = DOWN, State state = IDLE)
		: MovableGameObject(r, texture, move_speed, dir), state(state),
		autoattack_animation(autoattack_animation), ability_animation(ability_animation) {}

	virtual ~Hero() {}

	State state;
	Texture autoattack_animation;
	Texture ability_animation;

	/*virtual Ability* spec1() = 0;
	virtual Ability* spec2() = 0;
	virtual void autoattack(Hero&) = 0;*/

	void move(const Direction dir_)
	{
		if(dir != dir_)
		{
			dir = dir_;
			texture.frame.p.x = texture.frame.w;
			texture.frame.p.y = dir * texture.frame.h;
		}

		texture.frame.p.x += texture.frame.w;
		if(texture.frame.p.x >= 5 * texture.frame.w)
		{
			texture.frame.p.x = texture.frame.w;
		}
		
		state = MOVE;

		std::pair<int, int> c = move_coords(dir, move_speed);
		boundary.p.x += c.first;
		boundary.p.y += c.second;
	}

	void idle_state()
	{
		if(state == IDLE)
		{
			texture.frame.p.x = 0;
		}
	}

	virtual void draw()
	{
		al_draw_bitmap_region(texture.texture, texture.frame.p.x, texture.frame.p.y,
			texture.frame.w, texture.frame.h, boundary.p.x, boundary.p.y, NULL);
	}
};