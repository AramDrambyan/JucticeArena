#pragma once
#include "MeleeHero.h"
#include "LeeSinDefines.h"

struct LeeSin : public MeleeHero
{
	LeeSin(const Rect& r, Direction dir = UP, State state = IDLE)
		: MeleeHero(r, Texture("leesin.png", Point(), COUNT_OF_FRAMES, COUNT_OF_FRAMES),
		Texture("leesin_attack.png", Point(), COUNT_OF_FRAMES_AA, COUNT_OF_FRAMES), "LeeSin",
		LS_MOVE_SPEED, LS_HEALTH, LS_DAMAGE, LS_RANGE, LS_AUTOATTACK_SPEED,
        LS_SPEC1_COOLDOWN, LS_SPEC2_COOLDOWN, SoundEffect("melee_attack.wav"), dir, state)
	{
		max_health = LS_HEALTH;
		autoattack_state = 0;
		spec1_state = 0;
		spec2_state = 0;
		frozen = 0;
		extra = 0;
	}

	virtual ~LeeSin() {}

	virtual void draw() //  if state == ATTACK he will end his attack animation 
	{
		if (state == ATTACK)
		{
			al_draw_bitmap_region(autoattack_animation.texture, autoattack_animation.frame.p.x, autoattack_animation.frame.p.y,
				autoattack_animation.frame.w, autoattack_animation.frame.h, boundary.p.x, boundary.p.y, NULL);

			autoattack_animation.frame.p.x += autoattack_animation.frame.w;
			if (autoattack_animation.frame.p.x >= COUNT_OF_FRAMES_AA * autoattack_animation.frame.w)
			{
				state = IDLE;
			}
			return;
		}
		else if (state == IDLE)
		{
			texture.frame.p.x = 0;
		}
		al_draw_bitmap_region(texture.texture, texture.frame.p.x, texture.frame.p.y,
			texture.frame.w, texture.frame.h, boundary.p.x, boundary.p.y, NULL);

		if (autoattack_state != 0)
			--autoattack_state;
		if (spec1_state != 0)
			--spec1_state;
		if (spec2_state != 0)
			--spec2_state;
		if (frozen > 0)
			--frozen;
		else if (frozen < 0)
			++frozen;
		draw_life_bar();
	}
	virtual void move(const Direction dir_)
	{
		
			if (state == ATTACK)
			{
				return;
			}

			if (dir != dir_)
			{
				dir = dir_;
				texture.frame.p.x = texture.frame.w;
				texture.frame.p.y = dir * texture.frame.h;
				state = MOVE;
				return;
			}

			texture.frame.p.x += texture.frame.w;
			if (texture.frame.p.x >= COUNT_OF_FRAMES * texture.frame.w)
			{
				texture.frame.p.x = texture.frame.w;
			}

			state = MOVE;
			for (int i = move_speed; i >= 1; --i)
			{
				std::pair<int, int> c = move_coords(dir, i);
				Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), boundary.w, boundary.h);

