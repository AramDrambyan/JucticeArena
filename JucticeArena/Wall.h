#pragma once

#include "GameObject.h"

struct Wall : public GameObject 
{
	Wall(const Rect& r, const Texture& texture)
		: GameObject(r, texture){}

	virtual void draw()
	{
		al_draw_bitmap(texture.texture, boundary.p.x, boundary.p.y, NULL);
	}

	virtual ~Wall() {}
};