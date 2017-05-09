#pragma once
#include "MeleeHero.h"
#include "ZedDefines.h"

struct Zed : public MeleeHero
{
	Zed(const Rect& r, Direction dir = UP, State state = IDLE)
		: MeleeHero(r, Texture("zed.png", Point(), COUNT_OF_FRAMES, COUNT_OF_FRAMES),
		Texture("zed_attack.png", Point(), COUNT_OF_FRAMES_AA, COUNT_OF_FRAMES), "zed",
		Z_MOVE_SPEED, Z_HEALTH, Z_DAMAGE, Z_RANGE, Z_AUTOATTACK_SPEED,
        Z_SPEC1_COOLDOWN, Z_SPEC2_COOLDOWN, SoundEffect("melee_attack.wav"), dir, state)
	{
		max_health = Z_HEALTH;
		autoattack_state = 0;
		spec1_state = 0;
		spec2_state = 0;
		frozen = 0;
	}

	virtual ~Zed() {}

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

		if (timer <= 35 && timer >= 30)
		{
			ALLEGRO_BITMAP* img = al_load_bitmap("zed_mark.png");
			al_draw_bitmap(img, boundary.p.x, boundary.p.y, NULL);
		}

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
		if (timer != 0)
			--timer;
		draw_life_bar();
	}
	virtual void move(const Direction dir_)
	{
		if (frozen <= 0)
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

				if (!hit_water(r) && in_range(r))
				{
					boundary = r;
					break;
				}
			}
		}
	}
	virtual Ability spec1(Hero& h)
	{
		if (frozen <= 0 && spec1_state == 0)
		{
			state = ATTACK;
			autoattack_animation.frame.p.x = 0;
			autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;

			spec1_state = spec1_cooldown;
			std::pair<int, int> c = move_coords(dir, Z_SHURIKEN_SIZE);
			return Ability(Rect(Point(boundary.p.x + c.first, boundary.p.y + c.second), Z_SHURIKEN_SIZE, Z_SHURIKEN_SIZE),
				Texture("zed_shuriken.png"), Z_SHURIKEN_MOVE_SPEED, Z_SHURIKEN_DAMAGE, Z_SHURIKEN_TIME,
				SoundEffect("hit-ability.wav"), dir);
		}
        else if (sh_s && frozen <= 0)
        {
            sh_s = false;
            return Ability(Rect(Point(x_, y_), Z_SHURIKEN_SIZE, Z_SHURIKEN_SIZE),
				Texture("zed_shuriken.png"), Z_SHURIKEN_MOVE_SPEED, Z_SHURIKEN_DAMAGE / 2, Z_SHURIKEN_TIME,
				SoundEffect("hit-ability.wav"), dir_);
        }
		return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
	}
	virtual Ability spec1(Hero& h1, Hero& h2)
	{
		if (frozen <= 0 && spec1_state == 0)
		{
			state = ATTACK;
			autoattack_animation.frame.p.x = 0;
			autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;

			spec1_state = spec1_cooldown;
			std::pair<int, int> c = move_coords(dir, Z_SHURIKEN_SIZE);
			return Ability(Rect(Point(boundary.p.x + c.first, boundary.p.y + c.second), Z_SHURIKEN_SIZE, Z_SHURIKEN_SIZE),
				Texture("zed_shuriken.png"), Z_SHURIKEN_MOVE_SPEED, Z_SHURIKEN_DAMAGE, Z_SHURIKEN_TIME,
				SoundEffect("hit-ability.wav"), dir);
		}
        else if (sh_s && frozen <= 0)
        {
            sh_s = false;
            return Ability(Rect(Point(x_, y_), Z_SHURIKEN_SIZE, Z_SHURIKEN_SIZE),
                Texture("zed_shuriken.png"), Z_SHURIKEN_MOVE_SPEED, Z_SHURIKEN_DAMAGE / 2, Z_SHURIKEN_TIME,
				SoundEffect("hit-ability.wav"), dir_);
        }
		return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
	}
	virtual Ability spec2(Hero& h1, Hero& h2)
	{
		if (timer <= 60 && timer > 0)
		{
			boundary.p.x = x_;
			boundary.p.y = y_;
            move(dir_);
			return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
		}

		if (frozen <= 0 && spec2_state == 0)
		{
			Rect temp = boundary;

			for (int i = 3; i >= 1; --i)
			{
				std::pair<int, int> c = move_coords(dir, 50 * i);
				int x = boundary.p.x + c.first;
				int y = boundary.p.y + c.second;
				Rect r = Rect(Point(x, y), boundary.w, boundary.h);
				if (h1.boundary.intersects_rect(r) && !hit_water(r) && in_range(r))
				{
					boundary = r;
					spec2_state = spec2_cooldown;
					timer = 70;
					extra = 10 * h1.health + 1;
					x_ = temp.p.x;
					y_ = temp.p.y;
                    dir_ = dir;
                    sh_s = true;
					if (dir == UP)
						return Ability(temp, Texture("zed_shadow_up.png"), 0, 0, 70, SoundEffect("zed-shadow.wav"), UP);
					if (dir == DOWN)
						return Ability(temp, Texture("zed_shadow_down.png"), 0, 0, 70, SoundEffect("zed-shadow.wav"), DOWN);
					if (dir == LEFT)
						return Ability(temp, Texture("zed_shadow_left.png"), 0, 0, 70, SoundEffect("zed-shadow.wav"), LEFT);
					if (dir == RIGHT)
						return Ability(temp, Texture("zed_shadow_right.png"), 0, 0, 70, SoundEffect("zed-shadow.wav"), RIGHT);
				}
				else if (h2.boundary.intersects_rect(r) && !hit_water(r) && in_range(r))
				{
					boundary = r;
					spec2_state = spec2_cooldown;
					timer = 70;
					extra = 10 * h2.health + 2;
					x_ = temp.p.x;
					y_ = temp.p.y;
                    dir_ = dir;
                    sh_s = true;
					if (dir == UP)
						return Ability(temp, Texture("zed_shadow_up.png"), 0, 0, 70, SoundEffect("zed-shadow.wav"), UP);
					if (dir == DOWN)
						return Ability(temp, Texture("zed_shadow_down.png"), 0, 0, 70, SoundEffect("zed-shadow.wav"), DOWN);
					if (dir == LEFT)
						return Ability(temp, Texture("zed_shadow_left.png"), 0, 0, 70, SoundEffect("zed-shadow.wav"), LEFT);
					if (dir == RIGHT)
						return Ability(temp, Texture("zed_shadow_right.png"), 0, 0, 70, SoundEffect("zed-shadow.wav"), RIGHT);
				}
			}
		}
		return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
	}
	virtual Ability spec2(Hero& h)
	{
		if (timer <= 60 && timer > 0)
		{
			boundary.p.x = x_;
			boundary.p.y = y_;
            move(dir_);
			return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
		}

		if (frozen <= 0 && spec2_state == 0)
		{
			Rect temp = boundary;

			for (int i = 3; i >= 1; --i)
			{
				std::pair<int, int> c = move_coords(dir, 50 * i);
				int x = boundary.p.x + c.first;
				int y = boundary.p.y + c.second;
				Rect r = Rect(Point(x, y), boundary.w, boundary.h);
				if (h.boundary.intersects_rect(r) && !hit_water(r) && in_range(r))
				{
					boundary = r;
					spec2_state = spec2_cooldown;
					timer = 70;
					extra = h.health;

					x_ = temp.p.x;
					y_ = temp.p.y;
                    dir_ = dir;
                    sh_s = true;
					if (dir == UP)
						return Ability(temp, Texture("zed_shadow_up.png"), 0, 0, 70, SoundEffect("zed-shadow.wav") ,UP);
					if (dir == DOWN)
						return Ability(temp, Texture("zed_shadow_down.png"), 0, 0, 70, SoundEffect("zed-shadow.wav"), DOWN);
					if (dir == LEFT)
						return Ability(temp, Texture("zed_shadow_left.png"), 0, 0, 70, SoundEffect("zed-shadow.wav"), LEFT);
					if (dir == RIGHT)
						return Ability(temp, Texture("zed_shadow_right.png"), 0, 0, 70, SoundEffect("zed-shadow.wav"), RIGHT);
				}
			}
			

		}
		return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
	}
	virtual void passive(Hero& h)
	{
		if (timer == 30)
		{
			int dmg = extra - h.health;
			h.health -= dmg;
            al_reserve_samples(1);
            ALLEGRO_SAMPLE* mark = al_load_sample("zed_mark.wav");
            al_play_sample(mark, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			extra = 0;
		}
	}
	virtual void passive(Hero& h1, Hero& h2)
	{

		if (timer == 30)
		{
			if (extra % 10 == 1)
			{
				extra /= 10;
				int dmg = extra - h1.health;
				h1.health -= dmg;
                al_reserve_samples(1);
                ALLEGRO_SAMPLE* mark = al_load_sample("zed_mark.wav");
                al_play_sample(mark, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				extra = 0;
			}
			else if (extra % 10 == 2)
			{
				extra /= 10;
				int dmg = extra - h2.health;
				h2.health -= dmg;
                al_reserve_samples(1);
                ALLEGRO_SAMPLE* mark = al_load_sample("zed_mark.wav");
                al_play_sample(mark, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				extra = 0;
			}
		}
	}
};