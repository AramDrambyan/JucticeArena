#pragma once

#include "GameObject.h"

struct Water : public GameObject
{
    Water(const Rect& r)
        : GameObject(r, Texture("water.png")){}

    Water(){}

    virtual void draw()
    {
        al_draw_bitmap(texture.texture, boundary.p.x, boundary.p.y, NULL);
    }

    virtual ~Water() {}
};