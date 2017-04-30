#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "RangeHero.h"
#include "Map.h"
#include "Shen.h"
#include <iostream>

int main()
{
    al_init();

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY* display = al_create_display(MAP_WIDTH, MAP_HEIGHT);

    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_KEYBOARD_STATE key_state1, key_state2;
    ALLEGRO_TIMER* timer = al_create_timer(FPS);

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    Map map(Shen(Rect(Point(1150, 50), 50, 50)), Shen(Rect(Point(1150, 0), 50, 50)));
    add_walls();
    add_water();

    al_start_timer(timer);

    bool in_game = true;

    while (true)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        al_get_keyboard_state(&key_state1);
        al_get_keyboard_state(&key_state2);

        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if (events.type == ALLEGRO_EVENT_TIMER)
        {
            // first hero move
            if (al_key_down(&key_state1, ALLEGRO_KEY_S))
            {
                map.hero_1.move(DOWN);
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_W))
            {
                map.hero_1.move(UP);
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_A))
            {
                map.hero_1.move(LEFT);
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_D))
            {
                map.hero_1.move(RIGHT);
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_1))
            {
                map.abilities1.push_back(map.hero_1.spec1(map.hero_2));
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_2))
            {
                map.abilities1.push_back(map.hero_1.spec2(map.hero_2));
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_SPACE))
            {
                if (map.hero_1.is_able_to_attack(map.hero_2))
                {
                    map.hero_1.autoattack(map.hero_2);
                }
            }
            else
            {
                if (map.hero_1.state != ATTACK)
                {
                    map.hero_1.state = IDLE;
                }
            }

            //  second hero move
            if (al_key_down(&key_state2, ALLEGRO_KEY_DOWN))
            {
                map.hero_2.move(DOWN);
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_UP))
            {
                map.hero_2.move(UP);
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_LEFT))
            {
                map.hero_2.move(LEFT);
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_RIGHT))
            {
                map.hero_2.move(RIGHT);
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_PAD_1))
            {
                map.abilities2.push_back(map.hero_2.spec1(map.hero_1));
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_PAD_2))
            {
                map.abilities2.push_back(map.hero_2.spec2(map.hero_1));
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_PAD_0))
            {
                if (map.hero_2.is_able_to_attack(map.hero_1))
                {
                    map.hero_2.autoattack(map.hero_1);
                }
            }
            else
            {
                if (map.hero_2.state != ATTACK)
                {
                    map.hero_2.state = IDLE;
                }
            }

            // moving abilities1 
            for (int i = 0; i < map.abilities1.size(); ++i)
            {
                if (map.abilities1[i].range <= 0)
                {
                    map.erase_ability1(i);
                    --i;
                    continue;
                }

                if (map.hero_2.boundary.intersects_rect(map.abilities1[i].boundary))
                {
                    map.hero_2.health -= map.abilities1[i].damage;
                    map.erase_ability1(i);
                    --i;
                    continue;
                }

                map.abilities1[i].move();
            }
            // moving abilities2
            for (int i = 0; i < map.abilities2.size(); ++i)
            {
                if (map.abilities2[i].range <= 0)
                {
                    map.erase_ability2(i);
                    --i;
                    continue;
                }

                if (map.abilities2[i].boundary.intersects_rect(map.hero_1.boundary))
                {
                    map.hero_1.health -= map.abilities2[i].damage;
                    map.erase_ability2(i);
                    --i;
                    continue;
                }

                map.abilities2[i].move();
            }

            map.draw();
            al_flip_display();
        }

        if (map.hero_1.health <= 0 || map.hero_2.health <= 0)
        {
            break;
        }    
    }

    map.destroy();
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}
