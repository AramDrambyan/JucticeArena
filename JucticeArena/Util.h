#pragma once
#include <iostream>
#include "Enums.h"
#include "RangeHero.h"
#include "Wall.h"
#include "Water.h"
#include "Vectors.h"
#include <vector>

std::pair<int, int> move_coords(Direction dir, int move_speed)
{
	if(dir == LEFT)
	{
		return std::make_pair(-move_speed, 0);
	}
	if(dir == RIGHT)
	{
		return std::make_pair(move_speed, 0);
	}
	if(dir == UP)
	{
		return std::make_pair(0, -move_speed);
	}
	if(dir == DOWN)
	{
		return std::make_pair(0, move_speed);
	}
}

bool in_range(Rect r)
{
    return r.p.x >= 0 && r.p.x <= 1150 && r.p.y >= 0 && r.p.y <= 750;
}
bool hit_wall(Rect r)
{
    for (int i = 0; i < walls.size(); ++i)
    {
        if (r.intersects_rect(walls[i].boundary))
            return true;
    }
    return false;
}
bool hit_water(Rect r)
{
    for (int i = 0; i < water.size(); ++i)
    {
        if (r.intersects_rect(water[i].boundary))
            return true;
    }
    return false;
}
void add_water()
{

    for (int x = 940; x <= 1090; x += 50)
    {
        for (int y = 390; y <= 490; y += 50)
        {
            water.push_back(Water(Rect(Point(x, y), 50, 50)));
        }
    }

    for (int x = 210; x >= 60; x -= 50)
    {
        for (int y = 240; y <= 340; y += 50)
        {
            water.push_back(Water(Rect(Point(x, y), 50, 50)));
        }
    }
}
void add_walls()
{
    //  the worst function in this project

    //  walls near spawn-point
    walls.push_back(Wall(Rect(Point(100, 700), 50, 50)));
    walls.push_back(Wall(Rect(Point(100, 750), 50, 50)));
    walls.push_back(Wall(Rect(Point(1050, 0), 50, 50)));
    walls.push_back(Wall(Rect(Point(1050, 50), 50, 50)));

    //  walls in the oppisite side of spawn (left)
    for (int i = 0; i < 150; i += 50)
    {
        walls.push_back(Wall(Rect(Point(200, i), 50, 50)));
    }

    //  walls in the oppisite side of spawn (right)
    for (int i = 750; i > 600; i -= 50)
    {
        walls.push_back(Wall(Rect(Point(950, i), 50, 50)));
    }

    //  top-left of cross
    for (int i = 200; i <= 300; i += 50)
    {
        walls.push_back(Wall(Rect(Point(500, i), 50, 50)));
    }
    for (int i = 400; i < 500; i += 50)
    {
        walls.push_back(Wall(Rect(Point(i, 300), 50, 50)));
    }

    //  down-left of cross
    for (int i = 450; i <= 550; i += 50)
    {
        walls.push_back(Wall(Rect(Point(500, i), 50, 50)));
    }
    for (int i = 400; i < 500; i += 50)
    {
        walls.push_back(Wall(Rect(Point(i, 450), 50, 50)));
    }

    // up-right of cross
    for (int i = 200; i <= 300; i += 50)
    {
        walls.push_back(Wall(Rect(Point(650, i), 50, 50)));
    }
    for (int i = 700; i < 800; i += 50)
    {
        walls.push_back(Wall(Rect(Point(i, 300), 50, 50)));
    }

    // up-down of cross
    for (int i = 450; i <= 550; i += 50)
    {
        walls.push_back(Wall(Rect(Point(650, i), 50, 50)));
    }
    for (int i = 700; i < 800; i += 50)
    {
        walls.push_back(Wall(Rect(Point(i, 450), 50, 50)));
    }

    // cross left border
    for (int i = 100; i <= 400; i += 50)
    {
        walls.push_back(Wall(Rect(Point(i, 450), 50, 50)));
    }

    // cross right border
    for (int i = 800; i < 1100; i += 50)
    {
        walls.push_back(Wall(Rect(Point(i, 300), 50, 50)));
    }
}