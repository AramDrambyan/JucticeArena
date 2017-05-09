#pragma once
#include "Ability.h"
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

struct Hero : public MovableGameObject 
{
	Hero(const Rect& r, const Texture& texture, const Texture& autoattack_animation, std::string name,
		int move_speed, int health, int damage, int range, int autoattack_speed, int spec1_cooldown,
        int spec2_cooldown, SoundEffect hit_effect = SoundEffect("dummy.wav"), Direction dir = UP,
        State state = IDLE)
		: MovableGameObject(r, texture, move_speed, damage, hit_effect, dir), name(name), health(health),
        spec1_cooldown(spec1_cooldown), spec2_cooldown(spec2_cooldown), 
        autoattack_speed(autoattack_speed), state(state), autoattack_animation(autoattack_animation),
        range(range)
    {
        autoattack_state = 0;
        spec1_state = 0;
        spec2_state = 0;
        frozen = 0;
    }

	virtual ~Hero() {}
    
    std::string name;

	int extra;
    int frozen;
	int health;
    int max_health;
	int autoattack_speed;
    int spec1_cooldown;
    int spec2_cooldown;
    int range;

    int autoattack_state;
    int spec1_state;
    int spec2_state;

	State state;

    Texture autoattack_animation;

    virtual void passive(Hero&) = 0;
    virtual void passive(Hero&, Hero&) = 0;
    virtual void move(Direction) = 0;
	virtual Ability spec1(Hero&) = 0;
	virtual Ability spec1(Hero&, Hero&) = 0;
	virtual Ability spec2(Hero&, Hero&) = 0;
	virtual Ability spec2(Hero&) = 0;
	virtual void autoattack(Hero&) = 0;
	virtual bool is_able_to_attack(const Hero&) = 0;
    virtual bool is_alive()
    {
        return health > 0;
    }
    virtual void draw_life_bar()
    {
        double x1 = boundary.p.x;
        double y1 = boundary.p.y - 10;
        double l = ((health * 50.0) / max_health);
        double x2 = x1 + l;
        double y2 = y1 + 10;
        double x3 = x2 + (50 - l);

        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(50, 250, 70));
        al_draw_filled_rectangle(x2, y1, x3, y2, al_map_rgb(250, 50, 70));
    }
};