				if (!hit_wall(r) && !hit_water(r) && in_range(r))
				{
					boundary = r;
					break;
				}
			}
	}
	virtual Ability spec1(Hero& h)
	{
		if (spec1_state == 0)
		{
			std::pair<int, int> c = move_coords(dir, 25);
			Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), boundary.w, boundary.h);
			if (h.boundary.intersects_rect(r))
			{
				for (int i = 100; i >= 5; --i)
				{
					std::pair<int, int> k = move_coords(dir, i);
					Rect r(Point(h.boundary.p.x + k.first, h.boundary.p.y + k.second), h.boundary.w, h.boundary.h);
					if (!hit_wall(r) && !hit_water(r) && in_range(r))
					{
						spec1_state = spec1_cooldown;
						state = ATTACK;
						autoattack_animation.frame.p.x = 0;
						autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;

						h.boundary = r;
						h.health -= 200;
						h.frozen = 10;
						return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
					}
				}
			}
		}
		return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
	}
	virtual Ability spec1(Hero& h1, Hero& h2)
	{
		if (spec1_state == 0)
		{
			std::pair<int, int> c = move_coords(dir, 25);
			Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), boundary.w, boundary.h);
			if (h1.boundary.intersects_rect(r))
			{
				for (int i = 100; i >= 5; --i)
				{
					std::pair<int, int> k = move_coords(dir, i);
					Rect r(Point(h1.boundary.p.x + c.first, h1.boundary.p.y + c.second), h1.boundary.w, h1.boundary.h);
					if (!hit_wall(r) && !hit_water(r) && in_range(r))
					{
						state = ATTACK;
						autoattack_animation.frame.p.x = 0;
						autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;

						h1.boundary = r;
						h1.health -= 200;
						h1.frozen = 10;
                        break;
					}
				}
			}
			else if (h2.boundary.intersects_rect(r))
			{
				for (int i = 100; i >= 5; --i)
				{
					std::pair<int, int> k = move_coords(dir, i);
					Rect r(Point(h2.boundary.p.x + c.first, h2.boundary.p.y + c.second), h2.boundary.w, h2.boundary.h);
					if (!hit_wall(r) && !hit_water(r))
					{
						state = ATTACK;
						autoattack_animation.frame.p.x = 0;
						autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;

						h2.boundary = r;
						h2.health -= 200;
						h2.frozen = 10;
                        break;
					}
				}
			}
		}
		return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
	}
	virtual Ability spec2(Hero& h)
	{
		if (h.frozen < 0)
		{
			h.frozen = 0;
			frozen = -2;

			boundary.p.x = (boundary.p.x + h.boundary.p.x) / 2;
			boundary.p.y = (boundary.p.y + h.boundary.p.y) / 2;
			return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
		}

		if (spec2_state == 0)
		{
			state = ATTACK;
			autoattack_animation.frame.p.x = 0;
			autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;

			spec2_state = spec2_cooldown;
			std::pair<int, int> c = move_coords(dir, LS_SONIC_SIZE);
			return Ability(Rect(Point(boundary.p.x + c.first, boundary.p.y + c.second), LS_SONIC_SIZE, LS_SONIC_SIZE),
				Texture("leesin_sonic.png"), LS_SONIC_MOVE_SPEED, LS_SONIC_DAMAGE, LS_SONIC_TIME, SoundEffect("hit-ability.wav"), dir, -25);
		}
		return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
	}
	virtual Ability spec2(Hero& h1, Hero& h2)
	{
		if (h1.frozen < 0)
		{
			
			frozen = -2;
			h1.frozen = 0;
			boundary.p.x = (boundary.p.x + h1.boundary.p.x) / 2;
			boundary.p.y = (boundary.p.y + h1.boundary.p.y) / 2;
			extra = 1;
			return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
		}

		if (h2.frozen < 0)
		{
			
			frozen = -2;
			h2.frozen = 0;
			boundary.p.x = (boundary.p.x + h2.boundary.p.x) / 2;
			boundary.p.y = (boundary.p.y + h2.boundary.p.y) / 2;
			extra = 2;
			return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
		}

		if (spec2_state == 0)
		{
			state = ATTACK;
			autoattack_animation.frame.p.x = 0;
			autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;

			spec2_state = spec2_cooldown;
			std::pair<int, int> c = move_coords(dir, LS_SONIC_SIZE);
			return Ability(Rect(Point(boundary.p.x + c.first, boundary.p.y + c.second), LS_SONIC_SIZE, LS_SONIC_SIZE),
				Texture("leesin_sonic.png"), LS_SONIC_MOVE_SPEED, LS_SONIC_DAMAGE, LS_SONIC_TIME, SoundEffect("hit-ability.wav"), dir, -25);
		}
		return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
	}
	virtual void passive(Hero& h)
	{
		if (frozen == -1)
		{
			boundary = h.boundary;
			std::pair<int, int> c = move_coords(dir, 50);
			Rect r(Point(h.boundary.p.x + c.first, h.boundary.p.y + c.second), 50, 50);
			int dmg = (h.max_health - h.health) / 5;
			h.health -= dmg;
			if (!hit_wall(r) && !hit_water(r) && in_range(r))
			{
				boundary = r;
			}
			if (dir == LEFT)
				move(RIGHT);
			else if (dir == RIGHT)
				move(LEFT);
			else if (dir == UP)
				move(DOWN);
			else
				move(UP);
		}
	}
	virtual void passive(Hero& h1, Hero& h2)
	{
		if (frozen == -1)
		{
			if (extra == 1)
			{
				boundary = h1.boundary;
				std::pair<int, int> c = move_coords(dir, 50);
				Rect r(Point(h1.boundary.p.x + c.first, h1.boundary.p.y + c.second), 50, 50);
				int dmg = (h1.max_health - h1.health) / 5;
				h1.health -= dmg;
				if (!hit_wall(r) && !hit_water(r) && in_range(r))
				{
					boundary = r;
				}
				if (dir == LEFT)
					move(RIGHT);
				else if (dir == RIGHT)
					move(LEFT);
				else if (dir == UP)
					move(DOWN);
				else
					move(UP);
			}
			else if (extra == 2)
			{
				boundary = h2.boundary;
				std::pair<int, int> c = move_coords(dir, 50);
				Rect r(Point(h2.boundary.p.x + c.first, h2.boundary.p.y + c.second), 50, 50);
				int dmg = (h2.max_health - h2.health) / 5;
				h2.health -= dmg;
				if (!hit_wall(r) && !hit_water(r) && in_range(r))
				{
					boundary = r;
				}
				if (dir == LEFT)
					move(RIGHT);
				else if (dir == RIGHT)
					move(LEFT);
				else if (dir == UP)
					move(DOWN);
				else
					move(UP);
			}
			
		}
	}
};