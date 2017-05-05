#pragma once
#include "Wall.h"
#include "Hero.h"
#include "Ability.h"
#include "MapDefines.h"
#include "Water.h"
#include "Grass.h"
#include "Ground.h"
#include <vector>
#include "Vectors.h"
#include "Shen.h"

struct Map
{
    std::vector<Grass> grasses;
    std::vector<Ability> abilities1;
    std::vector<Ability> abilities2;
    Ground ground;
    Shen hero_1;
    Shen hero_2;

    Map(Shen hero_1, Shen hero_2)
        :ground(Ground()),
        hero_1(hero_1), hero_2(hero_2)
    {
        
    }
    void draw()
    { 
        ground.draw();

        for (int i = 0; i < walls.size(); ++i)
        {
            walls[i].draw();
        }

        for (int i = 0; i < water.size(); ++i)
        {
            water[i].draw();
        }

        hero_1.draw();
        hero_2.draw();

        for (int i = 0; i < abilities1.size(); ++i)
        {
            abilities1[i].draw();
        }
        for (int i = 0; i < abilities2.size(); ++i)
        {
            abilities2[i].draw();
        }

        for (int i = 0; i < grasses.size(); ++i)
        {
            grasses[i].draw();
        }
    }
    void destroy()
    {
        for (int i = 0; i < walls.size(); ++i)
        {
            walls[i].texture.destroy();
        }
        for (int i = 0; i < abilities1.size(); ++i)
        {
            abilities1[i].texture.destroy();
        }
        for (int i = 0; i < abilities2.size(); ++i)
        {
            abilities2[i].texture.destroy();
        }
        for (int i = 0; i < water.size(); ++i)
        {
            water[i].texture.destroy();
        }
        for (int i = 0; i < grasses.size(); ++i)
        {
            grasses[i].texture.destroy();
        }
        ground.texture.destroy();
    }
    void erase_ability1(int i)
    {
        for (int j = i; j < abilities1.size() - 1; ++j)
        {
            std::swap(abilities1[j], abilities1[j + 1]);
        }
        abilities1[i].texture.destroy();
        abilities1.pop_back();
    }
    void erase_ability2(int i)
    {
        for (int j = i; j < abilities2.size() - 1; ++j)
        {
            std::swap(abilities2[j], abilities2[j + 1]);
        }
        abilities2[i].texture.destroy();
        abilities2.pop_back();
    }
};