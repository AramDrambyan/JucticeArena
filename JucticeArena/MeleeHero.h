#pragma once
#include "Hero.h"

struct MeleeHero : public Hero
{
	MeleeHero(const Rect& r, const Texture& texture, const Texture& autoattack_animation, std::string name,
		int move_speed, int health, int damage, int range, int autoattack_speed,
        int spec1_cooldown, int spec2_cooldown, SoundEffect hit_effect = SoundEffect("dummy.wav"),
        Direction dir = UP, State state = IDLE)
        : Hero(r, texture, autoattack_animation, name, move_speed, health, damage, range, autoattack_speed,
        spec1_cooldown, spec2_cooldown, hit_effect, dir, state) 
    {
        autoattack_state = 0;
        spec1_state = 0;
        spec2_state = 0;
        frozen = 0;
    }

	virtual bool is_able_to_attack(const Hero& h)
	{
        std::pair<int, int> c = move_coords(dir, 25);
        Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), boundary.w, boundary.h);
		if (r.intersects_rect(h.boundary) && autoattack_state == 0 && frozen == 0)
		{
			return true;
		}
		return false;
	}
	virtual void autoattack(Hero& h)
	{
		state = ATTACK;
		h.health -= damage;

        hit_effect.play();
        autoattack_state = autoattack_speed;
        autoattack_animation.frame.p.x = 0;
        autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;
	}

	virtual ~MeleeHero() {}
};