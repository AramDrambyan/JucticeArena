#pragma once

#include "GameObject.h"

struct Wall : public GameObject 
{
	Wall(const Rect& r)
		: GameObject(r, Texture("wall.png")){}

    Wall(){}

	virtual void draw()
	{
		al_draw_bitmap(texture.texture, boundary.p.x, boundary.p.y, NULL);
	}

	virtual ~Wall() {}
};