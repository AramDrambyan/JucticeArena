#pragma once
#include "Wall.h"
#include "Hero.h"
#include "Ability.h"
#include "MapDefines.h"
#include "Water.h"
#include "Ground.h"
#include <vector>
#include "Vectors.h"
#include "Shen.h"
#include "Caitlyn.h"
#include "Ryze.h"
#include "Karma.h"
#include "LeeSin.h"
#include "Zed.h"

struct Map
{
    //
    std::vector<Ability> abilities1;
    std::vector<Ability> abilities2;
    Ground ground;
    Hero* hero_1;
    Hero* hero_2;

    Map(Hero* hero_1, Hero* hero_2)
        :ground(Ground()),
        hero_1(hero_1), hero_2(hero_2) {}
    
    void draw()
    { 
        ground.draw();


        for (int i = 0; i < water.size(); ++i)
        {
            water[i].draw();
        }

        for (int i = 0; i < abilities1.size(); ++i)
        {
            abilities1[i].draw();
        }
        for (int i = 0; i < abilities2.size(); ++i)
        {
            abilities2[i].draw();
        }

        if (hero_1->is_alive())
        {
            hero_1->draw();
        }
        if (hero_2->is_alive())
        {
            hero_2->draw();
        }

		for (int i = 0; i < walls.size(); ++i)
		{
			walls[i].draw();
		}
    }
    void erase_ability1(int i)
    {
        for (int j = i; j < abilities1.size() - 1; ++j)
        {
            std::swap(abilities1[j], abilities1[j + 1]);
        }
        abilities1.pop_back();
    }
    void erase_ability2(int i)
    {
        for (int j = i; j < abilities2.size() - 1; ++j)
        {
            std::swap(abilities2[j], abilities2[j + 1]);
        }
        abilities2.pop_back();
    }
    void move_abilities()
    {
        // abilities1
        for (int i = 0; i < abilities1.size(); ++i)
        {
            if (!abilities1[i].in_range())
            {
                erase_ability1(i);
                --i;
                continue;
            }

            if (hero_2->boundary.intersects_rect(abilities1[i].boundary))
            {
				abilities1[i].hit_effect.play();
                hero_2->health -= abilities1[i].damage;
                hero_2->frozen = abilities1[i].froze_time;
                erase_ability1(i);
                --i;
                continue;
            }

            abilities1[i].move();
        }
        // abilities2
        for (int i = 0; i < abilities2.size(); ++i)
        {
            if (!abilities2[i].in_range())
            {
                erase_ability2(i);
                --i;
                continue;
            }

            if (hero_1->boundary.intersects_rect(abilities2[i].boundary))
            {
				abilities2[i].hit_effect.play();
                hero_1->health -= abilities2[i].damage;
                hero_1->frozen = abilities2[i].froze_time;
                erase_ability2(i);
                --i;
                continue;
            }

            abilities2[i].move();
        }
    }
    void move_abilities(Shen& shen, Karma& karma)
    {
        // abilies1
        for (int i = 0; i < abilities1.size(); ++i)
        {
            if (!abilities1[i].in_range())
            {
                erase_ability1(i);
                --i;
                continue;
            }

            if (shen.boundary.intersects_rect(abilities1[i].boundary))
            {
                shen.health -= abilities1[i].damage;
                shen.frozen = abilities1[i].froze_time;
                erase_ability1(i);
                --i;
                continue;
            }
            else if (karma.boundary.intersects_rect(abilities1[i].boundary))
            {
                karma.health -= abilities1[i].damage;
                karma.frozen = abilities1[i].froze_time;
                erase_ability1(i);
                --i;
                continue;
            }

            abilities1[i].move();
        }
        // abilities2
        for (int i = 0; i < abilities2.size(); ++i)
        {
            if (!abilities2[i].in_range())
            {
                erase_ability2(i);
                --i;
                continue;
            }

            if (hero_1->boundary.intersects_rect(abilities2[i].boundary))
            {
                hero_1->health -= abilities2[i].damage;
                hero_1->frozen = abilities2[i].froze_time;
                erase_ability2(i);
                --i;
                continue;
            }
            else if (hero_2->boundary.intersects_rect(abilities2[i].boundary))
            {
                hero_2->health -= abilities2[i].damage;
                hero_2->frozen = abilities2[i].froze_time;
                erase_ability2(i);
                --i;
                continue;
            }

            abilities2[i].move();
        }
    }
};