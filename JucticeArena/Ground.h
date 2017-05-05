#pragma once

#include "GameObject.h"

struct Ground : public GameObject
{
    Ground()
        : GameObject(Rect(Point(), 1200, 800), Texture("ground.png")){}

    virtual void draw()
    {
        al_draw_bitmap(texture.texture, boundary.p.x, boundary.p.y, NULL);
    }

    virtual ~Ground() {}
};