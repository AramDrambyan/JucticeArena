#pragma once
#include <string>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro.h>
#include "Ability.h"

void print_health(int num, int health, ALLEGRO_FONT* font, int x, int y)
{
    char a[] = "Player0 Health: 0000";
    a[6] += + num;

    int i = 0;
    while (health > 0)
    {
        int t = health % 10;
        a[19 - i] += t;
        ++i;
        health /= 10;
    }

    al_draw_text(font, al_map_rgb(50, 180, 70), x, y, NULL, a);
}
void print_damage(int num, int damage, ALLEGRO_FONT* font, int x, int y)
{
    char a[] = "Player0 damage: 000";
    a[6] += +num;

    int i = 0;
    while (damage > 0)
    {
        int t = damage % 10;
        a[18 - i] += t;
        ++i;
        damage /= 10;
    }

    al_draw_text(font, al_map_rgb(50, 180, 70), x, y, NULL, a);
}
void print_spec(int num1, int num2, int time, ALLEGRO_FONT* font, int x, int y)
{
    char a[] = "Player0 Spec0:  None";
    a[6] += num1;
    a[12] += num2;

    if (time == 0)
    {
        a[15] = 'R', a[16] = 'e', a[17] = 'a',
            a[18] = 'd', a[19] = 'y';
    }

    al_draw_text(font, al_map_rgb(50, 180, 70), x, y, NULL, a);
}